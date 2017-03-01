/******************** ********************

 * Ӳ�����ӣ�------------------------
 *          | PB10  - USART3(Tx)      |
 *          | PB11 - USART3(Rx)      |
 *           ------------------------

**********************************************************************************/

#include "usart1.h"
#include "usart.h"	 
#include <stdarg.h>
/*RE��GPIOC5�ܽ�����*/   

u8  USART_RX_BUF[USART_REC_LEN]; 
extern int k;
extern int j;
extern u16 Len[12],set_length;
extern float error_sum;
u16 RX[300]={0};
u16 w=0;


void UART3Test(void);

void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* ʹ�� USART1 ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ������ʱ��
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//ʹ������ʱ��	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//ʹ������ʱ��	
	
	
	
	
  //GPIOB10 USART3_Tx
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             //�������
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  //GPIOB11 USART3_Rx
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
/*
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		//GPIO_SetBits(GPIOC,GPIO_Pin_5);			
		//GPIO_SetBits(GPIOC,GPIO_Pin_4);			
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
    GPIO_Init(GPIOC, &GPIO_InitStructure);*/
		
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		
		GPIO_ResetBits(GPIOC,GPIO_Pin_15);
    GPIO_Init(GPIOE, &GPIO_InitStructure);
		
		
		
  	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; 
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	  NVIC_Init(&NVIC_InitStructure);
		
  USART_InitStructure.USART_BaudRate = 115200;            //ֻ�޸Ĳ�����
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  //���ڳ�ʼ��
  USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  //ʹ��USART3
  USART_Cmd(USART3, ENABLE);
}

 /*����һ���ֽ�����*/
 void UART3SendByte(unsigned char SendData)
{	   
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
}  

/*����һ���ֽ�����*/
unsigned char UART3GetByte(unsigned char* GetData)
{   	   
        if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
        {  return 0;//û���յ����� 
		}
        *GetData = USART_ReceiveData(USART3); 
        return 1;//�յ�����
}
/*����һ�����ݣ����Ϸ��ؽ��յ����������*/
void UART3Test(void)
{
       unsigned char i = 0;

       while(1)
       {    
		 while(UART3GetByte(&i))
        {
         USART_SendData(USART3,i);
        }      
       }     
}


void USART3_IRQHandler(void)                	//����3�жϷ������
{
        if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
				{;}

          USART_RX_BUF[k] = USART_ReceiveData(USART3);
					Len[k]=USART_RX_BUF[k];
					k++;
					if(k==12)//��ȡ�ȳ���������Ϊһ���ȳ����ݣ�0��1��Ϊ1�Ŵӻ�����j=0��2��3Ϊ2�Ŵӻ�����j=2�����Σ�����
					{
						set_length=Len[j]<<8;
						j++;
						set_length=set_length|Len[j];
					  j=0;
						k=0;
						//RX[w++]=set_length;
						//if(w>=300)
						//	w=0;
						if(set_length>=400)
							set_length=400;
						if(set_length<=260)
							set_length=260;
						//error_sum=0;
					}	
					
					


} 






