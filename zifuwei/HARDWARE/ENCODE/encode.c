#include "stm32f10x.h"
#include "encode.h"
#include "misc.h"
#include "nvic.h"
#include "sys.h" 
#include "delay.h"

void TIM4_Mode_Config(void)//�������ӿ����ã�TIM4��/PB6-A��  PB7-B��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;   	

	//PB6 ch1  A,PB7 ch2 
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 //	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIOB����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);  //ʹ��GPIOD����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
	
	GPIO_StructInit(&GPIO_InitStructure);//��GPIO_InitStruct�еĲ�����ȱʡֵ����
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //����Ϊ��������ģʽ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //IO�ڵ�����Ϊ50M 
	//GPIO_Init(GPIOB, &GPIO_InitStructure);				   //IO�����ú���
	//GPIO_WriteBit(GPIOB, GPIO_Pin_6,Bit_SET);
	//GPIO_WriteBit(GPIOB, GPIO_Pin_7,Bit_SET);  
    GPIO_Init(GPIOD, &GPIO_InitStructure);				   //IO�����ú���
	  GPIO_WriteBit(GPIOD, GPIO_Pin_12,Bit_SET);
	  GPIO_WriteBit(GPIOD, GPIO_Pin_13,Bit_SET);  

	NVIC_Config(2);

	TIM_DeInit(TIM4);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 500*4;  //�趨��������װֵ   TIMx_ARR = 359*4
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //TIM3ʱ��Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;//����ʱ�ӷָ� T_dts = T_ck_int	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ��� 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              
                 
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);//ʹ�ñ�����ģʽ3�������½�������
	TIM_ICStructInit(&TIM_ICInitStructure);//���ṹ���е�����ȱʡ����
	TIM_ICInitStructure.TIM_ICFilter = 6;  //ѡ������Ƚ��˲��� 
	TIM_ICInit(TIM4, &TIM_ICInitStructure);//��TIM_ICInitStructure�е�ָ��������ʼ��TIM4
	
//	TIM_ARRPreloadConfig(TIM4, ENABLE);//ʹ��Ԥװ��
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM4�ĸ��±�־λ
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//���и����ж�
	//Reset counter
	TIM4->CNT = 0;//

	TIM_Cmd(TIM4, ENABLE);   //����TIM4��ʱ��

}
/*	
void TIM3_Mode_Config(void)
{
	///TIM3 clock source enable 
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��
	// Enable 1GPIOA, clock 
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��

	// Configure PA.06,07 as encoder input 
	GPIOA->CRL&=0XF0FFFFFF;//PA6
	GPIOA->CRL|=0X04000000;//��������
	GPIOA->CRL&=0X0FFFFFFF;//PA7
	GPIOA->CRL|=0X40000000;//��������

	// Enable the TIM3 Update Interrupt 
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM3->DIER|=1<<0;   //��������ж�				
	TIM3->DIER|=1<<6;   //�������ж�
	
	TIM3_NVIC_Config();
	

	//Timer configuration in Encoder mode 
	TIM3->PSC = 0x0;//Ԥ��Ƶ��
	TIM3->ARR = 15-1;//�趨�������Զ���װֵ 
	TIM3->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM3->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
		
	TIM3->CCMR1 |= 1<<0; //CC1S='01' IC1FP1ӳ�䵽TI1
	TIM3->CCMR1 |= 1<<8; //CC2S='01' IC2FP2ӳ�䵽TI2
	TIM3->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	TIM3->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2
	TIM3->CCMR1 |= 3<<4; //	IC1F='1000' ���벶��1�˲���
	TIM3->SMCR |= 3<<0;	 //SMS='011' ���е�������������غ��½�����Ч
	TIM3->CNT = 0;
	TIM3->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��

}*/

void TIM4_Init(void)
{
  TIM4_Mode_Config();
}
