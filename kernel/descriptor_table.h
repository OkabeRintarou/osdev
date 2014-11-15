#ifndef _TOYOS_DESCRIPTOR_TABLE_INCLUDE_
#define _TOYOS_DESCRIPTOR_TABLE_INCLUDE_

#include "type.h"

/* 数据段和代码段描述符 */
struct gdt_entry_struct
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
}__attribute((packed));
typedef struct gdt_entry_struct gdt_entry_t;

/* gdt_ptr 用于指定全局描述符的基地址和偏移 */
struct gdt_ptr_struct
{	
	uint16_t limit;
	uint32_t base;
}__attribute((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

void init_descriptor_tables(void);


// 中断描述符
struct idt_entry_struct
{
	uint16_t base_low;// 低16位地址
	uint16_t sel;	// 段描述符
	uint8_t always0;// 总是为0
	uint8_t flags;// 属性
	uint16_t base_high; // 高16位地址
}__attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

// 中断处理函数
// 0 ~ 19属于CPU的异常中断 
extern void isr0(void);  // 0  #DE 除法错
extern void isr1(void);  // 1  #DB 调试异常
extern void isr2(void);  // 2      非屏蔽中断
extern void isr3(void);  // 3  #BP 调试断点
extern void isr4(void);  // 4  #OF 溢出
extern void isr5(void);  // 5  #BR 越界
extern void isr6(void);  // 6  #UD 无效操作码
extern void isr7(void);  // 7  #NM 设备不可用
extern void isr8(void);  // 8  #DF 双重错误
extern void isr9(void);  // 9      协处理器段越界
extern void isr10(void); // 10 #TS 无效TSS
extern void isr11(void); // 11 #NP 段不存在
extern void isr12(void); // 12 #SS 堆栈段错误
extern void isr13(void); // 13 #GP 常规保护错误
extern void isr14(void); // 14 #PF 页错误
extern void isr15(void); // 15     Intel保留，未使用
extern void isr16(void); // 16 #MF x87FPU浮点错
extern void isr17(void); // 17 #AC 对齐检验
extern void isr18(void); // 18 #MC Machine Check
extern void isr19(void); // 19 #XF SIMD浮点异常
// 20 ～31 Intel保留，未使用
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
// 32 ~ 255 用户定义中断

// 
extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);


#endif //_TOYOS_DESCRIPTOR_TABLE_INCLUDE_
