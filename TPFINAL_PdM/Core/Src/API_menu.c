/*
 * API_menu.c
 *
 *  Created on: 5 dic. 2021
 *      Author: luis
 */

#include "API_menu.h"
#include "API_delay.h"
#include "API_uart.h"

static delay_t delay;

#define DELAY_TIME 1000

static delay_t duty;

#define DUTY_TIME 1



#define Intro 13
#define Esc 27

#define Message_1 "\r Ingrese sentido de giro + o -"
#define Message_2 "\r Caracter incorrecto, vuelva a ingresarlo\r"
#define Message_Clear "\33[2K\r"
#define Message_3 "\r Ingrese valor en grados de 1 a 90, que desea mover el servo\r"
#define Message_4 "\n\r El valor ingresado en grados es: "
#define Message_5 "\r Presionar INTRO para validar, de lo contrario ESCAPE"
#define Message_6 "\n\r Giro del servo realizado con éxito"
#define Message_7 "\n\r Girando Servo.."
#define Message_intro "\n\r"


// Función Inicializar MEF
bool_t menuInit(void)
{
    delayInit(&delay,DELAY_TIME );
	delayInit(&duty,DELAY_TIME );
	menuState = READ_FIRST_C;
	secuencia=false;
	return true;
}

// Función Actualizar MEF
/*	STATUS
 *  READ_FIRS_C
 *  READ_NUMBER_STEP_P,
	READ_NUMBER_STEP_N,
	TURN_SERVO,
	STATUS_TURN,
	STATUS_CHARACTER_INCORRECT,

 */

static char dataReceive;
static char dataGrade[2]={0,0};
static uint8_t dGinc=0;
static char dMax='9';
static bool turn=0;              //turn 0 = Clockwise ; turn 1 = anti Clockwise//
static uint16_t delayTurn=0;




void menuUpdate(uint16_t *dirP){
	switch (menuState) {
	case READ_FIRST_C :
	{
		uartSendString(Message_1,sizeof(Message_1)/sizeof(char));
		uartReceiveString(&dataReceive,1,500);
		if(dataReceive!=NULL)
		{
			if('+'==dataReceive)    //Clockwise
			{   turn=0;
				menuState=READ_NUMBER_STEP;
			}
			if('-'==dataReceive)
			{   turn=1;
				menuState=READ_NUMBER_STEP;
			}
			if(('+'!=dataReceive)&&('-'!=dataReceive))
			{
				menuState=STATUS_CHARACTER_INCORRECT;
			}
		}
		dataReceive=NULL;
	}
	break;
	case READ_NUMBER_STEP:
	{		uartSendString(Message_3,sizeof(Message_3)/sizeof(char));
			uartReceiveString(&dataReceive,1,500);
				if(dataReceive!=NULL)
					{ if('9'==dataGrade[0])
							{dMax='0';}
						else {dMax='9';}
						if((48<=dataReceive)&&(dMax>=dataReceive))
							{ dataGrade[dGinc]=dataReceive;
								dGinc++;
							}
						else{ if(Intro!=dataReceive)
								{uartSendString(Message_2,sizeof(Message_2)/sizeof(char));}
							}
						if(Intro==dataReceive)
						{
							uartSendString(Message_4,sizeof(Message_4)/sizeof(char));
							uartSendString(dataGrade,sizeof(dataGrade)/sizeof(char));
							uartSendString(Message_intro,sizeof(Message_intro)/sizeof(char));
							menuState=VALIDATE_STEP;

						}
						dataReceive=NULL;
					}
	}
	break;

	case TURN_SERVO :
	{      uartSendString(Message_Clear,sizeof(Message_Clear)/sizeof(char));
		   delayTurn=CharToInt(&dataGrade);
		   if(turn==0)
		   {delayTurn= (delayTurn*657/180) + 656;}
		   else{delayTurn= ((delayTurn + 90)*657/180)+656;}
           *dirP=delayTurn;
		   PWM_START();
		   menuState=STATUS_TURN;
    }
	break;
	case STATUS_TURN :
	{
		        uartSendString(Message_7,sizeof(Message_7)/sizeof(char));
      			if(delayRead(&delay))
				{menuState=READ_FIRST_C;
				uartSendString(Message_Clear,sizeof(Message_Clear)/sizeof(char));
				}
				dataReceive=NULL;
				dataGrade[0]=0;
			    dataGrade[1]=0;
			    dGinc=0;
	}
	break;
	case VALIDATE_STEP:
		{uartSendString(Message_5,sizeof(Message_5)/sizeof(char));
		  uartReceiveString(&dataReceive,1,500);
		 	if(Intro==dataReceive)
		 	  {menuState=TURN_SERVO;}
		 	if(Esc==dataReceive)
		 	  { dataGrade[0]=0;
		 	    dataGrade[1]=0;
		 	    menuState=READ_NUMBER_STEP;
		 	  }
		}
	break;
	case STATUS_CHARACTER_INCORRECT :
	{
		uartSendString(Message_2,sizeof(Message_2)/sizeof(char));

		if(delayRead(&delay))
		{menuState=READ_FIRST_C;
		uartSendString(Message_Clear,sizeof(Message_Clear)/sizeof(char));
		}
	}
	break;
	default:
		menuInit();
	 }
}

static uint16_t CharToInt(uint8_t *data)
{
  return atoi(data);
}


