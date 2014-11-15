#include "type.h"
#include "keyboard.h"
#include "keymap.h"
#include "monitor.h"
#include "isr.h"

static void keyboard_func(registers_t regs)
{
	uint8_t scan_code = inb(0x60);
	monitor_put((char)getkey(scan_code));
}

void init_keyboard(void)
{
	register_interrupt_handler(IRQ1,keyboard_func);
}

uint32_t getkey(uint32_t scan_code)
{
	return keymap[scan_code * MAP_COLS];
}