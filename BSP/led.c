/*****************************************************
* @Author  :  Fengzhaoliang
* @File    :  led.c
* @Date    :  2017-04-29
* @Function:  UCOSII transplant template
******************************************************/
#include "led.h"

static void Bsp_Led_Gpio_Init()
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Pin      =      GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode     =      GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed    =      GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void  Led_On(void)
{
    GPIO_SetBits(GPIOC,GPIO_Pin_12);
}

void  Led_Off(void)
{
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);
}

void Bsp_Led_Init(void)
{
    Bsp_Led_Gpio_Init();
}

