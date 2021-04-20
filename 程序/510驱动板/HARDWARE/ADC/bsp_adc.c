#include "bsp_adc.h"



/*??DMA?ADC?????*/

volatile u16 ADCConvertedValue[10][3];//????ADC????,??DMA?????,3??,?????10???????
         
void DMA_ADC_Init(void)
{

    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//????

    DMA_DeInit(DMA1_Channel1);    //????????????
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);//???????DMA?????
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;//???????DMA?????(?????????)
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//???????????????????????,???????
    DMA_InitStructure.DMA_BufferSize = 3*10;//????DMA???DMA?????,?????????????ADCConvertedValue???
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//?????????????,?????? Disable
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//???????????????,??????,Enable
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//?????16?
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//?????16?
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //?????????
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA???????? ??4??? ?????????
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//??DMA??????????
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);//??DMA_InitStruct?????????DMA???

    DMA_Cmd(DMA1_Channel1, ENABLE);//??DMA???
}


void Adc_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    /*3?IO????(PA0?PA1?PA2)*/
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    /*IO?ADC????*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //????
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 3;
    ADC_Init(ADC1, &ADC_InitStructure);
    
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);//??????????ADCConvertedValue[0~10][0]
	  ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_239Cycles5);//??????????ADCConvertedValue[0~10][1]
	  ADC_RegularChannelConfig(ADC1,ADC_Channel_12,3,ADC_SampleTime_239Cycles5);//??????????ADCConvertedValue[0~10][2]

	  
    ADC_DMACmd(ADC1, ENABLE);//??ADC?DMA??
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

}

//adc键盘检测函数，0-无任何值按下，返回按下键值
u8 ADC_Key(u16 adc,u8 mode){
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(adc < 4080))
	{
		delay_ms(5);//去抖动 
		key_up=0;	
		if(3690<=adc && adc<4080){return 9;}
		if(3600<=adc && adc<3690){return 8;}
		if(3500<=adc && adc<3600){return 7;}
		if(3400<=adc && adc<3500){return 6;}
		if(3250<=adc && adc<3400){return 5;}
		if(2900<=adc && adc<3250){return 4;}
		if(2400<=adc && adc<2900){return 3;}
		if(500<=adc && adc<2400){return 2;}
		if(adc<500){return 1;}

	}else if(adc >= 4080)key_up=1; 	    
 	return 0;// 无按键按下
	
}






