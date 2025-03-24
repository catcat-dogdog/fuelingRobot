#include "include.h"

/******************************************************
//	Company:���ڻö��Ƽ����޹�˾										   //	
//	���ǵĵ���:lobot-zone.taobao.com                  //
//	���ǵĹ�����www.lobot-robot.com                   //
******************************************************/
extern int16_t x_pos;          
extern int16_t y_pos;          
extern int16_t z_pos;
extern int16_t a;
extern int16_t lr;

void ServoInit()
{
	BusServoCtrl(2,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,350,1000);
	BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,100,1000);
	BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,300,1000);
	BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500,1000);
	DelayMs(1000);
}

	void MyGrab()
{
	MotorControl(0, 0);
	DelayMs(1000);
	if(lr)
	{
		BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500-a/0.24,1000);
	DelayMs(1000);
	}
	else
	{BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500+a/0.24,1000);
	DelayMs(1000);}

	//BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,0,1000);
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,200,1000);
	BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,840,1000);
	MotorControl(0, 0);
	DelayMs(1000);
	DelayMs(1000);
	MotorControl(60, 60);
	DelayMs(600);
	MotorControl(0, 0);
	DelayMs(500);
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,800,1000);
	DelayMs(1000);
	ServoInit();
	MotorControl(-80,-80);
	DelayMs(300);
	MotorControl(0,0);
	
}
void MyRelease()
{
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,0,1000);
}

void replace()
{
	if(lr)
	{BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500-a/0.24,1000);
	DelayMs(1000);
	}
	else
	{BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500+a/0.24,1000);
	DelayMs(1000);}

	DelayMs(1000);
	//BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,0,1000);
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,200,1000);
	DelayMs(1000);
	MotorControl(80, 80);
	DelayMs(750);
	MotorControl(0, 0);
	DelayMs(1000);
	BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500,1000);
	DelayMs(1000);
	MotorControl(-80,-80);
	DelayMs(2000);}
int main(void)
{	
	/*SystemInit(); 		 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	InitDelay(72); 		 //��ʼ����ʱ����
	InitServo();		 //�����ʼ��
	InitBuzzer();		 //��������ʼ��
	InitLED();     			//��ʼ��LEDָʾ��
	InitADC();       //ADC��ص�����ʼ��
	InitTimer2();		 //��ʱ��2��ʼ��
	Usart1_Init(115200);		 //���ڳ�ʼ��
	InitBusServoCtrl();
	DelayMs(100);
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,300,1000);
	BusServoCtrl(2,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,350,1000);
	BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,100,1000);
	BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,300,1000);
	BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500,1000);
	DelayMs(1000);
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,0,1000);
	DelayMs(1000);
	while (1)*/
	


int stage = 0;
	SystemInit(); 		//ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	InitDelay(72); 		//��ʼ����ʱ����
	InitServo();			//�����ʼ��
	InitBuzzer();			//��������ʼ��
	InitLED();        //��ʼ��LEDָʾ��
	InitADC();        //ADC��ص�����ʼ��
	InitTimer2();			//��ʱ��2��ʼ��
	InitMotor();      //�����ʼ��
	IIC_init();		//IIC��ʼ��
	DelayMs(100);
	Usart1_Init(115200); //���ڳ�ʼ��
	InitBusServoCtrl();
	DelayMs(100);//��ԭ
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,600,1000);
	BusServoCtrl(2,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,350,1000);
	BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,100,1000);
	BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,300,1000);
	BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500,1000);
	DelayMs(1000);
	stage++;
	//ץȡǰ���Ѳ������
	while (1){
	while(stage==1||stage==3||stage==4||stage==7||stage==9||stage==10)
		{
		u8 val;
		TaskTimeHandle();  //���������ADC���
		IIC_start(); //��ʼ�ź�
		IIC_send_byte(0xF0); //����дָ��
		IIC_wait_ack(); //Ӧ��
		IIC_send_byte(0x01); //���ͼĴ�����ַ
		IIC_wait_ack(); //Ӧ��
		
		IIC_start(); //��������
		IIC_send_byte(0xF1); //���Ͷ�ָ��
		IIC_wait_ack(); //Ӧ��
		val = IIC_read_byte(0); //��ȡһ���ֽ�
		IIC_stop(); //ֹͣ
//		printf("%d%d%d%d",val & 0x01,(val>>1) & 0x01, (val>>2) & 0x01, (val>>3) & 0x01); 
//		//���ڴ�ӡ4����������״̬�����ڲ�����9600��1��ʾ��⵽���ߣ�0��ʾ��⵽���ߣ������Ҷ�Ӧsensor1-sensor4
//		printf("\n");
//		DelayMs(500);
		if ((((val>>1) & 0x01) == 0) & (((val>>2) & 0x01) == 1))
			MotorControl(80, -80);
		else if (((((val) & 0x01) == 0) & (((val>>3) & 0x01) == 1)) & ((((val>>1) & 0x01) == 0) & (((val>>2) & 0x01) == 0)))
			MotorControl(80, -80);
		else if ((((val>>1) & 0x01) == 1) & (((val>>2) & 0x01) == 0))
			MotorControl(-80, 80);
		else if (((((val) & 0x01) == 1) & (((val>>3) & 0x01) == 0)) & ((((val>>1) & 0x01) == 0) & (((val>>2) & 0x01) == 0)))
			MotorControl(-80, 80);
		else if (((val & 0x01) == 1) & (((val>>1) & 0x01) == 1) & (((val>>2) & 0x01) == 1) & (((val>>3) & 0x01) == 1))
		{
			if (stage==3||stage==9){
				MotorControl(80, 80);
				DelayMs(400);
			}
			else{
				MotorControl(0, 0);
			}
			stage++;
		}
		else if(((val & 0x01) == 0) & (((val>>1) & 0x01) == 0) & (((val>>2) & 0x01) == 0) & (((val>>3) & 0x01) == 0));
	  else
			MotorControl(80, 80);
	}
//ץȡ
	if(stage==2)
	{MyGrab();
	stage++;}
	
//ʶ���ͷ�
	if(stage==5)
	{if(lr)
	{BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500-a/0.24,1000);
	DelayMs(1000);}
	//BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,0,1000);
	else
	{BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500+(a-2)/0.24,1000);
	DelayMs(1000);
	}
	MotorControl(0, 0);
	DelayMs(1000);
	BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,800,1000);
	BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,840,1000);
	DelayMs(3000);
	MotorControl(80, 80);
	DelayMs(300);
	MotorControl(0, 0);
	/*
	BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,700,1000);
	DelayMs(1000);
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,200,1000);
	DelayMs(1000);
	*/
	DelayMs(1000);
	DelayMs(1000);
	DelayMs(1000);
	DelayMs(1000);
	DelayMs(1000);
	ServoInit();
	MotorControl(-80,-80);
	DelayMs(600);
	MotorControl(0, 0);
	DelayMs(1000);
	MotorControl(-80, 75);
	DelayMs(1000);
	stage++;
	}
	
	//��ͷ
	while(stage == 6)
	{
		u8 val;
		TaskTimeHandle();  //���������ADC���
		IIC_start(); //��ʼ�ź�
		IIC_send_byte(0xF0); //����дָ��
		IIC_wait_ack(); //Ӧ��
		IIC_send_byte(0x01); //���ͼĴ�����ַ
		IIC_wait_ack(); //Ӧ��
		
		IIC_start(); //��������
		IIC_send_byte(0xF1); //���Ͷ�ָ��
		IIC_wait_ack(); //Ӧ��
		val = IIC_read_byte(0); //��ȡһ���ֽ�
		IIC_stop(); //ֹͣ
		if ((((val>>1) & 0x01) == 1) & (((val>>2) & 0x01) == 1))
			{
				MotorControl(0, 0);
				DelayMs(1000);
				stage++;
	}	
	}

	if(stage==8)
	{
	MotorControl(0, 0);
	DelayMs(1000);
	BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,650,1000);
	DelayMs(1000);
	DelayMs(1000);
	BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,440,1000);
	BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,780,1000);
	DelayMs(1000);
	DelayMs(1000);
	MotorControl(70, 70);
	DelayMs(600);
	MotorControl(0, 0);
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,200,1000);
	DelayMs(1000);
	ServoInit();
	DelayMs(1000);
	MotorControl(-80,-80);
	DelayMs(300);
	MotorControl(0, 0);
	stage++;
	}
}
}

