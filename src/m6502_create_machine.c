#include <stdlib.h>
#include <string.h>
#include <6502V/Opcodes.h>
#include <6502V/Types.h>
#include <6502V/ADDRGEN.h>
#include <6502V/Helpers.h>
#include <6502V/Build.h>

m6502* create_machine() {
   m6502* my_mach = malloc(sizeof(m6502));
   my_mach->acc = 0x00;
   my_mach->ix = 0x00;
   my_mach->iy = 0x00;
   my_mach->stack_ptr = 0;   
   memset(my_mach->stack, 16, 1);
   memset(my_mach->memory, 8192*8, 1);
   my_mach->pc = 0x0000;
   my_mach->zp_start = &my_mach->memory[0];
   my_mach->zp_end = &my_mach->memory[0xFF];
   my_mach->pls = &my_mach->memory[0x300];
   my_mach->i = &my_mach->memory[0xF00F];
   my_mach->o = &my_mach->memory[0xF000];
   my_mach->DID_CMP = OFF;
   my_mach->OUTFLAG = OFF;
   return my_mach;
}