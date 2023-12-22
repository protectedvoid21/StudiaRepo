#pragma once
#include  "atlstr.h"  //CString
#include  <math.h>
#include  <time.h>

#include <windows.h>



namespace  TimeCounters
{
	class  TimeCounter
	{
	public:

		TimeCounter();
		~TimeCounter()
		{ };

		void  setStartNow();
		bool  getTimePassed(double *timePassedSec);//if returned value is false it means the timer was not set on start
		bool  setFinishOn(double  timeToFinishSec);
		bool  isFinished();

	private:
		bool  startInited;
		LARGE_INTEGER  startPosition;
		LARGE_INTEGER  freq;

		bool  finishInited;
		LARGE_INTEGER  finishPosition;

	};//class  CTimeCounter
};//namespace  TimeCounters