#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键2 
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 






//#define FAULT  PD8in   	
//#define OTW    PD9in	 
//#define XW_A   PD10in
//#define XW_B   PD11in
//PD11     XW_B  下限位             高电平为未到，低电平为到了限位
//PD10     XW_A  上限位             高电平为未到，低电平为到了限位
//PD9      OTW   过温保护           高电平正常运行，低电平过温保护
//PD8     FAULT  过流或过压保护     高电平正常运行，低电平保护

#define FAULT  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)//读取过流或过压保护 
#define OTW    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)//读取过温保护    
#define XW_A   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)//读取上限位   
#define XW_B   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11)//读取下限位      






 

#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	2	//KEY1按下
#define KEY2_PRES	3	//KEY2按下
#define WKUP_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)


void KEY_Init(void);//IO初始化
void GPIOget_Init(void);
	
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
