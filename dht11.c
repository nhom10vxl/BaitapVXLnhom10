#include<reg51.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "LCD.h"
#include "dht.h"

#define max_Hum 80.00	
#define min_Hum 20.00	
#define max_Temp 40.00
#define min_Temp 10.00
unsigned char dat[20];

int count = 0;
sbit bom = P2^1;
sbit button = P2^2;
void main()
{
	LCD_Init();
	 
	
	
			/* initialize LCD */
	  
	while(1)
	{	
	 	Request();	/* send start pulse */
		Response();	/* receive response */
		
		I_RH=Receive_data();	/* store first eight bit in I_RH */	  // phan nguyen
		D_RH=Receive_data();	/* store next eight bit in D_RH */	  // phan thap phan
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */
	//	if((I_Temp +D_Temp) < min_Temp && (I_RH +D_RH) > max_Hum ){
	//		bom = 0;
	//	}
		if(((I_Temp +D_Temp) > max_Temp && (I_RH +D_RH) > max_Hum) || ((I_Temp +D_Temp) < min_Temp && (I_RH +D_RH) > max_Hum) ){
			bom = 0;
		}
		else{
			bom = 1;
		}
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			LCD_String_xy(0,0,"Error");
		}
		
		else
		{
			sprintf(dat,"Hum = %d.%d",I_RH,D_RH);
			LCD_String_xy(0,0,dat);
			LCD_String("%");
			sprintf(dat,"Tem = %d.%d",I_Temp,D_Temp);   
			LCD_String_xy(1,0,dat);
			LCD_Char(0xDF);
			LCD_String("C");

		}		
		


	/*	if(button == 0){
			delay(10);
			if(button == 0){
				while(button == 0);
				count++;
				if(count == 2){
					count = 0;
				}
			}
		}	   
		bom = count;*/	   
	}	
}