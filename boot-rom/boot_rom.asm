; This is a disassembly of the Gameboy boot rom

ROM:0000 ; stack starts at 0xFFFE
ROM:0000 ; SIZE 00000020 BYTES

ROM:0000 boot_gb: 
ROM:0000
ROM:0000        ld      sp, $FFFE      ; load the stack pointer

; Clear VRAM
ROM:0003        xor     a
ROM:0004        ld      hl, $9FFF      ; load the start address of the VRAM to HL
ROM:0007
ROM:0007 .clear_vram_loop:                         ; CODE XREF: boot_gb+A↓j
ROM:0007        ldd     [hl], a        ; zero byte in VRAM
ROM:0008        bit     7, h           ; check if it the end of VRAM by checking the last bit
ROM:000A        jr      nz, .clear_vram_loop


; Start making the boot sound

ROM:000C        ld      hl, $FF26      ; Load sound on/off register
ROM:000F        ld      c, $11         ; Load FF11 to create sound wave
ROM:0011        ld      a, $80 
ROM:0013        ldd     [hl], a ; 0xFF26 = 0x80 -> turn bit 7 on -> all sound on
               
         ;-> Set sound wave pattern duty to 50%
		 ;-> Set Sound Length to (64-t1)*1/256, t1=0 -> 64/256 = 1/4 second
ROM:0014        ld      [c], a  ; $FF11 =  0x80 

				; c = 0x12 -> 0xFF12 -> Sound Mode 1 Register
ROM:0015        inc     c       

ROM:0016        ld      a, $F3 ; 0b11110011
				; initial volume => 0b1111 => 15
				; envelope => down
				; envelope => 3
ROM:0018        ld      [c], a

				; hl = 0xFF25 = NR 51 => Sound Output Terminal Selection
ROM:0019        ldd     [hl], a

ROM:001A        ld      a, $77 ; 'w'
				; hl = 0xFF24 = Channel Control / ON-OFF/ Volume
				; 0b01110111 => 
				; SoundOutput1.Status = Off; SoundOutput1.Level = 7;
				; SoundOutput2.Status = off; SoundOutput2.Level = 7;
ROM:001C        ld      [hl], a

				; 0xFF47 = BackGround and Window Pallete Data
				; 0b1111 1100
				; Set the pixel color selectors
ROM:001D        ld      a, $FC
ROM:001F        ld      [$FF47], a

				; Copy Nintendo Logo to VRAM
				; 0x104 is the Nintendo Logo offset when the rom is in memory
ROM:0021        ld      de, $104
				; 0x8010 is the address of the second tile in the tile data
ROM:0024        ld      hl, $8010
ROM:0027
ROM:0027 loc_27:                        ; CODE XREF: boot_gb+32↓j
ROM:0027        ld      a, [de]
ROM:0028        call    sub_95
ROM:002B        call    sub_96
ROM:002E        inc     de
ROM:002F        ld      a, e
ROM:0030        cp      $34 ; '4'
ROM:0032        jr      nz, loc_27

				; Cop More Bytes to VRAM
ROM:0034        ld      de, $D8
ROM:0037        ld      b, 8
ROM:0039
ROM:0039 loc_39:                        ; CODE XREF: boot_gb+3E↓j
ROM:0039        ld      a, [de]
ROM:003A        inc     de
ROM:003B        ldi     [hl], a
ROM:003C        inc     hl
ROM:003D        dec     b
ROM:003E        jr      nz, loc_39

	; Wierd operation (??)
	; Copy 0x19 to 0xd to 0x992f to 0x9924
	; Copy 0xd to 0x1 to 0x990f to 0x9904
	; Copy 0x1 to 0x990f
ROM:0040        ld      a, $19
ROM:0042        ld      [$9910], a
ROM:0045        ld      hl, $992F
ROM:0048
ROM:0048 loc_48:                        ; CODE XREF: boot_gb+53↓j
ROM:0048        ld      c, $C
ROM:004A
ROM:004A loc_4A:                        ; CODE XREF: boot_gb+4F↓j
ROM:004A        dec     a
ROM:004B        jr      z, loc_55
ROM:004D        ldd     [hl], a
ROM:004E        dec     c
ROM:004F        jr      nz, loc_4A

ROM:0051        ld      l, $F
ROM:0053        jr      loc_48
ROM:0055 ; ------------------------------------------------------------------
ROM:0055



ROM:0055 loc_55:                        ; CODE XREF: boot_gb+4B↑j
				; move h, 0
				; move ff42, 0x64
				; Scroll Y Register 
				; Scroll 0x64 (100) to the Y
ROM:0055        ld      h, a
ROM:0056        ld      a, $64 ; 'd'
ROM:0058        ld      d, a
ROM:0059        ld      [$FF42], a

				; move 0xff40, 0x91
				; LCD Control Register
				; Set 
ROM:005B        ld      a, $91
ROM:005D        ld      [$FF40], a

ROM:005F        inc     b
ROM:0060
ROM:0060 loc_60:                        ; CODE XREF: boot_gb+8C↓j
ROM:0060                                ; boot_gb+93↓j
ROM:0060        ld      e, 2
ROM:0062


ROM:0062 loc_62:                        ; CODE XREF: boot_gb+6E↓j
ROM:0062        ld      c, $C
ROM:0064
; Wait for V-Blank
ROM:0064 loc_64:                        ; CODE XREF: boot_gb+68↓j
ROM:0064                                ; boot_gb+6B↓j
ROM:0064        ld      a, [$FF44]
ROM:0066        cp      $90
ROM:0068        jr      nz, loc_64
ROM:006A        dec     c

ROM:006B        jr      nz, loc_64
ROM:006D        dec     e
ROM:006E        jr      nz, loc_62

ROM:0070        ld      c, $13
ROM:0072        inc     h
ROM:0073        ld      a, h
ROM:0074        ld      e, $83
ROM:0076        cp      $62 ; 'b'
ROM:0078        jr      z, loc_80
ROM:007A        ld      e, $C1
ROM:007C        cp      $64 ; 'd'
ROM:007E        jr      nz, loc_86
ROM:0080
ROM:0080 loc_80:                        ; CODE XREF: boot_gb+78↑j
ROM:0080        ld      a, e
ROM:0081        ld      [c], a
ROM:0082        inc     c
ROM:0083        ld      a, $87
ROM:0085        ld      [c], a
ROM:0086
ROM:0086 loc_86:                        ; CODE XREF: boot_gb+7E↑j
ROM:0086        ld      a, [$FF42]
ROM:0088        sub     b
ROM:0089        ld      [$FF42], a
ROM:008B        dec     d
ROM:008C        jr      nz, loc_60
ROM:008E        dec     b
ROM:008F        jr      nz, loc_E0
ROM:0091        ld      d, $20 ; ' '
ROM:0093        jr      loc_60
ROM:0093 ; End on boot_gb
ROM:0093
ROM:0095
ROM:0095 ; ====== S U B R O U T I N E =======================================
ROM:0095
ROM:0095
ROM:0095 sub_95:                        ; CODE XREF: boot_gb+28↑p
ROM:0095        ld      c, a
ROM:0095 ; End on sub_95
ROM:0095
ROM:0096
ROM:0096 ; ====== S U B R O U T I N E =======================================
ROM:0096
ROM:0096
ROM:0096 sub_96:                        ; CODE XREF: boot_gb+2B↑p
ROM:0096        ld      b, 4
ROM:0098
ROM:0098 loc_98:                        ; CODE XREF: sub_96+B↓j
ROM:0098        push    bc
ROM:0099        rl      c
ROM:009B        rla
ROM:009C        pop     bc
ROM:009D        rl      c
ROM:009F        rla
ROM:00A0        dec     b
ROM:00A1        jr      nz, loc_98

ROM:00A3        ldi     [hl], a
ROM:00A4        inc     hl
ROM:00A5        ldi     [hl], a
ROM:00A6        inc     hl
ROM:00A7        ret
ROM:00A7 ; End on sub_96
ROM:00A7
ROM:00A7 ; ------------------------------------------------------------------
ROM:00A8        db $CE
ROM:00A9        db $ED
ROM:00AA        db $66 ; f
ROM:00AB        db $66 ; f
ROM:00AC        db $CC
ROM:00AD        db  $D
ROM:00AE        db   0
ROM:00AF        db  $B
ROM:00B0        db   3
ROM:00B1        db $73 ; s
ROM:00B2        db   0
ROM:00B3        db $83
ROM:00B4        db   0
ROM:00B5        db  $C
ROM:00B6        db   0
ROM:00B7        db  $D
ROM:00B8        db   0
ROM:00B9        db   8
ROM:00BA        db $11
ROM:00BB        db $1F
ROM:00BC        db $88
ROM:00BD        db $89
ROM:00BE        db   0
ROM:00BF        db  $E
ROM:00C0        db $DC
ROM:00C1        db $CC
ROM:00C2        db $6E ; n
ROM:00C3        db $E6
ROM:00C4        db $DD
ROM:00C5        db $DD
ROM:00C6        db $D9
ROM:00C7        db $99
ROM:00C8        db $BB
ROM:00C9        db $BB
ROM:00CA        db $67 ; g
ROM:00CB        db $63 ; c
ROM:00CC        db $6E ; n
ROM:00CD        db  $E
ROM:00CE        db $EC
ROM:00CF        db $CC
ROM:00D0        db $DD
ROM:00D1        db $DC
ROM:00D2        db $99
ROM:00D3        db $9F
ROM:00D4        db $BB
ROM:00D5        db $B9
ROM:00D6        db $33 ; 3
ROM:00D7        db $3E ; >
ROM:00D8        db $3C ; <
ROM:00D9        db $42 ; B
ROM:00DA        db $B9
ROM:00DB        db $A5
ROM:00DC        db $B9
ROM:00DD        db $A5
ROM:00DE        db $42 ; B
ROM:00DF        db $3C ; <
ROM:00E0 ; ------------------------------------------------------------------
ROM:00E0 ; STARTION CHUNK FOR boot_gb
ROM:00E0
ROM:00E0 loc_E0:                        ; CODE XREF: boot_gb+8F↑j
ROM:00E0        ld      hl, $104
ROM:00E3        ld      de, $A8
ROM:00E6
ROM:00E6 loc_E6:                        ; CODE XREF: boot_gb+EF↓j
ROM:00E6        ld      a, [de]
ROM:00E7        inc     de
ROM:00E8        cp      [hl]
ROM:00E9
ROM:00E9 loc_E9:                        ; CODE XREF: boot_gb:loc_E9↓j
ROM:00E9        jr      nz, @
ROM:00EB        inc     hl
ROM:00EC        ld      a, l
ROM:00ED        cp      $34 ; '4'
ROM:00EF        jr      nz, loc_E6
ROM:00F1        ld      b, $19
ROM:00F3        ld      a, b
ROM:00F4
ROM:00F4 loc_F4:                        ; CODE XREF: boot_gb+F7↓j
ROM:00F4        add     a, [hl]
ROM:00F5        inc     hl
ROM:00F6        dec     b
ROM:00F7        jr      nz, loc_F4
ROM:00F9        add     a, [hl]
ROM:00FA
ROM:00FA loc_FA:                        ; CODE XREF: boot_gb:loc_FA↓j
ROM:00FA        jr      nz, @
ROM:00FC        ld      a, 1
ROM:00FE        ld      [$FF50], a
ROM:00FE ; END ON CHUNK FOR boot_gb
ROM:00FE ; end o
ROM:00FE
ROM:00FE ; end o