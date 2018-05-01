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

// RLC_n
#define CB_RLC_n_A 0x07
#define CB_RLC_n_B 0x00
#define CB_RLC_n_C 0x01
#define CB_RLC_n_D 0x02
#define CB_RLC_n_E 0x03
#define CB_RLC_n_H 0x04
#define CB_RLC_n_L 0x05
#define CB_RLC_n_HL 0x06

// RL_n
#define CB_RL_n_A 0x17
#define CB_RL_n_B 0x10
#define CB_RL_n_C 0x11
#define CB_RL_n_D 0x12
#define CB_RL_n_E 0x13
#define CB_RL_n_H 0x14
#define CB_RL_n_L 0x15
#define CB_RL_n_HL 0x16

// RRC_n
#define CB_RRC_n_A 0xf
#define CB_RRC_n_B 0xf
#define CB_RRC_n_C 0xf
#define CB_RRC_n_D 0xf
#define CB_RRC_n_E 0xb
#define CB_RRC_n_H 0xc
#define CB_RRC_n_L 0xd
#define CB_RRC_n_HL 0xe

// SLA_n
#define CB_SLA_n_A 0x27
#define CB_SLA_n_B 0x20
#define CB_SLA_n_C 0x21
#define CB_SLA_n_D 0x22
#define CB_SLA_n_E 0x23
#define CB_SLA_n_H 0x24
#define CB_SLA_n_L 0x25
#define CB_SLA_n_HL 0x26

// SRA_n
#define CB_SRA_n_A 0x2F
#define CB_SRA_n_B 0x28
#define CB_SRA_n_C 0x29
#define CB_SRA_n_D 0x2A
#define CB_SRA_n_E 0x2B
#define CB_SRA_n_H 0x2C
#define CB_SRA_n_L 0x2D
#define CB_SRA_n_HL 0x2E