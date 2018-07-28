/*
	Very wierd function.
	Changes the C register, 
	but the value of C is not used anywhere after the calloc
	also does this wierd 'push bc' 'pop bc' thing
*/
void sub_96 (register c){
	// loop from b=4 to b=0
	/* Close to source
	for (register b=4; b>=0; --b){
		rla
		rl c
		rla
	}
	*/
	// Actually does this
	rl c, 4 // the value of c is not actually used anywhere. :(
	rl a, 8 // does nothing ???? :( nintendo is not cool
	
	*hl = a;
	hl += 2;
	*hl = a;
	hl += 2;
}

/*
	Just calls the sub_96 function.
	This is basically useless since C is not used anywhere
*/
void sub_95 (register a){
	register c = a;
	sub_96(c);
	
}

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
	
	// 0x21:
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
	
	// 0x34:
	
	// copy rom 0xd8 to 0xE0 to video ram memory (0x8030-0x8038)
	// each byte copied 4 times every 2 bytes
	// FF => FF 00 FF 00 FF 00 FF 00
	for (rom_mem = 0xd8; rom_mem < 0xE0; ++rom_mem)
	{
		*vram_mem = *rom_mem;
		vram_mem += 2;
	}
	
	// 0x40:
	*(0x9910) = 0x19;
	
	// Copy 0x19 to 0xd to 0x992f to 0x9924
	// Copy 0xd to 0x1 to 0x990f to 0x9904
	// Copy 0x1 to 0x990f
	
	//0x55:
	set_scroll_y(0x64);
	
	set_lcd_control(
		display = true,
		window_tilemap_display_select = 0x9800,
		display_window = false,
		bg_wnd_tile_data_select = 0x8000,
		bg_tilemap_display_select = 0x9800,
		sprite_size=(8, 8),
		display_sprite = false,
		display_bd_and_wnd = true
	);
			
	for (int i=0; i<134; ++i)
	{
		// Wait for 24 V-Blanks
		for (int i=0; i<24; ++i)
		{
			while (LYC != VBLANK_START);	
		}
		
		++h;
		
		if (h == 0x62)
		{
			*0xff13 = 0x83, 0x87
		}
		else if (h == 0x64)
		{
			*0xff13 = 0xc1, 0x87;
		}	
		
		if (i < 100){
			set_scroll_y(get_scroll_y()-1);	
		}
	}
}