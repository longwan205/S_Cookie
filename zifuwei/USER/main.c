#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"
#include "encode.h"
#include "timer.h"
#include "UserConfiguration.h"
#include "usart1.h"

void  TIM1_Configuration(void);
void  TIM8_Configuration(void);
void  UserMotorSpeedSetOne(void);



//int CNT_last=0,CNT_temp=0,Vcount=0,count=0;//编码器计数 
int k=0;
int t=0;
int j=0;




 int main(void)
 {		
  SystemInit();	//配置系统时钟为 72M 

	delay_init();	    	 //延时函数初始化	  
	 
 	USART3_Config(); //USART1 配置 	
	 
	//uart_init(115200);	 //串口初始化为115200
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3); //设置NVIC中断分组3:0位抢占优先级，0位响应优先级
	//EXTI_PA1_Config();//编码器Z相归零信号外部中断口初始化
	TIM3_Int_Init(1,7199);//10Khz的计数频率，计数到5000为500ms ,记到50为5ms
	TIM4_Init();//定时器编码器接口初始化,//编码器接口设置（TIM4）/PB6-A相  PB7-B相
 
//	TIM1_Configuration();//TIM1四通道分别输出PWM1/PWM2/PWM3/PWM4,对应引脚为PA8/PA9/PA10/PA11
	TIM8_Configuration();//TIM8四通道分别输出PWMA/PWMB/PWM3/PWM4,对应引脚为PC6/PC7/PC8/PC9
	 
	 GPIOget_Init();
	 
 	//LED_Init();			     //LED端口初始化
	//KEY_Init();          //初始化与按键连接的硬件接口
 	while(1)
	{
		/*
		USART_TX_BUF[0]=count>>8;
		USART_TX_BUF[1]=count;
					for(t=0;t<2;t++)
			{
	
				USART_SendData(USART1, USART_TX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}*/
		//delay_ms(1000);//每隔1s打印一次编码器角度,用手去拨动编码器  使其慢速旋转
		//printf("count = %d\n",count);
	}	 
 }

