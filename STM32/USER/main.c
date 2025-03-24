#include "include.h"

/******************************************************
//	Company:深圳幻尔科技有限公司										   //	
//	我们的店铺:lobot-zone.taobao.com                  //
//	我们的官网：www.lobot-robot.com                   //
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
	/*SystemInit(); 		 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	InitDelay(72); 		 //初始化延时函数
	InitServo();		 //舵机初始化
	InitBuzzer();		 //蜂鸣器初始化
	InitLED();     			//初始化LED指示灯
	InitADC();       //ADC电池电量初始化
	InitTimer2();		 //定时器2初始化
	Usart1_Init(115200);		 //串口初始化
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
	SystemInit(); 		//系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	InitDelay(72); 		//初始化延时函数
	InitServo();			//舵机初始化
	InitBuzzer();			//蜂鸣器初始化
	InitLED();        //初始化LED指示灯
	InitADC();        //ADC电池电量初始化
	InitTimer2();			//定时器2初始化
	InitMotor();      //电机初始化
	IIC_init();		//IIC初始化
	DelayMs(100);
	Usart1_Init(115200); //串口初始化
	InitBusServoCtrl();
	DelayMs(100);//复原
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,600,1000);
	BusServoCtrl(2,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,350,1000);
	BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,100,1000);
	BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,300,1000);
	BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500,1000);
	DelayMs(1000);
	stage++;
	//抓取前后均巡线行走
	while (1){
	while(stage==1||stage==3||stage==4||stage==7||stage==9||stage==10)
		{
		u8 val;
		TaskTimeHandle();  //舵机驱动与ADC检测
		IIC_start(); //起始信号
		IIC_send_byte(0xF0); //发送写指令
		IIC_wait_ack(); //应答
		IIC_send_byte(0x01); //发送寄存器地址
		IIC_wait_ack(); //应答
		
		IIC_start(); //重新启动
		IIC_send_byte(0xF1); //发送读指令
		IIC_wait_ack(); //应答
		val = IIC_read_byte(0); //读取一个字节
		IIC_stop(); //停止
//		printf("%d%d%d%d",val & 0x01,(val>>1) & 0x01, (val>>2) & 0x01, (val>>3) & 0x01); 
//		//串口打印4个传感器的状态，串口波特率9600，1表示检测到黑线，0表示检测到白线，从左到右对应sensor1-sensor4
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
//抓取
	if(stage==2)
	{MyGrab();
	stage++;}
	
//识别释放
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
	
	//调头
	while(stage == 6)
	{
		u8 val;
		TaskTimeHandle();  //舵机驱动与ADC检测
		IIC_start(); //起始信号
		IIC_send_byte(0xF0); //发送写指令
		IIC_wait_ack(); //应答
		IIC_send_byte(0x01); //发送寄存器地址
		IIC_wait_ack(); //应答
		
		IIC_start(); //重新启动
		IIC_send_byte(0xF1); //发送读指令
		IIC_wait_ack(); //应答
		val = IIC_read_byte(0); //读取一个字节
		IIC_stop(); //停止
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

