#include "type.h"
#include "monitor.h"
#include "descriptor_table.h"
#include "isr.h"
#include "timer.h"
#include "keyboard.h"

int main()
{

    init_descriptor_tables();
    monitor_clear();
    //monitor_printf("HelloWorld\n");
    monitor_setforecolor(tos_red);


    init_keyboard();
    //init_timer(10000);
    asm volatile("sti");
    asm volatile("int $0x03;\
		int $0x04");
    //register_interrupt_handler(IRQ1,show);
    
      
    return 0;
}
