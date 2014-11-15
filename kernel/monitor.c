#include "monitor.h"
#include "type.h"
#include "common.h"

static uint16_t cursor_x = 0;   // 0 <= cursor_x < 80
static uint16_t cursor_y = 0;   // 0 <= cursor_y < 25
static uint16_t * video_memory = (uint16_t*)0x0b8000;
static color_t  back_color = tos_black;  // 默认背景色是黑色
static color_t fore_color = tos_white;   // 默认前景色是白色

/* static function */
static void scroll(void);
static void move_cursor(void);

/* 屏幕打印一个字符 */
void monitor_put(char ch)
{
	uint8_t attributeByte = (fore_color & 0x0f) | (back_color << 4);

	//高8位为属性信息
	uint16_t attribute = attributeByte << 8;
	uint16_t * location;

	//处理退格键
	if(ch == 0x08 && cursor_x){
		cursor_x--;
	}

	//处理Tab键
	else if(ch == 0x09){
		cursor_x = (cursor_x + 8) & ~(8 - 1);
	}

	else if(ch == '\r'){
		cursor_x = 0;
	}
	else if(ch == '\n'){
		cursor_x = 0;
		cursor_y++;
	}
	// 处理可打印字符
	else if(ch >= ' '){
		location = video_memory + (cursor_y * 80 + cursor_x );
		*location = ch | attribute;
		cursor_x++;
	}

	if(cursor_x >= 80){
		cursor_x = 0;
		cursor_y++;
	}

	scroll();
	move_cursor();

}
/* 清屏 */
void monitor_clear(void)
{
	uint8_t attributeByte = ( back_color << 4) | (fore_color & 0x0f);
	uint16_t blank = 0x20 | (attributeByte << 8);

	int i;
	for(i = 0; i < 80 * 25;i++){
		video_memory[i] = blank;
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

/* 屏幕输出以\0结尾的字符串 */
void monitor_printf(const char * str)
{
	while(*str){
		monitor_put(*str);
		str++;
	} 
}

/* 设置前景色和背景色 */
void monitor_setbackcolor(color_t newcolor)
{
	back_color = newcolor;
}
void monitor_setforecolor(color_t newcolor)
{
	fore_color = newcolor;
}

void monitor_write_hex(uint32_t value)
{
	char low;
	char buf[8];
	int i;
	for(i = 0; i < 8;i++){
		low = (value & 0x0f) + '0';
		if(low > '9'){
			low += 7;
		}
		buf[i] = low;
		value >>= 4;
	}
	for(i = 7; i >= 0; i--){
		monitor_put(buf[i]);
	}
}

void monitor_write_dec(uint32_t value)
{
	char buf[33] ={0};
	int i = 0;
	if(value == 0){
		monitor_put(value + '0');
		return;
	}
	while(value){
		buf[i] = value % 10 + '0';
		i++;
		value /= 10;
	}
	buf[i] = value + '0';
	while(i--){
		monitor_put(buf[i]);
	}

}

static void move_cursor(void)
{
	 // The screen is 80 characters wide...
   uint16_t cursorLocation = cursor_y * 80 + cursor_x;
   outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

// Scrolls the text on the screen up by one line
static void scroll(void)
{
	// Get a space character with the default attributes
	uint8_t attributeByte = (back_color /* black */ << 4) | (fore_color/*white*/ & 0x0f);
	uint16_t blank =  0x20 /* space */ | (attributeByte << 8);

	// Row 25 is the end,this means we need to scroll up
	if(cursor_y >= 25){
		// Move the current text chunk that makes up the screen
       // back in the buffer by a line
       int i;
       for (i = 0*80; i < 24*80; i++)
       {
           video_memory[i] = video_memory[i+80];
       }

       // The last line should now be blank. Do this by writing
       // 80 spaces to it.
       for (i = 24*80; i < 25*80; i++)
       {
           video_memory[i] = blank;
       }
       // The cursor should now be on the last line.
       cursor_y = 24;
	}
}
