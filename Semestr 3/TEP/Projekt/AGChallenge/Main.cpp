#include "Evaluator.h"
#include "Optimizer.h"
#include "Timer.h"

#include <exception>
#include <iostream>
#include <random>

using namespace TimeCounters;

using namespace std;

#define MAX_TIME 20 * 60


void runExperiment(LFLNetEvaluator &configuredElevator)
{
	try
	{
		TimeCounter timeCounter;

		double timePassed;

		Optimizer opitmizer(configuredElevator);

		timeCounter.setStartNow();

		opitmizer.initialize();

		timeCounter.getTimePassed(&timePassed);

		while (timePassed <= MAX_TIME)
		{
			opitmizer.runIteration();
			opitmizer.getCurrentBest();

			timeCounter.getTimePassed(&timePassed);
		}
	}
	catch (exception &exception)
	{
		cout << exception.what() << endl;
	}
}

void  runLFLExperiment(CString  netName)
{
	LFLNetEvaluator lflEvalutaion;
	lflEvalutaion.bConfigure(netName);
	runExperiment(lflEvalutaion);

}

void main(int argCount, char **argValues)
{
	random_device maskSeedGenerator;
	int maskSeed = (int)maskSeedGenerator();


	CString test;
	runLFLExperiment("104b00");

	/*vRunIsingSpinGlassExperiment(81, 0, i_mask_seed);
	vRunIsingSpinGlassExperiment(81, 0, iSEED_NO_MASK);

	vRunLeadingOnesExperiment(50, i_mask_seed);
	vRunLeadingOnesExperiment(50, iSEED_NO_MASK);

	vRunMaxSatExperiment(25, 0, 4.27f, i_mask_seed);
	vRunMaxSatExperiment(25, 0, 4.27f, iSEED_NO_MASK);

	vRunNearestNeighborNKExperiment(100, 0, 4, i_mask_seed);
	vRunNearestNeighborNKExperiment(100, 0, 4, iSEED_NO_MASK);

	vRunOneMaxExperiment(100, i_mask_seed);
	vRunOneMaxExperiment(100, iSEED_NO_MASK);

	vRunRastriginExperiment(200, 10, i_mask_seed);
	vRunRastriginExperiment(200, 10, iSEED_NO_MASK);*/
}//void main(int iArgCount, char **ppcArgValues)