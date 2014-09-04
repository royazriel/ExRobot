//StateMachine.h
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "HardwareProfile.h"
#include "MotorDrive.h"
#include "Delay.h"


#define TURN_TIME_45DEG 				1900
#define TURN_TIME_90DEG 				(TURN_TIME_45DEG * 2)
#define TURN_TIME_180DEG 				(TURN_TIME_90DEG * 2)
#define REVERSE10CM		 				1250
#define REVERSE20CM		 				(REVERSE10CM * 2)
#define WHITE_LINE1_THRESHOLD_MILI		50
#define WHITE_LINE2_THRESHOLD_MILI		200

typedef enum __WhiteLineDirection
{
	etWLNone =0,
	etWLLeft,
	etWLRight,
	etWLStraight
}WhiteLineDirection;

typedef enum __WhiteLineVolume
{
	etWLFront = 0,
	etWLSoft,
	etWLParallel
}WhiteLineVolume;

typedef enum _States
{
	etIdle 				= 0,
	etStartStraight 	= 1 ,
	etDrivingStraight 	= 2,
	etStopStraight 		= 3,
	etStartReverse 		= 4,
	etReversing 		= 5,
	etStopRevers		= 6,
	etStartTurn			= 7,
	etTurning			= 8,
	etStopTurn			= 9,
}States;

void StateMachine();

