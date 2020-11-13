#include "lcd.h"

/**
 * @description: 10ms延时函数
 * @author: 林其星
 */
void delay10ms(void) //误差 0us
{
    unsigned char a, b, c;
    for (c = 1; c > 0; c--)
        for (b = 38; b > 0; b--)
            for (a = 130; a > 0; a--)
                ;
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

void InitLcd1602() //1602初始化
{
    Lcd1602_Write_Cmd(0x38); //打开，5*8,8位数据
    Lcd1602_Write_Cmd(0x0c);
    Lcd1602_Write_Cmd(0x06);
    Lcd1602_Write_Cmd(0x01); //清屏
}

/**
 * @description: 监听键盘按下事件
 * @param {*}
 * @return {*}
 * @author: 林其星
 */

unsigned char getvalue(unsigned char Key)
{
    switch (Key)
    {
    case 0:
        return '1';
        break;
    case 4:
        return '2';
        break;
    case 8:
        return '3';
        break;
    case 12:
        return '/';
        break;
    case 1:
        return '4';
        break;
    case 5:
        return '5';
        break;
    case 9:
        return '6';
        break;
    case 13:
        return '&';
        break;
    case 2:
        return '7';
        break;
    case 6:
        return '8';
        break;
    case 10:
        return '9';
        break;
    case 14:
        return '@';
        break;
    case 3:
        return '*';
        break;
    case 7:
        return '0';
        break;
    case 11:
        return '#';
        break;
    case 15:
        return '=';
        break;
    default:
        return '+';
        break;
    }
}

void clear(unsigned char *str)
{
    unsigned int i;
    for (i = 0; i < 16; i++)
    {
        str[i] = ' ';
    }
}

void delay(u16 i)
{
    while (i--)
        ;
}