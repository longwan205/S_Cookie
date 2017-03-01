/******************** ********************

 * 硬件连接：------------------------
 *          | PB10  - USART3(Tx)      |
 *          | PB11 - USART3(Rx)      |
 *           ------------------------

**********************************************************************************/

#include "usart1.h"
#include "usart.h"	 
#include <stdarg.h>
/*RE跟GPIOC5管脚相连*/   

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

	/* 使能 USART1 时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能外设时钟
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//使能外设时钟	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//使能外设时钟	
	
	
	
	
  //GPIOB10 USART3_Tx
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             //推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  //GPIOB11 USART3_Rx
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //浮动输入
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
		
  USART_InitStructure.USART_BaudRate = 115200;            //只修改波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  //串口初始化
  USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  //使能USART3
  USART_Cmd(USART3, ENABLE);
}

 /*发送一个字节数据*/
 void UART3SendByte(unsigned char SendData)
{	   
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
}  

/*接收一个字节数据*/
unsigned char UART3GetByte(unsigned char* GetData)
{   	   
        if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
        {  return 0;//没有收到数据 
		}
        *GetData = USART_ReceiveData(USART3); 
        return 1;//收到数据
}
/*接收一个数据，马上返回接收到的这个数据*/
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


void USART3_IRQHandler(void)                	//串口3中断服务程序
{
        if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
				{;}

          USART_RX_BUF[k] = USART_ReceiveData(USART3);
					Len[k]=USART_RX_BUF[k];
					k++;
					if(k==12)//读取腿长，读两次为一个腿长数据，0，1，为1号从机，令j=0；2，3为2号从机，令j=2；依次，，，
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






