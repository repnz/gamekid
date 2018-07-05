#pragma once

///
/// ALU Opcodes 
///
#define CCF       0x3f
#define SCF       0x37
#define NOP       0x00
#define HALT      0x76
#define RLCA      0x07
#define RLA       0x17
#define RRCA      0x0f
#define RRA       0x1f

    // RLC n
#define RLC_A      0xCB, 0x07
#define RLC_B      0xCB, 0x00
#define RLC_C      0xCB, 0x01
#define RLC_D      0xCB, 0x02
#define RLC_E      0xCB, 0x03
#define RLC_H      0xCB, 0x04
#define RLC_L      0xCB, 0x05
#define RLC_HL_mem 0xCB, 0x06

    // RL n
#define RL_A      0xCB, 0x17
#define RL_B      0xCB, 0x10
#define RL_C      0xCB, 0x11
#define RL_D      0xCB, 0x12
#define RL_E      0xCB, 0x13
#define RL_H      0xCB, 0x14
#define RL_L      0xCB, 0x15
#define RL_HL_mem 0xCB,  0x16

    // RRC n
#define RRC_A      0xCB, 0xf
#define RRC_B      0xCB, 0x8
#define RRC_C      0xCB, 0x9
#define RRC_D      0xCB, 0xa
#define RRC_E      0xCB, 0xb
#define RRC_H      0xCB, 0xc
#define RRC_L      0xCB, 0xd
#define RRC_HL_mem 0xCB, 0xe


    // RR n
#define RR_A      0xCB, 0x1f
#define RR_B      0xCB, 0x18
#define RR_C      0xCB, 0x19
#define RR_D      0xCB, 0x1a
#define RR_E      0xCB, 0x1b
#define RR_H      0xCB, 0x1c
#define RR_L      0xCB, 0x1d
#define RR_HL_mem 0xCB,  0x1e

    // SLA n
#define SLA_A      0xCB, 0x27
#define SLA_B      0xCB, 0x20
#define SLA_C      0xCB, 0x21
#define SLA_D      0xCB, 0x22
#define SLA_E      0xCB, 0x23
#define SLA_H      0xCB, 0x24
#define SLA_L      0xCB, 0x25
#define SLA_HL_mem 0xCB, 0x26

    // SRA n
#define SRA_A      0xCB, 0x2F
#define SRA_B      0xCB, 0x28
#define SRA_C      0xCB, 0x29
#define SRA_D      0xCB, 0x2A
#define SRA_E      0xCB, 0x2B
#define SRA_H      0xCB, 0x2C
#define SRA_L      0xCB, 0x2D
#define SRA_HL_mem 0xCB, 0x2E

    // SRL n
#define SRL_A      0xCB, 0x3f
#define SRL_B      0xCB, 0x38
#define SRL_C      0xCB, 0x39
#define SRL_D      0xCB, 0x3a
#define SRL_E      0xCB, 0x3b
#define SRL_H      0xCB, 0x3c
#define SRL_L      0xCB, 0x3d
#define SRL_HL_mem 0xCB, 0x3e


    // BIT b, r
#define BIT_A      0x47
#define BIT_B      0x40
#define BIT_C      0x41
#define BIT_D      0x42
#define BIT_E      0x43
#define BIT_H      0x44
#define BIT_L      0x45
#define BIT_HL_mem 0x46

    // SET b, r
#define SET_A      0xc7
#define SET_B      0xc0
#define SET_C      0xc1
#define SET_D      0xc2
#define SET_E      0xc3
#define SET_H      0xc4
#define SET_L      0xc5
#define SET_HL_mem 0xc6

    // RES b, r
#define RES_A      0x87
#define RES_B      0x80
#define RES_C      0x81
#define RES_D      0x82
#define RES_E      0x83
#define RES_H      0x84
#define RES_L      0x85
#define RES_HL_mem 0x86

    // ADD A, n
#define ADD_A      0x87
#define ADD_B      0x80
#define ADD_C      0x81
#define ADD_D      0x82
#define ADD_E      0x83
#define ADD_H      0x84
#define ADD_L      0x85
#define ADD_HL_mem 0x86
#define ADD_IMM    0xC6

    // ADD 16 bits
#define ADD_HL_BC  0x09
#define ADD_HL_DE  0x19
#define ADD_HL_HL  0x29
#define ADD_HL_SP  0x39
#define ADD_SP_IMM 0xE8


    // ADC n
#define ADC_A   0x8F
#define ADC_B   0x88
#define ADC_C   0x89
#define ADC_D   0x8A
#define ADC_E   0x8B
#define ADC_H   0x8C
#define ADC_L   0x8D
#define ADC_HL_mem  0x8E
#define ADC_IMM 0xCE


    // SUB n
#define SUB_A       0x97
#define SUB_B       0x90
#define SUB_C       0x91
#define SUB_D       0x92
#define SUB_E       0x93
#define SUB_H       0x94
#define SUB_L       0x95
#define SUB_HL_mem  0x96
#define SUB_IMM     0xD6

    // SBC A, n
#define SBC_A       0x9f
#define SBC_B       0x98
#define SBC_C       0x99
#define SBC_D       0x9a
#define SBC_E       0x9b
#define SBC_H       0x9c
#define SBC_L       0x9d
#define SBC_HL_mem  0x9e
#define SBC_IMM     0xde

    // AND A, n
#define AND_A       0xa7
#define AND_B       0xa0
#define AND_C       0xa1
#define AND_D       0xa2
#define AND_E       0xa3
#define AND_H       0xa4
#define AND_L       0xa5
#define AND_HL_mem  0xa6
#define AND_IMM     0xe6

    // OR n
#define OR_A      0xb7
#define OR_B      0xb0
#define OR_C      0xb1
#define OR_D      0xb2
#define OR_E      0xb3
#define OR_H      0xb4
#define OR_L      0xb5
#define OR_HL_mem 0xb6
#define OR_IMM    0xf6

    // XOR n
#define XOR_A      0xaf
#define XOR_B      0xa8
#define XOR_C      0xa9
#define XOR_D      0xaa
#define XOR_E      0xab
#define XOR_H      0xac
#define XOR_L      0xad
#define XOR_HL_mem 0xae
#define XOR_IMM    0xee

    // CP n
#define CP_A      0xbf
#define CP_B      0xb8
#define CP_C      0xb9
#define CP_D      0xba
#define CP_E      0xbb
#define CP_H      0xbc
#define CP_L      0xbd
#define CP_HL_mem 0xbe
#define CP_IMM    0xfe


    // INC n
#define INC_A      0x3c
#define INC_B      0x04
#define INC_C      0x0c
#define INC_D      0x14
#define INC_E      0x1c
#define INC_H      0x24
#define INC_L      0x2c
#define INC_HL_mem 0x34

    // INC nn
#define INC_BC 0x03
#define INC_DE 0x13
#define INC_HL 0x23
#define INC_SP 0x33

    // DEC n
#define DEC_A      0x3d
#define DEC_B      0x05
#define DEC_C      0x0d
#define DEC_D      0x15
#define DEC_E      0x1d
#define DEC_H      0x25
#define DEC_L      0x2d
#define DEC_HL_mem 0x35

    // DEC nn
#define DEC_BC 0x0b
#define DEC_DE 0x1b
#define DEC_HL 0x2b
#define DEC_SP 0x3b

    // SWAP n
#define SWAP_A      0xCB, 0x37
#define SWAP_B      0xCB, 0x30
#define SWAP_C      0xCB, 0x31
#define SWAP_D      0xCB, 0x32
#define SWAP_E      0xCB, 0x33
#define SWAP_H      0xCB, 0x34
#define SWAP_L      0xCB, 0x35
#define SWAP_HL_mem 0xCB, 0x36

    // LD nn, n
#define LD_B_n 0x6
#define LD_C_n 0xe
#define LD_D_n 0x16
#define LD_E_n 0x1e
#define LD_H_n 0x26
#define LD_L_n 0x2e

    // LD r1, r2
#define LD_A_r2 0x78
#define LD_B_r2 0x40
#define LD_C_r2 0x48
#define LD_D_r2 0x50
#define LD_E_r2 0x58
#define LD_H_r2 0x60
#define LD_L_r2 0x68
#define LD_HL_r2 0x70

#define LD_A_A 0x7f
#define LD_A_BC 0xa
#define LD_A_DE 0x1a
#define LD_A_HL 0x7e
#define LD_A_MEM 0xfa
#define LD_A_IMM 0x3e