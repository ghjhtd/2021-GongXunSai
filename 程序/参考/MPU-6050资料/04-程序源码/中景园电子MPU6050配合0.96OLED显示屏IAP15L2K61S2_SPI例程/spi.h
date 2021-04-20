#ifndef __SPI_H
#define __SPI_H

#include "REG51.h"
#include "led.h"

sbit SPI_SCL=P1^0;
sbit SPI_SDIN=P1^1;
sbit SPI_RST=P1^2;
sbit SPI_DC=P1^3;
sbit SPI_CS=P1^4;


#define u8  unsigned char
#define u16 unsigned short int
#define u32 unsigned int
#define OLED_CMD  0
#define OLED_DATA 1

#define SPI_SCL_HIGH()   SPI_SCL=1;
#define SPI_SCL_LOW()    SPI_SCL=0;

#define SPI_SDIN_HIGH()  SPI_SDIN=1;
#define SPI_SDIN_LOW()   SPI_SDIN=0;

#define SPI_RST_HIGH()   SPI_RST=1;
#define SPI_RST_LOW()    SPI_RST=0;

#define SPI_DC_HIGH()    SPI_DC=1;
#define SPI_DC_LOW()     SPI_DC=0;

#define SPI_CS_HIGH()    SPI_CS=1;
#define SPI_CS_LOW()     SPI_CS=0;

void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_WR_BP(u8 x,u8 y);
void OLED_Clear(void);
void OLED_ScrollDisplay(u8 num,u8 space);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
u32 OLED_Pow(u8 m,u8 n);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
void OLED_Init(void);

#endif