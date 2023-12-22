#pragma once


#include <string>
#include <vector>

#include <random>
#include <windows.h>
#include  "atlstr.h"  //CString
#include  "atlpath.h"
#include  "tools.h"

#include  "NETsimulator.h"
#include  "MyMath.h"


using namespace std;
using namespace NetSimulator;
using namespace MyMath;


class FOMfunction
{
public:
	FOMfunction()
	{ }

	virtual ~FOMfunction()
	{ }


	virtual CString getName() { return "no function"; }

	virtual double countFom(NETSimulator *simulator, long penalty, bool *capacityExtending, double *fitnessPure, double *penaltyPure) { return 0; }

	//penalty is used when we allow for the capacity extending

	double evalNumber() { return ffe; }

	//	virtual  int     iLoadWeights(CString  sFileName) {return(0);};


protected:
	double ffe;
};


class FOMFunctionLFL : public FOMfunction
{
public:
	FOMFunctionLFL();
	~FOMFunctionLFL();

	CString getName() { return "lfl function"; }

	double countFom(NETSimulator *pcSimulator, long lPenalty, bool *pbCapacityExtending, double *pdFitnessPure, double *pdPenaltyPure);

private:
};
