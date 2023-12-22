#pragma once


//tools
#include  "atlstr.h"  //CString
#include <windows.h>


//system tools
#include  "list.h"

//vector
#include  <vector>
#include  <iostream>

using namespace std;


namespace NetSimulator
{
	//predefinition of NETway tools
	class NETNode;
	class NETLink;
	class NETConnection;

	//simulator interface  definition
	class NETSimulator
	{
	public:
		virtual int getSimulatorType() = 0;
		virtual int copySimulator(NETSimulator* otherSimulator) = 0;

		virtual bool setAllowCapacityOverloading(bool allow) = 0; //returns the actual state

		virtual long addNewNode(long capacity, CString name) = 0; //returns the node id
		virtual int deleteNode(long nodeId) = 0;
		virtual int setNodeCapacity(long nodeId, long newCapacity) = 0;


		virtual long createLink(long startNodeId, long finishNodeId, long capacity) = 0;
		virtual int deleteLink(long linkId) = 0;

		virtual int checkConnection(long* way, int wayLength, long capacity, bool checkActualCapacity = true) = 0;
		virtual long findLinkIdForNodes(long startNodeId, long finishNodeId) = 0;

		virtual long setUpConnection(long* way, int wayLength, long capacity) = 0;
		virtual int removeConnection(long connectionId) = 0;
		virtual int removeAllConnections() = 0;


		virtual long getActNodeCapacity(long nodeId) = 0;
		virtual long getActLinkCapacity(long linkId) = 0;
		virtual long getMaxNodeCapacity(long nodeId) = 0;
		virtual long getMaxLinkCapacity(long linkId) = 0;


		virtual double countNodeLfn(long nodeId, long penalty, bool* capacityExtending, double* fitnessPure,
		                            double* penaltyPure) = 0;
		virtual double countNodeLfl(long nodeId, long penalty, bool* capacityExtending, double* fitnessPure,
		                            double* penaltyPure) = 0;

		virtual long getNodesNum() = 0;
		virtual long getLinksNum() = 0;


		NETSimulator()
		{
			checkConnectionOn = false;
			constSatIncrDemands = false;
		}

		virtual ~NETSimulator()
		{
		}

		void setConstSatIncrDemands(bool value) { constSatIncrDemands = value; }

		virtual int presentNetwork(CString fileName) = 0;
		virtual void presentNetwork(FILE* destFile, bool actualState) = 0;
		virtual int createBasicVirtualDatabaseFile(CString fileName) = 0;

		void turnConnectionCheck(bool onOff) { checkConnectionOn = onOff; }

		virtual int getShortestWays(int shortestWaysNumber, vector<long*>* ways, vector<long>* waysLenghts) = 0;
		virtual int getShortestWaysForNodes(int startNodeId, int finishNodeId, int shortestWaysNumber,
		                                    vector<long*>* ways, vector<long>* waysLenghts) = 0;

	protected:
		bool checkConnectionOn; //usually set on off - checks wheather the proposed connection is not "wrong"
		bool constSatIncrDemands;
	};


#define  CONST_SAT_MAX_DEMAND_INCREASE  99999

	class NETSimulatorSimplified : public NETSimulator
	{
	public:
		int getSimulatorType() { return 2; }
		int copySimulator(NETSimulator* otherSimulator);

		bool setAllowCapacityOverloading(bool allow)
		{
			allowCapacityOveloading = allow;
			return allow;
		} //returns the actual state

		long addNewNode(long capacity, CString name); //returns the node id
		int deleteNode(long nodeId) { return 1; } //method doesn't work for this network simulator
		int setNodeCapacity(long nodeId, long newCapacity) { return 1; }
		//method doesn't work for this network simulator


		long createLink(long startNodeId, long finishNodeId, long capacity);
		int deleteLink(long linkId) { return 1; } //method doesn't work for this network simulator


		int checkConnection(long* way, int wayLength, long capacity, bool checkActualCapacity = true);
		long findLinkIdForNodes(long startNodeId, long finishNodeId);
		//{return(lStartNodeId * nodeIdTool  +  lFinishNodeId);};


		long setUpConnection(long* way, int wayLength, long capacity);
		//method doesn't work for this network simulator\/ but you can remove connection using setUpConnection with the "-" capacity and the connection checking set "off"
		int removeConnection(long connectionId) { return -2; }
		int removeAllConnections();


		long getActNodeCapacity(long nodeId) { return -3; } //method doesn't work for this network simulator
		long getActLinkCapacity(long linkId);
		long getMaxNodeCapacity(long nodeId) { return -3; } //method doesn't work for this network simulator
		long getMaxLinkCapacity(long linkId);


		double countNodeLfn(long nodeId, long penalty, bool* capacityExtending, double* fitnessPure,
		                    double* penaltyPure);
		double countNodeLfl(long nodeId, long penalty, bool* capacityExtending, double* fitnessPure,
		                    double* penaltyPure);


		NETSimulatorSimplified();
		~NETSimulatorSimplified();

		int presentNetwork(CString fileName);
		void presentNetwork(FILE* destFile, bool actualState);
		int createBasicVirtualDatabaseFile(CString fileName);


		//new methods for CONetAdmin
		long getNodesNum() { return nodeIdTool; }
		long getLinksNum() { return numberOfLinks; }

		bool bIsTheSame(NETSimulatorSimplified* otherNetwork);

		int getShortestWays(int shortestWaysNumber, vector<long*>* ways, vector<long>* waysLenghts);
		int getShortestWaysForNodes(int startNodeId, int finishNodeId, int shortestWaysNumber, vector<long*>* ways,
		                            vector<long>* waysLenghts);

		int getMinimumAllowedDemandIncrease() { return minimumAllowedDemandIncrease; }

	private:
		void recomputeMinimumAllowedDemandIncrease();

		//tools for get shortest ways
		int expandPathTree(vector<int>* visitedPathTree, int finishNodeId);
		bool isNodeVisited(vector<int>* visitedPathsTree, int lastPathNodeIndex, int checkedNodeId);


		long** linksTableForNodes;
		long** actualNetworkState; //if there are no connections inputted it's the same as linksTableForNodes
		int** pathsPerLink;
		int minimumAllowedDemandIncrease;

		long nodeIdTool; //used as counter of ids of nodes

		long numberOfLinks;
		long* linksAddressTable; //store way: (linkId * 2)-start node (linkId * 2+1)-finish node

		bool allowCapacityOveloading;
	}; //class  NETSimulatorSimplified  :  public  NETSimulator


	class NETsimulatorComplex : public NETSimulator
	{
	public:
		int getSimulatorType() { return 2; }
		int copySimulator(NETSimulator* otherSimulator) { return 0; }

		bool setAllowCapacityOverloading(bool allow) { return false; } //method doesn't work for this network simulator

		long addNewNode(long capacity, CString name); //returns the node id
		int deleteNode(long nodeId);
		int setNodeCapacity(long nodeId, long newCapacity);


		long createLink(long startNodeId, long finishNodeId, long capacity);
		int deleteLink(long linkId);


		int checkConnection(long* way, int wayLength, long capacity, bool checkActualCapacity = true);
		long findLinkIdForNodes(long startNodeId, long finishNodeId);

		long setUpConnection(long* way, int wayLength, long capacity);
		int removeConnection(long connectionId);
		int removeAllConnections();


		long getActNodeCapacity(long nodeId);
		long getActLinkCapacity(long linkId);
		long getMaxNodeCapacity(long nodeId);
		long getMaxLinkCapacity(long linkId);


		double countNodeLfn(long nodeId, long penalty, bool* capacityExtending, double* penaltyPure);

		double countNodeLfl(long nodeId, long penalty, bool* capacityExtending, double* penaltyPure)
		{
			return 0;
		}

		//new methods for CONetAdmin
		long getNodesNum() { return listOfNodes.getCapacity(); }
		long getLinksNum() { return listOfLinks.getCapacity(); }


		NETsimulatorComplex();
		~NETsimulatorComplex();

		int presentNetwork(CString fileName);
		void presentNetwork(FILE* destFile, bool actualState) { return; }
		//method doesn't work for this network simulator
		int createBasicVirtualDatabaseFile(CString fileName);

		int getShortestWays(int shortestWaysNumber, vector<long*>* ways, vector<long>* waysLenghts) { return -1; }

		int getShortestWaysForNodes(int startNodeId, int finishNodeId, int shortestWaysNumber, vector<long*>* ways,
		                            vector<long>* waysLenghts) { return -1; }

	private:
		//similar to checkConnection, but it really sets the connection information for nodes abd links!
		bool setConnectionForNodesAndLinks(long* way, int wayLength, NETConnection* newConnection,
		                                   long connectionCapacity);

		bool removeConnectionOnTheWay(long* way, int wayLength, long connectionId);


		MyList listOfNodes;
		MyList listOfLinks;
		MyList listOfConnections;


		long nodeIdTool; //used as counter of ids of nodes
		long linkIdTool; //used as counter of ids of nodes
		long connectionIdTool; //used as counter of ids of nodes


		//acces optimalization tools
		NETNode** nodesTable;
		NETLink** linksTable;
		//	NETConnection  **pc_connections_table;
	}; //class  NETsimulatorComplex  :  public  NETSimulator


	class NETNode
	{
		friend class NETsimulatorComplex;

	public:
		long getId() { return id; }

		long getActualCapacity() { return actualCapacity; }
		long getMaxCapacity() { return maxCapacity; }
		bool setCapacity(long newCapacity);


		bool addNewLink(bool inOut, NETLink* newLink);
		bool removeLink(bool inOut, NETLink* removedLink);


		bool setUpConnection(NETConnection* newConnection, long connectionCapacity);
		int removeConnection(long connectionId);


		bool isDeletable(); //if the node is attracted to any connection or link then it is undeletable
		void setName(CString newName) { name = newName; }


		NETNode();
		~NETNode();


		long countLfn();

		void present(FILE* reportFile);

	private:
		bool changeId(long newId);


		//inforamtion part

		long id; //identification number of this node (given from outside)

		CString name; //set by user (unimportant from system point of view)


		long maxCapacity;
		long actualCapacity;


		MyList listNetLinksOut; //list of links going from the node to the other ones
		MyList listNetLinksIn; //list of links going to the node to the other ones
		MyList listOfNetConnections; //list of connections going through the node
	}; //class  NETNode


	class NETLink
	{
		friend class NETsimulatorComplex;

	public:
		long getId() { return id; }

		long getActualCapacity() { return actualCapacity; }
		long getMaxCapacity() { return maxCapacity; }
		bool setCapacity(long newCapacity);


		bool plugFinishStart(bool finishStart, long nodeId, NETNode* node);

		long getStartNodeId() { return startNodeId; }
		long getFinishNodeId() { return finishNodeId; }


		bool setUpConnection(NETConnection* newConnection, long connectionCapacity);
		int removeConnection(long connectionId);


		bool isDeletable(); //if the link is attracted to any connection then it is undeletable
		void setName(CString newName)
		{
			name = newName;
		}


		void createBasicVirtualWay(FILE* reportFile);

		NETLink();
		~NETLink();

	private:
		bool changeId(long newId);


		//data part


		long id; //identification number of this link  (given from outside)

		CString name; //set by user (unimportant from system point of view)


		long maxCapacity;
		long actualCapacity;


		//start and finish node information
		long startNodeId;
		NETNode* startNode;

		long finishNodeId;
		NETNode* finishNode;


		MyList listOfNetConnections; //list of connections going through the link
	};


	class NETConnection
	{
		friend class NETsimulatorComplex;

	public:
		long getId() { return id; }

		long getCapacity() { return capacity; }


		bool setConnectionWay(long* newWay, int wayLength);
		int getConnectionWay(long** way);


		bool setCapacity(long newCapacity);
		void setName(CString newName) { name = newName; }


		NETConnection();
		~NETConnection();

	private:
		bool changeId(long newId);


		long id;

		CString name; //set by user (unimportant from system point of view)


		long capacity; //how much capacity it takes

		long* pl_way;
		int i_way_length;
	}; //class  NETConnection
}; //namespace NetSimulator
