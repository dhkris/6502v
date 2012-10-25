#ifndef FUNCTIONS
#define FUNCTIONS
extern m6502* create_machine();
extern vm_state* create_vm_state(int argc, char** argv);
extern void print_machine_state(m6502* m);
#endif