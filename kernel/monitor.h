#ifndef _TOYOS_MONITOR_INCLUDE_
#define _TOYOS_MONITOR_INCLUDE_

#include "common.h"
/* 屏幕打印一个字符 */
void monitor_put(char ch);
/* 清屏 */
void monitor_clear(void);
/* 屏幕输出以\0结尾的字符串 */
void monitor_printf(const char * str);
/* 设置前景色和背景色 */
void monitor_setbackcolor(color_t newcolor);
void monitor_setforecolor(color_t newcolor);

/* 以16进制输出整型数 */
void monitor_write_hex(uint32_t value);
/* 以十进制输出整型数*/
void monitor_write_dec(uint32_t value);

#endif //_TOYOS_MONITOR_INCLUDE_
