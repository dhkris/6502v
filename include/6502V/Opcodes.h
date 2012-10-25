#ifndef ins_6502_hdr
#define ins_6502_hdr

#define op_DIE 0xFF

// ADC
// Add memory to A with carry
#define op_ADC_imm    0x69
#define op_ADC_zpm    0x65
#define op_ADC_zpx   0x75
#define op_ADC_abs   0x6D
#define op_ADC_abx  0x7D
#define op_ADC_aby   0x79
#define op_ADC_idx  0x61
#define op_ADC_idy  0x71

// AND
// Bitwise-AND A with memory
#define op_AND_imm   0x29
#define op_AND_zpm   0x25
#define op_AND_zpx   0x35
#define op_AND_abs   0x2D
#define op_AND_abx   0x3D
#define op_AND_aby   0x4D
#define op_AND_idx   0x21
#define op_AND_idy   0x31

// ASL
// Arithmetic Shift Left
#define op_ASL_acc   0x0A
#define op_ASL_zpm   0x06
#define op_ASL_zpx   0x16
#define op_ASL_abs   0x0E
#define op_ASL_abx   0x1E

// BCC
// Branch if and only if carry flag (PROGRAM.CARRY_FLAG) is clear
#define op_BCC_rel   0x90

// BCS
// Branch if and only if carry flag is set
#define op_BCS_rel   0xB0

// BEQ
// Branch if P.Z=0
#define op_BEQ_rel   0xF0

// BIT
// Test accumulator bits with M
#define op_BIT_zpm   0x24
#define op_BIT_abs   0x2C

// BMI
// if sign flag is set
#define op_BMI_rel 0x30

// BNE
// if cmp returned nonequality (P.Z=CLEAR)
#define op_BNE_rel   0xD0

// BPL
// if sign flag is clear
#define op_BPL_rel 0x10

// BRK
// IRQ emu
#define op_BRK    0x00

// CLC
// clear carry flag
#define op_CLC    0x18

// CMP
// compare acc with mem
#define op_CMP_imm   0xC9
#define op_CMP_zpm   0xC5
#define op_CMP_zpx   0xD5
#define op_CMP_abs   0xCD
#define op_CMP_abx   0xDD
#define op_CMP_aby   0xD9
#define op_CMP_inx   0xC1
#define op_CMP_iny   0xD1

// CPX
// compare x with mem
#define op_CPX_imm   0xE0
#define op_CPX_zpm   0xE4
#define op_CPX_abs   0xEC

// CPY
// compare y with mem
#define op_CPY_imm   0xC0
#define op_CPY_zpm   0xC4
#define op_CPY_abs   0xCC

// DEC
// *mem--;
#define op_DEC_zpm   0xC6
#define op_DEC_zpx   0xD6
#define op_DEC_abs   0xCE
#define op_DEC_abx   0xDE

// DEX; *x--;
#define op_DEX       0xCA

// INC: *mem++;
#define op_INC_zpm   0xE6
#define op_INC_zpx   0xF6
#define op_INC_abs   0xEE
#define op_INC_abx   0xFE

// INX: *x++;
#define op_INX       0xE8


// JMP
#define op_JMP_abs   0x4C
#define op_JMP_ind   0x6C

// JSR
// jump to subroutine with args on stack
#define op_JSR       0x20  //ALWAYS ABS!!!

// LOAD OPERATIONS
#define op_LDA_imm   0xA9
#define op_LDA_zpm   0xA5
#define op_LDA_zpx   0xB5
#define op_LDA_abs   0xAD
#define op_LDA_abx   0xBD
#define op_LDA_aby   0xB9
#define op_LDA_idx   0xA1
#define op_LDA_idy   0xB1
#define op_LDX_imm   0xA2
#define op_LDX_zpm   0xA6
#define op_LDX_zpy   0xB6
#define op_LDX_abs   0xAE
#define op_LDX_aby   0xBE

// NOP
#define op_NOP       0xEA

// STACK OPERATIONS (ACC->STK->ACC)
#define op_PHA       0x48
#define op_PLA       0x68

// STORE OPERATIONS
#define op_STA_zpm   0x85
#define op_STA_zpx   0x95
#define op_STA_abs   0x8d
#define op_STA_abx   0x9d
#define op_STA_idx   0x81
#define op_STA_idy   0x91
#define op_STX_zpm   0x86
#define op_STX_zpy   0x96
#define op_STX_abs   0x8E

// TRANSFER
#define op_TAX       0xAA
#define op_TXA       0x8A

#endif