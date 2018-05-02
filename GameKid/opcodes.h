#pragma once

#define CCF       0x3f
#define SCF       0x37
#define NOP       0x00
#define HALT      0x76
#define RLCA      0x07
#define RLA       0x17
#define RRCA      0x0f
#define RRA       0x1f

// All opcodes after the CB prefix
#define CB_PREFIX    0xcb

// RLC n
#define CB_RLC_A 0x07
#define CB_RLC_B 0x00
#define CB_RLC_C 0x01
#define CB_RLC_D 0x02
#define CB_RLC_E 0x03
#define CB_RLC_H 0x04
#define CB_RLC_L 0x05
#define CB_RLC_HL 0x06

// RL n
#define CB_RL_A 0x17
#define CB_RL_B 0x10
#define CB_RL_C 0x11
#define CB_RL_D 0x12
#define CB_RL_E 0x13
#define CB_RL_H 0x14
#define CB_RL_L 0x15
#define CB_RL_HL 0x16

// RRC n
#define CB_RRC_A 0xf
#define CB_RRC_B 0x8
#define CB_RRC_C 0x9
#define CB_RRC_D 0xa
#define CB_RRC_E 0xb
#define CB_RRC_H 0xc
#define CB_RRC_L 0xd
#define CB_RRC_HL 0xe


// RR n
#define CB_RR_A 0x1f
#define CB_RR_B 0x18
#define CB_RR_C 0x19
#define CB_RR_D 0x1a
#define CB_RR_E 0x1b
#define CB_RR_H 0x1c
#define CB_RR_L 0x1d
#define CB_RR_HL 0x1e

// SLA n
#define CB_SLA_A 0x27
#define CB_SLA_B 0x20
#define CB_SLA_C 0x21
#define CB_SLA_D 0x22
#define CB_SLA_E 0x23
#define CB_SLA_H 0x24
#define CB_SLA_L 0x25
#define CB_SLA_HL 0x26

// SRA n
#define CB_SRA_A 0x2F
#define CB_SRA_B 0x28
#define CB_SRA_C 0x29
#define CB_SRA_D 0x2A
#define CB_SRA_E 0x2B
#define CB_SRA_H 0x2C
#define CB_SRA_L 0x2D
#define CB_SRA_HL 0x2E

// SRL n
#define CB_SRL_A 0x3f
#define CB_SRL_B 0x38
#define CB_SRL_C 0x39
#define CB_SRL_D 0x3a
#define CB_SRL_E 0x3b
#define CB_SRL_H 0x3c
#define CB_SRL_L 0x3d
#define CB_SRL_HL 0x3e


// BIT b, r
#define CB_BIT_b_A 0x47
#define CB_BIT_b_B 0x40
#define CB_BIT_b_C 0x41
#define CB_BIT_b_D 0x42
#define CB_BIT_b_E 0x43
#define CB_BIT_b_H 0x44
#define CB_BIT_b_L 0x45
#define CB_BIT_b_HL  0x46

// SET b, r
#define CB_SET_b_A 0xc7
#define CB_SET_b_B 0xc0
#define CB_SET_b_C 0xc1
#define CB_SET_b_D 0xc2
#define CB_SET_b_E 0xc3
#define CB_SET_b_H 0xc4
#define CB_SET_b_L 0xc5
#define CB_SET_b_HL  0xc6

// RES b, r
#define CB_RES_b_A 0x87
#define CB_RES_b_B 0x80
#define CB_RES_b_C 0x81
#define CB_RES_b_D 0x82
#define CB_RES_b_E 0x83
#define CB_RES_b_H 0x84
#define CB_RES_b_L 0x85
#define CB_RES_b_HL  0x86

// ADD A, n
#define ADD_A_A 0x87
#define ADD_A_B 0x80
#define ADD_A_C 0x81
#define ADD_A_D 0x82
#define ADD_A_E 0x83
#define ADD_A_H 0x84
#define ADD_A_L 0x85
#define ADD_A_HL 0x85
#define ADD_A_IMM 0xC6

// ADC A, n
#define ADC_A_A 0x87
#define ADC_A_B 0x80
#define ADC_A_C 0x81
#define ADC_A_D 0x82
#define ADC_A_E 0x83
#define ADC_A_H 0x84
#define ADC_A_L 0x85
#define ADC_A_HL 0x85
#define ADC_A_IMM 0xC6


// SUB A, n
#define SUB_A_A 0x97
#define SUB_A_B 0x90
#define SUB_A_C 0x91
#define SUB_A_D 0x92
#define SUB_A_E 0x93
#define SUB_A_H 0x94
#define SUB_A_L 0x95
#define SUB_A_HL 0x96
#define SUB_A_IMM 0xD6

// SBC A, n
#define SBC_A_A 0x9f
#define SBC_A_B 0x98
#define SBC_A_C 0x99
#define SBC_A_D 0x9a
#define SBC_A_E 0x9b
#define SBC_A_H 0x9c
#define SBC_A_L 0x9d
#define SBC_A_HL 0x9e
#define SBC_A_IMM 0xde

// AND A, n
#define AND_A_A 0xa7
#define AND_A_B 0xa0
#define AND_A_C 0xa1
#define AND_A_D 0xa2
#define AND_A_E 0xa3
#define AND_A_H 0xa4
#define AND_A_L 0xa5
#define AND_A_HL 0xa6
#define AND_A_IMM 0xe6

// OR A, n
#define OR_A_A 0xb7
#define OR_A_B 0xb0
#define OR_A_C 0xb1
#define OR_A_D 0xb2
#define OR_A_E 0xb3
#define OR_A_H 0xb4
#define OR_A_L 0xb5
#define OR_A_HL 0xb6
#define OR_A_IMM 0xf6

// XOR A, n
#define XOR_A_A 0xaf
#define XOR_A_B 0xa8
#define XOR_A_C 0xa9
#define XOR_A_D 0xaa
#define XOR_A_E 0xab
#define XOR_A_H 0xac
#define XOR_A_L 0xad
#define XOR_A_HL 0xae
#define XOR_A_IMM 0xee

// CP A, n
#define CP_A_A 0xbf
#define CP_A_B 0xb8
#define CP_A_C 0xb9
#define CP_A_D 0xba
#define CP_A_E 0xbb
#define CP_A_H 0xbc
#define CP_A_L 0xbd
#define CP_A_HL 0xbe
#define CP_A_IMM 0xfe