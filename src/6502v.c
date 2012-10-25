/* david's 6502 emulator */
/*
   special mem pages:
      F000: output ascii character
      F00F: input ascii character [when JMP F00F]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <6502V/Opcodes.h>
#include <6502V/Types.h>
#include <6502V/ADDRGEN.h>
#include <6502V/Helpers.h>
#include <6502V/Build.h>

/* EXTERNAL FUNCTION DECLARATIONS */
extern m6502* create_machine(); 
extern vm_state* create_vm_state(int , char** );
extern void print_machine_state(m6502* );
extern void handle_syscall(m6502*);

// xqt : EXECUTE INSTRUCTION
   // m = virtual machine instance
   // j = instruction stream pointer
   // X = instruction stream offset


word xqt( m6502* m, byte* j, word X ) {
   word Y = 0;
   /* INSTRUCTIONS */
   if( CI == op_LDA_imm ) {
      Y++;
      byte new_a_value = j[X+Y];
      #ifdef DEBUG
      fprintf(stderr, "$%0.4x |  LDA:immediate <-- #%0.2x (was #%0.2x)\n", 
              CADD, new_a_value, m->acc);
      #endif
      m->acc = new_a_value;
      Y++;
   }
   else if( CI == op_STA_abs ) {
      Y++;
      word addr = ADDRGEN( j[CO], j[X+(++Y)]);
      #ifdef DEBUG
      fprintf(stderr, "$%0.4x |  STA:absolute --> $%4x\n", CADD, addr);      
      #endif
      if(addr == OUTCHAR_ADDR) m->OUTFLAG=ON;
      MEM(addr) = m->acc;
      ++Y;
   }
   else if( CI == op_CMP_imm ) {
      Y++;
      byte cmp_byte = j[CO];
      #ifdef DEBUG
      fprintf(stderr, "$%0.4x |  CMP:immediate #%0.2x = #%0.2x?...\n",
              CADD, cmp_byte, m->acc );
      #endif
      if( cmp_byte == m->acc ) {
         m->ZEROFLAG = ON;
         m->NOTZEROFLAG = OFF;
      } else if( cmp_byte > m->acc ) {
         m->NOTZEROFLAG = ON;
         m->NOTZEROFLAG = OFF;
      }
      ++Y;
   }
   else if( CI == op_CMP_abs ) {
      Y++;
      word cmp_addr = ADDRGEN( j[Y], j[++Y]);
      byte cmp_byte = MEM(cmp_addr);
      if( cmp_byte == m->acc ) {
         m->ZEROFLAG = ON;
         m->NOTZEROFLAG = OFF;
      } else if( cmp_byte > m->acc ) {
         m->NOTZEROFLAG = ON;
         m->NOTZEROFLAG = OFF;
      }      
   }
   else if( CI == op_BNE_rel ) {
      Y++;
      #ifdef DEBUG
      fprintf(stderr,"$%0.4x |  BNE:relative <if_branch_addr:=+$%x> ", CADD, j[CO]);
      #endif
      if( m->ZEROFLAG == OFF ) {
         #ifdef DEBUG
         fprintf(stderr,"-:true; branching to addr: %0.2x...\n", X+Y+j[X+1]+1);
         #endif
         Y = X+Y+j[X+1]+1;
         X = 0;
         m->DID_CMP = OFF;
                  return Y;
      } else {
         #ifdef DEBUG
         fprintf(stderr,"-:false; no_branch_taken");
         #endif
         Y++;
      }
      #ifdef DEBUG
      fprintf(stderr,"\n");
      #endif
   }
   else if( CI == op_BEQ_rel ) {
       Y++;
       #ifdef DEBUG
       fprintf(stderr,"$%0.4x | BEQ:relative <if_branch_addr:=$%0.2x> ", CADD, j[CO]);
       #endif
       if( m->ZEROFLAG == ON ) {
           #ifdef DEBUG
           fprintf(stderr, "-: branching>\n");
#endif
           Y=X+Y+j[X+1]+1;
           X=0;
           m->DID_CMP = OFF;
           return Y;
       } else {
           #ifdef DEBUG
           fprintf(stderr,"-/no_branch\n");
           #endif
       }
   }
   else if( CI == op_DEC_abs ) {
      word addr = ADDRGEN( j[X+(++Y)], j[X+(++Y)] );
      #ifdef DEBUG
         fprintf(stderr,"$%0.4x |  INC:absolute_addr:$%0.4x! %0.2x => %0.2x\n", 
                 CADD, addr, MEM(addr), MEM(addr)-1);
      #endif
      if(addr == OUTCHAR_ADDR) m->OUTFLAG=ON;
      MEM(addr) -= 1;
   } 
   else if( CI == op_INC_abs ) {
      word addr = ADDRGEN( j[X+(++Y)], j[X+(++Y)] );
      #ifdef DEBUG
         fprintf(stderr,"$%0.4x |  INC:absolute_addr:$%0.4x! #%0.2x => #%0.2x\n", 
                 CADD, addr, MEM(addr), MEM(addr)+1);
      #endif
      MEM(addr) += 1;      
   }
   else if( CI == op_INX ) {
      #ifdef DEBUG
         fprintf(stderr,"$%0.4x |  INX; x := #%0.2x -> #%0.2x\n", 
                 CADD, m->ix, m->ix+1 );
      #endif
      m->ix += 1;
   }
   else if( CI == op_JMP_abs )  /* absolute (immediate) */ {
      word addr = ADDRGEN( j[X+(++Y)], j[X+(++Y)] );
      #ifdef DEBUG
         fprintf(stderr,"$%0.4x |  JMP:absolute_addr ------> jump_to:$%0.4x\n", 
                 CADD, addr);
      #endif
      X = addr;
      Y = 0;
      return addr;
   }
   else if( CI == op_JMP_ind ) /*indirect*/ {
      word addr_addr = ADDRGEN( j[X+(++Y)], j[X+(++Y)] );
      word addr = MEM(addr_addr);
      #ifdef DEBUG
         fprintf(stderr,"$%0.4x |  JMP:indirection! jump_to_value_of:$%0.4x (-*=>$%0.4x)\n", 
                 CADD, addr_addr, addr);
      #endif      
      X = addr;
      Y = 0;
      return addr;
   }
   else if( CI == op_DIE ) {
      #ifdef DEBUG
         fprintf(stderr,"$%0.4x |  EXIT\n", CADD);
      #endif
      return 0xFFFF;
   }
   
   /* IRQ handling!*/
   else if( CI == op_BRK ) {
       m->stack_ptr++;
       m->stack[m->stack_ptr] = j[X+Y];
       handle_syscall(m);
   }
  
   /* HANDLE OUTCHAR */
   if( m->OUTFLAG == ON ) {
      #ifdef DEBUG
      fprintf(stderr, "$%0.4x |  POLL_OUTCHAR_FOUND: '%c'\n", 
              CO, m->memory[OUTCHAR_ADDR]);
      #else
      fputc(MEM(OUTCHAR_ADDR), stdout);
      #endif
      m->OUTFLAG=OFF;
   }

   /* HANDLE SYNC */
   if( DOES_WAIT == 1 ) usleep(1000000/CPS);
   m->pc = X+Y;
   if(Y==0) Y=1;
   return Y+X;
}

int main(int argc, char* argv[]) {
   #ifdef FANCY_STARTMESG
      fprintf(stderr,"6502V %1d.%2d : Lightning Fast 6502 Virtual Machine\n",VMAJOR,VMINOR);
      fprintf(stderr,"Copyright © HK (David Hanefelt Kristensen) 2012\n");
      fprintf(stderr,"http://github.com/dhkris/6502v\n");
   #endif 
    
   m6502* mach_instance = create_machine();
   vm_state* vm = create_vm_state(argc,argv);
   fputc('\n',stderr);

   #ifndef INTERNAL_TEST
   if(argc < 2 ) exit(255);
   FILE* input = fopen(argv[1],"rb");
   byte teststream[8192*8];
   int tsi = 0;
   while( (teststream[tsi] = (byte)fgetc(input)) != 0xFF ) tsi++;
   #else
   /* TEST PROGRAM
   byte teststream[]  = {op_LDA_imm, 0x43,  
                         op_STA_abs, 0xF0, 0x00, 
                         
                         // Set up indirect jump!
                         op_LDA_imm, 0x27,
                         op_STA_abs, 0xCA, 0x11,
                         op_CMP_imm, 0x41, 
                         op_BNE_rel, 0x09,
                         op_LDA_imm, 0x21,
                         op_LDA_imm, 0x21,
                         op_STA_abs, 0xF0, 0x00,
                         op_DIE, 
                         op_LDA_imm, 0x60,
                         op_STA_abs, 0xF0, 0x00,
                         op_INC_abs, 0xF0, 0x00,
                         op_INX,
                         op_JMP_ind, 0xCA, 0x11,
                         op_LDA_imm, 0x59,
                         op_STA_abs, 0xF0, 0x00,
                         op_LDA_imm, 0x49,
                         op_STA_abs, 0xF0, 0x00,
                         op_DIE 
                         }; */
   #endif
   
   
   #ifdef DEBUG
      fprintf(stderr,"                           ==== PROGRAM PRINTOUT ====\n");
      fprintf(stderr, "OPER@ |  DESCRIPTION\n");
      fprintf(stderr, "______|_________________________________________________________________________\n");
   #endif
   int program_counter = xqt(mach_instance, teststream, 0);
   while( (program_counter = xqt(mach_instance, teststream, program_counter)) != 0xFFFF ) ;
   
   #ifdef DEBUG
      fprintf(stderr,"______I_________________________________________________________________________\n");
   #endif
   
   
   fputc('\n',stderr);
}



