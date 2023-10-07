#pragma once
#include <iostream>
#include <string>

class CTable {
	const std::string defaultName = "Table";
	const int defaultTabSize = 10;

	std::string s_name;
	int *tab;
	int tableLength;
public:
	CTable();
	CTable(std::string sName, int iTableLen);
	CTable(const CTable &pcOther);
	~CTable();
	void vSetName(std::string sName);
	bool bSetNewSize(int iTableLen);
	CTable *pcClone();
};