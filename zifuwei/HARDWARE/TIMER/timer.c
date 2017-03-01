#include "timer.h"
#include "led.h"
#include "key.h"


int CNT_last=0,CNT_temp=0,PVcount=0,PPVcount=0;//���������� 
float Vcount=0,count=0;//���������� 

extern  int rcnt4;
extern void UserMotorSpeedSetOne();

float Kp=0.6,Ki=0.00005,Kd=0,I=0;

u16 d0=4,Length=0;//d0Ϊ���� 4����
u16 Length0=245;//��ʼ����
u16 set_length=312;//���ó���//312
u16 pi=180;//piΪ��

float error=0,error_pre=0,error_last=0,error_sum=0,derror=0;//
s32 the_last=0,the=0,set_the=0;
s32 out_old=0,out_new=0;
u16 Len[12]={0};
int q=0;

u16 setFlag=0;

u16 r=0;
u16 m=0;
u16 ready_Flag=0;
u16 protec_Flag=0;
u16 start_Flag=0;
u16 move_Flag=0;

u16 qk=0;
int sine_table[500]={
0,51,102,154,205,257,308,359,411,462,513,564,615,666,716,767,818,868,918,968,
1018,1068,1118,1167,1216,1265,1314,1363,1411,1459,1507,1555,1603,1650,1697,1743,1790,1836,1882,1928,
1973,2018,2062,2107,2151,2194,2238,2280,2323,2365,2407,2449,2490,2530,2571,2610,2650,2689,2727,2766,
2803,2841,2878,2914,2950,2985,3020,3055,3089,3122,3156,3188,3220,3252,3283,3313,3343,3373,3402,3430,
3458,3485,3512,3538,3564,3589,3613,3637,3661,3683,3706,3727,3748,3769,3789,3808,3827,3845,3862,3879,
3895,3911,3926,3940,3954,3967,3979,3991,4002,4013,4023,4032,4041,4049,4056,4063,4069,4075,4080,4084,
4087,4090,4093,4094,4095,4096,4095,4094,4093,4090,4087,4084,4080,4075,4069,4063,4056,4049,4041,4032,
4023,4013,4002,3991,3979,3967,3954,3940,3926,3911,3895,3879,3862,3845,3827,3808,3789,3769,3748,3727,
3706,3683,3661,3637,3613,3589,3564,3538,3512,3485,3458,3430,3402,3373,3343,3313,3283,3252,3220,3188,
3156,3122,3089,3055,3020,2985,2950,2914,2878,2841,2803,2766,2727,2689,2650,2610,2571,2530,2490,2449,
2407,2365,2323,2280,2238,2194,2151,2107,2062,2018,1973,1928,1882,1836,1790,1743,1697,1650,1603,1555,
1507,1459,1411,1363,1314,1265,1216,1167,1118,1068,1018,968,918,868,818,767,716,666,615,564,
513,462,411,359,308,257,205,154,102,51,-0,-51,-102,-154,-205,-257,-308,-359,-411,-462,
-513,-564,-615,-666,-716,-767,-818,-868,-918,-968,-1018,-1068,-1118,-1167,-1216,-1265,-1314,-1363,-1411,-1459,
-1507,-1555,-1603,-1650,-1697,-1743,-1790,-1836,-1882,-1928,-1973,-2018,-2062,-2107,-2151,-2194,-2238,-2280,-2323,-2365,
-2407,-2449,-2490,-2530,-2571,-2610,-2650,-2689,-2727,-2766,-2803,-2841,-2878,-2914,-2950,-2985,-3020,-3055,-3089,-3122,
-3156,-3188,-3220,-3252,-3283,-3313,-3343,-3373,-3402,-3430,-3458,-3485,-3512,-3538,-3564,-3589,-3613,-3637,-3661,-3683,
-3706,-3727,-3748,-3769,-3789,-3808,-3827,-3845,-3862,-3879,-3895,-3911,-3926,-3940,-3954,-3967,-3979,-3991,-4002,-4013,
-4023,-4032,-4041,-4049,-4056,-4063,-4069,-4075,-4080,-4084,-4087,-4090,-4093,-4094,-4095,-4096,-4095,-4094,-4093,-4090,
-4087,-4084,-4080,-4075,-4069,-4063,-4056,-4049,-4041,-4032,-4023,-4013,-4002,-3991,-3979,-3967,-3954,-3940,-3926,-3911,
-3895,-3879,-3862,-3845,-3827,-3808,-3789,-3769,-3748,-3727,-3706,-3683,-3661,-3637,-3613,-3589,-3564,-3538,-3512,-3485,
-3458,-3430,-3402,-3373,-3343,-3313,-3283,-3252,-3220,-3188,-3156,-3122,-3089,-3055,-3020,-2985,-2950,-2914,-2878,-2841,
-2803,-2766,-2727,-2689,-2650,-2610,-2571,-2530,-2490,-2449,-2407,-2365,-2323,-2280,-2238,-2194,-2151,-2107,-2062,-2018,
-1973,-1928,-1882,-1836,-1790,-1743,-1697,-1650,-1603,-1555,-1507,-1459,-1411,-1363,-1314,-1265,-1216,-1167,-1118,-1068,
-1018,-968,-918,-868,-818,-767,-716,-666,-615,-564,-513,-462,-411,-359,-308,-257,-205,-154,-102,-51,
};








//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
 		//�ж����ȼ�NVIC����
 	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
 
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			

		/*
			q++;
			
						if(q<=800)
			{
					TIM8->CCR1 = 6480; //PC6   PWMB    //����
          TIM8->CCR2 = 7128; //PC7   PWMA

			}

			
			else if(q>800&&q<850)
			{		setFlag=1;
				set_length=260;
			}
			else if(q>=850&&q<900)
			{
				set_length=270;
				error_sum=0;
			}
			else if(q>=900&&q<950)
			{	
				set_length=280;
				error_sum=0;
			}
			else if(q>=950&&q<1000)
			{	
				set_length=290;
				error_sum=0;

			}
				if(q>=1000)
				q=801;
				*/


	if(ready_Flag==0&&start_Flag==0)
	{
	 	TIM8->CCR1 = 3400; //PC6   PWMB    //����
    TIM8->CCR2 = 3528; //PC7   PWMA
		
		if(XW_B==0)
			r++;
		if(r>=10)
		{
			start_Flag=1;
			ready_Flag=1;
			r=0;
		}
		
	}
	
				if(start_Flag==1&&move_Flag==0)
			{		r++;
				if(r>=5000)
				{	
					move_Flag=1;
					r=5000;
					rcnt4=0;
					TIM4->CNT=0;
				}
			}	
			
			if(move_Flag==1&&protec_Flag==0)
			{
				m++;
				if(m>=5000)
				{
					protec_Flag=1;
					m=5000;
					setFlag=1;

				}
			
			
			}
	
	/*
	if(setFlag==0)
	{
		q++;
		set_length=312;
		
		
		if(q>=5000)
		{
			q=0;
			setFlag=1;
		}
	}
	
*/
	
	
	if(setFlag==1)
	{
		q++;
	if(q>=20)
	{
		q=0;

		set_length=sine_table[qk]/4096.0*60+312;
		error_sum=0;
				qk++;
		if(qk>=501)
			qk=0;
	}
	
}
	
	
				if(move_Flag==1)
			{
	
	
	
				CNT_temp = rcnt4 * 2000 + TIM4->CNT;  //200 *4?
        count = CNT_temp - CNT_last;		
			  CNT_last = CNT_temp;
        
			
    		Vcount = count/4;//��ȡ����ֵ



				
				
			//the=2*pi*Vcount/500+the_last;
			//the_last=the;
			the=2*pi*CNT_temp/2000;
			Length=set_length-Length0;
			set_the=Length*6*pi/d0;
	 		
		//	error=set_the+the;
		//out_old=Kp*(error-error_last)+Ki*error+Kd*(error-2*error_last+error_pre);
		//out_new += out_old;
			
		//	error_pre=error_last;
		//	error_last=error;
			
			error=set_the+the;
			error_sum+=error;
			derror=error-error_last;
			error_last=error;
			I=Ki*error_sum;
			if(I>3600)
				I=3600;
			if(I<-3600)
			  I=-3600;
			
			if(error<250&&error>-250)
			{	
				I=0;
				error_sum=0;
			}
			out_new=Kp*error+I+Kd*derror;
			
			
			UserMotorSpeedSetOne(); 
			}  
/*
						q++;
			if(q>=400)
			{
					TIM8->CCR1 = 3400; //PC6   PWMB    //����
          TIM8->CCR2 = 3528; //PC7   PWMA
				if(q>=800)
					q=0;
			}
			else
			{
				  //TIM8->CCR1 = 3528; //PC6   PWMB  //ǰ��
          //TIM8->CCR2 = 3400; //PC7   PWMA
			}			
			
		*/
		
		
		
		
		
		

			
	if(protec_Flag==1)
	{			
						//�������
     if(FAULT==0||OTW==0||XW_A==0||XW_B==0)
		 {
			// if(XW_A==0)
			// {
			//	 	TIM8->CCR1 = 3400; //PC6   PWMB    //����
      //    TIM8->CCR2 = 3528; //PC7   PWMA
			// }
				 
			// else
			 //{	
				  TIM8->CCR1 = 3528;   
          TIM8->CCR2 = 3528; 
			  	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
			// }	
		 }
			
	 }
       // TIM_Cmd(TIM4, ENABLE);
 }
			
		
}












