#ifndef __MPU6050_H_
#define __MPU6050_H_
#include "stm32f10x.h"                  // Device header

typedef struct
{
	int16_t AccX;
	int16_t AccY;
	int16_t AccZ;	//三轴加速度
	int16_t GyroX;
	int16_t GyroY;
	int16_t GyroZ;	//三轴角速度
	
}MPU6050DatasTypedef;

typedef struct 
{
	double AngleX;
	double AngleY;
	double AngleZ;
	
}XAngledef;

void MPU6050_Init(void);
uint8_t Get_MPU6050ID(void);
void GetDatas(MPU6050DatasTypedef* MPU6050Datas);
void Get_XAngle(MPU6050DatasTypedef* MPU6050Datas, XAngledef* XAngle);

#endif
