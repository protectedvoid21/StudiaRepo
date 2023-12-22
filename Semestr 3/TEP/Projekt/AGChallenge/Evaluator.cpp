#include "Evaluator.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>


LFLNetEvaluator::LFLNetEvaluator()
{
	nodesRenameTable = NULL;
	linksRenameTable = NULL;

	nodesWeights = NULL;
	linksWeights = NULL;

	fomCounter = NULL;

	netModel = new NETSimulatorSimplified;

	capa = NULL;
	pairs = NULL;

	startFinishPairs = NULL;
	capacities = NULL;

	fitnessComputer = NULL;
}


LFLNetEvaluator::~LFLNetEvaluator()
{
	if (nodesRenameTable != NULL)
	{
		delete[] nodesRenameTable;
	}

	if (linksRenameTable != NULL)
	{
		delete[] linksRenameTable;
	}

	if (nodesWeights != NULL)
	{
		delete[] nodesWeights;
	}

	if (linksWeights != NULL)
	{
		delete[] linksWeights;
	}


	if (netModel != NULL)
	{
		delete netModel;
	}

	if (fomCounter != NULL)
	{
		delete fomCounter;
	}

	if (capa != NULL)
	{
		delete[] capa;
	}
	if (pairs != NULL)
	{
		delete[] pairs;
	}

	if (capacities != NULL)
	{
		delete[] capacities;
	}
	if (startFinishPairs != NULL)
	{
		delete[] startFinishPairs;
	}

	if (fitnessComputer == NULL)
	{
		delete fitnessComputer;
	}
}


double LFLNetEvaluator::evaluate(vector<int>* solution)
{
	double result;
	fitnessComputer->setAndRateSolution(solution, &result, capacities, PENALTY);
	return result;
} //double  CLFLnetEvaluator::evaluate(vector<int>  *solution)


int LFLNetEvaluator::getNumberOfValues(int pairNumber)
{
	return fitnessComputer->getNumberOfValues(pairNumber);
} //int  CLFLnetEvaluator::getNumberOfValues(int  pairNumber)


bool LFLNetEvaluator::configure(CString netName)
{
	//FILE  *pf_net;
	CString netPath, conPath;

	netPath = TESTCASE_FOLDER + netName + "\\" + netName + TESTCASE_NET_POSTFIX;
	conPath = TESTCASE_FOLDER + netName + "\\" + netName + TESTCASE_CON_POSTFIX;

	if (loadTopology(netPath) == false)
	{
		return false;
	}
	netModel->createBasicVirtualDatabaseFile(VIRT_WAY_TEMP_FILE);
	virtualWays.loadVirtualWays(VIRT_WAY_TEMP_FILE, this, false);

	for (int i = 0; i < CLONE_ROUNDS; i++)
	{
		if (virtualWays.cloneVirtualWays() != 1)
		{
			return false;
		}
	}


	if (getShortestWays() == false)
	{
		return false;
	}
	fomCounter = new FOMFunctionLFL();

	if (readDemands(conPath) == false)
	{
		return false;
	}

	if (inputTrajectorySetToFind(pairs, capa, pairsNum) != 1)
	{
		return false;
	}

	fitnessComputer = new CSingleTrajectorySet();
	fitnessComputer->bInit(startFinishPairs, numberOfPairs, &virtualWays, netModel, fomCounter,capacities, PENALTY);

	double test = fitnessComputer->dCountFOM(fomCounter, capacities, PENALTY);
	//::Tools::vShow(d_test);

	return true;
}


/*
returned values:
1  -  ok
0  -  memory allocation problem
*/
int LFLNetEvaluator::inputTrajectorySetToFind(long* nodePairs, long* plCapacities, int iNumberOfPairs)
{
	numberOfPairs = 0;

	if (startFinishPairs != NULL)
	{
		delete[] startFinishPairs;
	}

	//	if  (pc_population  !=  NULL)
	//		delete []  pc_population;


	if (capacities != NULL)
	{
		delete[] capacities;
	}


	startFinishPairs = new long[iNumberOfPairs * 2];
	if (startFinishPairs == NULL)
	{
		return 0;
	}


	capacities = new long[iNumberOfPairs];
	if (capacities == NULL)
	{
		return 0;
	}


	numberOfPairs = iNumberOfPairs;

	for (int ii = 0; ii < numberOfPairs * 2; ii++)
	{
		startFinishPairs[ii] = lTranslateNodeNum(nodePairs[ii]);
	}


	for (int ii = 0; ii < numberOfPairs; ii++)
	{
		capacities[ii] = plCapacities[ii];
	}


	return 1;
} //int   CTrajectorySetsFinder::inputTrajectorySetToFind(long  *nodePairs,  int  iNumberOfPairs)


bool LFLNetEvaluator::readDemands(CString sPairsFile)
{
	FILE* pf_pairs;
	CString s_comments;

	l_skip_comments_and_open(sPairsFile, &pf_pairs, &s_comments);


	CString s_buf;
	if (pf_pairs == NULL)
	{
		return false;
	}


	long l_num_of_pairs;

	fscanf(pf_pairs, "%ld\n", &l_num_of_pairs);
	pairsNum = l_num_of_pairs;


	if (capa != NULL)
	{
		delete[] capa;
	}
	if (pairs != NULL)
	{
		delete[] pairs;
	}

	capa = new long[l_num_of_pairs];
	pairs = new long[l_num_of_pairs * 2];


	long l_buf;
	for (long li = 0; li < l_num_of_pairs; li++)
	{
		fscanf(pf_pairs, "%ld\n", &l_buf);


		fscanf(pf_pairs, "%ld", &l_buf);
		pairs[li * 2] = l_buf;

		fscanf(pf_pairs, "%ld", &l_buf);
		pairs[li * 2 + 1] = l_buf;

		fscanf(pf_pairs, "%ld\n", &l_buf);
		//l_buf = l_buf / 4;//prw remove
		//if  (l_buf <= 0)  l_buf = 1;//prw remove
		capa[li] = l_buf;
		//capa[li] = 10;//l_buf;
	} //for  (long  li = 0; li < l_num_of_pairs; li++)


	fclose(pf_pairs);

	return true;
}; //int  CHefanSystem::iCreatePairs(CString  sPairsFile)


bool LFLNetEvaluator::getShortestWays()
{
	vector<long*> v_virt_ways;
	vector<long> v_virt_ways_lengths;

	if (netModel->getShortestWays(i_SHORTEST_WAYS_RANGE, &v_virt_ways, &v_virt_ways_lengths) != 1)
	{
		for (int ii = 0; ii < (int)v_virt_ways.size(); ii++)
		{
			delete[] v_virt_ways.at(ii);
		}

		return false;
	} //if (netModel->getShortestWays(i_SHORTEST_WAYS_RANGE, &v_virt_ways, &v_virt_ways_lengths) != 1)

	VirtualWay *pc_new_vw, *pc_vw_buf;
	int i_vw_input_res;

	for (int ii = 0; ii < (int)v_virt_ways.size(); ii++)
	{
		//now we create the proper virtual way and try to insert it into the virtual way database
		pc_new_vw = new VirtualWay;

		if (pc_new_vw->bSetWay(v_virt_ways.at(ii), v_virt_ways_lengths.at(ii)) == false)
		{
			for (int ii = 0; ii < (int)v_virt_ways.size(); ii++)
			{
				delete[] v_virt_ways.at(ii);
			}

			return -1;
		} //if  (pc_new_vw->bSetWay(v_virt_ways.at(ii), v_virt_ways_lengths.at(ii))  ==  false)

		i_vw_input_res = virtualWays.iInputNewVirtWay
		(
			pc_new_vw, v_virt_ways.at(ii)[0], v_virt_ways.at(ii)[v_virt_ways_lengths.at(ii) - 1],
			&pc_vw_buf, true
		);


		//virtual way not inserted because it already exists
		if (i_vw_input_res != 1)
		{
			delete pc_new_vw;
		} //if  (i_vw_input_res  ==  2)
	} //for  (int  ii = 0; ii < (int) v_virt_ways.size(); ii++)

	for (int ii = 0; ii < (int)v_virt_ways.size(); ii++)
	{
		delete[](long*)v_virt_ways.at(ii);
	}

	return true;
} //bool  CLFLnetEvaluator::getShortestWays()


bool LFLNetEvaluator::loadTopology(CString sNet)
{
	FILE* pf_source;

	//before we really start we have to count the number of links in the net
	numberOfLinks = i_links_count(sNet);

	if (numberOfLinks <= 0)
	{
		return false;
	}


	//if the number of links is properly found we create the links rename table
	if (linksRenameTable != NULL)
	{
		delete[] linksRenameTable;
	}
	linksRenameTable = new long[numberOfLinks * 2];

	if (linksRenameTable == NULL)
	{
		return -2;
	}


	CString s_buf;
	if (l_skip_comments_and_open(sNet, &pf_source, &s_buf) == -1)
	{
		return 0;
	}


	if (feof(pf_source) == 0)
	{
		fscanf(pf_source, "%ld", &numberOfNodes);
	}
	else
	{
		return false;
	}


	//now when we have the number of nodes we input them into the web and
	//create the nodes rename table
	if (nodesRenameTable != NULL)
	{
		delete[] nodesRenameTable;
	}

	nodesRenameTable = new long[numberOfNodes * 2];
	if (nodesRenameTable == 0)
	{
		return false;
	}


	for (long li = 0; li < numberOfNodes; li++)
	{
		nodesRenameTable[li * 2] = li + 1;
		nodesRenameTable[li * 2 + 1] = netModel->addNewNode(0, "");

		if (nodesRenameTable[li * 2 + 1] == -1)
		{
			return -3;
		}
	} //for  (long  li = 0; li < numberOfNodes; li++)


	//before we start to create links we must create a tool for enumarating them...
	long l_link_number = 1;

	for (long li = 0; li < numberOfNodes; li++)
	{
		if (i_read_one_node(pf_source, &l_link_number) == 10)
		{
			return -1;
		}
	} //for  (long  li = 0; li < numberOfNodes)*/


	fclose(pf_source);


	//netModel->presentNetwork("networkCheck.dat");
	//::Tools::vShow("modelOK");


	return 1;
} //bool  CLFLnetEvaluator::loadTopology(CString  sNet)


/*
returned values:
1..n  -  modeling system node num
-2    -  node num too small
-1    -  node num too high
*/
long LFLNetEvaluator::lTranslateNodeNum(long nodeNum)
{
	if (nodeNum < 1)
	{
		return -2;
	}
	if (numberOfNodes < nodeNum)
	{
		return -1;
	}

	return nodesRenameTable[(nodeNum - 1) * 2 + 1];
} //long  CTopologyTranslator::lTranslateNodeNum(long  nodeNum)


/*
returned values:
1..n  -  modeling system link num
-2    -  link num too small
-1    -  link num too high
*/
long LFLNetEvaluator::lTranslateLinkNum(long linkNum)
{
	if (linkNum < 1)
	{
		return -2;
	}
	if (numberOfLinks < linkNum)
	{
		return -1;
	}

	return linksRenameTable[(linkNum - 1) * 2 + 1];
} //long  CTopologyTranslator::lTranslateNodeNum(long  lNodeNum)


int LFLNetEvaluator::i_links_count(CString sFileName)
{
	FILE* pf_source;
	CString s_buf;


	int i_links_num;
	long l_buf;
	long l_num_of_conn_nodes;


	i_links_num = 0;


	if (l_skip_comments_and_open(sFileName, &pf_source, &s_buf) == -1)
	{
		return i_ERR_FILE_NOT_FOUND;
	}


	//first we have to read the number of nodes
	int i_nodes_num;
	fscanf(pf_source, "%ld", &i_nodes_num);
	//::Tools::vShow(i_nodes_num);


	//now we count the number of links
	long li, lj;
	for (li = 0; li < i_nodes_num; li++)
	{
		//now we read in the node number
		if (feof(pf_source) == 0)
		{
			fscanf(pf_source, "%ld", &l_buf);
		}
		else
		{
			fclose(pf_source);
			return -2;
		}


		//now it is the number of connected nodes (which means links in this case)
		if (feof(pf_source) == 0)
		{
			fscanf(pf_source, "%ld", &l_num_of_conn_nodes);
		}
		else
		{
			fclose(pf_source);
			return i_ERR_FILE_UNEXPECTED_FILE_END;
		} //else  if (feof(pf_source) == 0)


		i_links_num += l_num_of_conn_nodes;


		for (lj = 0; lj < l_num_of_conn_nodes * 2; lj++)
		{
			if (feof(pf_source) == 0)
			{
				fscanf(pf_source, "%ld", &l_buf);
			}
			else
			{
				fclose(pf_source);
				return i_ERR_FILE_UNEXPECTED_FILE_END;
			} //else if (feof(pf_source) == 0)
		} //for  (long  lj = 0; lj < l_num_of_conn_nodes; lj++)
	} //for  (long  li = 0; li < l_nodes_num; li++)


	fclose(pf_source);

	return i_links_num;
} //long  CLFLnetEvaluator::l_count_number_of_links(CString  sFileName)


long LFLNetEvaluator::l_skip_comments_and_open(CString sFileName, FILE** pfFile, CString* psComments)
{
	char c_buf;
	int i_num_of_comm_lines = 0;
	bool b_comment;


	*pfFile = fopen((LPCSTR)sFileName.GetString(), "r+");
	if (*pfFile == NULL)
	{
		return -1;
	}

	b_comment = true;

	while (b_comment == true)
	{
		b_comment = false;

		fscanf(*pfFile, "%c", &c_buf);
		if (c_buf == '/')
		{
			fscanf(*pfFile, "%c", &c_buf);
			if (c_buf == '/')
			{
				b_comment = true;
				i_num_of_comm_lines++;

				for (; c_buf != '\n';)
				{
					fscanf(*pfFile, "%c", &c_buf);
					if (c_buf != '\n')
					{
						*psComments += c_buf;
					}
					else
					{
						c_buf = i_ASCII_CARRIAGE_RETURN;
						*psComments += c_buf;
						c_buf = i_ASCII_NEW_LINE;
						*psComments += c_buf;
					} //else  if  (c_buf  !=  '\n')  
				} //for  (;c_buf  !=  '\n';)
			} //if  (c_buf  ==  '/')	
		} //if  (c_buf  ==  '/')
	} //while  (b_comment  ==  true)

	fclose(*pfFile);

	*pfFile = fopen((LPCSTR)sFileName.GetString(), "r+");
	while (i_num_of_comm_lines > 0)
	{
		c_buf = 'a';
		for (; c_buf != '\n';)
		{
			fscanf(*pfFile, "%c", &c_buf);
		}
		i_num_of_comm_lines--;
	} //while  (i_num_of_comm_lines  >  0)
} //void  CLFLnetEvaluator::v_read_comments(CString  *psComments)


/*
returned values:
1  -  ok
10 -  unexpected end of file
-3 - link creation process unsuccessfull
-4 - node capacity setting unsuccessfull
-5 - node number for link creation is not valid
-6 - unexpected link number (link number is too big)
*/
int LFLNetEvaluator::i_read_one_node(FILE* pfSource, long* plActualLinkNumber)
{
	long l_node_number;
	int i_connected_nodes;

	long l_connected_node_num;
	long l_link_capacity;

	long l_new_link_id;


	//initialization of data
	if (feof(pfSource) == 0)
	{
		fscanf(pfSource, "%ld", &l_node_number);
	}
	else
	{
		return 10;
	}


	if (feof(pfSource) == 0)
	{
		fscanf(pfSource, "%d", &i_connected_nodes);
	}
	else
	{
		return 10;
	}


	//	printf("Node number:%ld\n", l_node_number);
	//	printf("Number of connected nodes:%d\n",i_connected_nodes);


	//node and link creating
	long l_summary_capacity = 0;
	for (int ii = 0; ii < i_connected_nodes; ii++)
	{
		if (feof(pfSource) == 0)
		{
			fscanf(pfSource, "%ld", &l_connected_node_num);
		}
		else
		{
			return 10;
		}


		//		printf("Connected node num:%ld\n",l_connected_node_num);


		if (feof(pfSource) == 0)
		{
			fscanf(pfSource, "%ld", &l_link_capacity);
		}
		else
		{
			return 10;
		}


		//		printf("Connected node link capacity:%ld\n",l_link_capacity);


		//now we create a proper links
		if (
			l_node_number - 1 < numberOfNodes &&
			l_connected_node_num - 1 < numberOfNodes
		)
		{
			l_new_link_id =
				netModel->createLink(
					nodesRenameTable[(l_node_number - 1) * 2 + 1],
					nodesRenameTable[(l_connected_node_num - 1) * 2 + 1],
					l_link_capacity);

			if (l_new_link_id < 0)
			{
				return -3;
			}

			if (*plActualLinkNumber - 1 >= numberOfLinks)
			{
				return -6;
			}

			linksRenameTable[(*plActualLinkNumber - 1) * 2] = *plActualLinkNumber;
			linksRenameTable[(*plActualLinkNumber - 1) * 2 + 1] = l_new_link_id;

			(*plActualLinkNumber)++;
		} //if
		else
		{
			return -5;
		}


		l_summary_capacity += l_link_capacity;
	} //for  (int  ii = 0; ii < i_connected_nodes; ii++)


	l_summary_capacity *= 2;


	//now we must set the node capactiy so this is able to maintain all links
	if (
		netModel->setNodeCapacity(
			nodesRenameTable[(l_node_number - 1) * 2 + 1],
			l_summary_capacity)
		!=
		1
	)
	{
		return -4;
	}


	//	printf("\n\n");


	return 1;
} //int  CTopologyTranslator::i_read_one_node(FILE  pfSource)


//-------------------------------------------------------------------------------------------
//--------------------------implementation of class VirtualWayDatabase--------------------------


VirtualWayDatabase::VirtualWayDatabase()
{
	pc_virtual_ways_sets = NULL;
	l_number_of_nodes = 0;
} //VirtualWayDatabase::VirtualWayDatabase()


VirtualWayDatabase::~VirtualWayDatabase()
{
	if (pc_virtual_ways_sets != NULL)
	{
		for (long li = 0; li < l_number_of_nodes; li++)
		{
			delete[] pc_virtual_ways_sets[li];
		}

		delete[] pc_virtual_ways_sets;
	} //if  (pl_virtual_ways  !=  NULL)
} //VirtualWayDatabase::VirtualWayDatabase()


/*
returned values:
1  -  ok
0  -  file not found
-1 -  unexpected end of file
-2 -  memory allocation problems
-3 -  node creation unsuccessfull
*/
int VirtualWayDatabase::loadVirtualWays(CString sFileName, LFLNetEvaluator* pcTranslator, bool bTranslate)
{
	FILE* pf_source;

	long l_number_of_ways;


	pc_translator = pcTranslator;


	pf_source = fopen((LPCSTR)sFileName.GetString(), "r+");
	if (pf_source == NULL)
	{
		return 0;
	}


	if (feof(pf_source) == 0)
	{
		fscanf(pf_source, "%ld", &l_number_of_ways);
	}
	else
	{
		return 10;
	}


	l_number_of_nodes = pcTranslator->getNumberOfNodes();


	pc_virtual_ways_sets = new CVirtualWaysSingleSet*[l_number_of_nodes];

	if (pc_virtual_ways_sets == NULL)
	{
		fclose(pf_source);
		return -2;
	} //if  (pc_virtual_ways_sets  ==  NULL)


	long li;
	for (li = 0; li < l_number_of_nodes; li++)
	{
		pc_virtual_ways_sets[li] = new CVirtualWaysSingleSet[l_number_of_nodes];


		if (pc_virtual_ways_sets[li] == NULL)
		{
			for (long lj = 0; lj < li; lj++)
			{
				delete[] pc_virtual_ways_sets[lj];
			}

			delete[] pc_virtual_ways_sets;

			fclose(pf_source);

			return -2;
		} //if  (pc_virtual_ways_sets[li]  ==  NULL)
	} //for  (li = 0; li < numberOfNodes; li++)


	//from this point we start to read the data in...
	long l_start_node, l_finish_node;
	int i_buf;
	for (li = 0; li < l_number_of_ways; li++)
	{
		//read one set of virtual ways
		if (feof(pf_source) == 0)
		{
			fscanf(pf_source, "%ld", &l_start_node);
		}
		else
		{
			return -1;
		}

		if (feof(pf_source) == 0)
		{
			fscanf(pf_source, "%ld", &l_finish_node);
		}
		else
		{
			return -1;
		}


		if (bTranslate == true)
		{
			i_buf =
				pc_virtual_ways_sets
				[pcTranslator->lTranslateNodeNum(l_start_node)]
				[pcTranslator->lTranslateNodeNum(l_finish_node)]
				.iLoadVirtualWays(pf_source, pcTranslator, bTranslate);
		} //if  (bTranslate  ==  true)
		else
		{
			i_buf =
				pc_virtual_ways_sets
				[l_start_node]
				[l_finish_node]
				.iLoadVirtualWays(pf_source, pcTranslator, bTranslate);
		} //else  if  (bTranslate  ==  true)

		if (i_buf != 1)
		{
			//	printf("result:%d start:%ld  finish:%ld\n\n", i_buf, l_start_node, l_finish_node);

			fclose(pf_source);
			return i_buf;
		} //if  (i_buf  !=  1)
	} //for  (li = 0; li < l_number_of_ways; li++)


	fclose(pf_source);


	return 1;
} //int  VirtualWayDatabase::loadVirtualWays(CString  sFileName, CTopologyTranslator *pcTranslator)


VirtualWay* VirtualWayDatabase::pcGetVirtualWay(long lStartNode, long lFinishNode, bool bTranslated)
{
	if (bTranslated == false)
	{
		return
			pc_virtual_ways_sets
			[pc_translator->lTranslateNodeNum(lStartNode)]
			[pc_translator->lTranslateNodeNum(lFinishNode)].pcGetVirtualWay();
	}
	else
	{
		return
			pc_virtual_ways_sets
			[lStartNode]
			[lFinishNode].pcGetVirtualWay();
	}
} //VirtualWay*  VirtualWayDatabase::pcGetVirtualWay(long  lStartNode, long lFinishNode)


int VirtualWayDatabase::iGetVirtualWaysNumber(long lStartNode, long lFinishNode, bool bTranslated /*= true*/)
{
	if (bTranslated == false)
	{
		return
			pc_virtual_ways_sets
			[pc_translator->lTranslateNodeNum(lStartNode)]
			[pc_translator->lTranslateNodeNum(lFinishNode)].lGetNumberOfWays(NULL, NULL);
	}
	else
	{
		return
			pc_virtual_ways_sets
			[lStartNode]
			[lFinishNode].lGetNumberOfWays(NULL, NULL);
	}
} //VirtualWay*  VirtualWayDatabase::pcGetVirtualWay(long  lStartNode, long lFinishNode)


VirtualWay* VirtualWayDatabase::pcGetVirtualWayAtOffset(long lStartNode, long lFinishNode, int iOffset,
                                                          bool bTranslated /*= true*/)
{
	if (bTranslated == false)
	{
		return
			pc_virtual_ways_sets
			[pc_translator->lTranslateNodeNum(lStartNode)]
			[pc_translator->lTranslateNodeNum(lFinishNode)].pcGetVirtualWayAtOffset(iOffset);
	}
	else
	{
		return
			pc_virtual_ways_sets
			[lStartNode]
			[lFinishNode].pcGetVirtualWayAtOffset(iOffset);
	}
} //VirtualWay*  VirtualWayDatabase::pcGetVirtualWay(long  lStartNode, long lFinishNode)


/*
returned values:
1  -  ok
0  -
-1 -  wrong start node
-2 -  wrong finish node
*/
int VirtualWayDatabase::iInputNewVirtWay
(VirtualWay* pcNewWay, long lStartNode, long lFinishNode,
 VirtualWay** pcTheSameWayAsNew,
 bool bTranslated) //**pcTheSameWayAsNew is used for returning an addres of the way that is the same in the database)
{
	if (bTranslated == false)
	{
		return i_input_new_virt_way
		(pcNewWay,
		 pc_translator->lTranslateNodeNum(lStartNode),
		 pc_translator->lTranslateNodeNum(lFinishNode),
		 pcTheSameWayAsNew
		);
	}
	else
	{
		return i_input_new_virt_way
		(pcNewWay,
		 lStartNode,
		 lFinishNode,
		 pcTheSameWayAsNew
		);
	}
} //int   VirtualWayDatabase::iInputNewVirtWay


/*
returned values:
1  -  ok
0  -  memory allocation problems
-1 -  wrong start node number
*/
int VirtualWayDatabase::cloneVirtualWays(long lStartNode)
{
	MyList*** pc_new_ways;


	if (
		lStartNode != -1 &&
		(lStartNode < 0 || lStartNode >= l_number_of_nodes)
	)
	{
		return -1;
	}


	//now we create a new virtual ways database
	pc_new_ways = new MyList**[l_number_of_nodes];
	if (pc_new_ways == NULL)
	{
		return 0;
	}

	long li, lj;
	for (li = 0; li < l_number_of_nodes; li++)
	{
		pc_new_ways[li] = new MyList*[l_number_of_nodes];

		if (pc_new_ways[li] == NULL)
		{
			for (lj = 0; lj < li; lj++)
			{
				delete[] pc_new_ways[lj];
			}

			delete[] pc_new_ways;

			return 0;
		} //if  (pc_new_ways[li]  =  NULL)
	} //for  (long  li = 0; li < numberOfNodes; li++)


	//now for all of the poniters we allocate the list
	for (li = 0; li < l_number_of_nodes; li++)
	{
		for (lj = 0; lj < l_number_of_nodes; lj++)
		{
			pc_new_ways[li][lj] = new MyList;

			if (pc_new_ways[li][lj] == NULL)
			{
				for (long lx = 0; lx < lj; lx++)
				{
					delete pc_new_ways[li][lx];
				}

				for (long ly = 0; ly < li; ly++)
				{
					for (long lx = 0; lx < l_number_of_nodes; lx++)
					{
						delete pc_new_ways[ly][lx];
					}
				}


				for (long lx = 0; lx < l_number_of_nodes; lx++)
				{
					delete[] pc_new_ways[lx];
				}

				delete[] pc_new_ways;


				return 0;
			} //if  (pc_new_ways[li][lj]  ==  NULL)
		} //for  (lj = 0; lj < numberOfNodes; lj++)
	} //for  (li = 0; li < numberOfNodes; li++)


	//now we clone all ways we have
	MyList* pc_list1;
	MyList* pc_list2;
	long lk;

	//this if-construction is not the best one because the only diffrence is in li but it was the easiest one to carry up
	if (lStartNode == -1)
	{
		for (li = 0; li < l_number_of_nodes; li++)
		{
			for (lj = 0; lj < l_number_of_nodes; lj++)
			{
				if (li != lj)
				{
					pc_list1 = &pc_virtual_ways_sets[li][lj].c_virtual_ways;

					for (lk = 0; lk < l_number_of_nodes; lk++)
					{
						if (lk != li && lk != lj)
						{
							pc_list2 = &pc_virtual_ways_sets[lj][lk].c_virtual_ways;

							i_clone_two_lists(pc_list1, pc_list2, pc_new_ways[li][lk]);
						} //if  ( (lk != li)&&(lk != lj) )
					} //for  (lk = 0; lk < numberOfNodes; lk++)
				} //if  (li != lj)
			} //for  (lj = 0; lj < numberOfNodes; lj++)
		} //for  (li = 0; li < numberOfNodes; li++)
	} //if  (lStartNode  !=  -1)
	else
	{
		li = lStartNode;

		for (lj = 0; lj < l_number_of_nodes; lj++)
		{
			if (li != lj)
			{
				pc_list1 = &pc_virtual_ways_sets[li][lj].c_virtual_ways;

				for (lk = 0; lk < l_number_of_nodes; lk++)
				{
					if (lk != li && lk != lj)
					{
						pc_list2 = &pc_virtual_ways_sets[lj][lk].c_virtual_ways;

						i_clone_two_lists(pc_list1, pc_list2, pc_new_ways[li][lk]);
					} //if  ( (lk != li)&&(lk != lj) )
				} //for  (lk = 0; lk < numberOfNodes; lk++)
			} //if  (li != lj)
		} //for  (lj = 0; lj < numberOfNodes; lj++)
	} //else  if  (lStartNode  !=  -1)


	//now for all lists we try to input them into the virtual way database
	for (li = 0; li < l_number_of_nodes; li++)
	{
		for (lj = 0; lj < l_number_of_nodes; lj++)
		{
			if (pc_new_ways[li][lj]->first() == true)
			{
				for (lk = 0; lk < pc_new_ways[li][lj]->getCapacity(); lk++)
				{
					if
					(
						pc_virtual_ways_sets[li][lj].iInputNewVirtWay
						(
							(VirtualWay*)pc_new_ways[li][lj]->getNode()->getObject(),
							pc_translator
						)
						!= 1
					)
					{
						//if the way was not inputted we MUST destroy if
						delete (VirtualWay*)pc_new_ways[li][lj]->getNode()->getObject();
						//printf("One not inptutted\n");
					} //if
					/*else
						printf("One inptutted\n");*/

					pc_new_ways[li][lj]->next();
				} //for  (lk = 0; lk < pc_new_ways[li][lj].getCapacity(); lk++)
			} //if  (pc_new_way[li][lj].first()  ==  true)
		} //for  (lj = 0; lj < numberOfNodes; lj++)
	} //for  (li = 0; li < numberOfNodes; li++)


	//now we destroy the lists
	for (li = 0; li < l_number_of_nodes; li++)
	{
		for (lj = 0; lj < l_number_of_nodes; lj++)
		{
			delete pc_new_ways[li][lj];
		}
	}

	for (li = 0; li < l_number_of_nodes; li++)
	{
		delete pc_new_ways[li];
	}

	delete pc_new_ways;


	return 1;
} //int   VirtualWayDatabase::cloneVirtualWays(int iNumberOfRepetations, long lStartNode = -1)


/*
1  -  ok
0  -  memory allocation problems
*/
int VirtualWayDatabase::i_clone_two_lists(MyList* pcStartList, MyList* pcFinishList, MyList* pcDestList)
{
	if (pcStartList->first() == false)
	{
		return 1;
	}
	if (pcFinishList->first() == false)
	{
		return 1;
	}


	VirtualWay *pc_mother, *pc_father, *pc_child;
	long *pl_mother_way, *pl_father_way, *pl_child_way;
	int i_mother_length, i_father_length, i_child_length;
	long li, lj, lk;

	for (li = 0; li < pcStartList->getCapacity(); li++)
	{
		pc_mother = (VirtualWay*)pcStartList->getNode()->getObject();
		i_mother_length = pc_mother->iGetWay(&pl_mother_way);

		for (lj = 0; lj < pcFinishList->getCapacity(); lj++)
		{
			pc_father = (VirtualWay*)pcFinishList->getNode()->getObject();
			i_father_length = pc_father->iGetWay(&pl_father_way);


			pc_child = new VirtualWay;
			if (pc_child == NULL)
			{
				return 0;
			}

			i_child_length = i_mother_length + i_father_length - 1;
			pl_child_way = new long[i_child_length];

			if (pl_child_way == NULL)
			{
				delete pc_child;
				return 0;
			} //if  (pl_child_way  ==  NULL)

			//now rewrite the way
			for (lk = 0; lk < i_mother_length; lk++)
			{
				pl_child_way[lk] = pl_mother_way[lk];
				//	printf("child way[%ld]: %ld (mother part)\n",lk,pl_mother_way[lk]);
			} //for  (lk = 0; lk < i_mother_length; lk++)

			for (lk = 0; lk < i_father_length; lk++)
			{
				pl_child_way[i_mother_length - 1 + lk] = pl_father_way[lk];
				//	printf("child way[%ld]: %ld (father part)\n",lk,pl_father_way[lk]);
			} //for  (lk = 0; lk < i_father_length; lk++)


			if (pc_child->bSetWay(pl_child_way, i_child_length) == false)
			{
				delete pc_child;
				delete[] pl_child_way;
				return 0;
			} //if  (pc_child->bSetWay(pl_child_way, i_child_way_length)  == false)


			if (pcDestList->add(pc_child) == false)
			{
				delete pc_child;
				delete[] pl_child_way;
				return 0;
			} //if  (pcDestList->add(pc_child)  ==  false)


			delete[] pl_child_way;

			pcFinishList->next();
		} //for  (lj = 0;  pcFinishList->getCapacity(); lj++)


		pcStartList->next();
	} //for  (li = 0;  pcStartList->getCapacity(); li++)


	return 1;
} //int  VirtualWayDatabase::i_clone_two_lists(MyList  *pcStartList,  MyList  *pcFinishList,  MyList  *pcDestList)


/*
returned values:
1  -  ok
0  -
-1 -  wrong start node
-2 -  wrong finish node
-3 -  virtual ways database is missing
*/
int VirtualWayDatabase::i_input_new_virt_way
(VirtualWay* pcNewWay, long lTranslatedStartNode, long lTranslatedFinishNode,
 VirtualWay** pcTheSameWayAsNew)
//**pcTheSameWayAsNew is used for returning an addres of the way that is the same in the database)
{
	long* pl_way;
	int i_way_length;

	i_way_length = pcNewWay->iGetWay(&pl_way);

	//now we check the start and finish node if they are not proper we retrun an error
	if (pl_way[0] != lTranslatedStartNode)
	{
		return -1;
	}
	if (pl_way[i_way_length - 1] != lTranslatedFinishNode)
	{
		return -2;
	}


	if (pc_virtual_ways_sets == NULL)
	{
		return -3;
	}


	return
		pc_virtual_ways_sets
		[lTranslatedStartNode]
		[lTranslatedFinishNode].iInputNewVirtWay(pcNewWay, pc_translator, pcTheSameWayAsNew);
} //int   VirtualWayDatabase::iInputNewVirtWay


//-------------------------------------------------------------------------------------------
//--------------------------implementation of class VirtualWay--------------------------


VirtualWay::VirtualWay()
{
	pl_way = NULL;
	i_way_length = 0;
} //VirtualWay::VirtualWay()


VirtualWay::~VirtualWay()
{
	if (pl_way != NULL)
	{
		delete[] pl_way;
	} //if  (pl_way  !=  NULL)
} //VirtualWay::~VirtualWay()


double VirtualWay::dCountFOM(NETSimulator* pcNetSim)
{
	double d_specie_fom;
	double d_buf;

	d_specie_fom = 0;
	for (int ii = 1; ii < i_way_length; ii += 2)
	{
		d_buf = pcNetSim->getActLinkCapacity(pl_way[ii]);

		if (d_buf < 0)
		{
			d_buf = d_buf * -1.0 + 1;
			d_specie_fom += d_buf;
		} //if  (l_buf  <=  0)
		else
		{
			d_buf += 1;
			d_buf *= d_buf;
			d_specie_fom += 1 / d_buf;
		} //else  if  (l_buf  <=  0)
	} //for  (int  ii = 0; ii < i_buf; ii+=2)

	d_specie_fom = 1.0 / d_specie_fom;

	return d_specie_fom;
} //double  VirtualWay::countFom(CTopologyTranslator  *pcTranslator)


//returns the returned way length
int VirtualWay::iGetWay(long** plWay)
{
	if (i_way_length > 0)
	{
		*plWay = pl_way;
		return i_way_length;
	} //if  (i_way_length  >  0)


	return 0;
} //int  VirtualWay::iGetWay(long  **plWay)


bool VirtualWay::bSetWay(long* plNewWay, int iNewWayLength)
{
	long* pl_new_way;


	pl_new_way = new long[iNewWayLength];


	if (pl_new_way == NULL)
	{
		return false;
	}


	for (int ii = 0; ii < iNewWayLength; ii++)
	{
		pl_new_way[ii] = plNewWay[ii];
	}


	if (pl_way != NULL)
	{
		delete[] pl_way;
	}


	pl_way = pl_new_way;
	i_way_length = iNewWayLength;


	v_remove_loops_from_way();


	return true;
} //bool  VirtualWay::bSetWay(long  *plNewWay,  int  iNewWayLength)


/*
1  -  ok
0  -  memory allocation problems
-1 -  unable to communicate with other objects
*/
int VirtualWay::iCross
(
	VirtualWay* pcFather, VirtualWay** pcChild1, VirtualWay** pcChild2,
	VirtualWayDatabase* pCVirtualWays,
	NETSimulator* pcNetSim
)
{
	VirtualWay *pc_child1, *pc_child2;

	*pcChild1 = NULL;
	*pcChild2 = NULL;


	pc_child1 = new VirtualWay;
	if (pc_child1 == NULL)
	{
		return false;
	}

	pc_child2 = new VirtualWay;
	if (pc_child2 == NULL)
	{
		delete pc_child1;
		return 0;
	} //if  (pc_child2  ==  NULL)


	//now we extract ways from mother and father virtual way
	long *pl_mother_way, *pl_father_way;
	int i_mother_way_len, i_father_way_len;


	i_mother_way_len = iGetWay(&pl_mother_way);
	i_father_way_len = pcFather->iGetWay(&pl_father_way);


	if (i_mother_way_len == 0 || i_father_way_len == 0)
	{
		delete pc_child1;
		delete pc_child2;

		return -1;
	} //if  ( (i_mother_way_len  ==  0)||(i_father_way_len  ==  0) )


	//now when we have extracted all data we cross to way sets

	//first we pick up mother and father crossing point
	int i_mother_crossing_node;
	int i_father_crossing_node;


	//we must remeber that way length is inpair and every second number is a link id
	i_mother_crossing_node = (int)lRand((i_mother_way_len + 1) / 2);
	i_father_crossing_node = (int)lRand((i_father_way_len + 1) / 2);

	i_mother_crossing_node *= 2;
	i_father_crossing_node *= 2;


	long l_mother_cross_node_id;
	long l_father_cross_node_id;

	l_mother_cross_node_id = pl_mother_way[i_mother_crossing_node];
	l_father_cross_node_id = pl_father_way[i_father_crossing_node];


	//now if these two nodes are not the same we must find a a virtual way connecting them both
	VirtualWay *pc_moth_fath_way, *pc_fath_moth_way;
	long *pl_moth_fath_way, *pl_fath_moth_way;
	int i_moth_fath_way_len, i_fath_moth_way_len;


	if (l_mother_cross_node_id != l_father_cross_node_id)
	{
		pc_moth_fath_way =
			pCVirtualWays->pcGetVirtualWay(l_mother_cross_node_id, l_father_cross_node_id, true);
		pc_fath_moth_way =
			pCVirtualWays->pcGetVirtualWay(l_father_cross_node_id, l_mother_cross_node_id, true);


		i_moth_fath_way_len = pc_moth_fath_way->iGetWay(&pl_moth_fath_way);
		i_fath_moth_way_len = pc_fath_moth_way->iGetWay(&pl_fath_moth_way);
	} //if  (l_mother_cross_node_id  ==  l_father_cross_node_id)
	else
	{
		i_moth_fath_way_len = 0;
		i_fath_moth_way_len = 0;
	} //else  if  (l_mother_cross_node_id  !=  l_father_cross_node_id)


	//now all we have to do is just to glue all pieces together

	long *pl_child1_way, *pl_child2_way;
	int i_child1_way_len, i_child2_way_len;


	if (i_moth_fath_way_len > 0)
	{
		i_child1_way_len = i_mother_crossing_node + 1
			+
			i_moth_fath_way_len - 1
			+
			i_father_way_len - i_father_crossing_node - 1;
	}
	else
	{
		i_child1_way_len = i_mother_crossing_node + 1
			+
			i_father_way_len - i_father_crossing_node - 1;
	}


	pl_child1_way = new long[i_child1_way_len];
	if (pl_child1_way == NULL)
	{
		delete pc_child1;
		delete pc_child2;
	} //if  (pl_child1_way  ==  NULL)


	if (i_fath_moth_way_len > 0)
	{
		i_child2_way_len = i_father_crossing_node + 1
			+
			i_fath_moth_way_len - 1
			+
			i_mother_way_len - i_mother_crossing_node - 1;
	}
	else
	{
		i_child2_way_len = i_father_crossing_node + 1
			+
			i_mother_way_len - i_mother_crossing_node - 1;
	}


	pl_child2_way = new long[i_child2_way_len];
	if (pl_child2_way == NULL)
	{
		delete[] pl_child1_way;

		delete pc_child1;
		delete pc_child2;
	} //if  (pl_child2_way  ==  NULL)  


	//now we fill up the ways
	int ii, ij, ik;
	for (ii = 0; ii < i_mother_crossing_node + 1; ii++)
	{
		pl_child1_way[ii] = pl_mother_way[ii];
	}

	ii--;
	for (ij = 1; ij < i_moth_fath_way_len; ij++)
	{
		pl_child1_way[ii + ij] = pl_moth_fath_way[ij];
	}

	ij--;
	for (ik = 1; ik < i_father_way_len - i_father_crossing_node; ik++)
	{
		pl_child1_way[ii + ij + ik] = pl_father_way[ik + i_father_crossing_node];
	}


	for (ii = 0; ii < i_father_crossing_node + 1; ii++)
	{
		pl_child2_way[ii] = pl_father_way[ii];
	}

	ii--;
	for (ij = 1; ij < i_fath_moth_way_len; ij++)
	{
		pl_child2_way[ii + ij] = pl_fath_moth_way[ij];
	}

	ij--;
	for (ik = 1; ik < i_mother_way_len - i_mother_crossing_node; ik++)
	{
		pl_child2_way[ii + ij + ik] = pl_mother_way[ik + i_mother_crossing_node];
	}


	//now we insert the ways into virtual way object
	if (pc_child1->bSetWay(pl_child1_way, i_child1_way_len) == false)
	{
		delete[] pl_child1_way;
		delete[] pl_child2_way;

		delete pc_child1;
		delete pc_child2;

		return -1;
	} //if  (pc_child1->bSetWay(pl_child1_way, i_child1_way_len)  ==  false)


	if (pc_child2->bSetWay(pl_child2_way, i_child2_way_len) == false)
	{
		delete[] pl_child1_way;
		delete[] pl_child2_way;

		delete pc_child1;
		delete pc_child2;

		return -1;
	} //if  (pc_child2->bSetWay(pl_child2_way, i_child2_way_len)  ==  false)


	//when the ways are inserted we delete them
	delete[] pl_child1_way;
	delete[] pl_child2_way;


	//now we try to input the virtual ways into the database
	//if there alredy is the same way we delete currently created and use the older one
	VirtualWay* pc_the_same_way;
	int i_insert_res;

	i_insert_res = pCVirtualWays->iInputNewVirtWay(pc_child1,
	                                               pl_way[0], pl_way[i_way_length - 1],
	                                               &pc_the_same_way, true);

	//if  (i_insert_res == 1) printf("JEST\n");

	//if the created way already exists
	if (i_insert_res == 2)
	{
		*pcChild1 = pc_the_same_way;
		delete pc_child1;
	} //if  (i_insert_res  ==  2)

	if (i_insert_res == 1)
	{
		*pcChild1 = pc_child1;
	}


	//if the operation was unsuccesful we delete everything and return false
	if (i_insert_res < 1)
	{
		delete pc_child1;
		delete pc_child2;

		return -1;
	} //if  (i_insert_res  ==  2)


	//NOW SECOND CHILD
	i_insert_res = pCVirtualWays->iInputNewVirtWay(pc_child2,
	                                               pl_way[0], pl_way[i_way_length - 1],
	                                               &pc_the_same_way, true);

	//if the created way already exists
	if (i_insert_res == 2)
	{
		*pcChild2 = pc_the_same_way;
		delete pc_child2;
	} //if  (i_insert_res  ==  2)

	if (i_insert_res == 1)
	{
		*pcChild2 = pc_child2;
	}


	//if the operation was unsuccesful we delete everything and return false
	if (i_insert_res < 1)
	{
		//step back with first child
		*pcChild1 = NULL;

		if (pc_child1 != NULL)
		{
			delete pc_child1;
		}
		delete pc_child2;

		return -1;
	} //if  (i_insert_res  ==  2)


	return 1;
} //int  VirtualWay::iCross(VirtualWay *pcFather,  VirtualWay *pcChild1, VirtualWay *pcChild2)


/*
returned values:
1  -  ok
0  -  memory allocation problems
-1 -  unable to communicate wuth other objects
*/
int VirtualWay::iMutate
(
	VirtualWay** pcNewWay,
	VirtualWayDatabase* pCVirtualWays,
	NETSimulator* pcNetSim
)
{
	VirtualWay* pc_new_way;

	*pcNewWay = NULL;

	pc_new_way = new VirtualWay;
	if (pc_new_way == NULL)
	{
		return 0;
	}


	long* pl_actual_way;
	int i_actual_way_len;

	i_actual_way_len = iGetWay(&pl_actual_way);


	//now we find the start and finish mutation nodes
	int i_start_mut_node, i_finish_mut_node;

	i_start_mut_node = (int)lRand((i_actual_way_len + 1) / 2);
	i_finish_mut_node = i_start_mut_node;
	while (i_start_mut_node == i_finish_mut_node)
	{
		i_finish_mut_node = (int)lRand((i_actual_way_len + 1) / 2);
	}


	i_start_mut_node *= 2;
	i_finish_mut_node *= 2;


	long l_start_mut_node_id;
	long l_finish_mut_node_id;

	l_start_mut_node_id = pl_actual_way[i_start_mut_node];
	l_finish_mut_node_id = pl_actual_way[i_finish_mut_node];


	VirtualWay* pc_inserted_way;
	long* pl_inserted_way;
	int i_inserted_way_len;


	pc_inserted_way =
		pCVirtualWays->pcGetVirtualWay(l_start_mut_node_id, l_finish_mut_node_id, true);

	i_inserted_way_len = pc_inserted_way->iGetWay(&pl_inserted_way);


	int i_new_way_len;
	long* pl_new_way;

	i_new_way_len = i_start_mut_node + 1
		+
		i_inserted_way_len - 1
		+
		i_actual_way_len - i_finish_mut_node - 1;


	pl_new_way = new long[i_new_way_len];

	if (pl_new_way == NULL)
	{
		delete pc_new_way;
		return 0;
	} //if  (pl_new_way  ==  NULL)


	//now we fill up the ways
	int ii, ij, ik;
	for (ii = 0; ii < i_start_mut_node + 1; ii++)
	{
		pl_new_way[ii] = pl_actual_way[ii];
	}

	ii--;
	for (ij = 1; ij < i_inserted_way_len; ij++)
	{
		pl_new_way[ii + ij] = pl_inserted_way[ij];
	}

	ij--;
	for (ik = 1; ik < i_actual_way_len - i_finish_mut_node; ik++)
	{
		pl_new_way[ii + ij + ik] = pl_actual_way[ik + i_finish_mut_node];
	}


	if (pc_new_way->bSetWay(pl_new_way, i_new_way_len) == false)
	{
		delete pc_new_way;
		delete[] pl_new_way;

		return -1;
	} //if  (pc_new_way->bSetWay(pl_new_way,i_new_way_len)  ==  false)


	//now we cane freely delete the table with new way
	delete[] pl_new_way;


	//now we try to input the virtual ways into the database
	//if there alredy is the same way we delete currently created and use the older one
	VirtualWay* pc_the_same_way;
	int i_insert_res;

	i_insert_res = pCVirtualWays->iInputNewVirtWay(pc_new_way,
	                                               pl_way[0], pl_way[i_way_length - 1],
	                                               &pc_the_same_way);


	//if the created way already exists
	if (i_insert_res == 2)
	{
		*pcNewWay = pc_the_same_way;
		delete pc_new_way;
	} //if  (i_insert_res  ==  2)

	if (i_insert_res == 1)
	{
		*pcNewWay = pc_new_way;
	}


	//if the operation was unsuccesful we delete everything and return false
	if (i_insert_res < 1)
	{
		delete pc_new_way;
		return i_insert_res;
	} //if  (i_insert_res  ==  2)


	return 1;
} //VirtualWay  * VirtualWay::pcMutate(VirtualWayDatabase  *pCVirtualWays)


/*
returned  values:
1  -  ok
-1 -  number of ways below 0
-2 -  unexpected end of file
-3 -  memory allocation problems
-4 -  bad node number
-5 -  bad link number
-6 -  way setting unsuccessfull
*/
int VirtualWay::iLoadWay(FILE* pfSource, LFLNetEvaluator* pcTranslator, bool bTranslate)
{
	int i_way_length_buf;


	if (feof(pfSource) == 0)
	{
		fscanf(pfSource, "%d", &i_way_length_buf);
	}
	else
	{
		return -2;
	}


	long* pl_way_buf;

	pl_way_buf = new long[i_way_length_buf];

	if (pl_way_buf == NULL)
	{
		return -3;
	}


	long l_num;

	if (feof(pfSource) == 0)
	{
		fscanf(pfSource, "%ld", &l_num);
	}
	else
	{
		return -2;
	}


	if (bTranslate == true)
	{
		pl_way_buf[0] = pcTranslator->lTranslateNodeNum(l_num);
	}
	else
	{
		pl_way_buf[0] = l_num;
	}


	if (pl_way_buf[0] < 0)
	{
		delete[] pl_way_buf;
		return -4;
	} //if  (pl_way_buf[0]  <  0)


	for (int ii = 0; ii < (i_way_length_buf - 1) / 2; ii++)
	{
		if (feof(pfSource) == 0)
		{
			fscanf(pfSource, "%ld", &l_num);
		}
		else
		{
			delete[] pl_way_buf;
			return -2;
		} //else  if  (feof(pfSource)  ==  0)


		if (bTranslate == true)
		{
			pl_way_buf[ii * 2 + 1] = pcTranslator->lTranslateLinkNum(l_num);
		}
		else
		{
			pl_way_buf[ii * 2 + 1] = l_num;
		}


		if (pl_way_buf[ii * 2 + 1] < 0)
		{
			delete[] pl_way_buf;
			return -5;
		} //if  (pl_way_buf[ii * 2 + 1]  <  0)  


		if (feof(pfSource) == 0)
		{
			fscanf(pfSource, "%ld", &l_num);
		}
		else
		{
			delete[] pl_way_buf;
			return -2;
		} //else  if  (feof(pfSource)  ==  0)


		if (bTranslate == true)
		{
			pl_way_buf[ii * 2 + 2] = pcTranslator->lTranslateNodeNum(l_num);
		}
		else
		{
			pl_way_buf[ii * 2 + 2] = l_num;
		}


		if (pl_way_buf[ii * 2 + 2] < 0)
		{
			delete[] pl_way_buf;
			return -4;
		} //if  (pl_way_buf[ii * 2 + 2]  <  0)  
	} //for  (int  ii; ii < i_way_length_buf; ii++)


	if (bSetWay(pl_way_buf, i_way_length_buf) == false)
	{
		delete[] pl_way_buf;
		return -6;
	} //if  (bSetWay(pl_way_buf, i_way_length_buf)  ==  false)  


	//now we must delete the buffer
	delete[] pl_way_buf;


	return 1;
} //int  VirtualWay::iLoadWay(FILE  *pfSource, CTopologyTranslator *pcTranslator)


void VirtualWay::v_remove_loops_from_way()
{
	for (int ii = 0; ii < i_way_length; ii += 2)
	{
		for (int ij = ii + 2; ij < i_way_length; ij += 2)
		{
			//if there are 2 the same nodes we cut them everything between them down
			if (pl_way[ii] == pl_way[ij])
			{
				for (int ik = 0; ij + ik < i_way_length; ik++)
				{
					pl_way[ii + ik] = pl_way[ij + ik];
				}

				i_way_length = i_way_length - (ij - ii);

				ij = ii + 2;
			} //if  (pl_way[ii]  ==  pl_way[ij])
		} //for  (int ij = ii + 2; ij < i_way_length;  ij+=2)
	} //for  (int ii = 0; ii < i_way_length;  ii+=2)
} //void  VirtualWay::v_remove_loops_from_way()


bool VirtualWay::operator ==(VirtualWay& pcOther)
{
	if (pcOther.i_way_length != i_way_length)
	{
		return false;
	}

	for (int ii = 0; ii < i_way_length; ii++)
	{
		if (pcOther.pl_way[ii] != pl_way[ii])
		{
			return false;
		}
	}


	return true;
} //bool  VirtualWay::operator ==(VirtualWay  &pcOther)


void VirtualWay::vCreateReportFile(FILE* pfReport)
{
	fprintf(pfReport, "%d", i_way_length);

	for (int ii = 0; ii < i_way_length; ii++)
	{
		fprintf(pfReport, " %ld", pl_way[ii]);
	}
} //void   VirtualWay::vCreateReportFile(FILE  *pfReport)


//-------------------------------------------------------------------------------------------
//--------------------------implementation of class CVirtualWaysSingleSet--------------------------

CVirtualWaysSingleSet::CVirtualWaysSingleSet()
{
} //CVirtualWaysSingleSet::CVirtualWaysSingleSet()


CVirtualWaysSingleSet::~CVirtualWaysSingleSet()
{
	c_virtual_ways.first();

	for (long li = 0; li < c_virtual_ways.getCapacity(); li++)
	{
		delete (VirtualWay*)c_virtual_ways.getNode()->getObject();


		c_virtual_ways.next();
	} //for  (long  li = 0; li < virtualWays.getCapacity(); li++)


	c_virtual_ways.bye(false);
} //CVirtualWaysSingleSet::~CVirtualWaysSingleSet()


/*
returned  values:
1  -  ok
-1 -  number of ways below 0
-2 -  unexpected end of file
-3 -  error creating the virtual way
-4 -  insertion into list unsuccessfull
-5 -  virtual way not apropriate for a given topology
*/
int CVirtualWaysSingleSet::iLoadVirtualWays
(FILE* pfSource, LFLNetEvaluator* pcTranslator, bool bTranslate)
{
	long l_number_of_ways;


	if (feof(pfSource) == 0)
	{
		fscanf(pfSource, "%ld", &l_number_of_ways);
	}
	else
	{
		return -2;
	}


	if (l_number_of_ways < 0)
	{
		return -1;
	}


	VirtualWay* pc_virt_way;

	for (long li = 0; li < l_number_of_ways; li++)
	{
		pc_virt_way = new VirtualWay;

		if (pc_virt_way == NULL)
		{
			return -2;
		}
		if (pc_virt_way->iLoadWay(pfSource, pcTranslator, bTranslate) != 1)
		{
			return -3;
		}


		if (iInputNewVirtWay(pc_virt_way, pcTranslator) != 1)
		{
			delete pc_virt_way;
			return -4;
		} //if  (iInputNewVirtWay(pc_virt_way,  pcTranslator)  !=  1)  
	} //for  (long  li = 0; li < l_number_of_ways; li++)


	return 1;
} //int  CVirtualWaysSingleSet::loadVirtualWays


/*
returned values:
2  -  virtual way already exists in the database ()
1  -  ok
0  -  bad way
-3 -  memory allocation problems
*/
int CVirtualWaysSingleSet::iInputNewVirtWay
(VirtualWay* pcNewWay, LFLNetEvaluator* pcTranslator,
 VirtualWay** pcTheSameWayAsNew)
//**pcTheSameWayAsNew is used for returning an addres of the way that is the same in the database
{
	//first we check if the way is correct from topography simulator point of view
	long* pl_way;
	int i_way_length;

	i_way_length = pcNewWay->iGetWay(&pl_way);


	if (pcTranslator->checkConnection(pl_way, i_way_length, 0, false) != 1)
	{
		return 0;
	}


	//now we check if we don't have this way already in the topology
	if (c_virtual_ways.first() == true)
	{
		for (long li = 0; li < c_virtual_ways.getCapacity(); li++)
		{
			if (
				*(VirtualWay*)c_virtual_ways.getNode()->getObject()
				==
				*pcNewWay
			)
			{
				//we return the same way only if we have a given buffer for that
				if (pcTheSameWayAsNew != NULL)
				{
					*pcTheSameWayAsNew = (VirtualWay*)c_virtual_ways.getNode()->getObject();
				}

				return 2;
			} //if

			c_virtual_ways.next();
		} //for  (long  li = 0; li < virtualWays.getCapacity(); li++)
	} //if  (virtualWays.first()  ==  true)

	if (c_virtual_ways.add(pcNewWay) == false)
	{
		return -3;
	}

	pcNewWay->iId = c_virtual_ways.getCapacity();


	return 1;
} //int  CVirtualWaysSingleSet::iInputNewVirtWay(VirtualWay  *pcNewWay)


VirtualWay* CVirtualWaysSingleSet::pcGetVirtualWayAtOffset(int iOffset)
{
	if (c_virtual_ways.setPos(iOffset + 1) == false)
	{
		return NULL;
	}

	return (VirtualWay*)c_virtual_ways.getNode()->getObject();
} //VirtualWay*  CVirtualWaysSingleSet::pcGetVirtualWay()


VirtualWay* CVirtualWaysSingleSet::pcGetVirtualWay()
{
	if (c_virtual_ways.setPos(lRand(c_virtual_ways.getCapacity()) + 1) == false)
	{
		return NULL;
	}

	return (VirtualWay*)c_virtual_ways.getNode()->getObject();
} //VirtualWay*  CVirtualWaysSingleSet::pcGetVirtualWay()


bool CVirtualWaysSingleSet::bGet2VirtualWaysWithLowLevelFOM
(
	NETSimulator* pcNetSim,
	VirtualWay** pcMother, VirtualWay** pcFather,
	bool bTranslated
)
{
	double* pd_pop_fom;

	pd_pop_fom = new double[c_virtual_ways.getCapacity()];
	if (pd_pop_fom == NULL)
	{
		return false;
	}


	//first we compute the whole "population" fom
	double d_pop_fom, d_specie_fom;
	VirtualWay* pc_vw_buf;


	c_virtual_ways.first();
	d_pop_fom = 0;

	long li;
	for (li = 0; li < c_virtual_ways.getCapacity(); li++)
	{
		pc_vw_buf = (VirtualWay*)c_virtual_ways.getNode()->getObject();

		d_specie_fom = pc_vw_buf->dCountFOM(pcNetSim);


		d_pop_fom += d_specie_fom;
		pd_pop_fom[li] = d_specie_fom;

		c_virtual_ways.next();
	} //for  (long  li = 0; li < virtualWays.getCapacity(); li++)


	//mother
	double d_rand = dRand();
	d_rand *= d_pop_fom;


	double d_sum = 0;
	bool b_found = false;

	c_virtual_ways.first();
	for (li = 0; li < c_virtual_ways.getCapacity() && b_found == false; li++)
	{
		d_sum += pd_pop_fom[li];
		if (d_sum > d_rand)
		{
			*pcMother = (VirtualWay*)c_virtual_ways.getNode()->getObject();
			b_found = true;
		} //if (d_sum  >  d_rand)
	} //for  (li = 0; li < virtualWays.getCapacity(); li++)

	if (b_found == false)
	{
		c_virtual_ways.last();
		*pcMother = (VirtualWay*)c_virtual_ways.getNode()->getObject();
	} //if  (b_found  ==  false)


	if (pcFather == NULL)
	{
		c_virtual_ways.first();
		delete[] pd_pop_fom;
		return true;
	} //if  (pcFather  ==  NULL)

	//father
	d_rand = dRand();
	d_rand *= d_pop_fom;

	d_sum = 0;
	b_found = false;

	c_virtual_ways.first();
	for (li = 0; li < c_virtual_ways.getCapacity() && b_found == false; li++)
	{
		d_sum += pd_pop_fom[li];
		if (d_sum > d_rand)
		{
			*pcFather = (VirtualWay*)c_virtual_ways.getNode()->getObject();
			b_found = true;
		} //if (d_sum  >  d_rand)
	} //for  (li = 0; li < virtualWays.getCapacity(); li++)

	if (b_found == false)
	{
		c_virtual_ways.last();
		*pcFather = (VirtualWay*)c_virtual_ways.getNode()->getObject();
	} //if  (b_found  ==  false)

	c_virtual_ways.first();
	delete[] pd_pop_fom;
	return true;
} //void  CVirtualWaysSingleSet::vGet2VirtualWaysWithLowLevelFOM


void CVirtualWaysSingleSet::vCreateReportFile(FILE* pfReport)
{
	fprintf(pfReport, "%ld\n", c_virtual_ways.getCapacity());


	c_virtual_ways.first();


	for (long li = 0; li < c_virtual_ways.getCapacity(); li++)
	{
		((VirtualWay*)c_virtual_ways.getNode()->getObject())->vCreateReportFile(pfReport);

		fprintf(pfReport, "\n");

		c_virtual_ways.next();
	} //for  (long  li = 0; li < virtualWays.getCapacity(); li++)
} //int  CVirtualWaysSingleSet::iCreateConnectionFile(FILE  *pfDest)


/*
returns a number of virtual ways in the set.
If plLengthSets  ==  NULL the only answer will be the above
returned values:
0 or more  -  ok
-1  -  memory allocation problems
-2  -  unexpected trajectory length (this error shouldn't occur)
*/
long CVirtualWaysSingleSet::lGetNumberOfWays(long** plLengthSets, int* piTableLen)
{
	if (plLengthSets == NULL)
	{
		return c_virtual_ways.getCapacity();
	}


	//searching for the longest virual way
	int i_longest_way_len = 0;
	long* pl_buf;

	c_virtual_ways.first();
	for (long li = 0; li < c_virtual_ways.getCapacity(); li++)
	{
		if (
			((VirtualWay*)c_virtual_ways.getObject())->iGetWay(&pl_buf)
			>
			i_longest_way_len
		)
		{
			i_longest_way_len
				=
				((VirtualWay*)c_virtual_ways.getObject())->iGetWay(&pl_buf);
		}

		c_virtual_ways.next();
	} //for (long li = 0; li < virtualWays.getCapacity(); li++)


	if (i_longest_way_len == 0)
	{
		*plLengthSets = NULL;
		*piTableLen = 0;
		return 0;
	} //if  (i_longest_way_len  ==  0)


	//now we create a proper table for statistical information
	*plLengthSets = new long[(i_longest_way_len - 1) / 2];
	if (*plLengthSets == NULL)
	{
		*piTableLen = 0;
		return -1;
	} //if  (*plLengthSets  ==  NULL)
	*piTableLen = (i_longest_way_len - 1) / 2;

	//now preparing the table to work
	for (long li = 0; li < (i_longest_way_len - 1) / 2; li++)
	{
		(*plLengthSets)[li] = 0;
	}


	//now we input the proper nubers of ways into the returned table
	int i_len_buf;
	c_virtual_ways.first();
	for (long li = 0; li < c_virtual_ways.getCapacity(); li++)
	{
		i_len_buf = ((VirtualWay*)c_virtual_ways.getObject())->iGetWay(&pl_buf);

		if (i_len_buf > i_longest_way_len)
		{
			return -2;
		}

		(*plLengthSets)[(i_len_buf - 1) / 2 - 1]++;

		c_virtual_ways.next();
	} //for (li = 0; li < virtualWays.getCapacity(); li++)


	return c_virtual_ways.getCapacity();
} //long  CVirtualWaysSingleSet::lGetNumberOfWays(long  **plLengthSets, int *piTableLen)


//-------------------------------------------------------------------------------------------
//--------------------------implementation of class CSingleTrajectorySet--------------------------


CSingleTrajectorySet::CSingleTrajectorySet()
{
	fomLvlActual = false;
	populationWhenCreated = 0;

	fomLevelPenalized = 0;
	fomLevelPure = 0;
	penaltyPure = 0;

	startFinishPairs = NULL;
	numberOfPairs = 0;
	capacityExtending = true;


	trajectories = NULL;

	fitnessCounter = NULL;
} //CSingleTrajectorySet::CSingleTrajectorySet


CSingleTrajectorySet::~CSingleTrajectorySet()
{
	if (startFinishPairs != NULL)
	{
		delete[] startFinishPairs;
	}


	//if (pc_net_sim != NULL)  delete  pc_net_sim;


	if (trajectories != NULL)
	{
		delete[] trajectories;
	}
} //CSingleTrajectorySet::CSingleTrajectorySet


bool CSingleTrajectorySet::bInit
(long* plStartFinishPairs, int iNumberOfPairs, VirtualWayDatabase* pcWaysDatabase, NETSimulator* pcNetSim,
 FOMfunction* pcFOMcounter, long* plCapacities, long lPenalty)
{
	fitnessCounter = pcFOMcounter;

	fomLevelPenalized = 0;
	fomLevelPure = 0;
	penaltyPure = 0;

	virtualWays = pcWaysDatabase;
	if (virtualWays == NULL)
	{
		return false;
	}


	if (startFinishPairs != NULL)
	{
		delete[] startFinishPairs;
	}

	numberOfPairs = 0;


	startFinishPairs = new long[iNumberOfPairs * 2];

	if (startFinishPairs == NULL)
	{
		return false;
	}

	numberOfPairs = iNumberOfPairs;


	for (int ii = 0; ii < numberOfPairs * 2; ii++)
	{
		startFinishPairs[ii] = plStartFinishPairs[ii];
	}


	//now we init the trajectories
	if (trajectories != NULL)
	{
		delete[] trajectories;
	}
	trajectories = new VirtualWay*[numberOfPairs];
	if (trajectories == NULL)
	{
		return false;
	}


	for (int ii = 0; ii < numberOfPairs; ii++)
	{
		trajectories[ii] =
			virtualWays->pcGetVirtualWay
			(
				startFinishPairs[ii * 2],
				startFinishPairs[ii * 2 + 1]
			);

		//we do NOT break the process HERE!!! because
		//it is an init procedure...
		//if  (trajectories[ii]  ==  NULL)  return(false);
	} //for  (int ii = 0; ii < numberOfPairs; ii++)


	//if (pc_net_sim->copySimulator(pcNetSim) != 1)  return(false);
	pc_net_sim = pcNetSim;

	pc_net_sim->removeAllConnections();
	//if  (b_set_all_conns(plCapacities)  ==  false)  return(false);
	//we allow set all conns to return false, because it is ONLY the init
	b_set_all_conns(plCapacities);
	fomLvlActual = false;

	dCountFOM(fitnessCounter, plCapacities, lPenalty);

	return true;
} //bool  CSingleTrajectorySet::bInit


int CSingleTrajectorySet::getNumberOfValues(int iPairOffset)
{
	if (iPairOffset >= numberOfPairs)
	{
		return -1;
	}
	return virtualWays->iGetVirtualWaysNumber(startFinishPairs[iPairOffset * 2],
	                                              startFinishPairs[iPairOffset * 2 + 1]);
} //int  CSingleTrajectorySet::getNumberOfValues(int  iPairNumber)


bool CSingleTrajectorySet::setAndRateSolution(vector<int>* pvSolution, double* pdFitness, long* plCapacities,
                                               long lPenalty)
{
	if (pvSolution->size() != numberOfPairs)
	{
		return false;
	}

	for (int ii = 0; ii < numberOfPairs; ii++)
	{
		if (
			virtualWays->iGetVirtualWaysNumber(startFinishPairs[ii * 2], startFinishPairs[ii * 2 + 1])
			<= pvSolution->at(ii)
		)
		{
			return false;
		}

		trajectories[ii] =
			virtualWays->pcGetVirtualWayAtOffset
			(
				startFinishPairs[ii * 2],
				startFinishPairs[ii * 2 + 1],
				pvSolution->at(ii)
			);
	} //for  (int ii = 0; ii < numberOfPairs; ii++)

	pc_net_sim->removeAllConnections();
	//if  (b_set_all_conns(plCapacities)  ==  false)  return(false);
	//we allow set all conns to return false, because it is ONLY the init
	b_set_all_conns(plCapacities);
	fomLvlActual = false;

	*pdFitness = dCountFOM(fitnessCounter, plCapacities, lPenalty);

	return true;
} //bool  CSingleTrajectorySet::setAndRateSolution(vector<int>  *pvSolution, double  *pdFitness)


double CSingleTrajectorySet::dCountFOM(FOMfunction* pcFOMcounter, long* plCapacities, long lPenalty)
{
	if (fomLvlActual == true)
	{
		return fomLevelPenalized;
	}

	//now we ask the model about the fom value
	pc_net_sim->removeAllConnections();


	b_set_all_conns(plCapacities); //


	fomLevelPenalized = pcFOMcounter->countFom(pc_net_sim, lPenalty, &capacityExtending, &fomLevelPure,
	                                                &penaltyPure);
	//fomLevelPure = fomLevelPenalized - penaltyPure;


	fomLvlActual = true;
	return fomLevelPenalized;
} //double  CSingleTrajectorySet::countFom(CTopologyTranslator  *pcTranslator)


bool CSingleTrajectorySet::b_set_all_conns(long* plCapacities)
{
	long* pl_buf;
	int i_buf;
	long l_conn_set_result;

	//first we set up all connections
	capacityExtending = false;
	for (int ii = 0; ii < numberOfPairs; ii++)
	{
		if (trajectories[ii] != NULL)
		{
			i_buf = trajectories[ii]->iGetWay(&pl_buf);
			l_conn_set_result = pc_net_sim->setUpConnection(pl_buf, i_buf, plCapacities[ii]);

			if (l_conn_set_result < 1)
			{
				return false;
			} //if  (pcTranslator->lSetUpConnetcion(pl_buf, i_buf, plCapacities[ii])  <  1)

			if (l_conn_set_result == 2)
			{
				capacityExtending = true;
			}
		} //if  (trajectories[ii]  !=  NULL)
		else
		{
			return false;
		}
	} //for  (int ii = 0; ii < numberOfPairs; ii++)


	return true;
} //bool  CSingleTrajectorySet::b_set_all_conns(long *plCapacities,  long  lPenalty)
