/**
  ******************************************************************************
  * @文件名 datastore.c
  * @文件说明：本函数为数据储存相关函数文件，主要储存关于配置循迹传感器参数的一些数据
  ******************************************************************************/
#include "datastore.h"
#include "stmflash.h"
#include "track.h"
#include "usart.h"
#include "stdio.h"    
    
	
#define FLASH_SAVE_ADDR  0X0800fc00	//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)，本程序采用STM32F103C8T6最后1K字节储存（FLASH总共64K）	
	
#define DateSize 16//储存数据长度大小
u8 DateBUF[30];



/**
  * @brief  储存与循迹相关的变量
  * @param  None
  * @return None
  */
void StoreTrackData(void)
{
    DateBUF[0]=D_AD_VALUE>>8;
    DateBUF[1]=D_AD_VALUE;
    
    DateBUF[2]=LEFT_MAX>>8;
    DateBUF[3]=LEFT_MAX;
    
	DateBUF[4]=MID_MAX>>8;
    DateBUF[5]=MID_MAX;
	
    DateBUF[6]=RIGHT_MAX>>8;
    DateBUF[7]=RIGHT_MAX;
    
    DateBUF[8]=LEFT_THERSH>>8;
    DateBUF[9]=LEFT_THERSH;
    
    DateBUF[10]=RIGHT_THERSH>>8;
    DateBUF[11]=RIGHT_THERSH;
     
    DateBUF[12]=LEFT_SPAN>>8;
    DateBUF[13]=LEFT_SPAN;

    DateBUF[14]=RIGHT_SPAN>>8;
    DateBUF[15]=RIGHT_SPAN;
	
	STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)DateBUF,DateSize);	
}


/**
  * @brief  读取与循迹相关的变量
  * @param  None
  * @return None
  */
void ReadTrackData(void)
{
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)DateBUF,DateSize);   
    D_AD_VALUE=(short int)(DateBUF[0]<<8)+DateBUF[1];
    LEFT_MAX=(short int)(DateBUF[2]<<8)+DateBUF[3];
	MID_MAX=(short int)(DateBUF[4]<<8)+DateBUF[5];
    RIGHT_MAX=(short int)(DateBUF[6]<<8)+DateBUF[7];
    LEFT_THERSH=(short int)(DateBUF[8]<<8)+DateBUF[9];
    RIGHT_THERSH=(short int)(DateBUF[10]<<8)+DateBUF[11];
    LEFT_SPAN=(short int)(DateBUF[12]<<8)+DateBUF[13];
    RIGHT_SPAN=(short int)(DateBUF[14]<<8)+DateBUF[15];
	printf("%d %d %d %d %d %d %d %d",D_AD_VALUE,LEFT_MAX,MID_MAX,RIGHT_MAX,LEFT_THERSH,RIGHT_THERSH,LEFT_SPAN,RIGHT_SPAN);
}


/**
  * @brief  检查是否EEROM中存放数据
  * @param  None
  * @return 存放过数据返回1，否者返回0
  */
u8 CheckData(void)
{
    STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)DateBUF,DateSize);   
    if((DateBUF[1]!=0)&&(DateBUF[3]!=0)&&(DateBUF[5]!=0)&&(DateBUF[7]!=0))
    {
        return 1;
    }
    return 0;
}

