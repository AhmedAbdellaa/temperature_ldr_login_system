/*
 * main.c
 *
 *  Created on: Jun 4, 2023
 *      Author: ahmed
 */

#include <util/delay.h>

#include "libraries/STD_TYPES_H.h"
#include "0-MCAL/1-DIO/DIO_interface.h"
#include "0-MCAL/2-Port/PORT_interface.h"
#include "0-MCAL/3-EXTI/EXTI_interface.h"
#include "0-MCAL/5-ADC/ADC_interface.h"
#include "0-MCAL/4-GIE/GIE_interface.h"


#include "1-HAL/CLCD/CLCD_interface.h"
#include "1-HAL/LDR/LDR_interface.h"
#include "1-HAL/LM35/LM_interface.h"
#include "1-HAL/DC_motor/DCM_interface.h"

#include "3-APP/login/LOGIN_interface.h"
#include "3-APP/TempSys/Temp_interface.h"

static uint8 Gloabl_u8INTFlag = 0;

void INT0ISR(void)
{
	Gloabl_u8INTFlag = 1;
}

void main()
{


	uint8 Local_u8LoginState;
	/*Initialize*/
	Port_voidInit();
	EXTI_voidInit();
	ADC_voidInit();
	UART_voidInit();
	GIE_voidEnableGlobal();
	CLCD_VoidInit();

	/*initialize ISR*/
	EXTI_u8SetCallBack(INT0, &INT0ISR);

	// ADC connected devices global

	TESY_CONFIG_t Local_TESY = {
			.TE_LDR = {ADC7_SINGLE_ENDED, 5000ul, 9u},
			.TE_LM = {ADC0_SINGLE_ENDED, 5000ul, 9u},
			.TE_DCMotor = {DIO_PORTC, DIO_PIN3, DIO_PIN4}};

	TESY_u8init(&Local_TESY);
	while (1)
	{
		_delay_ms(150);
		if (Gloabl_u8INTFlag == 1)
		{

			LOGIN_voidSystemStart();

			Local_u8LoginState = LOGIN_u8login(&Gloabl_u8INTFlag);

			if (Local_u8LoginState == LOGIN_SUCCESS)
			{

				TESY_voidMainSystem(&Gloabl_u8INTFlag);
				Gloabl_u8INTFlag = 0;
			}
			else if ((Local_u8LoginState == LOGIN_ID_FAILD) || (Local_u8LoginState == LOGIN_PASS_FAILD))
			{
				CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
				CLCD_voidGoToXY(0u, 0u);
				CLCD_VoidPrintChars("LOG IN Faild");
				_delay_ms(2000);
				CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
			}
			else
			{
				/*do nothing*/
			}
		}
		else
		{
			/*do nothing*/
		}
	}
}
