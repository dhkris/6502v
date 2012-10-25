#include <stdio.h>
#include <6502V/Opcodes.h>
#include <6502V/Types.h>
#include <6502V/ADDRGEN.h>
#include <6502V/Helpers.h>
#include <6502V/Build.h>
void print_machine_state(m6502* m) {
   fprintf(stderr, "A:%2x, X:%2x, Y:%2x. I:%4x. Carry:%1d|Sign:%1d|CmpZero:%1d\n", m->acc, m->ix, m->iy, m->pc, m->CARRYFLAG, m->SIGNFLAG, m->ZEROFLAG);
}