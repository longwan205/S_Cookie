#include "stm32f10x.h"
#include "misc.h"
#include "nvic.h"
#include "sys.h" 
#include "delay.h"
/*
�жϷ���˵�������ȼ��ɸ������
˳��       ����            ����                   ��ռ���ȼ�      ��Ӧ���ȼ�
 1         EXTI1        ������Z���0                  0                 0
 2         TIM4         ��ʱ���ı�����ģʽ            1                 1
 3         USART1       ����ͨ���ж�                  2                 1
*/

//1.-----Z�źŹ���  PA1
/*void PA_NVIC_Config(NVIC_InitTypeDef NVIC_InitStructure1)
{
  
	NVIC_InitStructure1.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure1);
}

*/





//2----��ʱ���ı������ӿ�ģʽ,�Ա��������м���
void TIM4_NVIC_Config(NVIC_InitTypeDef NVIC_InitStructure2)
{
	NVIC_InitStructure2.NVIC_IRQChannel = TIM4_IRQn; 
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure2);

}


//3----����1ͨ�ţ�����Modbus-Rtu-485S
void USART1_NVIC_Config(NVIC_InitTypeDef NVIC_InitStructure4)
{
	NVIC_InitStructure4.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure4.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure4.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure4.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure4);
}


void NVIC_Config(u8 Interrupt_flag)
{

  	NVIC_InitTypeDef   NVIC_InitStructure;
	/* �����ж�ʹ�����  ��ռʽ3λ(0-7)����Ӧʽ1λ(0-1) */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

	if(Interrupt_flag == 1)
	{
		/*�ⲿ�ж�1��Z�����----���ȼ���� 0 0*/
		//PA_NVIC_Config(NVIC_InitStructure);
	
	}
	
	if(Interrupt_flag == 2)
	{	
		/*TIM4�жϣ�����������----���ȼ� 1  1*/
		TIM4_NVIC_Config(NVIC_InitStructure);
	}
	if(Interrupt_flag == 3)
	{
		/* USART1�жϣ����ݽ���----���ȼ� 2  1*/
		USART1_NVIC_Config(NVIC_InitStructure);
	}
}

