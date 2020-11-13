
#include <reg51.h>
#include "lcd.h"

unsigned char first[] = " Hi!My name is ";
unsigned char name[] = "kying-star      ";
unsigned char temp[] = "1234567890123456";

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void main(void)
{
    //unsigned char i;
    P1 = 0xf0;
    InitLcd1602();
    LcdShowStr(2, 0, first);
    while (1)
    {
        ShowLoop(name, 1);
        ShowMyName(0, 1, name);
        delay1s();
    }
}