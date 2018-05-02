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

// SET b, r
#define CB_RES_b_A 0x87
#define CB_RES_b_B 0x80
#define CB_RES_b_C 0x81
#define CB_RES_b_D 0x82
#define CB_RES_b_E 0x83
#define CB_RES_b_H 0x84
#define CB_RES_b_L 0x85
#define CB_RES_b_HL  0x86