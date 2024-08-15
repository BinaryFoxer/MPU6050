#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void Key_init(){
	//开RCC IO口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//io口初始化
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//配置io口为输入模式，上拉输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

uint8_t GetKeyNum(){
	uint8_t KeyNum;
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0){	//读输入寄存器，低电平说明按下
		Delay_ms(10);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0);//循环等待松手
		Delay_ms(10);
		KeyNum = 1;
	}
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0){
		Delay_ms(10);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0);
		Delay_ms(10);
		KeyNum = 2;
	}
	return KeyNum;
}
