#ifndef __LCD_H_
#define __LCD_H_
/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
#define LCD1602_4PINS

/**********************************
����ͷ�ļ�
**********************************/
#include <reg51.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

/**********************************
PIN�ڶ���
**********************************/
#define LCD1602_DB P0 //data bus ��������
#define GPIO_DIG P0
#define GPIO_KEY P1
sbit LCD1602_RS = P2 ^ 6;
sbit LCD1602_RW = P2 ^ 5;
sbit LCD1602_EN = P2 ^ 7;
typedef unsigned int u16; //���������ͽ�����������
typedef unsigned char u8;
/**********************************
��������
**********************************/
/*��51��Ƭ��12MHZʱ���µ���ʱ����*/
void Lcd1602_Delay1ms(uint c); //��� 0us
void delay(u16 i);
void Read_Busy();                                                      //æ��⺯�����ж�bit7��0������ִ�У�1��ֹ
void Lcd1602_Write_Cmd(unsigned char cmd);                             //д����
void Lcd1602_Write_Data(unsigned char dat);                            //д����
void LcdSetCursor(unsigned char x, unsigned char y);                   //������ʾ
void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str); //��ʾ�ַ���
void InitLcd1602();
void KeyDown(); //1602��ʼ��
unsigned char getvalue(unsigned char Key);
void clear(unsigned char *str);
#endif
