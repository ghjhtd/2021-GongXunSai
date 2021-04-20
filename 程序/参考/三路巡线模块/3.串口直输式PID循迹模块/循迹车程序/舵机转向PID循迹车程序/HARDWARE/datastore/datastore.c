/**
  ******************************************************************************
  * @�ļ��� datastore.c
  * @�ļ�˵����������Ϊ���ݴ�����غ����ļ�����Ҫ�����������ѭ��������������һЩ����
  ******************************************************************************/
#include "datastore.h"
#include "stmflash.h"
#include "track.h"
#include "usart.h"
#include "stdio.h"    
    
	
#define FLASH_SAVE_ADDR  0X0800fc00	//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)�����������STM32F103C8T6���1K�ֽڴ��棨FLASH�ܹ�64K��	
	
#define DateSize 16//�������ݳ��ȴ�С
u8 DateBUF[30];



/**
  * @brief  ������ѭ����صı���
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
  * @brief  ��ȡ��ѭ����صı���
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
  * @brief  ����Ƿ�EEROM�д������
  * @param  None
  * @return ��Ź����ݷ���1�����߷���0
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

