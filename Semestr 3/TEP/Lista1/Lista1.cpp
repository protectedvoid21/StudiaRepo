#include <iostream>
#include "CTable.h"

void fillArrayWith34(int arrSize)
{
	const int FILL_NUMBER = 34;

	if (arrSize <= 0)
	{
		return;
	}

	int *tab = new int[arrSize];

	for (int i = 0; i < arrSize; i++)
	{
		tab[i] = FILL_NUMBER;
	}

	for (int i = 0; i < arrSize; i++)
	{
		std::cout << tab[i] << std::endl;
	}

	delete[] tab;
}

bool allocateTwoDimTable(int ***pTable, int width, int height)
{
	if (width <= 0 || height <= 0 || pTable == nullptr)
	{
		return false;
	}

	*pTable = new int *[width];

	for (int i = 0; i < width; i++)
	{
		(*pTable)[i] = new int[height];
		for (int j = 0; j < height; j++)
		{
			(*pTable)[i][j] = i * j;
		}
	}

	return true;
}

bool deallocTwoDimArray(int ***pTable, int width)
{
	if (width <= 0 || pTable == nullptr)
	{
		return false;
	}

	for (int i = 0; i < width; i++)
	{
		delete[](*pTable)[i];
	}

	delete[] * pTable;
	return true;
}

void modifyTable(Table *pTable, int newArraySize)
{
	pTable->setTabSize(newArraySize);
}

void modifyTable(Table table, int newArraySize)
{
	table.setTabSize(newArraySize);
}

void modification()
{
	Table table(true);
	Table *pointerTable;

	table.addOneAndCopy(pointerTable);
	pointerTable->display();

	delete pointerTable;
}

int main()
{
	modification();

	/*std::cout << "ZADANIE 1 (Wypelnienie 6 razy tablicy liczba 34)" << std::endl;
	fillArrayWith34(6);
	std::cout << "\n\n";

	std::cout << "ZADANIE 2 (Alokacja tablicy dwuwymiarowej o wymiarach 3x5)" << std::endl;
	int **tab;
	allocateTwoDimTable(&tab, 5, 3);
	std::cout << "Tab[4][2]: " << tab[4][2] << std::endl;
	std::cout << "Tab[2][1]: " << tab[2][1] << std::endl;
	std::cout << "Tab[1][2]: " << tab[1][2] << std::endl;
	std::cout << "\n\n";

	std::cout << "ZADANIE 3 (Dealokacja tablicy)" << std::endl;
	deallocTwoDimArray(&tab, 5);
	std::cout << "\n\n";

	std::cout << "ZADANIE 4" << std::endl;
	std::cout << "Tworzymy obiekt Table" << std::endl;
	Table table;
	std::cout << "\nZmodyfikujmy obiekt przy pomocy funkcji void modifyTable(Table table, int newArraySize)" << std::endl;
	std::cout << "Przed modyfikacja:\n";
	table.display();
	std::cout << "Po modyfikacji (tablica powinna miec rozmiar 5): ";
	modifyTable(table, 5);
	table.display();

	std::cout << "\nZmodyfikujmy obiekt przy pomocy funkcji void modifyTable(Table &table, int newArraySize)" << std::endl;
	std::cout << "Przed modyfikacja:\n";
	table.display();
	std::cout << "Po modyfikacji (tablica powinna miec rozmiar 15): ";
	modifyTable(&table, 15);
	table.display();
	std::cout << "\n\n";

	std::cout << "Zmienmy rozmiar tablicy na 10\n";
	table.setTabSize(10);
	table.display();*/
}