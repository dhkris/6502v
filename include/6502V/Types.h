#ifndef SYSTYPES_HEADER
#define SYSTYPES_HEADER
typedef enum {OFF=0,ON=1} bit;
typedef unsigned char byte;
typedef unsigned short word;
typedef struct {
   bit does_step;
   bit cps_specified;
   word cps;
   bit does_prompt;
} vm_state;
typedef struct {
   byte acc;
   byte ix;
   byte iy;
   byte stack[16];
   byte stack_ptr;
   byte memory[8192*8];
   word pc;
   byte *zp_start, *zp_end, *pls, *i, *o;
   bit CARRYFLAG, SIGNFLAG, ZEROFLAG, NOTZEROFLAG, DID_CMP, OUTFLAG;
} m6502;
#endif