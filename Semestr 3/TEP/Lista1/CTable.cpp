#include "CTable.h"

CTable::CTable() {
	s_name = defaultName;
	tab = new int[defaultTabSize];
	tableLength = defaultTabSize;
	std::cout << "bezp: " << s_name << std::endl;
}

CTable::CTable(std::string sName, int iTableLen) {
	std::cout << "parametr: " << sName << std::endl;
	s_name = sName;
	tab = new int[iTableLen];
	tableLength = iTableLen;
}

CTable::CTable(const CTable &pcOther) {
	s_name = pcOther.s_name + "_copy";
	for (int i = 0; i < pcOther.tableLength; i++) {
		tab[i] = pcOther.tab[i];
	}
	std::cout << "kopiuj: " << s_name << std::endl;
}

CTable::~CTable() {
	std::cout << "usuwam: " << s_name << std::endl;
	delete[] tab;
}

void CTable::vSetName(std::string sName) {
	s_name = sName;
}

bool CTable::bSetNewSize(int iTableLen) {
	if (iTableLen < 0) {
		return false;
	}

	int *newTab = new int[iTableLen];

	for (int i = 0; i < iTableLen; i++) {
		newTab[i] = tab[i];
	}

	delete[] tab;
	tab = newTab;
	tableLength = iTableLen;

	return true;
}

CTable *CTable::pcClone() {
	CTable *pcClone = new CTable(s_name, tableLength);

	for (int i = 0; i < tableLength; i++) {
		pcClone->tab[i] = tab[i];
	}

	return pcClone;
}