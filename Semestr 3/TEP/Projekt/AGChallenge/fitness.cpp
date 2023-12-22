#include "fitness.h"

//------------------------------------------------------------------------------------------
//------------------implementation of  FOMFunctionLFL-----------------------------------

FOMFunctionLFL::FOMFunctionLFL()
{
	ffe = 0;
}//FOMFunctionLFL::FOMFunctionLFL(CTopologyTranslator)



FOMFunctionLFL::~FOMFunctionLFL()
{

}//FOMFunctionLFL::~FOMFunctionLFL()









double  FOMFunctionLFL::countFom(NETSimulator  *pcSimulator, long  lPenalty, bool  *pbCapacityExtending, double *pdFitnessPure, double *pdPenaltyPure)
{
	ffe++;

	double  d_result;



	d_result = 0;
	*pbCapacityExtending = false;

	bool  b_capacity_ext;
	*pdPenaltyPure = 0;
	*pdFitnessPure = 0;

	for (long li = 0; li < pcSimulator->getNodesNum(); li++)
	{
		d_result += pcSimulator->countNodeLfl(li, lPenalty, &b_capacity_ext, pdFitnessPure, pdPenaltyPure);
		if (b_capacity_ext)  *pbCapacityExtending = true;
	}//for  (long  li = 0; li < l_number_of_nodes; li++)


	d_result = d_result + *pdPenaltyPure;
	d_result = 1.0 / (d_result + 1.0);



	return d_result;


}//double  FOMFunctionLFL::countFom(CTopologyTranslator  *pcTranslator)
