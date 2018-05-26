void boot(){
	set_stack_ptr(0xFFFE);
	
	byte* vram = 0x9FFF;
	
	while (!is_bit_set(vram, 7)
	{
		*vram = 0;
		vram++;
	}
	
	set_sound(true);
	
	// do more sound stuff
	// will be written here later
	
	shade_selectors.shades = {3, 3, 3, 0};
	
	register de rom_mem;
	register hl vram_mem = 0x8010;
	
	// copy rom 0x104 to 0x134 to video ram memory (0x8010-0x8030)
	// each byte copied 4 times every 2 bytes
	// FF => FF 00 FF 00 FF 00 FF 00
	
	for (rom_mem = 0x104; rom_mem < 0x134; rom_mem++)
	{
		for (int i=0; i<4; ++i)
		{
			*vram_mem = *rom_mem;
			vram_mem += 2;	
		}
	}
	
	// copy rom 0xd8 to 0xE0 to video ram memory (0x8030-0x8038)
	// each byte copied 4 times every 2 bytes
	// FF => FF 00 FF 00 FF 00 FF 00
	for (rom_mem = 0xd8; rom_mem < 0xE0; ++rom_mem)
	{
		*vram_mem = *rom_mem;
		vram_mem += 2;
	}
}