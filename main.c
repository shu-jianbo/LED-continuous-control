#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include<intrins.h>		//因为要用到左右移函数，所以加入这个头文件

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit led=P2^0;
bit DIR;
sbit P2_7=P2^7;
sbit P2_6=P2^6;
sbit P2_5=P2^5;
sbit P2_4=P2^4;
sbit P2_3=P2^3;
sbit P2_2=P2^2;
sbit P2_1=P2^1;
u8 m;
/*******************************************************************************
* 函 数 名         : 
* 函数功能		   : 
*******************************************************************************/
void UsartInit()
{
	SCON=0X50;			//串口设置为工作方式1
	
	PCON=0X80;			//波特率加倍
	TH1=0XF4;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF4;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器1
	PS=1; //设计串口中断优先级
}

void Timer0Init()
{
	
	TH0 = 0xF3; 
	TL0 = 0xf3;   //1us
	ET0=1;//打开定时器0中断允许
	TR0=1;//打开定时器0		
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{
	TMOD=0X22;			//设置计数器工作方式2
	UsartInit();  //	串口初始化	
	Timer0Init();  //定时器0初始化
	while(1);
}
void Usart() interrupt 4//串口中断
{
        u8 receiveData;
        m=SBUF;
        receiveData=SBUF;//出去接收到的数据
        RI = 0;//清除接收中断标志位
        SBUF=receiveData;//将接收到的数据放入到发送寄存器
        while(!TI);//等待发送数据完成
        TI=0;//清除发送完成标志位
}
void Time1(void) interrupt 1    //3 为定时器1的中断号  1 定时器0的中断号 0 外部中断1 2 外部中断2  4 串口中断
{
	static u8 i;
	TH0 = 0xF3;     //1us之后溢出产生溢出，计算器清零，重新赋值
	TL0 = 0xf3;   //1us
	P2=0xff;
	i++;
	if(i<m*0x46)
	{
		led=0;
	}
	else led=1;
	if(i==0x10*0x46)
	{
		i=0;
	}
	if(m==0x01)
	{
		P2_7=0;
	}
	if(m==0x02)
	{
		P2_7=0;P2_6=0;
	}
	if(m==0x03)
	{
		P2_7=0;P2_6=0;P2_5=0;
	}
	if(m==0x04)
	{
		P2_7=0;P2_6=0;P2_5=0;P2_4=0;
	}
	if(m==0x05)
	{
		P2_7=0;P2_6=0;P2_5=0;P2_4=0;P2_3=0;
	}
	if(m==0x06)
	{
		P2_7=0;P2_6=0;P2_5=0;P2_4=0;P2_3=0;P2_2=0;
	}
	if(m==0x07)
	{
		P2_7=0;P2_6=0;P2_5=0;P2_4=0;P2_3=0;P2_2=0;P2_1=0;
	}
}
