INCLUDE_FLDR=./include
BLD=.
CFLAGS=-O3 -I${INCLUDE_FLDR} -mtune=corei7 -m64 -msse4
SOURCES=./src
all: dir m6502_create_machine main create_vm_state print_machine_state syscalls
	cc ${BLD}/6502v_obj000.o ${BLD}/6502v_obj001.o ${BLD}/6502v_obj002.o ${BLD}/6502v_obj003.o ${BLD}/6502v_obj004.o -o 6502v
	make clean
dir:
m6502_create_machine:
	cc ${SOURCES}/m6502_create_machine.c -c -o ${BLD}/6502v_obj001.o ${CFLAGS}
create_vm_state:
	cc ${SOURCES}/vm_state-create_vm_state.c -c -o ${BLD}/6502v_obj002.o ${CFLAGS}
print_machine_state:
	cc ${SOURCES}/print_machine_state.c -c -o ${BLD}/6502v_obj003.o ${CFLAGS}
main:
	cc ${SOURCES}/6502v.c -c -o ${BLD}/6502v_obj000.o ${CFLAGS}
syscalls:
	cc ${SOURCES}/syscall.c -c -o ${BLD}/6502v_obj004.o ${CFLAGS}
clean:
	rm -rf *.o
