/*
 * @Description: 
 * @Version: 0.0
 * @Autor: 林其星
 * @Date: 2020-11-12 15:24:46
 * @LastEditors: kyingstar
 * @LastEditTime: 2020-11-12 20:38:01
 */
#include "lcd.h"
#include <string.h>
#include <intrins.h>
/**
 * @description:  延时函数
 * @param {*}
 * @return {*}
 * @author: 林其星
 */

void delay300ms(void) //误差 0us
{
  unsigned char a, b, c;
  for (c = 123; c > 0; c--)
    for (b = 116; b > 0; b--)
      for (a = 9; a > 0; a--)
        ;
}

void delay1s(void) //误差 0us
{
  unsigned char a, b, c;
  for (c = 167; c > 0; c--)
    for (b = 171; b > 0; b--)
      for (a = 16; a > 0; a--)
        ;
  _nop_(); //if Keil,require use intrins.h
}

void Read_Busy() //忙检测函数，判断bit7是0，允许执行；1禁止
{
  unsigned char sta; //
  LCD1602_DB = 0xff;
  LCD1602_RS = 0;
  LCD1602_RW = 1;
  do
  {
    LCD1602_EN = 1;
    sta = LCD1602_DB;
    LCD1602_EN = 0; //使能，用完就拉低，释放总线
  } while (sta & 0x80);
}

void Lcd1602_Write_Cmd(unsigned char cmd) //写命令
{
  Read_Busy();
  LCD1602_RS = 0;
  LCD1602_RW = 0;
  LCD1602_DB = cmd;
  LCD1602_EN = 1;
  LCD1602_EN = 0;
}

void Lcd1602_Write_Data(unsigned char dat) //写数据
{
  Read_Busy();
  LCD1602_RS = 1;
  LCD1602_RW = 0;
  LCD1602_DB = dat;
  LCD1602_EN = 1;
  LCD1602_EN = 0;
}

void LcdSetCursor(unsigned char x, unsigned char y) //坐标显示
{
  unsigned char addr;
  if (y == 0)
    addr = 0x00 + x;
  else
    addr = 0x40 + x;

  Lcd1602_Write_Cmd(addr | 0x80);
}

void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str) //显示字符串
{
  LcdSetCursor(x, y); //当前字符的坐标
  while (*str != '\0')
  {
    Lcd1602_Write_Data(*str++);
  }
}

void ShowMyName(unsigned char x, unsigned char y, unsigned char *str) //显示字符串
{
  LcdSetCursor(x, y); //当前字符的坐标
  while (*str != '\0')
  {
    Lcd1602_Write_Data(*str++);
    //delay300ms();
  }
}

void InitLcd1602() //1602初始化
{
  Lcd1602_Write_Cmd(0x38); //打开，5*8,8位数据
  Lcd1602_Write_Cmd(0x0c);
  Lcd1602_Write_Cmd(0x06);
  Lcd1602_Write_Cmd(0x01); //清屏
}

/**
 * @description: 循环显示
 * @param {*}
 * @return {*}
 * @author: 林其星
 */

void ShowLoop(unsigned char *str, unsigned int drift)
{
  unsigned char temp[16];
  unsigned int i;
  for (i = 0; i < 16; i++)
  {
    temp[i] = str[i];
  }
  for (i = 0; i < 16; i++)
  {
    str[i] = temp[(i + drift) % 16];
  }
}