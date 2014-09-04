//MotorDrive.c
#include "MotorDrive.h"

long MotorStraight( MotorSpeed speed, MotorDirection direction )
{
	switch(speed)
	{
		case etSlow:
			break;
		case etMid:
			break;
		case etFast:
			break;
	}
	switch(direction)
	{
		case etForward:
			R_MOTOR_PHASE = 0;
			L_MOTOR_PHASE = 0;
			break;
		case etReverse:
			R_MOTOR_PHASE = 1;
			L_MOTOR_PHASE = 1;
			break;
	}

	L_MOTOR_BREAK = 1;
	R_MOTOR_BREAK = 1;	
	return getMiliTicks();
}

long MotorsTurn( MotorSpeed speed, MotorTurn direction )
{
	switch(speed)
	{
		case etSlow:
			break;
		case etMid:
			break;
		case etFast:
			break;
	}
	switch(direction)
	{
		case etLeft:
			R_MOTOR_PHASE = 0;
			L_MOTOR_PHASE = 1;
			break;
		case etRight:
			R_MOTOR_PHASE = 1;
			L_MOTOR_PHASE = 0;
			break;
	}

	L_MOTOR_BREAK = 1;
	R_MOTOR_BREAK = 1;	
	return getMiliTicks();
}

void MotorsStop()
{
	L_MOTOR_BREAK = 0;
	R_MOTOR_BREAK = 0;	
}