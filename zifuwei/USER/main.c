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



//int CNT_last=0,CNT_temp=0,Vcount=0,count=0;//���������� 
int k=0;
int t=0;
int j=0;




 int main(void)
 {		
  SystemInit();	//����ϵͳʱ��Ϊ 72M 

	delay_init();	    	 //��ʱ������ʼ��	  
	 
 	USART3_Config(); //USART1 ���� 	
	 
	//uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3); //����NVIC�жϷ���3:0λ��ռ���ȼ���0λ��Ӧ���ȼ�
	//EXTI_PA1_Config();//������Z������ź��ⲿ�жϿڳ�ʼ��
	TIM3_Int_Init(1,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms ,�ǵ�50Ϊ5ms
	TIM4_Init();//��ʱ���������ӿڳ�ʼ��,//�������ӿ����ã�TIM4��/PB6-A��  PB7-B��
 
//	TIM1_Configuration();//TIM1��ͨ���ֱ����PWM1/PWM2/PWM3/PWM4,��Ӧ����ΪPA8/PA9/PA10/PA11
	TIM8_Configuration();//TIM8��ͨ���ֱ����PWMA/PWMB/PWM3/PWM4,��Ӧ����ΪPC6/PC7/PC8/PC9
	 
	 GPIOget_Init();
	 
 	//LED_Init();			     //LED�˿ڳ�ʼ��
	//KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
 	while(1)
	{
		/*
		USART_TX_BUF[0]=count>>8;
		USART_TX_BUF[1]=count;
					for(t=0;t<2;t++)
			{
	
				USART_SendData(USART1, USART_TX_BUF[t]);//�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}*/
		//delay_ms(1000);//ÿ��1s��ӡһ�α������Ƕ�,����ȥ����������  ʹ��������ת
		//printf("count = %d\n",count);
	}	 
 }

