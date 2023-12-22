#include  "NETsimulator.h"

using namespace NetSimulator;


#pragma warning(disable:4996)




//--------------implemenatation of class  NETSimulatorSimplified--------------------------------------------
//--------------------------------------------------------------------------------------------------------------





NETSimulatorSimplified::NETSimulatorSimplified()
{

	nodeIdTool  =  0;
	actualNetworkState  =  NULL;
	pathsPerLink = NULL;
	linksTableForNodes =  NULL;

	numberOfLinks  =  0;
	linksAddressTable  =  NULL;

	allowCapacityOveloading  =  false;

	minimumAllowedDemandIncrease = -1;
}//NETSimulatorSimplified::NETSimulatorSimplified()






NETSimulatorSimplified::~NETSimulatorSimplified()
{

	if  (actualNetworkState  !=  NULL)
	{
		for  (long  li = 0; li < nodeIdTool; li++)
			delete  []  actualNetworkState[li];

		delete  []  actualNetworkState;
	
	}//if  (actualNetworkState  !=  NULL)


	if  (pathsPerLink  !=  NULL)
	{
		for  (long  li = 0; li < nodeIdTool; li++)
			delete  []  pathsPerLink[li];

		delete  []  pathsPerLink;
	
	}//if  (actualNetworkState  !=  NULL)



	if  (linksTableForNodes !=  NULL)
	{
		for  (long  li = 0; li < nodeIdTool; li++)
			delete  []  linksTableForNodes[li];

		delete  []  linksTableForNodes;
	
	}//if  (linksTableForNodes !=  NULL)


	if  (linksAddressTable  !=  NULL)
		delete  []  linksAddressTable;
	


}//NETSimulatorSimplified::~NETSimulatorSimplified()






/*
WARNING: in this type of net simulator both inputted values are unimportant!
WARNING2: this operation RESETS the network state for this model
returns the node id (-1 if the operation is unsuccessfull)
*/
long  NETSimulatorSimplified::addNewNode(long  capacity, CString name)
{

	if  ( linksTableForNodes  ==  NULL&&nodeIdTool  !=  0 )  return-1;
		
	
	long  **pl_new_table, **pl_new_actual_table;
	int  **pi_new_paths_per_link;
	long  lj;



	//first - create the new network tables
	pl_new_table  =  new  long* [nodeIdTool + 1];
	if  (pl_new_table  ==  NULL)  return-1;

	pl_new_actual_table  =  new  long* [nodeIdTool + 1];
	if  (pl_new_actual_table  ==  NULL)  
	{
		delete  []  pl_new_table;
		return-1;
	}//if  (pl_new_actual_table  ==  NULL)  


	pi_new_paths_per_link = new int* [nodeIdTool + 1];
	if  (pi_new_paths_per_link  ==  NULL)  
	{
		delete  []  pl_new_table;
		delete  pl_new_actual_table;
		return-1;
	}//if  (pl_new_actual_table  ==  NULL)  


	for  (long  li = 0; li < nodeIdTool + 1; li++)
	{

		pl_new_table[li]  =  new  long[nodeIdTool + 1];
				
		if  (pl_new_table[li]  ==  NULL)
		{

			for  (long  lj = 0; lj < li; lj++)
				delete  []  pl_new_table[lj];

			delete  []  pl_new_table;

			return-1;
			
		}//if  (pl_new_table[li]  ==  NULL)




		pl_new_actual_table[li]  =  new  long[nodeIdTool + 1];
				
		if  (pl_new_actual_table[li]  ==  NULL)
		{

			for  (lj = 0; lj < li; lj++)
				delete  []  pl_new_actual_table[lj];
			for  (lj = 0; lj < nodeIdTool; lj++)
				delete  []  pl_new_table[lj];

			delete  []  pl_new_table;
			delete  []  pl_new_actual_table;

			return-1;
			
		}//if  (pl_new_table[li]  ==  NULL)


		pi_new_paths_per_link[li] =  new  int[nodeIdTool + 1];

	}//for  (long  li = 0; li < nodeIdTool + 1; li++)





	//now if the old table exists we copy all of the old data into the new table
	for  (long  li = 0; li < nodeIdTool; li++)
	{
		for  (long  lj = 0; lj < nodeIdTool; lj++)
		{
			pl_new_table[li][lj]  =  linksTableForNodes[li][lj];
			pl_new_actual_table[li][lj]  =  linksTableForNodes[li][lj];
			pi_new_paths_per_link[li][lj] = pathsPerLink[li][lj];
		
		}//for  (lj = 0; lj < nodeIdTool; lj++)

		//after copying data we can already delete the parts of table
		delete  []  linksTableForNodes[li];
		delete  []  actualNetworkState[li];
		delete  []  pathsPerLink[li];
		
	}//for  (li = 0; li < nodeIdTool; li++)
	
	//after data copying we can delete the main table structure (the rets of it was already deleted during coping)
	if  (linksTableForNodes  !=  NULL)  delete  []  linksTableForNodes;
	if  (actualNetworkState  !=  NULL)  delete  []  actualNetworkState;
	if  (pathsPerLink  !=  NULL)  delete  []  pathsPerLink;
	
	
	
	//now just setting all the possible links between new node and the rest as 0
	for  (lj = 0; lj < nodeIdTool + 1; lj++)
	{
		pl_new_table[nodeIdTool][lj]  =  0;
		pl_new_actual_table[nodeIdTool][lj]  =  0;
		pi_new_paths_per_link[nodeIdTool][lj]  =  0;
	}//for  (lj = 0; lj < nodeIdTool + 1; lj++)

	for  (long  li = 0; li < nodeIdTool + 1; li++)
	{
		pl_new_table[li][nodeIdTool]  =  0;
		pl_new_actual_table[li][nodeIdTool]  =  0;
		pi_new_paths_per_link[li][nodeIdTool]  =  0;
	}//for  (li = 0; li < nodeIdTool + 1; li++)

	linksTableForNodes  =  pl_new_table;
	actualNetworkState  =  pl_new_actual_table;
	pathsPerLink  =  pi_new_paths_per_link;

	
	return nodeIdTool++;

}//long  NETSimulatorSimplified::addNewNode(long  capacity, CString name)





/*
WARNING: if the link already exists (value > 0) the actual state for it will be reseted
returned values (if it's below 0 it's an error):
0 or more - new link id
-1 - start node does not exist
-2 - finish node does not exist
-3 - memory allocation problem
**-4 - plug operation unsuccesfull
-5 - bad capacity inputted
** - doesn't work for this model
*/ 
long  NETSimulatorSimplified::createLink(long  startNodeId, long  finishNodeId, long capacity)
{

	if  ( startNodeId < 0||startNodeId >= nodeIdTool )  return-1;
	if  ( finishNodeId < 0||finishNodeId >= nodeIdTool )  return-1;

	if  (capacity  <=  0)  return-5;

	//try to allocate the new link addres table
	long  *pl_buf;
	pl_buf  =  new  long[(numberOfLinks + 1) * 2];
	if  (pl_buf  ==  NULL)  return-3;
	

	linksTableForNodes[startNodeId][finishNodeId]  =  capacity;
	actualNetworkState[startNodeId][finishNodeId]  =  capacity;
	pathsPerLink[startNodeId][finishNodeId]  =  0;


	//copy old link addres table into the new one
	for  (long  li = 0; li < numberOfLinks * 2; li++)
		pl_buf[li]  =  linksAddressTable[li];
	
	pl_buf[numberOfLinks * 2]  =  startNodeId;
	pl_buf[numberOfLinks * 2 + 1]  =  finishNodeId;


	if  (linksAddressTable  !=  NULL)  delete  []  linksAddressTable;
	linksAddressTable  =  pl_buf;



	return numberOfLinks++;


}//long  NETSimulatorSimplified::createLink(long  startNodeId, long  finishNodeId, long capacity)








/*
returned values:
1  -  ok
0  -  physically ok, but capacity is too small
-1 -  bad way length
-2 -  parity error
-3 -  capacity below 0
-4 -  one of links does not exist
-5 -  one nodes does not exist or is not a begin/end of one of links
*/
int   NETSimulatorSimplified::checkConnection
		(long  *way, int wayLength, long  capacity, bool checkActualCapacity)
{

	if  (linksTableForNodes  ==  NULL)  return-5;

	//if  (capacity  <  0)  return(-3);

	if  (wayLength  <  3)  return-1;

	//if the way length is a parit number then it is wrong
	int  ii;
	ii  =  wayLength / 2;
	if  (ii * 2  ==  wayLength)  return-2;





	bool  b_capacity_ok;
	long  l_start_node_id;
	long  l_finish_node_id;
	

	b_capacity_ok  =  true;//initial step for loop
	l_finish_node_id  =  way[0];//initial step for loop

	for  (int ij = 0; ij < (wayLength - 1) / 2; ij++)
	{

		l_start_node_id  =  l_finish_node_id;
		l_finish_node_id  =  way[ij * 2 + 2];


		
		//capacity checking only if this is still ok
		if  (b_capacity_ok  ==  true)
		{
			if  (checkActualCapacity  ==  true)
			{

				if  ( l_start_node_id < 0||l_finish_node_id >= nodeIdTool )  return-5;
				if  (linksTableForNodes[l_start_node_id][l_finish_node_id]  <=  0)  return-4;

				if  (actualNetworkState[l_start_node_id][l_finish_node_id]  <  capacity)
					b_capacity_ok  =  false;

			}//if  (checkActualCapacity  ==  true)
			else
			{

				if  ( l_start_node_id < 0||l_finish_node_id >= nodeIdTool )  return-5;
				if  (linksTableForNodes[l_start_node_id][l_finish_node_id]  <=  0)  return-4;

				if  (linksTableForNodes[l_start_node_id][l_finish_node_id]  <  capacity)
					b_capacity_ok  =  false;
			
			}//else if  (checkActualCapacity  ==  true)

		}//if  (b_capacity_ok  ==  true)

	}//for  (int ij = 0; ij < (wayLength - 1) / 2; ij++)


	//if we managed to get here it means that trajectory exists
	//so the value returned depends only on capacity check...

	if  (b_capacity_ok  ==  true)
		return 1;
	else
		return 0;


	return 0;

}//int   NETSimulatorSimplified::checkConnection



long  NETSimulatorSimplified::findLinkIdForNodes(long  startNodeId,  long  finishNodeId)
{
	for  (int  ii = 0; ii < numberOfLinks; ii++)
		if  (
			linksAddressTable[ii*2]  ==  startNodeId&&
			linksAddressTable[ii*2 + 1]  ==  finishNodeId
			)
			return ii;

	return-1;

}//long  NETSimulatorSimplified::findLinkIdForNodes(long  startNodeId,  long  finishNodeId)




bool  NETSimulatorSimplified::isNodeVisited
	(
	vector  <int>  *visitedPathsTree, 
	int  lastPathNodeIndex,
	int  checkedNodeId
	)
{
	int  i_current_node_index  =  lastPathNodeIndex;
	

	while  (true)
	{
		if  (visitedPathsTree->at(i_current_node_index) ==  checkedNodeId)  return true;

		i_current_node_index  =  visitedPathsTree->at(i_current_node_index + 1);
		if  (i_current_node_index  <  0)  return false;	
	}//while  (b_root_found  ==  false)
	
	return false;
}//bool  NETSimulatorSimplified::isNodeVisited(vector  <int>  vVisitedPath)




int  NETSimulatorSimplified::expandPathTree(vector  <int>  *visitedPathTree, int finishNodeId)
{
	int  i_start_size;


	//VERY IMPORTANT!!! 
	//while the loop is running the tree expands, but we only check
	//for expanding the nodes which existed in the tree at the start momment
	i_start_size  =  (int) visitedPathTree->size();

	//expanding loop
	for  (int ii =  0;  ii < i_start_size; ii += 3)
	{
		int  i_current_node_id;
		i_current_node_id  =  visitedPathTree->at(ii);

		if  ( visitedPathTree->at(ii + 2)  ==  -1&&i_current_node_id  !=  finishNodeId )
		{
			if  ( i_current_node_id < 0||i_current_node_id >= nodeIdTool )  return-5;

			int  i_child_number  =  0;
			//now we find all nodes connected to current node
			for  (int i_connected_node_id  =  0;  i_connected_node_id < nodeIdTool;  i_connected_node_id++)
			{
				if  (
					linksTableForNodes[i_current_node_id][i_connected_node_id]  >  0
					&&
					i_current_node_id  !=  i_connected_node_id
					)
				{
					if  (isNodeVisited(visitedPathTree, ii,  i_connected_node_id)  ==  false)
					{
						visitedPathTree->push_back(i_connected_node_id);
						visitedPathTree->push_back(ii);
						visitedPathTree->push_back(-1);

						i_child_number++;				
					}//if  (isNodeVisited(&v_visited_path, i_connected_node)  ==  false)		
				}//if  (linksTableForNodes[i_current_node_id][i_connected_node]  >  0)

			}//for  (int i_connected_node  =  0;  i_connected_node < nodeIdTool;  i_connected_node++)
			

			visitedPathTree->at(ii + 2)  =  i_child_number;
		}//if  ( (visitedPathTree->at(ii + 2)  ==  -1)&&(i_current_node_id  !=  finishNodeId) )

	}//for  (ii =  0;  ii < (int) visitedPathTree->size(); ii += 3)

	return 1;
}//int  NETSimulatorSimplified::expandPathTree(vector  <int>  *visitedPathTree)




int  NETSimulatorSimplified::getShortestWaysForNodes
	(int startNodeId, int finishNodeId, int  shortestWaysNumber, vector <long *> *ways, vector <long> *waysLenghts)
{
	//it is a tree but it is flat
	//it contains 3s:
	//node_id, parent_index, child_num (0..n,  -1 - not checked yet!)
	vector  <int>  v_visited_path_tree;

    v_visited_path_tree.push_back(startNodeId);
	v_visited_path_tree.push_back(-1);
	v_visited_path_tree.push_back(-1);

	int  i_found_ways_counter  =  0;

	while  (i_found_ways_counter  <  shortestWaysNumber)
	{
		if  (expandPathTree(&v_visited_path_tree,  finishNodeId)  !=  1)  return-1;

		//now we check if there is the propoer number of searched ways
		i_found_ways_counter  =  0;
		for  (int ii =  0;  ii < (int) v_visited_path_tree.size(); ii += 3)
		{
			if  (v_visited_path_tree.at(ii)  ==  finishNodeId)  i_found_ways_counter++;	
		}//for  (int ii =  0;  ii < (int) v_visited_path_tree.size(); ii += 3)
	}//while  (i_found_ways_counter  <  shortestWaysNumber)

	
	//now we retrieve the ways
	long  *pl_v_way;
	vector  <int>  v_path_buffer;
	for  (int ii =  0;  ii < (int) v_visited_path_tree.size(); ii += 3)
	{
		v_path_buffer.clear();

		if  (v_visited_path_tree.at(ii)  ==  finishNodeId)
		{
			int  i_current_node_index  =  ii;
			v_path_buffer.push_back(v_visited_path_tree.at(i_current_node_index));

			while  (v_visited_path_tree.at(i_current_node_index + 1)  !=  -1)
			{
				i_current_node_index  =  v_visited_path_tree.at(i_current_node_index + 1);
				v_path_buffer.push_back(v_visited_path_tree.at(i_current_node_index));
				if  (i_current_node_index  <  0)  return-1;	
			}//while  (b_root_found  ==  false)


			//now creating virtual way...
			pl_v_way  =  new  long[(int) v_path_buffer.size() * 2 - 1];
			for  (int ij = 0; ij < (int) v_path_buffer.size(); ij++)
				pl_v_way[ij * 2]  =  v_path_buffer.at(v_path_buffer.size() - 1 - ij);
			
			for  (int ij = 1; ij < (int) v_path_buffer.size() * 2 - 1; ij+=2)
				pl_v_way[ij]  =  findLinkIdForNodes(pl_v_way[ij - 1], pl_v_way[ij + 1]);

			ways->push_back(pl_v_way);
			waysLenghts->push_back((int) v_path_buffer.size() * 2 - 1);
		
		}//if  (v_visited_path_tree.at(ii)  ==  finishNodeId)
	}//for  (int ii =  0;  ii < (int) v_visited_path_tree.size(); ii += 3)


	return 1;    
}//int  NETSimulatorSimplified::getShortestWaysForNodes




int  NETSimulatorSimplified::getShortestWays(int  shortestWaysNumber, vector <long *> *ways, vector <long> *waysLenghts)
{
	int  i_result;
	CString  s_buf;

	for  (int  ii = 0; ii < nodeIdTool; ii++)
	{
		for  (int  ik = 0; ik < nodeIdTool; ik++)
		{
			if  (ii  !=  ik)
			{
				i_result  =  
					getShortestWaysForNodes(ii, ik, shortestWaysNumber, ways, waysLenghts);
				
				if  (i_result  !=  1)
				{
					for  (int  ij = 0; ij < (int) ways->size(); ij++)
						delete  []  ways->at(ij);
					return i_result;
				}//if  (i_result  !=  1)
			}//if  (ii  !=  ik)
		}//for  (int  ii = 0; ii < nodeIdTool; ii++)	
	}//for  (int  ii = 0; ii < nodeIdTool; ii++)

	return 1;
}//int  NETSimulatorSimplified::getShortestWays



/*
returned values:
2  -  capacity too small but the connection is set
1  -  ok
0  -  physically ok, but capacity is too small so the connection was NOT set
-1 -  bad way length
-2 -  parity error
-3 -  capacity below 0
-4 -  one of links does not exist
-5 -  one nodes does not exist or is not a begin/end of one of links
-6 -  mewmory allocation problem
-7 -  connection setting for nodes and links unsuccesfull
-8 -  way set in connection objerct unsuccessfull
*/
long  NETSimulatorSimplified::setUpConnection(long  *way, int wayLength, long  capacity)
{

	bool  b_connection_set_with_too_small_capacity  =  false;

	int i_buf;
	int i_minimum_allowed_demand_increase_on_the_way;
	
	
	//if the trajectory is ok we set up a connection
	i_minimum_allowed_demand_increase_on_the_way = -1;
	for  (int  ii = 2; ii < wayLength;  ii+=2)
	{
		actualNetworkState[way[ii-2]][way[ii]]  =  
			actualNetworkState[way[ii-2]][way[ii]]  -  capacity;

		if  (constSatIncrDemands = true)
		{
			if  (capacity > 0)
				pathsPerLink[way[ii-2]][way[ii]]  =  pathsPerLink[way[ii-2]][way[ii]] + 1;
			else
				pathsPerLink[way[ii-2]][way[ii]]  =  pathsPerLink[way[ii-2]][way[ii]] - 1;

			//computing minimum allowed capacity increase on the way
			i_buf = actualNetworkState[way[ii-2]][way[ii]];
			if  (i_buf > 0)
			{
				if  (pathsPerLink[way[ii-2]][way[ii]] == 0)
					i_buf = CONST_SAT_MAX_DEMAND_INCREASE;
				else
					i_buf = i_buf / pathsPerLink[way[ii-2]][way[ii]];
			}//if  (i_buf > 0)
			else
				i_buf = 0;

			if  (i_minimum_allowed_demand_increase_on_the_way < 0)  i_minimum_allowed_demand_increase_on_the_way = i_buf;
			if  (i_minimum_allowed_demand_increase_on_the_way > i_buf)  i_minimum_allowed_demand_increase_on_the_way = i_buf;
		}//if  (constSatIncrDemands = true)
	}//for  (ii = 0; ii < wayLength;  ii+=2)
		
	
	if  (constSatIncrDemands = true)
	{
		if  (capacity > 0)
		{
			//the minimum may only decrease
			if  (minimumAllowedDemandIncrease < 0)  minimumAllowedDemandIncrease = i_minimum_allowed_demand_increase_on_the_way;
			if  (minimumAllowedDemandIncrease > i_minimum_allowed_demand_increase_on_the_way)  minimumAllowedDemandIncrease = i_minimum_allowed_demand_increase_on_the_way;		
		}//if  (capacity > 0)

		if  (capacity < 0)
		{
			//the minimum may only increase
			if  (minimumAllowedDemandIncrease < i_minimum_allowed_demand_increase_on_the_way)  
			{
				recomputeMinimumAllowedDemandIncrease();
			}//if  (minimumAllowedDemandIncrease < i_minimum_allowed_demand_increase_on_the_way)  
		}//if  (capacity < 0)		
	}//if  (constSatIncrDemands = true)


	if  (b_connection_set_with_too_small_capacity  ==  true)
		return 2;
	else
		return 1;


}//long  NETSimulatorSimplified::setUpConnection(long  *way, int wayLength, long  capacity)




void  NETSimulatorSimplified::recomputeMinimumAllowedDemandIncrease()
{

	int i_buf;
	minimumAllowedDemandIncrease = -1;

	for  (long  li = 0; li < nodeIdTool; li++)
	{
		for  (long  lj = 0; lj < nodeIdTool; lj++)
		{ 
			if  (linksTableForNodes[li][lj]  >  0)
			{
				i_buf = actualNetworkState[li][lj];
				if  (i_buf > 0)
				{
					if  (pathsPerLink[li][lj] == 0)
						i_buf = CONST_SAT_MAX_DEMAND_INCREASE;
					else
						i_buf = i_buf / pathsPerLink[li][lj];
				}//if  (i_buf > 0)
				else
					i_buf = 0;

				if  (minimumAllowedDemandIncrease < 0)  minimumAllowedDemandIncrease = i_buf;
				if  (minimumAllowedDemandIncrease > i_buf)  minimumAllowedDemandIncrease = i_buf;
			}//if  (linksTableForNodes[li][lj]  >  0)
		}//for  (long  lj = 0; lj < nodeIdTool; lj++)
	}//for  (long  li = 0; li < nodeIdTool; li++)

	//CString  s_buf;
	//s_buf.Format("recomputeMinimumAllowedDemandIncrease : %d", minimumAllowedDemandIncrease);
	//::MessageBox(NULL, s_buf, s_buf, MB_OK);
}//void  NETSimulatorSimplified::v_recompute_minimum_allowed_demand()





/*
returned  values:
1  -  ok
0  -  no connections to remove
-1 -  problems occured when removing one or more connections
*/
int  NETSimulatorSimplified::removeAllConnections()
{

	for  (long  li = 0; li < nodeIdTool; li++)
	{

		for  (long  lj = 0; lj < nodeIdTool; lj++)
		{

			actualNetworkState[li][lj]  =  linksTableForNodes[li][lj];
			pathsPerLink[li][lj] = 0;
		
		}//for  (long  lj = 0; lj < nodeIdTool; lj++)

	}//for  (long  li = 0; li < nodeIdTool; li++)

	minimumAllowedDemandIncrease = -1;

	return 1;

}//int  NETSimulatorSimplified::removeAllConnections()







/*
returned values:
any number  -  capacity
WARNING: capactiy may be below 0 in this simulator case so no error cod is returned
if any errors occur the returned value is 0
*/
long  NETSimulatorSimplified::getActLinkCapacity(long  linkId)
{

	long  l_start_node_id,  l_finish_node_id;


	if  (linkId  <  0)  return 0;
	if  (linkId  >=  numberOfLinks)  return 0;

	l_start_node_id  =  linksAddressTable[linkId * 2];
	l_finish_node_id  =  linksAddressTable[linkId * 2 + 1];
	

	if  (constSatIncrDemands == false)	return actualNetworkState[l_start_node_id][l_finish_node_id];

	long l_capa;
	l_capa = actualNetworkState[l_start_node_id][l_finish_node_id];

	if  (minimumAllowedDemandIncrease < 0)  return l_capa;

	l_capa = l_capa - pathsPerLink[l_start_node_id][l_finish_node_id] * (minimumAllowedDemandIncrease + 1);
	return l_capa;
}//long  NETSimulatorSimplified::getActLinkCapacity(long  linkId)






/*
returned values:
any number  -  capacity
WARNING: capactiy may be below 0 in this simulator case so no error cod is returned
if any errors occur the returned value is 0
*/
long  NETSimulatorSimplified::getMaxLinkCapacity(long  linkId)
{

	long  l_start_node_id,  l_finish_node_id;


	if  (linkId  <  0)  return 0;
	if  (linkId  >=  numberOfLinks)  return 0;

	l_start_node_id  =  linksAddressTable[linkId * 2];
	l_finish_node_id  =  linksAddressTable[linkId * 2 + 1];
	

	return linksTableForNodes[l_start_node_id][l_finish_node_id];

}//long  NETSimulatorSimplified::getMaxLinkCapacity(long  linkId)







/*
returned values:
0 or more - capacity
-1  -  number too high
-2  -  number below 0
-3  -  unexpected error or node/link does not exist
*/
double  NETSimulatorSimplified::countNodeLfn(long  nodeId,  long  penalty,  bool  *capacityExtending, double *fitnessPure, double *penaltyPure)
{

	if  (nodeId  <  0)  return-2;
	if  (nodeId  >=  nodeIdTool)  return-1;
	


	//first we compute all max capacity of links outgoing from current node
	//and all dataflow going out of the node
	double  d_max_out_capa;
	double  d_out_data_flow;
	double  d_capacity_extending;//the number of capacity units below 0 in the links outgoing from the node for penalty computing
	
	
	d_max_out_capa  =  0;
	d_out_data_flow  =  0;
	d_capacity_extending  =  0;
	for  (long li = 0; li < nodeIdTool; li++)
	{

		d_max_out_capa  +=  linksTableForNodes[nodeId][li];
		d_out_data_flow  +=  linksTableForNodes[nodeId][li] - actualNetworkState[nodeId][li];


		if  (actualNetworkState[nodeId][li]  <  0)
		{
			d_capacity_extending  +=  actualNetworkState[nodeId][li]*-1;
		}//if  (actualNetworkState[nodeId][li]  <  0)

		
	}//for  (long li = 0; li < nodeIdTool; li++)




	//now we compute LFN result
	double  d_lfn;
	double  d_buf;


	d_lfn  =  0;
	for  (long  li = 0; li < nodeIdTool; li++)
	{

		//we care only of those links that really exists (their max capacity is above 0)
		if  (linksTableForNodes[nodeId][li]  >  0)
		{
			d_buf  =  d_out_data_flow  -  (d_max_out_capa - linksTableForNodes[nodeId][li]);

			if  (d_buf  <  0)  d_buf  =  0;

			d_lfn  +=  d_buf;
		}//if  (linksTableForNodes[nodeId][li]  >  0)
	
	}//for  (li = 0; li < nodeIdTool; li++)



	//now we have to add the capacity extending penalty
	*capacityExtending  =  false;

	double  d_lfn_penalized;
	d_lfn_penalized = d_lfn;

	if  (penalty  >  0)
	{
		if  (d_capacity_extending  >  0)
		{
			
			d_lfn_penalized  +=  d_capacity_extending * penalty;
			d_lfn_penalized  =  d_lfn_penalized * d_lfn_penalized;

			*penaltyPure += d_lfn_penalized - d_lfn;
			*fitnessPure += d_lfn;

			*capacityExtending  =  true;
		}//if  (l_capacity_extending  >  0)
	}//if  (bPenalty  ==  true)






	return d_lfn_penalized;
}//long  NETSimulatorSimplified::lCountNodeLFN(long  nodeId)




double  NETSimulatorSimplified::countNodeLfl(long  nodeId,  long  penalty,  bool  *capacityExtending, double *fitnessPure, double *penaltyPure)
{

	if  (nodeId  <  0)  return-2;
	if  (nodeId  >=  nodeIdTool)  return-1;
	


	//first we compute all max capacity of links outgoing from current node
	//and all dataflow going out of the node
	double  d_max_out_capa, d_max_in_capa;
	double  d_out_data_flow, d_in_data_flow;
	double  d_capacity_extending;//the number of capacity units below 0 in the links outgoing from the node for penalty computing
	
	
	d_max_out_capa  =  0;
	d_out_data_flow  =  0;
	d_max_in_capa  =  0;
	d_in_data_flow  =  0;
	d_capacity_extending  =  0;
	for  (long li = 0; li < nodeIdTool; li++)
	{

		d_max_in_capa  +=  linksTableForNodes[li][nodeId];
		d_in_data_flow  +=  linksTableForNodes[li][nodeId] - actualNetworkState[li][nodeId];

		d_max_out_capa  +=  linksTableForNodes[nodeId][li];
		d_out_data_flow  +=  linksTableForNodes[nodeId][li] - actualNetworkState[nodeId][li];


		if  (actualNetworkState[nodeId][li]  <  0)
		{
			d_capacity_extending  +=  actualNetworkState[nodeId][li]*-1;
		}//if  (actualNetworkState[nodeId][li]  <  0)


		if  (actualNetworkState[li][nodeId]  <  0)
		{
			d_capacity_extending  +=  actualNetworkState[li][nodeId]*-1;
		}//if  (actualNetworkState[nodeId][li]  <  0)

		
	}//for  (long li = 0; li < nodeIdTool; li++)




	//now we compute LFN result
	double  d_lfl;
	double  d_buf;


	d_lfl  =  0;
	for  (long  li = 0; li < nodeIdTool; li++)
	{

		//we care only of those links that really exists (their max capacity is above 0)
		if  (linksTableForNodes[nodeId][li]  >  0)
		{
			d_buf  =  d_out_data_flow  -  (d_max_out_capa - linksTableForNodes[nodeId][li]);

			if  (d_buf  <  0)  d_buf  =  0;

			d_lfl  +=  d_buf;
		}//if  (linksTableForNodes[nodeId][li]  >  0)


		//we care only of those links that really exists (their max capacity is above 0)
		if  (linksTableForNodes[li][nodeId]  >  0)
		{
			d_buf  =  d_in_data_flow  -  (d_max_in_capa - linksTableForNodes[li][nodeId]);

			if  (d_buf  <  0)  d_buf  =  0;

			d_lfl  +=  d_buf;
		}//if  (linksTableForNodes[nodeId][li]  >  0)
	
	}//for  (li = 0; li < nodeIdTool; li++)

	d_lfl  =  d_lfl  /  2.0;

	//now we have to add the capacity extending penalty
	*capacityExtending  =  false;

	double  d_lfl_penalized;
	d_lfl_penalized = d_lfl;

	if  (penalty  >  0)
	{
		if  (d_capacity_extending  >  0)
		{
			
			d_lfl_penalized  +=  d_capacity_extending * penalty;
			d_lfl_penalized  =  d_lfl_penalized * d_lfl_penalized;
			*penaltyPure += d_lfl_penalized - d_lfl;
			*fitnessPure += d_lfl;

			*capacityExtending  =  true;
		}//if  (l_capacity_extending  >  0)
	}//if  (bPenalty  ==  true)


	return d_lfl_penalized;
}//long  NETSimulatorSimplified::lCountNodeLFL(long  nodeId,  long  penalty)










/*
retruned values:
1  -  ok
0  -  file creation impossible
*/
int   NETSimulatorSimplified::presentNetwork(CString  fileName)
{

	FILE  *pf_report;

	
	pf_report  =  fopen( (LPCSTR) fileName.GetString(), "w+");
	if  (pf_report  ==  NULL)  return 0;

	presentNetwork(pf_report,false);

	fclose(pf_report);
	return 1;

}//int   NETSimulatorSimplified::presentNetwork(CString  fileName)







void   NETSimulatorSimplified::presentNetwork(FILE  *destFile,  bool  actualState)
{

	
	fprintf(destFile,"Number of nodes:%ld\n", nodeIdTool);
	fprintf(destFile,"Number of links:%ld\n\n\n", numberOfLinks);

	fprintf(destFile,"  \t");
	for  (long  li = 0; li < nodeIdTool; li++)
		fprintf(destFile,"%ld  \t", li);
	fprintf(destFile,"\n");

	for  (long  li = 0; li < nodeIdTool; li++)
	{
		fprintf(destFile,"%ld  \t", li);

		for  (long  lj = 0; lj < nodeIdTool; lj++)
		{
			if  (linksTableForNodes[li][lj]  ==  0)
				fprintf(destFile,"*  \t");
			else
				if  (actualState  ==  true)
					fprintf(destFile,"%ld  \t",  actualNetworkState[li][lj]);
				else
					fprintf(destFile,"%ld  \t",  linksTableForNodes[li][lj]);
		}//for  (long  lj = 0; lj < nodeIdTool; lj++)
		
		fprintf(destFile,"\n");
	}//for  (long  li = 0; li < nodeIdTool; li++)



	fprintf(destFile,"\n\n\n\nCapacity incr:\n\n");

	for  (long  li = 0; li < nodeIdTool; li++)
	{
		fprintf(destFile,"%ld  \t", li);

		for  (long  lj = 0; lj < nodeIdTool; lj++)
		{
			if  (linksTableForNodes[li][lj]  ==  0)
				fprintf(destFile,"*  \t");
			else
			{
				if  (pathsPerLink[li][lj] == 0)
					fprintf(destFile,"(%ld)  \t",  actualNetworkState[li][lj]);
				else
					fprintf(destFile,"%ld  \t",  actualNetworkState[li][lj]/pathsPerLink[li][lj]);
			}//else
		}//for  (long  lj = 0; lj < nodeIdTool; lj++)
		
		fprintf(destFile,"\n");
	}//for  (long  li = 0; li < nodeIdTool; li++)
	

	fprintf(destFile,"\n\n\n\nWays per link:\n\n");

	for  (long  li = 0; li < nodeIdTool; li++)
	{
		fprintf(destFile,"%ld  \t", li);

		for  (long  lj = 0; lj < nodeIdTool; lj++)
		{
			if  (linksTableForNodes[li][lj]  ==  0)
				fprintf(destFile,"*  \t");
			else
				fprintf(destFile,"%d  \t",  pathsPerLink[li][lj]);
		}//for  (long  lj = 0; lj < nodeIdTool; lj++)
		
		fprintf(destFile,"\n");
	}//for  (long  li = 0; li < nodeIdTool; li++)


	if  (constSatIncrDemands == true)  fprintf(destFile,"\n\n minimumAllowedDemandIncrease: %d\n\n\n\n\n\n", minimumAllowedDemandIncrease); 

	recomputeMinimumAllowedDemandIncrease();

	if  (constSatIncrDemands == true)  fprintf(destFile,"\n\n minimumAllowedDemandIncrease: %d\n\n\n\n\n\n", minimumAllowedDemandIncrease); 
	

}//int   NETSimulatorSimplified::presentNetwork(CString  sFileName)










/*
retruned values:
1  -  ok
0  -  file creation impossible
*/
int   NETSimulatorSimplified::createBasicVirtualDatabaseFile(CString  fileName)
{


	FILE  *pf_report;

	
	pf_report  =  fopen( (LPCSTR) fileName.GetString(), "w+");
	if  (pf_report  ==  NULL)  return 0;


	fprintf(pf_report,"%ld\n\n",  numberOfLinks);


	for  (long  li = 0; li < numberOfLinks; li++)
	{

		fprintf(pf_report,"%ld\n", linksAddressTable[li * 2] );
		fprintf(pf_report,"%ld\n", linksAddressTable[li * 2 + 1]);
		fprintf(pf_report,"1\n");
		fprintf(pf_report,"3 %ld %ld %ld\n", linksAddressTable[li * 2], li, linksAddressTable[li * 2 + 1]);
		fprintf(pf_report,"\n");

	}//for  (long  li = 0; li < listOfLinks.getCapacity(); li++)

	
	fclose(pf_report);

	return 1;


}//int   NETSimulatorSimplified::createBasicVirtualDatabaseFile(CString  fileName)


/*
1 - ok
0 - failed due to unknwon problem
-1 - simulator types different
*/
int  NETSimulatorSimplified::copySimulator(NETSimulator  *otherSimulator)
{
	if  (getSimulatorType()  !=  otherSimulator->getSimulatorType())
		return-1;

	constSatIncrDemands = ((NETSimulatorSimplified *)  otherSimulator)->constSatIncrDemands;
	minimumAllowedDemandIncrease = ((NETSimulatorSimplified *)  otherSimulator)->minimumAllowedDemandIncrease;

	if  (nodeIdTool  !=  ((NETSimulatorSimplified *)  otherSimulator)->nodeIdTool)
	{
		if  (actualNetworkState  !=  NULL)
		{
			for  (long  li = 0; li < nodeIdTool; li++)
				delete  []  actualNetworkState[li];

			delete  []  actualNetworkState;		
		}//if  (actualNetworkState  !=  NULL)
		actualNetworkState  =  NULL;


		if  (pathsPerLink  !=  NULL)
		{
			for  (long  li = 0; li < nodeIdTool; li++)
				delete  []  pathsPerLink[li];

			delete  []  pathsPerLink;		
		}//if  (actualNetworkState  !=  NULL)
		pathsPerLink  =  NULL;



		if  (linksTableForNodes !=  NULL)
		{
			for  (long  li = 0; li < nodeIdTool; li++)
				delete  []  linksTableForNodes[li];

			delete  []  linksTableForNodes;		
		}//if  (linksTableForNodes !=  NULL)
		linksTableForNodes  =  NULL;


		if  (linksAddressTable  !=  NULL)
			delete  []  linksAddressTable;
		linksAddressTable  =  NULL;


		nodeIdTool  =  ((NETSimulatorSimplified *)  otherSimulator)->nodeIdTool;

		linksTableForNodes  =  new  long*[nodeIdTool];
		actualNetworkState  =  new  long*[nodeIdTool];
		pathsPerLink  =  new  int*[nodeIdTool];
		for  (int  ii = 0; ii < nodeIdTool; ii++)
		{
			linksTableForNodes[ii]  =  new  long[nodeIdTool];
			actualNetworkState[ii]  =  new  long[nodeIdTool];		
			pathsPerLink[ii]  =  new  int[nodeIdTool];
		}//for  (int  ii = 0; ii < nodeIdTool; ii++)


		numberOfLinks  =  ((NETSimulatorSimplified *)  otherSimulator)->numberOfLinks;
		linksAddressTable  =  new  long[numberOfLinks  *  2];
	}//if  (nodeIdTool  !=  pcOtherNetowrk->nodeIdTool)



	if  (numberOfLinks  !=  ((NETSimulatorSimplified *)  otherSimulator)->numberOfLinks)
	{
		numberOfLinks  =  ((NETSimulatorSimplified *)  otherSimulator)->numberOfLinks;
		linksAddressTable  =  new  long[numberOfLinks * 2];
	}//if  (numberOfLinks  !=  pcOtherNetowrk->numberOfLinks)



	for  (int  ii = 0; ii < nodeIdTool;  ii++)
	{
		for  (int  ij = 0; ij < nodeIdTool;  ij++)
		{
			linksTableForNodes[ii][ij]  =  ((NETSimulatorSimplified *)  otherSimulator)->linksTableForNodes[ii][ij];
			actualNetworkState[ii][ij]  =  ((NETSimulatorSimplified *)  otherSimulator)->actualNetworkState[ii][ij];
			pathsPerLink[ii][ij]  =  ((NETSimulatorSimplified *)  otherSimulator)->pathsPerLink[ii][ij];
		}//for  (int  ij = 0; ij < nodeIdTool;  ij++)
	}//for  (int  ii = 0; ii < nodeIdTool;  ii++)


	for  (int  ii = 0; ii < numberOfLinks;  ii++)
	{
		linksAddressTable[ii * 2]  =  ((NETSimulatorSimplified *)  otherSimulator)->linksAddressTable[ii * 2];
		linksAddressTable[ii * 2 + 1]  =  ((NETSimulatorSimplified *)  otherSimulator)->linksAddressTable[ii * 2 + 1];	
	}//for  (int  ii = 0; ii < numberOfLinks;  ii++)
			

	return 1;
}//int  NETSimulatorSimplified::copySimulator()


bool  NETSimulatorSimplified::bIsTheSame(NETSimulatorSimplified  *otherNetwork)
{
	if  (nodeIdTool  !=  otherNetwork->nodeIdTool)  return false;
	if  (numberOfLinks  !=  otherNetwork->numberOfLinks)  return false;

	for  (int  ii = 0; ii < nodeIdTool;  ii++)
		for  (int  ij = 0; ij < nodeIdTool;  ij++)
			if  (
					linksTableForNodes[ii][ij]
					!=
					otherNetwork->linksTableForNodes[ii][ij]
				)
				return false;

	return true;

}//bool  NETSimulatorSimplified::bIsTheSame(NETSimulatorSimplified  *otherNetwork)







//----------------------end of implementation of NETSimulatorSimplified--------------------------------------------

















//--------------implemenatation of class  NETsimulatorComplex--------------------------------------------
//--------------------------------------------------------------------------------------------------------------

NETsimulatorComplex::NETsimulatorComplex()
{

	nodeIdTool  =  0;//used as counter of ids of nodes
	linkIdTool  =  0;//used as counter of ids of nodes
	connectionIdTool  =  1;//used as counter of ids of nodes


	//acces optimalization tools
	nodesTable  =  NULL;
	linksTable  =  NULL;
//	pc_connections_table  =  NULL;


}//NETsimulatorComplex::NETsimulatorComplex()




NETsimulatorComplex::~NETsimulatorComplex()
{

	long  l_max;
	long  li;


	listOfNodes.first();
	l_max  =  listOfNodes.getCapacity();

	for  (li = 0; li < l_max; li++)
	{
		delete (NETNode *) listOfNodes.getNode()->getObject();
		listOfNodes.next();
	}//for  (li = 0; li < l_max; li++)



	listOfLinks.first();
	l_max  =  listOfLinks.getCapacity();

	for  (li = 0; li < l_max; li++)
	{
		delete (NETLink *) listOfLinks.getNode()->getObject();
		listOfLinks.next();
	}//for  (li = 0; li < l_max; li++)



	listOfConnections.first();
	l_max  =  listOfConnections.getCapacity();

	for  (li = 0; li < l_max; li++)
	{
		delete (NETConnection *) listOfConnections.getNode()->getObject();
		listOfConnections.next();
	}//for  (li = 0; li < l_max; li++)
	


	
	

	listOfNodes.bye(false);
	listOfLinks.bye(false);
	listOfConnections.bye(false);


	if  (nodesTable  !=  NULL)  delete  nodesTable;
	if  (linksTable  !=  NULL)  delete  linksTable;
//	if  (pc_connections_table  !=  NULL)  delete  pc_connections_table;

}//NETsimulatorComplex::~NETsimulatorComplex()










//returns the node id (-1 if the operation is unsuccessfull)
long  NETsimulatorComplex::addNewNode(long  capacity,  CString  name)
{

	NETNode  *pc_new_node;
	long      l_new_node_id;
	NETNode  **pc_new_nodes_table;


	pc_new_node  =  new  NETNode;

	
	
	if  (pc_new_node  ==  NULL)  return-1;// we return error if the operation is unsuccessfull

	
	if  (pc_new_node->setCapacity(capacity)  ==  false)  return-2;

	
	
	if  (listOfNodes.add(pc_new_node)  ==  false)
	{
		delete  pc_new_node;
		return-1;
	}//if  (listOfNodes.add()  ==  false)




	//first we check wheather there's no free places in current table
	l_new_node_id  =  -1;
	if  (nodesTable  !=  NULL)
	{

		for  (long  li = 0;li < nodeIdTool&&l_new_node_id == -1; li++)
		{

			if  (nodesTable[li]  ==  NULL)  l_new_node_id  =  li;
		
		}//for  (long  li = 0;li < nodeIdTool; li++)
	
	}//if  (nodesTable  !=  NULL)





	//if we have found a free id in the table we set it as new node's id and finish
	if  (l_new_node_id  !=  -1)
	{

		pc_new_node->changeId(l_new_node_id);
		nodesTable[l_new_node_id]  =  pc_new_node;

		return l_new_node_id;
			
	}//if  (l_new_node_id  !=  -1)




	//if there's no free id in the table we have to create a new one and rewrite the values from previous
	nodeIdTool++;
	pc_new_nodes_table  =  new   NETNode*  [nodeIdTool];

	//if the error occurs
	if  (pc_new_nodes_table  ==  NULL)
	{

		nodeIdTool--;
		delete  (NETNode*)  listOfNodes.getNode()->getObject();
		listOfNodes.deleteActual(false);
		return-1;
	
	}//if  (pc_new_nodes_table  ==  NULL)




	//if everything is ok we copy the data and destroy the previous table 
	//and put the new one instead
	for  (long lj = 0; lj < nodeIdTool - 1;lj++)
		pc_new_nodes_table[lj]  =  nodesTable[lj];


	pc_new_node->changeId(nodeIdTool - 1);
	pc_new_nodes_table[nodeIdTool - 1]  =  pc_new_node;


	delete  []  nodesTable;
	nodesTable  =  pc_new_nodes_table;



	return nodeIdTool - 1;



}//long  NETsimulatorComplex::addNewNode(long  capacity,  CString  name)






/*
returned values:
0  -  operation successfull
-1 - node id below 0
-2 - node id above upper border
-3 - node does not exist
-4 - node undeletable!
-5 - fatal error!!! node id was not found in the main list!!!
*/  
int  NETsimulatorComplex::deleteNode(long  nodeId)
{

	//first error communication
	if  (nodeId  <  0)  return-1;
	if  (nodeId  >= nodeIdTool)  return-2;

	if  (nodesTable[nodeId]  ==  NULL)  return-3;

	if  (nodesTable[nodeId]->isDeletable()  ==  false)  return-4;


	//first we must search for the node in the main list
	listOfNodes.first();

	long  l_max  =  listOfNodes.getCapacity();
	bool  b_finished  =  false;

	for  (long  li = 0; li < l_max&&b_finished == false ; li++)
	{

		if  (
			((NETNode*)  listOfNodes.getNode()->getObject())->getId()
			==
			nodeId
			)
		{

			b_finished  =  true;
			delete  (NETNode*)  listOfNodes.getNode()->getObject();
			listOfNodes.deleteActual(false);
		
		}//if

		listOfNodes.next();
	
	}//for  (long  li = 0; (li < l_max)&&(b_finished == false) ; li++)

	
	if  (b_finished  ==  false)  return-5;

	nodesTable[nodeId]  =  NULL;


	return 0;//all ok!



}//bool  NETsimulatorComplex::bDeleteNode(long  nodeId)










/*
returned values:
1  -  ok
0  -  node not found
-1 -  operation unsuccessfull

*/
int   NETsimulatorComplex::setNodeCapacity(long  nodeId, long  newCapacity)
{

	if  (nodesTable  ==  NULL)  return 0;
	if  (nodeIdTool  <=  nodeId)  return 0;
	if  (nodesTable[nodeId]  ==  NULL)  return 0;

	if  (nodesTable[nodeId]->setCapacity(newCapacity)  ==  true)
		return 1;
	else
		return-1;

}//int   NETsimulatorComplex::setNodeCapacity(long  nodeId, newCapacity)










/*
returned values (if it's below 0 it's an error):
0 or more - new link id
-1 - start node does not exist
-2 - finish node does not exist
-3 - memory allocation problem
-4 - plug operation unsuccesfull
-5 - bad capacity inputted
*/ 
long  NETsimulatorComplex::createLink(long  startNodeId, long  finishNodeId,  long capacity)
{

	if  (nodesTable  ==  NULL)  return-1;
	if  (nodesTable[startNodeId]  ==  NULL)  return-1;

	if  (nodesTable[finishNodeId]  ==  NULL)  return-2;

	
	NETLink  *pc_new_link;
	long      l_new_link_id;
	NETLink  **pc_new_links_table;


	pc_new_link  =  new  NETLink;
	if  (pc_new_link->setCapacity(capacity)  ==  false)  return-5;

	if  (
		pc_new_link->plugFinishStart(false,startNodeId,nodesTable[startNodeId])
		==
		false
		)
	{
		delete  pc_new_link;
		return-4;
	}//if



	if  (
		pc_new_link->plugFinishStart(true,finishNodeId,nodesTable[finishNodeId])
		==
		false
		)
	{
		delete  pc_new_link;
		return-4;
	}//if


	
	

	
	if  (pc_new_link  ==  NULL)  return-3;// we return error if the operation is unsuccessfull

	
	
	if  (listOfLinks.add(pc_new_link)  ==  false)
	{
		delete  pc_new_link;
		return-3;
	}//if  (listOfNodes.add()  ==  false)




	//first we check wheather there's no free places in current table
	l_new_link_id  =  -1;
	if  (linksTable  !=  NULL)
	{

		for  (long  li = 0;li < linkIdTool&&l_new_link_id == -1; li++)
		{

			if  (linksTable[li]  ==  NULL)  l_new_link_id  =  li;
		
		}//for  (long  li = 0;li < nodeIdTool; li++)
	
	}//if  (nodesTable  !=  NULL)





	//if we have found a free id in the table we set it as new node's id and finish
	if  (l_new_link_id  !=  -1)
	{

		pc_new_link->changeId(l_new_link_id);
		linksTable[l_new_link_id]  =  pc_new_link;

		return l_new_link_id;
			
	}//if  (l_new_node_id  !=  -1)




	//if there's no free id in the table we have to create a new one and rewrite the values from previous
	linkIdTool++;
	pc_new_links_table  =  new   NETLink*  [linkIdTool];

	//if the error occurs
	if  (pc_new_links_table  ==  NULL)
	{

		linkIdTool--;
		delete  (NETLink *) listOfLinks.getNode()->getObject();
		listOfLinks.deleteActual(false);
		return-1;
	
	}//if  (pc_new_nodes_table  ==  NULL)




	//if everything is ok we copy the data and destroy the previous table 
	//and put the new one instead
	for  (long lj = 0; lj < linkIdTool - 1;lj++)
		pc_new_links_table[lj]  =  linksTable[lj];


	pc_new_link->changeId(linkIdTool - 1);
	pc_new_links_table[linkIdTool - 1]  =  pc_new_link;


	delete  []  linksTable;
	linksTable  =  pc_new_links_table;



	return linkIdTool - 1;



}//long  NETsimulatorComplex::lCreteLink(long  startNodeId, long  finishNodeId)









/*
returned values:
0  -  operation successfull
-1 - link id below 0
-2 - link id above upper border
-3 - link does not exist
-4 - link undeletable!
-5 - fatal error!!! link id was not found in the main list!!!
*/  
int   NETsimulatorComplex::deleteLink(long  linkId)
{

	//first error communication
	if  (linkId  <  0)  return-1;
	if  (linkId  >= linkIdTool)  return-2;

	if  (linksTable[linkId]  ==  NULL)  return-3;

	if  (linksTable[linkId]->isDeletable()  ==  false)  return-4;


	//first we must search for the node in the main list
	listOfLinks.first();

	long  l_max  =  listOfLinks.getCapacity();
	bool  b_finished  =  false;

	for  (long  li = 0; li < l_max&&b_finished == false ; li++)
	{

		if  (
			((NETLink*)  listOfLinks.getNode()->getObject())->getId()
			==
			linkId
			)
		{

			b_finished  =  true;
			delete  (NETLink *) listOfLinks.getNode()->getObject();
			listOfLinks.deleteActual(false);
		
		}//if

		listOfLinks.next();
	
	}//for  (long  li = 0; (li < l_max)&&(b_finished == false) ; li++)

	
	if  (b_finished  ==  false)  return-5;

	linksTable[linkId]  =  NULL;


	return 0;//all ok!


}//int   NETsimulatorComplex::deleteLink(long  linkId)






/*
returned values:
1  -  ok
0  -  physically ok, but capacity is too small
-1 -  bad way length
-2 -  parity error
-3 -  capacity below 0
-4 -  one of links does not exist
-5 -  one nodes does not exist or is not a begin/end of one of links
*/
int   NETsimulatorComplex::checkConnection
	(long  *way, int wayLength, long  capacity, bool checkActualCapacity)
{

	if  (nodesTable  ==  NULL)  return-5;

	if  (capacity  <  0)  return-3;

	if  (wayLength  <  3)  return-1;

	//if the way length is a parit number then it is wrong
	int  ii;
	ii  =  wayLength / 2;
	if  (ii * 2  ==  wayLength)  return-2;



	bool  b_capacity_ok;
	long  l_start_node_id;
	long  l_finish_node_id;
	long  l_link_id;


	b_capacity_ok  =  true;//initial step for loop
	l_finish_node_id  =  way[0];//initial step for loop

	for  (int ij = 0; ij < (wayLength - 1) / 2; ij++)
	{

		l_start_node_id  =  l_finish_node_id;
		l_link_id  =  way[ij * 2 + 1];
		l_finish_node_id  =  way[ij * 2 + 2];


		if  (linksTable  ==  NULL)  return-4;
		if  (linksTable[l_link_id]  ==  NULL)  return-4;
		if  (linksTable[l_link_id]->getStartNodeId()  !=  l_start_node_id)  return-5;
		if  (linksTable[l_link_id]->getFinishNodeId()  !=  l_finish_node_id)  return-5;


		//capacity checking only if this is still ok
		if  (b_capacity_ok  ==  true)
		{
			if  (checkActualCapacity  ==  true)
			{

				if  (nodesTable[l_start_node_id]->getActualCapacity()  <  capacity)
					b_capacity_ok  =  false;

				if  (linksTable[l_link_id]->getActualCapacity()  <  capacity)
					b_capacity_ok  =  false;

			}//if  (checkActualCapacity  ==  true)
			else
			{

				if  (nodesTable[l_start_node_id]->getMaxCapacity()  <  capacity)
					b_capacity_ok  =  false;

				if  (linksTable[l_link_id]->getMaxCapacity()  <  capacity)
					b_capacity_ok  =  false;
			
			}//else if  (checkActualCapacity  ==  true)

		}//if  (b_capacity_ok  ==  true)

	}//for  (int ij = 0; ij < (wayLength - 1) / 2; ij++)


	//the post step of trajectory checking algorithm
	//capacity checking only if this is still ok
	if  (b_capacity_ok  ==  true)
	{
		if  (checkActualCapacity  ==  true)
		{

			if  (nodesTable[l_finish_node_id]->getActualCapacity()  <  capacity)
				b_capacity_ok  =  false;

		}//if  (checkActualCapacity  ==  true)
		else
		{

			if  (nodesTable[l_finish_node_id]->getMaxCapacity()  <  capacity)
				b_capacity_ok  =  false;

		}//else if  (checkActualCapacity  ==  true)

	}//if  (b_capacity_ok  ==  true)

	

	//if we managed to get here it means that trajectory exists
	//so the value returned depends only on capacity check...

	if  (b_capacity_ok  ==  true)
		return 1;
	else
		return 0;


	return 0;

}//int   NETsimulatorComplex::checkConnection(long  *way, int wayLength)







/*
returned values:
0 or more - link id
-1  -  link not found
-2  -  link table empty
*/
long  NETsimulatorComplex::findLinkIdForNodes(long  lStartNode,  long  lFinishNode)
{

	//if the links table does not exist we return an error message
	if  ( linksTable  ==  NULL&&linkIdTool  <  0 )  return-2;

	for  (long  li = 0; li < linkIdTool; li++)
	{

		if  (linksTable[li]  !=  NULL)
		{
			if  (
				linksTable[li]->getStartNodeId()  ==  lStartNode
				&&
				linksTable[li]->getFinishNodeId()  ==  lFinishNode
				)
				return li;//when we find the proper link we just return it and finish whole procedure
							
		
		}//if  (linksTable[li]  !=  NULL)
	
	}//for  (long  li = 0; (b_found == false)&&(li < linkIdTool) ; li++)


	return-1;

}//long  NETsimulatorComplex::findLinkIdForNodes(long  lStartNode,  long  lFinishNode)









/*
returned values:
1 or more  -  ok
0  -  physically ok, but capacity is too small
-1 -  bad way length
-2 -  parity error
-3 -  capacity below 0
-4 -  one of links does not exist
-5 -  one nodes does not exist or is not a begin/end of one of links
-6 -  mewmory allocation problem
-7 -  connection setting for nodes and links unsuccesfull
-8 -  way set in connection objerct unsuccessfull
*/
long  NETsimulatorComplex::setUpConnection(long  *way, int wayLength, long  capacity)
{

	int  i_check_trajectory_result;



	if  (checkConnectionOn  ==  false)
		i_check_trajectory_result  =  1;
	else
		i_check_trajectory_result  =  checkConnection(way, wayLength, capacity);


	if  (i_check_trajectory_result  !=  1)  return i_check_trajectory_result;

	
	//if the trajectory is ok we set up a connection


	NETConnection  *pc_new_connection;

	pc_new_connection  =  new  NETConnection;
	pc_new_connection->setCapacity(capacity);
	if  (pc_new_connection  ==  NULL)  return-6;


	
	
	if  (listOfConnections.add(pc_new_connection)  ==  false)
	{
		delete  pc_new_connection;
		return-6;
	}//if  (listOfNodes.add()  ==  false)



	//we give the connection an id...
	pc_new_connection->changeId(connectionIdTool++);



	//now we have to set up connection for all the nodes and links on the connection way
	if  (
		setConnectionForNodesAndLinks(way, wayLength, pc_new_connection, capacity)  
		==
		false
		)
	{

		delete  (NETConnection *) listOfConnections.getNode()->getObject();
		listOfConnections.deleteActual(false);

		return-7;
			
	}//if



	//now we put the connection way into the connection object
	if  (pc_new_connection->setConnectionWay(way, wayLength)  ==  false )
	{

		removeConnectionOnTheWay(way, wayLength, connectionIdTool);
		return-8;
	}//if  (pc_new_connection->setConnectionWay(way, wayLength)  ==  false )
	




	return connectionIdTool - 1;


}//int   NETsimulatorComplex::iSetUpConnection(long  *way, int wayLength, long  capacity)








bool  NETsimulatorComplex::setConnectionForNodesAndLinks
	(long  *way, int wayLength,  
	 NETConnection *newConnection, long  connectionCapacity)
{


	if  (
		nodesTable[way[0]]->setUpConnection (newConnection, connectionCapacity)
		==
		false
		)
		return false;


	for  (int  ii = 1;  ii <  wayLength;  ii += 2)
	{

		if  (
			linksTable[way[ii]]->setUpConnection (newConnection, connectionCapacity)
			==
			false
			)
		{

			long  l_conn_id;
			l_conn_id  =  newConnection->getId();

			for  (int  ij = ii;  ij > 0; ij = ij - 2)
			{

				linksTable[ij]->removeConnection(l_conn_id);
				nodesTable[ij - 1]->removeConnection(l_conn_id);
			
			}//for  (int  ij = ii;  ij > 0; ij = ij - 2)


			return false;
		
		}//if



		if  (
			nodesTable[way[ii+1]]->setUpConnection (newConnection, connectionCapacity)
			==
			false
			)
		{

			long  l_conn_id;
			l_conn_id  =  newConnection->getId();

			for  (int  ij = ii;  ij > 0; ij = ij - 2)
			{

				nodesTable[ij]->removeConnection(l_conn_id);

				if  (ij - 1 >= 0)
					linksTable[ij - 1]->removeConnection(l_conn_id);
			
			}//for  (int  ij = ii;  ij > 0; ij = ij - 2)


			return false;

		}//if
	
	}//for  (int  ii = 1;  ii <  wayLength;  ii += 2)




	return true;
	

	

}//bool  NETsimulatorComplex::setConnectionForNodesAndLinks







/*
returned values:
1  -  ok
0  -  operarion done, but some of nodes/links returned unsuccessfull result after removal
-1 -  connection not found
*/
int   NETsimulatorComplex::removeConnection(long  connectionId)
{

	NETConnection  *pc_searched_conn;

	//first we find connection and connection way
	if  (listOfConnections.last()  ==  false)  return-1;


	long  l_max;
	bool  b_finished  =  false;
	l_max  =  listOfConnections.getCapacity();

	for  (long  li = 0; li < l_max&&b_finished == false; li++)
	{

		if  (
			((NETConnection *)  listOfConnections.getNode()->getObject())->getId()
			==
			connectionId
			)
		{

			b_finished  =  true;
			pc_searched_conn  =  (NETConnection *) listOfConnections.getNode()->getObject();
			
			listOfConnections.deleteActual(false);
		
		}//if


		listOfConnections.prev();
	
	}//for  (long  li = 0; li < l_max; li++)



	//if we didn't find a proper id in the list
	if  (b_finished  ==  false)  return-2;







	//now we get the way
	long  *pl_way;
	int  i_way_length;
	

	i_way_length  =  pc_searched_conn->getConnectionWay(&pl_way);


	
	if  (removeConnectionOnTheWay(pl_way, i_way_length, connectionId)  ==  true)
	{
		delete  pc_searched_conn;
		return 1;
	}//if  (removeConnectionOnTheWay(pl_way, i_way_length, connectionId)  ==  true)
	else
	{
		delete  pc_searched_conn;
		return 0;
	}//else  if  (removeConnectionOnTheWay(pl_way, i_way_length, connectionId)  ==  true)


}//int   NETsimulatorComplex::removeConnection(long  connectionId)








/*
returned  values:
1  -  ok
0  -  no connections to remove
-1 -  problems occured when removing one or more connections
*/
int  NETsimulatorComplex::removeAllConnections()
{


	if  (listOfConnections.first()  ==  false)  return 0;


	NETConnection  *pc_conn_buff;
	long  *pl_way;
	int   i_way_length;
	bool  b_all_removed_correct  =  true;




	for  (long  li = 0; listOfConnections.first()  ==  true; li++)
	{

		pc_conn_buff  =  (NETConnection *) listOfConnections.getNode()->getObject();
		listOfConnections.deleteActual(false);

		i_way_length  =  pc_conn_buff->getConnectionWay(&pl_way);


		if  (removeConnectionOnTheWay(pl_way, i_way_length, pc_conn_buff->getId())  ==  true)
			delete  pc_conn_buff;
		else
		{
			delete  pc_conn_buff;
			b_all_removed_correct  =  false;
		}//else  if  (removeConnectionOnTheWay(pl_way, i_way_length, pc_conn_buff->getId())  ==  true)
		
	}//for  (long  li = 0; li <  listOfConnections.getCapacity(); li++)


	if  (b_all_removed_correct  ==  true)
		return 1;
	else
		return-1;

}//int  NETsimulatorComplex::removeAllConnections()









bool  NETsimulatorComplex::removeConnectionOnTheWay(long  *way, int wayLength, long  connectionId)
{

	bool  b_all_op_ok = true;// needed to remember that something was wrong during removal



	if  (wayLength  >  0)
	{

		if  (nodesTable[way[0]]->removeConnection(connectionId)  !=  1)
			b_all_op_ok  =  false;


		for  (int  ii = 1; ii < wayLength;  ii+=2)
		{

			if  (linksTable[way[ii]]->removeConnection(connectionId)  !=  1)
				b_all_op_ok  =  false;


			if  (nodesTable[way[ii + 1]]->removeConnection(connectionId)  !=  1)
				b_all_op_ok  =  false;
		
		}//for  (int  ii = 1; ii < i_way_length;  ii+=2)

	
	}//if  (i_way_length  >  0)



	if  (b_all_op_ok  ==  true)
		return 1;
	else
		return 0;




}//bool  NETsimulatorComplex::removeConnectionOnTheWay(long  *way, int wayLength)










/*
returned values:
0 or more - capacity
-1  -  number too high
-2  -  number below 0
-3  -  unexpected error or node/link does not exist
*/
long  NETsimulatorComplex::getActNodeCapacity(long  nodeId)
{

	if  (nodeId  <  0)  return-2;
	if  (nodeId  >=  nodeIdTool)  return-1;
	if  (nodesTable[nodeId]  ==  NULL)  return-3;

	return nodesTable[nodeId]->getActualCapacity();

}//long  NETsimulatorComplex::getActNodeCapacity(long  lNodeNum)




/*
returned values:
0 or more - capacity
-1  -  number too high
-2  -  number below 0
-3  -  unexpected error or node/link does not exist
*/
long  NETsimulatorComplex::getActLinkCapacity(long  linkId)
{

	if  (linkId  <  0)  return-2;
	if  (linkId  >=  linkIdTool)  return-1;
	if  (linksTable[linkId]  ==  NULL)  return-3;

	return linksTable[linkId]->getActualCapacity();

}//long  NETsimulatorComplex::getActLinkCapacity(long  linkId)





/*
returned values:
0 or more - capacity
-1  -  number too high
-2  -  number below 0
-3  -  unexpected error or node/link does not exist
*/
long  NETsimulatorComplex::getMaxNodeCapacity(long  nodeId)
{

	if  (nodeId  <  0)  return-2;
	if  (nodeId  >=  nodeIdTool)  return-1;
	if  (nodesTable[nodeId]  ==  NULL)  return-3;

	return nodesTable[nodeId]->getMaxCapacity();

}//long  NETsimulatorComplex::getMaxNodeCapacity(long  nodeId)






/*
returned values:
0 or more - capacity
-1  -  number too high
-2  -  number below 0
-3  -  unexpected error or node/link does not exist
*/
long  NETsimulatorComplex::getMaxLinkCapacity(long  linkId)
{

	if  (linkId  <  0)  return-2;
	if  (linkId  >=  linkIdTool)  return-1;
	if  (linksTable[linkId]  ==  NULL)  return-3;

	return linksTable[linkId]->getActualCapacity();


}//long  NETsimulatorComplex::getMaxLinkCapacity(long  linkId);






/*
returned values:
0 or more - capacity
-1  -  number too high
-2  -  number below 0
-3  -  unexpected error or node/link does not exist
*/
double    NETsimulatorComplex::countNodeLfn(long  nodeId,  long  penalty,  bool  *capacityExtending, double *penaltyPure)
{

	if  (nodeId  <  0)  return-2;
	if  (nodeId  >=  nodeIdTool)  return-1;
	if  (nodesTable[nodeId]  ==  NULL)  return-3;


	return nodesTable[nodeId]->countLfn();


}//double  NETsimulatorComplex::countNodeLfn(long  nodeId)











/*
retruned values:
1  -  ok
0  -  file creation impossible
*/
int   NETsimulatorComplex::presentNetwork(CString  fileName)
{

	FILE  *pf_report;

	
	pf_report  =  fopen( (LPCSTR) fileName.GetString(), "w+");
	if  (pf_report  ==  NULL)  return 0;



	listOfNodes.first();
	for  (long  li = 0; li < listOfNodes.getCapacity(); li++)
	{

		((NETNode *)  listOfNodes.getNode()->getObject())->present(pf_report);

		listOfNodes.next();

	}//for  (long  li = 0; li < listOfNodes.getCapacity; li++)




	fclose(pf_report);

	return 1;


}//void  NETsimulatorComplex::presentNetwork(CString  fileName)








/*
retruned values:
1  -  ok
0  -  file creation impossible
*/
int   NETsimulatorComplex::createBasicVirtualDatabaseFile(CString  fileName)
{


	FILE  *pf_report;

	
	pf_report  =  fopen( (LPCSTR) fileName.GetString(), "w+");
	if  (pf_report  ==  NULL)  return 0;


	fprintf(pf_report,"%ld\n\n",  listOfLinks.getCapacity());


	listOfLinks.first();
	for  (long  li = 0; li < listOfLinks.getCapacity(); li++)
	{

		((NETLink *)  listOfLinks.getNode()->getObject())->createBasicVirtualWay(pf_report);

		listOfLinks.next();

	}//for  (long  li = 0; li < listOfLinks.getCapacity(); li++)



	fclose(pf_report);

	return 1;


}//int   NETsimulatorComplex::createBasicVirtualDatabaseFile(CStringsFileName)



//----------------------end of implementation of NETsimulatorComplex--------------------------------------------








//--------------implemenatation of class  NETNode--------------------------------------------
//--------------------------------------------------------------------------------------------------------------

NETNode::NETNode()
{

	id  = -1;//"unset" value assigned

	name  =  "no name";

		
	maxCapacity  =  0;//no capacity
	actualCapacity  =  0;

}//NETNode::NETNode()





NETNode::~NETNode()
{

	listNetLinksOut.bye(false);//just delete list components without deleting carried objects
	listNetLinksIn.bye(false);//just delete list components without deleting carried objects
	listOfNetConnections.bye(false);

}//NETNode::~NETNode()





bool  NETNode::changeId(long  newId)
{

	if  (newId  <  0)  return false;

	id  =  newId;

	return true;

}//bool  NETNode::changeId(long  newId)









bool  NETNode::setCapacity(long  newCapacity)
{

	if  (maxCapacity  -  actualCapacity  >  newCapacity)
		return false;


	actualCapacity  =  newCapacity  -  (maxCapacity  -  actualCapacity);
	maxCapacity  =  newCapacity;



	return true;
	

}//bool  NETNode::setCapacity(long  newCapacity)






//if the node is attracted to any connection or link then it is undeletable
bool  NETNode::isDeletable()
{

	//if the lists are not empty we can not delete the node
	if  (listNetLinksIn.first()  ==  true)  return false;
	if  (listNetLinksOut.first()  ==  true)  return false;
	if  (listOfNetConnections.first()  ==  true)  return false;

	return true;

}//bool  NETNode::isDeletable()







bool  NETNode::addNewLink(bool  inOut, NETLink  *newLink)
{

	MyList  *pc_list_for_adding;


	if  (inOut  ==  true)
		pc_list_for_adding  =  &listNetLinksIn;
	else
		pc_list_for_adding  =  &listNetLinksOut;


	if  (pc_list_for_adding->add(newLink)  ==  true)
		return true;
	else
		return false;


}//bool  NETNode::addNewLink(bool  inOut, NETLink  *newLink)








bool  NETNode::removeLink(bool  inOut, NETLink  *removedLink)
{

	MyList  *pc_list_for_removal;


	if  (inOut  ==  true)
		pc_list_for_removal  =  &listNetLinksIn;
	else
		pc_list_for_removal  =  &listNetLinksOut;


	//now we are looking for the specified link
	if  (pc_list_for_removal->first()  ==  false)  return false;


	long  l_max;
	l_max  =  pc_list_for_removal->getCapacity();
	bool  b_finish;
	b_finish  =  false;


	for  (long  li = 0; li < l_max&&b_finish == false; li++)
	{
		if  (
			(NETLink*) pc_list_for_removal->getNode()->getObject()
			==
			removedLink
			)
		{
			b_finish  =  true;
			pc_list_for_removal->deleteActual(false);
		}//if
	}//for  (long  li = 0; (li < l_max)&&(b_finish == false); li++)


	return b_finish;

	

}//bool  NETNode::removeLink(bool  inOut, NETLink  *removedLink)








bool  NETNode::setUpConnection(NETConnection  *newConnection, long  connectionCapacity)
{

	//if it's impossible to set the connection
	if  (actualCapacity  <  connectionCapacity)  return false;

	//if the capacity is ok we set up the connection
	if  (listOfNetConnections.add(newConnection)  ==  false)  return false;

	//now we decrease the actual capacity information
	actualCapacity  =  actualCapacity  -  connectionCapacity;


	return true;
	

}//bool  NETNode::setUpConnection(NETConnection  *newConnection, long  connectionCapacity)







/*
returned values:
1  -  ok
0  -  connection was not found
-1 -  removal of found connection unsuccessfull
*/
int   NETNode::removeConnection(long  connectionId)
{

	//if the list is emopty...
	if  (listOfNetConnections.last()  ==  false)  return 0;


	long  l_list_capacity;
	
	l_list_capacity  =  listOfNetConnections.getCapacity();

	
	
	for  (long  li = 0; li < l_list_capacity; li++)
	{

		if  (
			((NETConnection *) listOfNetConnections.getNode()->getObject())->getId()
			==
			connectionId
			)
		{

			actualCapacity  +=
			(
			(NETConnection *) listOfNetConnections.getNode()->getObject()
			)->getCapacity();
			
				
			//not likely to happen but you never know...
			if  (listOfNetConnections.deleteActual(false)  ==  false) 
			{
				actualCapacity  =  actualCapacity  -
				(
				(NETConnection *) listOfNetConnections.getNode()->getObject()
				)->getCapacity();
				
				return-1;
			}//if  (listOfNetConnections.deleteActual(false)  ==  false) 

			return 1;
		}//if


		listOfNetConnections.prev();
	
	}//for  (long  li = 0; li < l_list_capacity; li++)


	return 0;

}//int   NETNode::removeConnection(long  connectionId)








long  NETNode::countLfn()
{

	//first we compute all max capacity of links outgoing from current node
	//and all dataflow going out of the node
	long  l_max_out_capa;
	long  l_out_data_flow;
	NETLink  *pc_buf_link;


	if  (listNetLinksOut.first()  !=  true)  return 0;


	l_max_out_capa  =  0;
	l_out_data_flow  =  0;
	for  (long li = 0; li < listNetLinksOut.getCapacity(); li++)
	{

		pc_buf_link  =  (NETLink *)  listNetLinksOut.getNode()->getObject();


		l_max_out_capa  +=  pc_buf_link->getMaxCapacity();	
		l_out_data_flow  +=  pc_buf_link->getMaxCapacity() - pc_buf_link->getActualCapacity();

		listNetLinksOut.next();

	}//for  (long li = 0; li < listNetLinksOut.getCapacity; li++)




	//now we compute LFN result
	long  l_lfn;
	long  l_buf;


	listNetLinksOut.first();
	l_lfn  =  0;
	for  (long  li = 0; li < listNetLinksOut.getCapacity(); li++)
	{

		pc_buf_link  =  (NETLink *)  listNetLinksOut.getNode()->getObject();

		l_buf  =  l_out_data_flow  -  (l_max_out_capa - pc_buf_link->getMaxCapacity());

		if  (l_buf  <  0)  l_buf  =  0;

		l_lfn  +=  l_buf;

		listNetLinksOut.next();
	
	}//for  (li = 0; li < listNetLinksOut.getCapacity; li++)



	return l_lfn;


}//double  NETNode::dCountLFN()








void  NETNode::present(FILE  *reportFile)
{

	fprintf(reportFile,"\n\n");

	fprintf(reportFile,"node number:%ld\n", id);
	fprintf(reportFile,"node capacity:%ld\n", maxCapacity);
	fprintf(reportFile,"node actual capacity:%ld\n", actualCapacity);

	fprintf(reportFile,"Number of outgoing links:%ld\n", listNetLinksOut.getCapacity());
	fprintf(reportFile,"Number of incoming links:%ld\n", listNetLinksIn.getCapacity());



}//void  NETNode::present(FILE  reportFile)




//----------------------end of implementation of NETNode--------------------------------------------
















//--------------implemenatation of class  NETLink--------------------------------------------
//--------------------------------------------------------------------------------------------------------------

NETLink::NETLink()
{

	id  = -1;//"unset" value assigned

	name  =  "no name";

		
	maxCapacity  =  0;//no capacity
	actualCapacity  =  0;


	startNodeId  =  -1;//impossible id;
	finishNodeId  =  -1;//impossible id;

	startNode  =  NULL;
	finishNode  =  NULL;


	

}//NETLink::NETLink()





NETLink::~NETLink()
{

	if  (startNodeId >= 0)
	{

		if  (startNode  !=  NULL)
			startNode->removeLink(false,this);
	
	}//if  (startNodeId >= 0)


	if  (finishNodeId >= 0)
	{

		if  (finishNode  !=  NULL)
			finishNode->removeLink(true,this);
	
	}//if  (startNodeId >= 0)



	listOfNetConnections.bye(false);

}//NETLink::~NETLink()







bool  NETLink::changeId(long  newId)
{

	if  (newId  <  0)  return false;

	id  =  newId;

	return true;

}//bool  NETLink::changeId(long  newId)










bool  NETLink::setCapacity(long  newCapacity)
{


	if  (maxCapacity  -  actualCapacity  >  newCapacity)
		return false;


	actualCapacity  =  newCapacity  -  (maxCapacity  -  actualCapacity);
	maxCapacity  =  newCapacity;



	return true;
	

}//bool  NETLink::setCapacity(long  newCapacity)












//if the link is attracted to any connection then it is undeletable
bool  NETLink::isDeletable()
{

	//if the lists are not empty we can not delete the node
	if  (listOfNetConnections.first()  ==  true)  return false;

	return true;

}//bool  NETNode::isDeletable()









bool  NETLink::plugFinishStart(bool  finishStart, long nodeId, NETNode *node)
{


	if  (finishStart  ==  TRUE)
	{

		finishNodeId  =  nodeId;
		finishNode  =  node;
	
	}//if  (finishStart  ==  TRUE)
	else
	{

		startNodeId  =  nodeId;
		startNode  =  node;
	
	}//else  if  (finishStart  ==  TRUE)



	return node->addNewLink(finishStart,this);



}//bool  NETLink::bPlugInOut(bool  bInOut, long LNodeId, NETNode *node)






bool  NETLink::setUpConnection(NETConnection  *newConnection, long  connectionCapacity)
{

	//if it's impossible to set the connection
	if  (actualCapacity  <  connectionCapacity)  return false;

	//if the capacity is ok we set up the connection
	if  (listOfNetConnections.add(newConnection)  ==  false)  return false;

	//now we decrease the actual capacity information
	actualCapacity  =  actualCapacity  -  connectionCapacity;


	return true;
	

}//bool  NETLink::setUpConnection(NETConnection  *newConnection, long  connectionCapacity)






/*
returned values:
1  -  ok
0  -  connection was not found
-1 -  removal of found connection unsuccessfull
*/
int  NETLink::removeConnection(long  connectionId)
{

	//if the list is emopty...
	if  (listOfNetConnections.last()  ==  false)  return 0;


	long  l_list_capacity;
	
	l_list_capacity  =  listOfNetConnections.getCapacity();

	
	
	for  (long  li = 0; li < l_list_capacity; li++)
	{

		if  (
			((NETConnection *) listOfNetConnections.getNode()->getObject())->getId()
			==
			connectionId
			)
		{

			actualCapacity  +=
			(
			(NETConnection *) listOfNetConnections.getNode()->getObject()
			)->getCapacity();
			
				
			//not likely to happen but you never know...
			if  (listOfNetConnections.deleteActual(false)  ==  false) 
			{
				actualCapacity  =  actualCapacity  -
				(
				(NETConnection *) listOfNetConnections.getNode()->getObject()
				)->getCapacity();
				
				return-1;
			}//if  (listOfNetConnections.deleteActual(false)  ==  false) 

			return 1;
		}//if



		listOfNetConnections.prev();
	
	}//for  (long  li = 0; li < l_list_capacity; li++)


	return 0;

}//bool  NETLink::bRemoveConnection(long  connectionId)







void  NETLink::createBasicVirtualWay(FILE  *reportFile)
{

	fprintf(reportFile,"%ld\n",getStartNodeId());
	fprintf(reportFile,"%ld\n",getFinishNodeId());
	fprintf(reportFile,"1\n");
	fprintf(reportFile,"3 %ld %ld %ld\n", getStartNodeId(), id, getFinishNodeId());
	fprintf(reportFile,"\n");

}//void  NETLink::createBasicVirtualWay(FILE  *reportFile)



//----------------------end of implementation of NETLink--------------------------------------------





















//--------------implemenatation of class  NETConnection--------------------------------------------
//--------------------------------------------------------------------------------------------------------------


NETConnection::NETConnection()
{

	id  = -1;//"unset" value assigned

	name  =  "no name";


	capacity  =  0;//no weight

	pl_way  =  NULL;
	i_way_length = 0;


}//NETConnection::NETConnection()




NETConnection::~NETConnection()
{

	if  (pl_way  !=  NULL)  delete [] pl_way;
	

}//NETConnection::~NETConnection






bool  NETConnection::changeId(long  newId)
{

	if  (newId  <  0)  return false;

	id  =  newId;

	return true;

}//bool  NETConnection::changeId(long  newId)






bool  NETConnection::setCapacity(long  newCapacity)
{

	if  (newCapacity  <  0)  return false;


	capacity  =  newCapacity;
	
	return true;

}//bool  NETConnection::setCapacity(long  newCapacity)







bool  NETConnection::setConnectionWay(long  *newWay,  int  wayLength)
{


	if  (pl_way  !=  NULL)  delete  []  pl_way;

	i_way_length = 0;

	
	pl_way  =  NULL;
	pl_way  =  new  long[wayLength];

	if  (pl_way  ==  NULL)  return false;


	for  (int  ii = 0; ii < wayLength; ii++)
		pl_way[ii]  =  newWay[ii];


	i_way_length  =  wayLength;

	return true;


}//bool  NETConnection::setConnectionWay(long  newWay,  int  wayLength)











int  NETConnection::getConnectionWay(long  **way)
{

	*way  =  pl_way;

	return i_way_length;

}//int  NETConnection::getConnectionWay(long  *way)









//----------------------end of implementation of NETConnection--------------------------------------------