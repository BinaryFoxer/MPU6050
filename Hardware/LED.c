#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void LEDInitAll(void)
{
	//片内外设都挂在PB2总线上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//先开IO时钟使能
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//配置输出模式为推挽
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}

void LEDFlow(void)
{
		//直接给输出寄存器赋值，低电平有效
		GPIO_Write(GPIOA, ~0x0001);
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0002);
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0004);
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0008);
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0010);
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0020);
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0040);
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0080);
		Delay_ms(100);	
	
}

void LEDInit(void){
	//开RCC_IO时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//io初始化
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);//设置初始为高电平，即不亮
	
}

void LED1On(void){
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void LED1Off(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void LED1Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);					//则设置PA1引脚为高电平
	}
	else													//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);					//则设置PA1引脚为低电平
	}
}

void LED2On(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void LED2Off(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void LED2Turn(void){
	if  (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
	
}

//void LED2_Turn(void)
//{
//	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
//	{                                                  
//		GPIO_SetBits(GPIOA, GPIO_Pin_2);               		//则设置PA2引脚为高电平
//	}                                                  
//	else                                               		//否则，即当前引脚输出高电平
//	{                                                  
//		GPIO_ResetBits(GPIOA, GPIO_Pin_2);             		//则设置PA2引脚为低电平
//	}
//}
