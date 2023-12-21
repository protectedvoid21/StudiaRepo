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
		~TimeCounter()  {};

		void  setStartNow();
		bool  getTimePassed(double  *pdTimePassedSec);//if returned value is false it means the timer was not set on start
		bool  bSetFinishOn(double  dTimeToFinishSec);
		bool  bIsFinished();

	private:
		bool  b_start_inited;
		LARGE_INTEGER  li_start_position;
		LARGE_INTEGER  li_freq;
		
		bool  b_finish_inited;
		LARGE_INTEGER  li_finish_position;

	};//class  CTimeCounter
};//namespace  TimeCounters