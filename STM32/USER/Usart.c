#include "include.h"
#include "Usart.h"

#pragma import(__use_no_semihosting)    

int openmv[6];//stm32??????
int16_t x_pos;          
int16_t y_pos;          
int16_t z_pos;
int16_t a;
int16_t lr;
int i;

//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
///重定义printf到USART1
int fputc(int ch, FILE *f)
{
USART_SendData(USART1, (uint8_t) ch);
while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
return (ch);
}


void Usart1_Init(uint32_t Bound)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
  	
	USART_InitStructure.USART_BaudRate = Bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1,&USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
}
 
void Openmv_Data(void)//??Openmv?????
{
	lr =openmv[2];
  a =openmv[3];
	z_pos =openmv[4];
}
 
void Openmv_Receive_Data(int16_t data)//??Openmv??????
{
	static u8 state = 0;
	if(state==0&&data==0xb3)//?????
	{
		state=1;
		openmv[0]=data;
	}
	else if(state==1&&data==0xb3)//?????
	{
		state=2;
		openmv[1]=data;
	}
	else if(state==2)//???????
	{
		state=3;
		openmv[2]=data;
	}
	else if(state==3)//???????
	{
		state = 4;
		openmv[3]=data;
	}
  else if(state==4)//???????
	{
		state = 5;
		openmv[4]=data;
	} 
	else if(state==5)		//???????????,??????
	{
        if(data == 0x5B)
        {
            state = 0;
            openmv[5]=data;
            Openmv_Data();
        }
        else if(data != 0x5B)
        {
            state = 0;
            for(i=0;i<6;i++)
            {
                openmv[i]=0x00;
            }           
        }
	}    
	else
		{
			state = 0;
            for(i=0;i<6;i++)
            {
                openmv[i]=0x00;
            }
		}
}
 
 
void USART_SendByte(USART_TypeDef* USARTx, char  str)
{
 
		USART_SendData(USARTx, str);//??????
 
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);//????????
 
	
 
}
 
 
 
void USART1_IRQHandler(void)                	//??1??????
	{
	u8 com_data;
#if SYSTEM_SUPPORT_OS 		//??SYSTEM_SUPPORT_OS??,?????OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //????(?????????0x0d 0x0a??)
		{
			USART_ClearFlag(USART1,USART_FLAG_RXNE);
      com_data = USART1->DR;
			Openmv_Receive_Data(com_data);     //openmv??????
			Openmv_Data();		                 //openmv??????		
 		
     } 
#if SYSTEM_SUPPORT_OS 	//??SYSTEM_SUPPORT_OS??,?????OS.
	OSIntExit();  											 
#endif
} 
