#ifndef _TOYOS_COMMON_INCLUDE_
#define _TOYOS_COMMON_INCLUDE_

#include "type.h"

/* color enum */
enum tos_color_{
	tos_black 			= 0,
	tos_blue 			= 1,
	tos_green 			= 2,
	tos_cyan 			= 3,
	tos_red 			= 4,
	tos_magenta 		= 5,
	tos_brown 			= 6,
	tos_lightgrey 		= 7,
	tos_darkgrey 		= 8,
	tos_lightblue 		= 9,
	tos_lightgreen 		= 10,
	tos_lightcray 		= 11,
	tos_lightred 		= 12,
	tos_lightmagneta 	= 13,
	tos_lightbrown 		= 14,
	tos_white 			= 15
};	

typedef enum tos_color_ color_t;

/* 端口写一个字节 */
void outb(uint16_t port,uint8_t value);
/* 端口读一个字节 */
uint8_t inb(uint16_t port);
/* 端口读一个字 */
uint16_t inw(uint16_t port);

#endif //_TOYOS_COMMON_INCLUDE_
