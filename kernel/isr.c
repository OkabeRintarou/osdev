#include "monitor.h"
#include "isr.h"

static isr_t interrupt_handler[256] = {0};

// 调用中断处理函数
void isr_handler(registers_t * regs)
{
	//monitor_printf("recived interrupot:");
	//monitor_write_dec(regs.int_no);
	//monitor_put('\n');	
	if(interrupt_handler[regs->int_no] != 0){
		interrupt_handler[regs->int_no](regs);
	}
	else{
		monitor_printf("unhandled interrupt.\n");
	}
	return;
}

void irq_handler(registers_t * regs)
{
	if(regs->int_no >= 40)
	{
		// send reset signal to slave
		outb(0xA0,0x20);
	}

	// send reset signal to master
	outb(0x20,0x20);

	if(interrupt_handler[regs->int_no] != 0){
		isr_t handler = interrupt_handler[regs->int_no];
		handler(regs);
	}
}

void register_interrupt_handler(uint8_t n,isr_t handler)
{
	interrupt_handler[n] = handler;
}
