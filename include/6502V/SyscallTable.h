/* 
 * File:   SyscallTable.h
 * Author: david
 *
 * Created on October 25, 2012, 4:23 AM
 */

#ifndef SYSCALLTABLE_H
#define	SYSCALLTABLE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/* STACK LAYOUT OF A SYSCALL
         (PUTC)
 *     byte  val
 *     0    0x01
 *     1    0x41
 *   
 * Then, call BRK 0x0
 
 */

    // Pop character off stack and print it
#define SYSCALL_PUTC 0x01
    
    // Get stdin character and push it onto stack
#define SYSCALL_GETC 0x02
    

    
    



#ifdef	__cplusplus
}
#endif

#endif	/* SYSCALLTABLE_H */

