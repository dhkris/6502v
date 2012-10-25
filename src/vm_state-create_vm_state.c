#include <stdlib.h>
#include <string.h>
#include <6502V/Opcodes.h>
#include <6502V/Types.h>
#include <6502V/ADDRGEN.h>
#include <6502V/Helpers.h>
#include <6502V/Build.h>
vm_state* create_vm_state(int argc, char** argv) {
   int i = 1;
   vm_state* vms = malloc(sizeof(vm_state));
   vms->cps_specified = 0;
   vms->cps = 0;
   vms->does_step = 0;
   for(i = 1; i < argc; i++) {
      if( !strcmp("-step",argv[i]) ) vms->does_step = ON;
      if( !strcmp("-cps",argv[i]) ) {
         vms->cps_specified = ON;
         vms->cps = atoi(argv[++i]);
      }
      if( !strcmp("-p",argv[i]) ) vms->does_prompt = ON;
   }
   return vms;
}