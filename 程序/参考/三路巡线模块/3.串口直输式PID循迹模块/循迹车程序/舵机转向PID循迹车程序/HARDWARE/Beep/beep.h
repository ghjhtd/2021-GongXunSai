#ifndef __BEEP_H__
#define __BEEP_H__
#include "sys.h"
							
#define	Beep PAout(5)  //ѡ��FLASH										

void Beep_Init(void);
void Beep_Test(void);
void N_Beep(char n);
#endif
