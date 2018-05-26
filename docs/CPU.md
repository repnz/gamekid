# Gameboy CPU Documentation

## Intro

### Why make this?

CPU documentation for the GameKid project - 
CPU manual for GameBoy is pretty bad, 
So writing a good manual will make the development of an
Emulator, Debugger, Disassembler, Assembler easier.


## LD 

The Load instruction comes in 4 variants:

1) Immidiate -> Register
2) Register -> Register
3) Memory ->  Register
4) Register ->  Memory
5) Immidiate -> Memory 

### Immidiate to Register

#### 8 Bit Registers

8 cycles.

|Register |A   |B   |C   |D   |E   |H   |L   |
|-------- |--- |----|----|----|----|----|----|
|Opcode   |0x3E|0x06|0x0E|0x16|0x1E|0x26|0x2E|


##### Examples

```assembly
06 0A : ld B, 10 
3E 64 : ld A, 100
```
#### 16 Bit Registers

12 Cycles.

|Register |BC   |DE   |HL |SP |
|-------- |--- |----|----|----|
|Opcode   |0x01|0x11|0x21|0x31|

### Register to Register

- LD r1, r2
  - r1 - destination register
  - r2 - source register

#### 8 Bit Registers

4 cycles.

 
|     |  A |  B |  C |  D |  E |  H |  L |
|------|----|----|----|----|----|----|----|
|**A** |0x7F|0x78|0x79|0x7A|0x7B|0x7C|0x7D|
|**B** |0x47|0x40|0x41|0x42|0x43|0x44|0x45|
|**C** |0x4F|0x48|0x49|0x4A|0x4B|0x4C|0x3D|
|**D** |0x57|0x50|0x51|0x52|0x53|0x54|0x55|
|**E** |0x5F|0x58|0x59|0x5A|0x5B|0x5C|0x5D|
|**H** |0x67|0x60|0x61|0x62|0x63|0x64|0x65|
|**L** |0x6F|0x68|0x69|0x6A|0x6B|0x6C|0x6D|

### Register to Memory

Unless moved from register A, memory access must be done
by putting the address in register HL, and using it as a pointer.

#### Immidiate To [HL]

12 Cycles.
Opcode=0x36

#### Register to [HL]

8 cycles.

|Register |A   |B   |C   |D   |E   |H   |L   |
|-------- |--- |----|----|----|----|----|----|
|Opcode   |0x77|0x70|0x71|0x72|0x73|0x74|0x75| 

Examples
```assembly
77 : ld [HL], A
72 : ld [HL], D
```

#### A register to BC, DE, HL


|Register |BC   |DE  
|-------- |--- |----|
|Opcode   |0x02|0x12|


Examples
```assembly
02 : ld [BC], A
12 : ld [DE], A
```

#### A To Immidiate Memory

memory write can be done by specifying the memory address in the code as 
an opcode parameter.

Opcode=0xEA
- LD (nn), A
  - nn is the address to write to, encoded as little endian after the opcode.
- Cycles = 16

Examples
```assembly
EA 0F 00 : ld [0x000f], A
EA 0E FF : ld [0xff0e], A
```

#### A To (C+0xFF00)

the C register is used to access memory from 0xFF00+C.

Opcode=0xE2
- LD (C), A
- Cycles = 8

Example
```assembly
0E 20 : ld c, 0x20
E2    : ld [c], A ; Write A to 0xFF20 
```

### Memory To Register

#### [HL] to Register

|Register |A   |B   |C   |D   |E   |H   |L   |
|-------- |--- |----|----|----|----|----|----|
|Opcode   |0x7E|0x46|0x4E||0x56|0x5E|0x66|0x6E|

#### Immidiate Memory to A

Opcode=FA
Cycles=16

#### (C+0xFF00) Memory to A

Opcode=F2
Cycles=8

