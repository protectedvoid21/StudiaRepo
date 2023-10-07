#include <iostream>
#include "CTable.h"

void v_alloc_table_fill_34(int iSize) {
	const int fillNumber = 34;

	if (iSize < 0) {
		iSize = 0;
	}

	int *tab = new int[iSize];

	for (int i = 0; i < iSize; i++) {
		tab[i] = fillNumber;
	}

	for (int i = 0; i < iSize; i++) {
		std::cout << tab[i] << std::endl;
	}
}

bool b_alloc_table_2_dim(int **&piTable, int iSizeX, int iSizeY) {
	piTable = new int *[iSizeX];

	if (piTable == nullptr) {
		return false;
	}

	for (int i = 0; i < iSizeX; i++) {
		piTable[i] = new int[iSizeY];

		if (piTable[i] == nullptr) {
			for (int j = 0; j < i; j++) {
				delete[] piTable[j];
			}
			delete[] piTable;
			return false;
		}
	}

	return true;
}

bool b_dealloc_table_2_dim(int **&piTable, int iSizeX, int iSizeY) {
	for (int i = 0; i < iSizeX; i++) {
		delete[] piTable[i];
	}

	delete[] piTable;
	return true;
}

void v_mod_tab(CTable *pcTab, int iNewSize) {
	pcTab->bSetNewSize(iNewSize);
}

void v_mod_tab(CTable cTab, int iNewSize) {
	cTab.bSetNewSize(iNewSize);
}

int main() {

}