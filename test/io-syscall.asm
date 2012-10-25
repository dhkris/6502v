; I/O syscall test
;   for 650V
; copyright (c) david hanefelt kristensen, 2012

lda #$48 ;load 0x48 (ascii:'H') into acc
pha ;push it onto stack

lda #$02 ;load 0x2 (syscall:putc) into acc
pha ;push it onto stack
brk ;interrupt to syscall

lda #$01 ;load 0x01 (syscall:getc) into acc
pha ;push it onto stack
brk ;interrupt to syscall

lda #$02 ;load 0x02 into acc
pha ;push it onto stack
brk ;interrupt to syscall
