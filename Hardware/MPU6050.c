#include "stm32f10x.h"                  // Device header
#include "myI2C.h"
#include "MPU6050_Reg.h"
#include "MPU6050.h"
#include "math.h"

#define MPU6050Address		0xD0

void WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t TimeOut = 10000;
	while(I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
	{
		TimeOut --;
		if(TimeOut == 0)
		{
			break;
		}
	}
	
}

void MPU6050_WriteReg(uint8_t RegAdress, uint8_t Data)
{
	I2C_GenerateSTART(I2C2, ENABLE);
	WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2, MPU6050Address, I2C_Direction_Transmitter);
	WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	
	I2C_SendData(I2C2, RegAdress);
	WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
	
	I2C_SendData(I2C2, Data);
	WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	
	I2C_GenerateSTOP(I2C2, ENABLE);
	
}

int16_t MPU6050_ReadReg(uint8_t RegAdress)
{
	int16_t Data;
	
	I2C_GenerateSTART(I2C2, ENABLE);
	WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2, MPU6050Address, I2C_Direction_Transmitter);
	WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	
	I2C_SendData(I2C2, RegAdress);
	WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	
	I2C_GenerateSTART(I2C2, ENABLE);
	WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2, MPU6050Address, I2C_Direction_Receiver);
	WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);
	
	//提前停止发送ACK，产生停止
	I2C_AcknowledgeConfig(I2C2, DISABLE);
	I2C_GenerateSTOP(I2C2, ENABLE);
	
	WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);	//等待数据寄存器装载完成
	Data = I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);	//恢复使能应答
	
	return Data;
}

void MPU6050_Init(void)
{
	myI2C_Init();
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);	//配置电源管理寄存器1，关闭睡眠，使用x轴陀螺仪时钟
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00); //配置电源管理寄存器2
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09); //采样率10分频，8KHz
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);		//配置数字低通滤波器
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);//陀螺仪满量程 
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);//加速度计满量程
	
}

uint8_t Get_MPU6050ID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void GetDatas(MPU6050DatasTypedef* MPU6050Datas)
{
	uint16_t DataH, DataL;
	DataH =MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL =MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	MPU6050Datas->AccX = (DataH << 8) |	DataL;
	
	DataH =MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL =MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	MPU6050Datas->AccY = (DataH << 8) |	DataL;
	
	DataH =MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL =MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	MPU6050Datas->AccZ = (DataH << 8) |	DataL;
	
	DataH =MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL =MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	MPU6050Datas->GyroX = (DataH << 8) | DataL;
	
	DataH =MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL =MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	MPU6050Datas->GyroY = (DataH << 8) | DataL;
	
	DataH =MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL =MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	MPU6050Datas->GyroZ = (DataH << 8) | DataL;
	
}

void Get_XAngle(MPU6050DatasTypedef* MPU6050Datas, XAngledef* XAngle)
{
	double XG = MPU6050Datas->AccX / 2048.0;
	double YG = MPU6050Datas->AccY / 2048.0;
	double ZG = MPU6050Datas->AccZ / 2048.0;
	
	XAngle->AngleX = acos(XG) * 57.29577;
	XAngle->AngleY = acos(YG) * 57.29577;
	XAngle->AngleZ = acos(ZG) * 57.29577;
	
}

