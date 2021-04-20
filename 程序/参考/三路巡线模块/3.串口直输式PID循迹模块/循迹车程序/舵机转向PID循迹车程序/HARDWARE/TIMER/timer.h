#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"





/************************º¯ÊýÉùÃ÷******************************/
extern void TIM1_PWM_Init(u16 arr,u16 psc);
extern void TIM1_Int_Init(u16 arr,u16 psc);
extern void TIM2_Int_Init(u16 arr,u16 psc);
extern void Encoder_Init_TIM2(void);
extern void Encoder_Init_TIM3(void);
extern void TIM4_PWM_Init(u16 arr,u16 psc);
#endif
