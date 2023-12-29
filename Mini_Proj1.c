/*
 * Mini_Proj1.c
 *      Author: Amr Mohamed
 ===========================================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define G 0
#define O 1
#define R 2
#define WITH_ENGINE_TEMP_CONTROLLER 1

typedef enum state{
	OFF,
	ON
}state;

typedef struct VSensor{
	float speed;
	float temp;
	float etemp;
}Sensors;

void turnON(state *EN, state *AC, state *ETC, Sensors *veh);
void turnOFF(state *EN);
void printStatus(Sensors *veh, state EN, state *AC, state *ETC);

int main(void)
{
	// For the scanf function:
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	/* Sensors set menu:
	  		a. Turn off the engine
			b. Set the traffic light color.
			c. Set the room temperature (Temperature Sensor)
			d. Set the engine temperature (Engine Temperature Sensor)*/
	state EN = ON, AC = OFF, ETC = OFF;
	Sensors veh = {100, 25, 110};
	char c;
	//state engine = ON;
	while(1){
		printf("Main Menu:\n");
		printf("	a. Turn on the vehicle engine\n");
		printf("	b. Turn off the vehicle engine\n");
		printf("	c. Quit the system\n");
		scanf(" %c", &c);
		switch(c){
		case 'a':
			turnON(&EN, &AC, &ETC, &veh);
		break;
		case 'b':
			turnOFF(&EN);
			break;
		case 'c':
			printf("********* GoodBye! *********\n"); // Quit the code
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}

void turnON(state *EN, state *AC, state *ETC, Sensors *veh)
{
	/* Sensors set menu:
	  		a. Turn off the engine
			b. Set the traffic light color.
			c. Set the room temperature (Temperature Sensor)
			d. Set the engine temperature (Engine Temperature Sensor)*/
	char s;
	*EN = ON;
	int light;
	do{
		printf("\nSensor Set Menu:\n");
		printf("	a. Turn off the engine\n");
		printf("	b. Set the traffic light color\n");
		printf("	c. Set the room temperature\n");
		printf("	d. Set the engine temperature\n");
		scanf(" %c", &s);
		switch(s)
		{
		case 'a':
			turnOFF(EN);
			return;
			break;
		case 'b':
			// traffic light sensor
			do{
			printf("Enter the current traffic light status color:	0:Green   1:Orange   2:Red\n");
			scanf("%d", &light);
			switch(light){
			case G:
					veh->speed = 100;
					break;
			case O:
					veh->speed = 30;
					break;
			case R:
					veh->speed = 0;
					break;
			default:
				printf("Invalid Input!\n");
					break;
						}
			}while((light != G) && (light != O) && (light != R));
			printStatus(veh, *EN, AC, ETC);
			break;
		case 'c':
			printf("Enter the current room temperature: (Celsius)\n");
			scanf("%f", &(veh->temp));
			// room temperature
			if(veh->temp < 10)
			{
				*AC = ON;
				veh->temp = 20;
			}
			else if(veh->temp > 30)
			{
				*AC = ON;
				veh->temp = 20;
			}
			else
			{
				*AC = OFF;
			}
			printStatus(veh, *EN, AC, ETC);
			break;
		case 'd':
			#if WITH_ENGINE_TEMP_CONTROLLER
			printf("Enter the engine temperature (Celsius):\n");
			scanf("%f", &(veh->etemp));
			// engine temperature
			if(veh->etemp < 100)
			{
				*ETC = ON;
				veh->etemp = 125;
			}
			else if(veh->etemp > 150)
			{
				*ETC = ON;
				veh->etemp = 125;
			}
			else
			{
				*ETC = OFF;
			}
			printStatus(veh, *EN, AC, ETC);
			#endif
			break;
		default:
			printf("Invalid Input!\n");
			break;
		}
	}while(1);

	return;
}

void printStatus(Sensors *veh, state EN, state *AC, state *ETC)
{
	if(veh->speed == 30)
	{
		*AC = ON;
		veh->temp = (5 * (veh->temp) / 4) + 1;
		#if WITH_ENGINE_TEMP_CONTROLLER
		*ETC = ON;
		veh->etemp = (5 * (veh->etemp) / 4) + 1;
		#endif
	}
	printf("Current Vehicle State:\n");
	EN? printf("Engine:\tON\n") : printf("Engine:\tOFF\n");
	(*AC)? printf("AC:\tON\n") : printf("AC:\tOFF\n");
	printf("Vehicle Speed:\t%.2f\n", veh->speed);
	printf("Room Temperature:\t%.2f\n", veh->temp);
	#if WITH_ENGINE_TEMP_CONTROLLER
	(*ETC)? printf("Engine Temperature Controller:\tON\n") : printf("Engine Temperature Controller:\tOFF\n");
	printf("Engine Temperature:\t%.2f\n", veh->etemp);
	#endif
}

void turnOFF(state *EN)
{
	char n;
		printf("Are You Sure You Want To Turn Off The Engine? (Y/N)\n");
		scanf(" %c", &n);
		switch(n){
			case 'y':
			case 'Y':
				*EN = OFF;
				printf("Turn Off Vehicle Engine\n\n");
				break;
			case 'n':
			case 'N':
				*EN = ON;;
				break;
			default:
				printf("Invalid Input!\n");
				*EN = ON;;
				break;
		}
}







