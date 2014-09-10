//StateMachine.h
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "HardwareProfile.h"
#include "MotorDrive.h"
#include "Delay.h"


#define TURN_TIME_45DEG 				1900
#define TURN_TIME_60DEG 				2500
#define TURN_TIME_90DEG 				(TURN_TIME_45DEG * 2)
#define TURN_TIME_180DEG 				(TURN_TIME_90DEG * 2)
#define REVERSE10CM		 				1250
#define REVERSE20CM		 				(REVERSE10CM * 2)
#define WHITE_LINE1_THRESHOLD_MILI		50
#define WHITE_LINE2_THRESHOLD_MILI		200
#define WAIT_BEFORE_REVERSE				400
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
	etWaitBeforeReverse	= 4,
	etStartReverse 		= 5,
	etReversing 		= 6,
	etStopRevers		= 7,
	etStartTurn			= 8,
	etTurning			= 9,
	etStopTurn			= 10,
}States;

void StateMachine();

