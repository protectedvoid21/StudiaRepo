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

#include "fitness.h"


using namespace std;
using namespace NetSimulator;
using namespace MyMath;

#define TESTCASE_FOLDER   "data\\"
#define TESTCASE_NET_POSTFIX   ".net"
#define TESTCASE_CON_POSTFIX   ".con"
#define VIRT_WAY_TEMP_FILE   "temp.cod"


#define i_ASCII_CARRIAGE_RETURN   13
#define i_ASCII_NEW_LINE		  10

#define CLONE_ROUNDS			  2

#define i_ERR_FILE_NOT_FOUND   -1
#define i_ERR_FILE_UNEXPECTED_FILE_END   -2

#define i_SHORTEST_WAYS_RANGE			  16

#define PENALTY			  10


class LFLNetEvaluator;
class VirtualWayDatabase;
class CSingleTrajectorySet;


class VirtualWay
{
public:
	int iId;

	int iGetWay(long** plWay);
	bool bSetWay(long* plNewWay, int iNewWayLength);


	int iLoadWay(FILE* pfSource, LFLNetEvaluator* pcTranslator, bool bTranslate);
	void vCreateReportFile(FILE* pfReport);

	double dCountFOM(NETSimulator* pcNetSim);


	bool operator==(VirtualWay& pcOther);

	VirtualWay();
	~VirtualWay();

	//the offsprings pointers are returned but handling them is the task of CVirtualWaysDatabase
	int iCross
	(
		VirtualWay* pcFather, VirtualWay** pcChild1, VirtualWay** pcChild2,
		VirtualWayDatabase* pCVirtualWays,
		NETSimulator* pcNetSim = NULL
	);

	int iMutate
	(
		VirtualWay** pcNewWay,
		VirtualWayDatabase* pCVirtualWays,
		NETSimulator* pcNetSim = NULL
	);

private:
	long* pl_way;
	int i_way_length;

	void v_remove_loops_from_way();
}; //class  VirtualWay


class CVirtualWaysSingleSet
{
	friend class VirtualWayDatabase; //needed for acces to virtual ways list when cloning


public:
	VirtualWay* pcGetVirtualWayAtOffset(int iOffset);
	VirtualWay* pcGetVirtualWay();
	bool bGet2VirtualWaysWithLowLevelFOM(NETSimulator* pcNetSim, VirtualWay** pcMother, VirtualWay** pcFather = NULL,
	                                     bool bTranslated = false);


	int iLoadVirtualWays(FILE* pfSource, LFLNetEvaluator* pcTranslator, bool bTranslate);
	int iInputNewVirtWay(VirtualWay* pcNewWay, LFLNetEvaluator* pcTransltor,
	                     VirtualWay** pcTheSameWayAsNew = NULL);
	//**pcTheSameWayAsNew is used for returning an addres of the way that is the same in the database

	//information methods
	long lGetNumberOfWays(long** plLengthSets, int* piTableLen);
	void vCreateReportFile(FILE* pfReport);


	CVirtualWaysSingleSet();
	~CVirtualWaysSingleSet();

private:
	MyList c_virtual_ways;
}; //class  CVirtualWaysSingleSet


class VirtualWayDatabase
{
public:
	VirtualWayDatabase();
	~VirtualWayDatabase();

	int loadVirtualWays(CString sFileName, LFLNetEvaluator* pcTranslator, bool bTranslate);


	int cloneVirtualWays(long lStartNode = -1);
	//start node is needed when we want to generate new ways for a specialized node


	int iInputNewVirtWay
	(VirtualWay* pcNewWay, long lStartNode, long lFinishNode,
	 VirtualWay** pcTheSameWayAsNew = NULL,
	 bool bTranslated = true);
	//**pcTheSameWayAsNew is used for returning an addres of the way that is the same in the database);


	int iGetVirtualWaysNumber(long lStartNode, long lFinishNode, bool bTranslated = true);
	VirtualWay* pcGetVirtualWay(long lStartNode, long lFinishNode, bool bTranslated = true);
	VirtualWay* pcGetVirtualWayAtOffset(long lStartNode, long lFinishNode, int iOffset, bool bTranslated = true);
	bool bGet2VirtualWaysWithLowLevelFOM(NETSimulator* pcNetSim, long lStartNode, long lFinishNode,
	                                     VirtualWay** pcMother, VirtualWay** pcFather = NULL,
	                                     bool bTranslated = true);


	int iCreateReportFile(CString sFileName);
	int iCreateStatisticsReportFile(CString sFileName);

private:
	int i_input_new_virt_way
	(VirtualWay* pcNewWay, long lTranslatedStartNode, long lTranslatedFinishNode,
	 VirtualWay** pcTheSameWayAsNew);
	//**pcTheSameWayAsNew is used for returning an addres of the way that is the same in the database);

	int i_clone_two_lists(MyList* pcStartList, MyList* pcFinishList, MyList* pcDestList);


	CVirtualWaysSingleSet** pc_virtual_ways_sets;

	LFLNetEvaluator* pc_translator;


	long l_number_of_nodes;
}; //class  VirtualWayDatabase


class LFLNetEvaluator
{
public:
	LFLNetEvaluator();
	~LFLNetEvaluator();

	double evaluate(vector<int>* solution);
	int getNumberOfBits() { return numberOfPairs; }
	int getNumberOfValues(int iPairOffset);

	long getNumberOfNodes() { return numberOfNodes; }
	long getNumberOfLinks() { return numberOfLinks; }

	long lTranslateNodeNum(long nodeNum);
	long lTranslateLinkNum(long linkNum);

	int checkConnection(long* way, int wayLength, long capacity, bool checkActualCapacity = true)
	{
		return netModel->checkConnection(way, wayLength, capacity, checkActualCapacity);
	}

	int inputTrajectorySetToFind(long* nodePairs, long* plCapacities, int iNumberOfPairs);


	bool configure(CString netName);

private:
	bool loadTopology(CString sNet);
	int i_links_count(CString sFileName);
	long l_skip_comments_and_open(CString sFileName, FILE** pfFile, CString* psComments);
	int i_read_one_node(FILE* pfSource, long* plActualLinkNumber);
	bool getShortestWays();
	bool readDemands(CString sPairsFile);


	long numberOfNodes;
	long* nodesRenameTable; //contains pairs [TFinderNodeNumber, NETsimulatorNumber]
	double* nodesWeights;


	long numberOfLinks;
	long* linksRenameTable; //contains pairs [TFinderLinkNumber, NETsimulatorNumber]
	double* linksWeights;


	long* pairs;
	long* capa;
	long pairsNum;


	long* startFinishPairs;
	long* capacities;
	int numberOfPairs;


	CSingleTrajectorySet* fitnessComputer;

	VirtualWayDatabase virtualWays;
	NETSimulator* netModel;

	FOMfunction* fomCounter;
}; //class  CLFLnetEvaluator


class CSingleTrajectorySet
{
	friend class LFLNetEvaluator;

public:
	CSingleTrajectorySet();
	~CSingleTrajectorySet();

	bool bInit(long* plStartFinishPairs, int iNumberOfPairs, VirtualWayDatabase* pcWaysDatabase,
	           NETSimulator* pcNetSim, FOMfunction* pcFOMcounter, long* plCapacities, long lPenalty);

	double dCountFOM(FOMfunction* pcFOMcounter, long* plCapacities, long lPenalty);

	bool setAndRateSolution(vector<int>* pvSolution, double* pdFitness, long* plCapacities, long lPenalty);
	int getNumberOfValues(int iPairOffset);

private:
	bool b_set_all_conns(long* plCapacities);


	NETSimulator* pc_net_sim;
	FOMfunction* fitnessCounter;

	VirtualWayDatabase* virtualWays;

	long* startFinishPairs;
	int numberOfPairs;

	bool fomLvlActual;
	double fomLevelPenalized;
	double fomLevelPure;
	double penaltyPure;


	long populationWhenCreated; //statistical information
	bool capacityExtending;

	VirtualWay** trajectories;
}; //class  CSingleTrajectorySet
