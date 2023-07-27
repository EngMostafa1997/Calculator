#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"

#define  F_CPU   8000000
#include <util/delay.h>


int main(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	
	u8 k,first_num_flag=0,operation_flag=0;
	u32 num=0,num2=0,result=0;
	while (1)
	{
		k=KEYPAD_GetKey();
		
		if(k!=NO_KEY)
		{
			if (k>='0' && k<='9')
			{
				if(first_num_flag==0)
				{
					LCD_Clear();
					first_num_flag=1;
					result=0;
					num=0;
					num2=0;
				}
				num=num*10+(k-'0');
				LCD_WriteChar(k);
			}
			else if (k=='C')
			{
				LCD_Clear();
				first_num_flag=0;
				num2=0;
				num=0;
				operation_flag=0;
			}
			else if (k=='=')
			{
				LCD_WriteChar('=');
				first_num_flag=0;
				if (operation_flag==1)
				{
					result=num2+num;
				}
				else if (operation_flag==2)
				{
					result=num2-num;
				}
				else if (operation_flag==3)
				{
					result=num2*num;
				}
				else if (operation_flag==4)
				{
					result=num2/num;
				}
				operation_flag=0;
				LCD_GoTo(1,0);
				LCD_WriteNumber(result);
			}
			else 
			{
				if (operation_flag==0)
				{
					if (first_num_flag==1)
					{
						num2=num;
						num=0;
					}
					else
					{
						num2=result;
						LCD_Clear();
						LCD_WriteNumber(result);
						first_num_flag=1;
						num=0;
					}
					if (k=='+' && operation_flag==0)
					{
						LCD_WriteChar(k);
						operation_flag=1;
					}
					else if (k=='-' && operation_flag==0)
					{
						LCD_WriteChar(k);
						operation_flag=2;
					}
					else if (k=='*' && operation_flag==0)
					{
						LCD_WriteChar(k);
						operation_flag=3;
					}
					else if (k=='/' && operation_flag==0)
					{
						LCD_WriteChar(k);
						operation_flag=4;
					}
				}
			}
		}
	}
}

