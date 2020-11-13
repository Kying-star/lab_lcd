#include <reg51.h>
#include "lcd.h"
unsigned char Key_Value[] = "The key value is";
unsigned char Value[] = "The key value is";
unsigned char word[] = "                ";
unsigned int i = 0;
/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void main(void)
{
	P1 &= 0xf0;		 //���ε���λ���ÿ�������ܵ�4��λѡ���ؽ�ֹ
	InitLcd1602(); //��ʼ��1602
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
	u8 KeyValue = 17; //������Ŷ�ȡ���ļ�ֵ
	char a;
	GPIO_KEY = 0x0f;
	if (GPIO_KEY != 0x0f) //��ȡ�����Ƿ���
	{
		delay(1000);					//��ʱ10ms��������
		if (GPIO_KEY != 0x0f) //�ٴμ������Ƿ���
		{
			//������
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
			//������
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
			while ((a < 50) && (GPIO_KEY != 0xf0)) //��ⰴ�����ּ��
			{
				delay(1000);
				a++;
			}
		}
		word[i++] = getvalue(KeyValue);
	}
}
