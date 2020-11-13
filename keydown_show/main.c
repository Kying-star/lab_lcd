#include <reg51.h>
#include "lcd.h"
unsigned char Key_Value[] = "The key value is";
unsigned char Value[] = "The key value is";
unsigned char word[] = "                ";
unsigned int i = 0;
/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void main(void)
{
	P1 &= 0xf0;		 //屏蔽低四位，让控制数码管的4个位选开关截止
	InitLcd1602(); //初始化1602
	LcdShowStr(0, 0, Key_Value);
	while (1)
	{
		KeyDown();
		LcdShowStr(0, 1, word);
		if (i >= 17)
		{
			i = 0;
			clear(word);
		}
	}
}

void KeyDown()
{
	u8 KeyValue = 17; //用来存放读取到的键值
	char a;
	GPIO_KEY = 0x0f;
	if (GPIO_KEY != 0x0f) //读取按键是否按下
	{
		delay(1000);					//延时10ms进行消抖
		if (GPIO_KEY != 0x0f) //再次检测键盘是否按下
		{
			//测试列
			GPIO_KEY = 0X0F;
			switch (GPIO_KEY)
			{
			case (0X07):
				KeyValue = 0;
				break;
			case (0X0b):
				KeyValue = 4;
				break;
			case (0X0d):
				KeyValue = 8;
				break;
			case (0X0e):
				KeyValue = 12;
				break;
			}
			//测试行
			GPIO_KEY = 0XF0;
			switch (GPIO_KEY)
			{
			case (0X70):
				KeyValue = KeyValue;
				break;
			case (0Xb0):
				KeyValue = KeyValue + 1;
				break;
			case (0Xd0):
				KeyValue = KeyValue + 2;
				break;
			case (0Xe0):
				KeyValue = KeyValue + 3;
				break;
			}
			while ((a < 50) && (GPIO_KEY != 0xf0)) //检测按键松手检测
			{
				delay(1000);
				a++;
			}
		}
		word[i++] = getvalue(KeyValue);
	}
}
