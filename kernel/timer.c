#include "timer.h"
#include "isr.h"
#include "monitor.h"

static uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
	tick++;
	monitor_printf("Tick:");
	monitor_write_dec(tick);
	monitor_put('\n');
}

void init_timer(uint32_t frequence)
{
	register_interrupt_handler(IRQ0,&timer_callback);

	uint32_t divisor = 1193180 / frequence;

	outb(0x43,0x36);

	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor>>8)  & 0xFF);

	outb(0x40,l);
	outb(0x40,h);
}