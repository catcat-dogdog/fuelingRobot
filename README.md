# README

该项目使用 OpenMV 和 STM32 两部分硬件和程序代码实现机械臂的自动抓取和释放功能。以下是具体的项目介绍与代码结构说明。

## OpenMV

OpenMV部分`FuelingRobot`负责图像识别和处理，主要通过 `find_apriltags` 函数检测目标，并计算目标的姿态信息（如位置和旋转角度），通过串口发送信息。
openMV
│  FuelingRobot.py        # 处理OpenMV视觉信息并控制加油操作
│
└─test                    # OpenMV 相关的测试代码

### STM32

STM32 部分控制机械臂的抓取与释放动作，通过串口接收来自 OpenMV 的控制信息，根据位置和角度调整机械臂的位置。根据传感器信息进行自动导航。。
STM32
├─CORE                    # STM32核心调度代码
├─STM32F10x_FWLib         # STM32F10x 官方固件库
└─USER                    # 用户代码
    │  ADC.c              # 模数转换（ADC）读取传感器数据
    │  BusServoCtrl.c     # 总线舵机控制
    │  Delay.c            # 延时函数库
    │  IIC.c              # I2C 通信接口
    │  include.h          # 公共头文件，包含宏定义和全局变量
    │  main.c             # 主程序，系统初始化与主循环
    │  Motor.c            # 电机控制
    │  MyTime.c           # 时间管理模块（定时任务/计时）
    │  Servo.c            # 舵机控制（机械臂或运动部件）
    │  Usart.c            # 串口通信（与上位机或其他设备通信）
