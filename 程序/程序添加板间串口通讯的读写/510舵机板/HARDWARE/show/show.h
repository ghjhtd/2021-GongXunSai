#ifndef __SHOW_H
#define __SHOW_H
#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
void lcd_show(void);
void openmv(void);
void OLED_Num_Next(u8* px,u8* py,int num,u8 len,u8 size1,u8*len_last,u8*size_last);
void OLED_Num_Newline(u8* px,u8* py,int num,u8 len,u8 size1,u8*len_last,u8*size_last);
void OLED_Str_Next(u8* px,u8* py,char* chr,u8 size1,u8*len_last,u8*size_last);
void OLED_Str_Newline(u8* px,u8* py,char* chr,u8 size1,u8*len_last,u8*size_last);
void DataScope(void);
#endif
