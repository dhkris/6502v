#include <stdio.h>
#include <6502V/Opcodes.h>
#include <6502V/Types.h>
#include <6502V/ADDRGEN.h>
#include <6502V/Helpers.h>
#include <6502V/Build.h>
#include <6502V/Functions.h>
#include <6502V/SyscallTable.h>

/* SYSCALL.C
 * 6502V SYSTEM CALL INTERFACE.
 * Copyright (c) DHK (DAVID HANEFELT KRISTENSEN) 2012
 * LICENSE AS SPECIFIED IN LICENSE.TXT IN THE ROOT DIRECTORY OF THE 6502V SOURCE
 * DISTRIBUTION
 
 * --- handle_syscall(*m):
 * Whenever the virtual machine receives an interrupt through the IRQ
 * or BRK instructions, control is passed to the syscall interface.
 * The system calls are stack-based. The topmost (most recently pushed)
 * value is an 8-bit integer [or a single byte] with a value of 0..255
 * which determines the function called.
 * 
 * The system functions have macro aliases for better readability, defined
 * in /include/6502V/SyscallTable.h. Each alias is prefixed with SYSCALL_,
 * such as SYSCALL_PUTC (0x01), which print the next byte on the stack as
 * a character value.
 * 
 * Syscalls may consume additional byte arguments from the stack.
 */

void handle_syscall( m6502* m ) {
    byte* i = &(m->stack[m->stack_ptr]);
    if( *i == SYSCALL_PUTC ) {
        m->stack_ptr--;
        fputc(m->stack[m->stack_ptr],stderr);
    }
    else if( *i == SYSCALL_GETC ) {
        m->stack[m->stack_ptr] = fgetc(stdin);
    }
}
