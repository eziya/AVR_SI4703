/*
 * SI4703.c
 *
 * Created: 2018-05-29 오후 9:13:44
 * Author : kiki
 */ 

#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "SI4703.h"
#include "128A_USART.h"

#define PRESET1	89.9
#define PRESET2	105.7
#define PRESET3	95.7
#define PRESET4	97.5
#define PRESET5	101.5

uint8_t rcvCmd = 0;
char msg[150];

int main(void)
{	
	USART0_Init();	
	
	if(!SI4703_Init())
	{
		memset(msg, 0, sizeof(msg));
		sprintf(msg, "SI4703_Init failed.\r\n");
		USART0_TxBuffer((uint8_t *)msg, strlen(msg));		
		
		while(1)
		{
			
		}
	}
	else
	{
		memset(msg, 0, sizeof(msg));
		sprintf(msg, "SI4703_Init succeeded.\r\n");
		USART0_TxBuffer((uint8_t *)msg, strlen(msg));	
	}	
	
    /* Replace with your application code */
    while (1) 
    {
		if(USART0_RxByte(&rcvCmd))
		{
			if(rcvCmd == '+')
			{
				if(!SI4703_SeekUp())
				{
					memset(msg, 0, sizeof(msg));
					sprintf(msg, "SI4703_SeekUp failed.\r\n");
					USART0_TxBuffer((uint8_t *)msg, strlen(msg));
				}
			}
			else if(rcvCmd == '-')
			{
				if(!SI4703_SeekDown())
				{
					memset(msg, 0, sizeof(msg));
					sprintf(msg, "SI4703_SeekDown failed.\r\n");
					USART0_TxBuffer((uint8_t *)msg, strlen(msg));
				}
			}
			else if(rcvCmd == '=')
			{								
				if(SI4703_UpdateRadioInfo())
				{
					memset(msg, 0, sizeof(msg));
					sprintf(msg, "Freq: [%f], RDS Ready: [%d], Stereo: [%d], RSSI: [%d], Band limit: [%d]\r\n",
					(0.2 * radioInfo.ReadChannel) + 87.5, radioInfo.RDSReady, radioInfo.Stereo, radioInfo.RSSI, radioInfo.SeekFailBandLimit);
					USART0_TxBuffer((uint8_t *)msg, strlen(msg));
				}
			}
			else if(rcvCmd == '1')
			{
				if(!SI4703_SetFreq(PRESET1))
				{
					memset(msg, 0, sizeof(msg));
					sprintf(msg, "SI4703_SetFreq(PRESET1) failed.\r\n");
					USART0_TxBuffer((uint8_t *)msg, strlen(msg));
				}
			}
			else if(rcvCmd == '2')
			{
				if(!SI4703_SetFreq(PRESET2))
				{
					memset(msg, 0, sizeof(msg));
					sprintf(msg, "SI4703_SetFreq(PRESET2) failed.\r\n");
					USART0_TxBuffer((uint8_t *)msg, strlen(msg));
				}
			}
			else if(rcvCmd == '3')
			{
				if(!SI4703_SetFreq(PRESET3))
				{
					memset(msg, 0, sizeof(msg));
					sprintf(msg, "SI4703_SetFreq(PRESET3) failed.\r\n");
					USART0_TxBuffer((uint8_t *)msg, strlen(msg));
				}
			}
			else if(rcvCmd == '4')
			{
				if(!SI4703_SetFreq(PRESET4))
				{
					memset(msg, 0, sizeof(msg));
					sprintf(msg, "SI4703_SetFreq(PRESET4) failed.\r\n");
					USART0_TxBuffer((uint8_t *)msg, strlen(msg));
				}
			}
			else if(rcvCmd == '5')
			{
				if(!SI4703_SetFreq(PRESET5))
				{
					memset(msg, 0, sizeof(msg));
					sprintf(msg, "SI4703_SetFreq(PRESET5) failed.\r\n");
					USART0_TxBuffer((uint8_t *)msg, strlen(msg));
				}
			}
		}
    }
}

