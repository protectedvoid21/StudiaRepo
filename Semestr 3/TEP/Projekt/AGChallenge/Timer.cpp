//#include  "stdafx.h"
#include  "timer.h"
using namespace TimeCounters;


TimeCounter::TimeCounter()
{
	startInited = false;
	finishInited = false;
} //CTimeCounter::CTimeCounter()


void TimeCounter::setStartNow()
{
	startInited = true;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startPosition);
} //void  CTimeCounter::vSetStartNow()


//if returned value is false it means the timer was not set on start
bool TimeCounter::getTimePassed(double *timePassedSec)
{
	if (startInited == false)
	{
		return false;
	}

	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	double result;

	result = now.QuadPart - startPosition.QuadPart;
	result = result / freq.QuadPart;

	*timePassedSec = result;

	return true;
}

bool TimeCounter::setFinishOn(double timeToFinishSec)
{
	if (startInited == false || timeToFinishSec <= 0)
	{
		return false;
	}

	finishInited = true;

	finishPosition.QuadPart =
		startPosition.QuadPart
		+
		freq.QuadPart * timeToFinishSec;

	return true;
}


bool TimeCounter::isFinished()
{
	if (startInited != true || finishInited != true)
	{
		return true;
	}

	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	if (now.QuadPart > finishPosition.QuadPart)
	{
		return true;
	}
	else
	{
		return false;
	}
}
