//StateMachine.c
#include "StateMachine.h"

static int 	s_state 					= etIdle;
static long s_start 					= 0;
static long s_targetStraightTime 		= REVERSE10CM;
static long s_targetTurnTime 			= TURN_TIME_45DEG;
static int 	s_prevState 				= -1;
static long s_rightWhiteLineTime 		= 0;
static long s_leftWhiteLineTime  		= 0;
static long s_WaitBeforeReversTime 		= 0;
static	WhiteLineDirection whiteLineDirection = etWLNone;
static	WhiteLineVolume    whiteLineVolume;
static 	long deltaTime = 0;

void checkRearBumpers()
{
	if(  R_BACK_BUMPER || L_BACK_BUMPER )
	{
		s_state = etStopStraight;
	}
}

void StateMachine()
{
	switch(s_state)
	{
		case etIdle:
			if(  R_BACK_BUMPER && L_BACK_BUMPER )
			{
				s_state = etStartStraight;
				DelayMs(500);
			}
			break;
		case etStartStraight:
			s_start = MotorStraight( etFast,etForward );
			s_state = etDrivingStraight;
			break;
		case etDrivingStraight:
			checkRearBumpers();
			if( FRONT_BUMPER )
			{
				s_state = etWaitBeforeReverse;
			}
			if( !R_WHITE_LINE_SENSE && s_rightWhiteLineTime==0 )
			{
				s_rightWhiteLineTime = getMiliTicks();
			}
			if( !L_WHITE_LINE_SENSE && s_leftWhiteLineTime==0 )
			{
				s_leftWhiteLineTime = getMiliTicks();
			}
			if( s_rightWhiteLineTime != 0 || s_leftWhiteLineTime != 0 )  
			{
				if( s_rightWhiteLineTime != 0 && s_leftWhiteLineTime != 0)
				{
					if( s_rightWhiteLineTime < s_leftWhiteLineTime )  //right first
					{
					
						deltaTime = s_leftWhiteLineTime - s_rightWhiteLineTime;
						s_rightWhiteLineTime = 0;
						s_leftWhiteLineTime = 0;
						whiteLineDirection = etWLRight;				
					}
					else											 //left first
					{
						deltaTime = s_rightWhiteLineTime - s_leftWhiteLineTime;
						s_rightWhiteLineTime = 0;
						s_leftWhiteLineTime = 0;
						whiteLineDirection = etWLLeft;
					}
					if( deltaTime < WHITE_LINE1_THRESHOLD_MILI )
					{
						whiteLineDirection = etWLStraight;
						whiteLineVolume = etWLFront;
						s_state = etWaitBeforeReverse;
					}
					else
						if( deltaTime < WHITE_LINE2_THRESHOLD_MILI )
						{
							whiteLineVolume = etWLSoft;
							s_state = etWaitBeforeReverse;
						}
						else
						{
							whiteLineVolume = etWLParallel;
							s_state = etWaitBeforeReverse;
						}
				}
				if( R_WHITE_LINE_SENSE && L_WHITE_LINE_SENSE )
				{
					s_rightWhiteLineTime = 0;
					s_leftWhiteLineTime = 0;
					s_state = etStopStraight;
				}
			}
			s_WaitBeforeReversTime = getMiliTicks();
			break;
		case etStopStraight:
			MotorsStop();
			s_state = etIdle;		
			break;
		case etWaitBeforeReverse:
			MotorsStop();
			if( getMiliTicks()-s_WaitBeforeReversTime > WAIT_BEFORE_REVERSE )
			{
		    	s_state = etStartReverse;
			}
			break;
		case etStartReverse:
			s_start = MotorStraight( etFast,etReverse );
			s_targetStraightTime = REVERSE10CM;
			if( whiteLineDirection != etWLNone )
			{
				s_targetStraightTime = REVERSE20CM;
			}
			s_state = etReversing;
			break;
		case etReversing:
			checkRearBumpers();
			if( (getMiliTicks() - s_start) > s_targetStraightTime )
			{
				s_state = etStopRevers;
			}
			break;
		case etStopRevers:
			MotorsStop();
			s_state = etStartTurn;
			break;
		case etStartTurn:
			if( whiteLineDirection != etWLNone )
			{
				switch( whiteLineDirection )
				{
					case  etWLStraight:
						s_start = MotorsTurn( etFast,etRight );  //can turn from both sides
						s_targetTurnTime = TURN_TIME_180DEG;
						break;
					case  etWLLeft:
					case  etWLRight:
						s_start = MotorsTurn( etFast, whiteLineDirection == etWLLeft ? etRight:etLeft  );
						if( whiteLineVolume > etWLFront )
						{
							if( whiteLineVolume == etWLSoft )
							{
								s_targetTurnTime = TURN_TIME_60DEG; //TURN_TIME_45DEG;
							}
							else
							{
								s_targetTurnTime = TURN_TIME_45DEG; //TURN_TIME_90DEG;
							}
						}
						break;
				}
				whiteLineDirection = etWLNone;
			}
			else
			{
				s_start = MotorsTurn( etFast,etRight );
				s_targetTurnTime = TURN_TIME_45DEG;
			}
			s_state = etTurning;
			break;
		case etTurning:
			checkRearBumpers();
			if( (getMiliTicks() - s_start) > s_targetTurnTime )
			{
				s_state = etStopTurn;
			}
			break;
		case etStopTurn:
			s_state = etStartStraight;
			break;
	}
	if( s_state != s_prevState )
	{
		sprintf(GetLcdBuffer()+16,"s%d t%d d%d v%d", s_state, (int)deltaTime,whiteLineDirection,(int)whiteLineVolume );
		LCDUpdate();
		s_prevState = s_state;
	}
}