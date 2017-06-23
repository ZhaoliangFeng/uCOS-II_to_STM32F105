#ifndef _BSP_H
#define _BSP_H

#include "stm32f10x.h"
#include "led.h"
#include "os_cfg_r.h"

#define BSP_RCC_TO_VAL   0x00000FFF;  /*Max Timeout for RCC register*/

void Bsp_Init(void);

#endif
