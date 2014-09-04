//MotorDrive.h
#include "HardwareProfile.h"
#include "Delay.h"


typedef enum __MotorSpeed
{
	etSlow = 0,
	etMid,
	etFast,
}MotorSpeed;

typedef enum __MotorDirection
{
	etForward = 0,
	etReverse
}MotorDirection;

typedef enum __MotorTurn
{
	etLeft = 0,
	etRight
}MotorTurn;

long MotorStraight( MotorSpeed speed, MotorDirection direction );
void MotorsStop();
long MotorsTurn( MotorSpeed speed, MotorTurn direction );




















