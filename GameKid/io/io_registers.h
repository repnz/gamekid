#pragma once

///
/// Boot ROM
///
#define ENABLE_BOOT_ROM 0xFF50


///
/// Interrups
///
#define IE 0xFFFF // Interrupts Enable (R/W)
#define IF 0xFF0F // Interrupt Flag (R/W)

///
/// JoyPad IO
///
#define P1 0xFF00 // Register for reading joy pad info 


///
/// Serial IO (Link Cable)
///
#define SB 0xFF01 // Serial transfer data (R/W)
#define SC 0xFF02  // Serial sIO control  (R/W)

///
/// Timer IO
///
#define DIV 0xFF04 // Divider Register (R/W) 
#define TIMA 0xFF05 // Timer counter (R/W)
#define TMA 0xFF06 // Timer Modulo (R/W)
#define TAC 0xFF07 //Timer Control (R/W)


/// 
/// Sound IO
///

// Sound Mode 1 Registers
#define NR_10 0xFF10 // Sound Mode 1 Register, Sweep Register (R/W)
#define NR_11 0xFF11 // Sound Mode 1 Register, Sound Length / Wave pattern duty (R/W)
#define NR_12 0xFF12 // Sound Mode 1 Register, Envelope (R/W)
#define NR_13 0xFF13 // Sound Mode 1 Register, Frequency lo (W)
#define NR_14 0xFF14 // Sound Mode 1 Register, Frequency hi (R/W)

// Sound Mode 2 Registers
#define NR_21 0xFF16 // Sound Mode 2 Register, Sound Length; Wave Pattern Duty (R/W)
#define NR_22 0xFF17 // Sound Mode 2 Register, Envelope (R/W)
#define NR_23 0xFF18 // Sound Mode 2 Register, Frequency lo (W)
#define NR_24 0xFF19 // Sound Mode 2 Register, Frequency hi (R/W)

// Sound Mode 3 Registers
#define NR_30 0xFF1A // Sound Mode 3 Register, Sound On / Off (R/W)
#define NR_31 0xFF1B // Sound Mode 3 Register, Sound Length (R/W)
#define NR_32 0xFF1C // Sound Mode 3 Register, Select Output Level (R/W)
#define NR_33 0xFF1D // Sound Mode 3 Register, Frequency lo (W)
#define NR_34 0xFF1E // Sound Mode 3 Register, Frequency hi (R/W)

// Sound Mode 4 Registers
#define NR_41 0xFF20 // Sound Mode 4 Register, Sound Length (R/W)
#define NR_42 0xFF21 // Sound Mode 4 Register, Envelope (R/W)
#define NR_43 0xFF22 // Sound Mode 4 Register, Polynomial Counter (R/W)
#define NR_44 0xFF23 // Sound Mode 4 Register, Counter / Consecutive; Initial (R/W)

// General Sound Registers
#define NR_50 0xFF24 // Channel Control / On - Off / Volume (R/W)
#define NR_51 0xFF25 // Selection of Sound output terminal (R/W)
#define NR_52 0xFF26 // Sound On / Off (R/W)
#define WAVE_PATTERN_RAM 0xFF30, 0xFF3F // Wave Pattern RAM

///
/// Video IO
///
#define LCDC 0xFF40 // LCDC Control (R/W)
#define STAT 0xFF41 // LCDC Status (R/W)
#define SCY 0xFF42 // Scroll Y (R/W)
#define SCX 0xFF43 // Scroll X (R/W)
#define LY 0xFF44 // LCDC Y-Coordinate (R)
#define LYC 0xFF45 // LY Compare (R/W)
#define DMA 0xFF46 // DMA Transfer and Start Address (W)
#define BGP 0xFF47 // Background and Window Pallete Data
#define OBP0 0xFF48 // Object Pallete 0 Data (R/W)
#define OBP1 0xFF49 // Object Pallete 1 Data (R/W)
#define WY 0xFF4A // Window Y Position (R/W)
#define WX 0xFF4B // Window X Position (R/W)