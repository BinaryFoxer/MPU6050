#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "OLED.h"
#include "OLED_Data.h"
#include "Key.h"
#include "MPU6050.h"

int main(){
	uint8_t ID;
	
	OLED_Init();
	MPU6050_Init();
	LEDInit();
	
	ID = Get_MPU6050ID();
	
	OLED_ShowString(0, 0, "ID:", OLED_6X8);
	OLED_ShowHexNum(24, 0, ID, 2, OLED_6X8);
	OLED_Update();
	
	OLED_ShowString(0, 16, "Ax:", OLED_6X8);
	OLED_ShowString(0, 32, "Ay:", OLED_6X8);
	OLED_ShowString(0, 48, "Az:", OLED_6X8);
	OLED_Update();
	OLED_ShowString(60, 16, "Gx:", OLED_6X8);
	OLED_ShowString(60, 32, "Gy:", OLED_6X8);
	OLED_ShowString(60, 48, "Gz:", OLED_6X8);
	OLED_Update();
	
	MPU6050DatasTypedef MPU6050Datas;
	XAngledef XAngle;
	while(1)
	{		
		GetDatas(&MPU6050Datas);
		Get_XAngle(&MPU6050Datas, &XAngle);
		OLED_ShowFloatNum(18, 16, XAngle.AngleX,3, 1, OLED_6X8);
		OLED_Update();
		OLED_ShowFloatNum(18, 32, XAngle.AngleY, 3, 1, OLED_6X8);
		OLED_Update();
		OLED_ShowFloatNum(18, 48, XAngle.AngleZ, 3, 1, OLED_6X8);
		OLED_Update();
		OLED_ShowSignedNum(78, 16, MPU6050Datas.GyroX, 4, OLED_6X8);
		OLED_Update();
		OLED_ShowSignedNum(78, 32, MPU6050Datas.GyroY, 4, OLED_6X8);
		OLED_Update();
		OLED_ShowSignedNum(78, 48, MPU6050Datas.GyroZ, 4, OLED_6X8);
		OLED_Update();
		
		if(XAngle.AngleY > 150)
		{
			GPIO_Write(GPIOA, 0x0020);
		}
		else if(XAngle.AngleY > 125)
		{
			GPIO_Write(GPIOA, 0x0010);
		}
		else if(XAngle.AngleY > 100)
		{
			GPIO_Write(GPIOA, 0x0008);
		}
		else if(XAngle.AngleY > 75)
		{
			GPIO_Write(GPIOA, 0x0004);
		}
		else if(XAngle.AngleY > 50)
		{
			GPIO_Write(GPIOA, 0x0002);
		}
		else if(XAngle.AngleY > 25)
		{
			GPIO_Write(GPIOA, 0x0001);
		}
		else
		{
			GPIO_Write(GPIOA, 0x0000);
		}
	}

}
