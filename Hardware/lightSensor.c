#include "stm32f10x.h"                  // Device header

void L_Sensor_Init(void)
{
	//开RCC_IO时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//io初始化
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	//PB13配置为输入口，上拉模式防止浮空脚电压漂移
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_13);//设置初始为高电平，即不响
	
}

uint8_t Get_L_SensorDatabit(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
	//直接返回PB13引脚读到的值
}
