#include "CTable.h"

Table::Table()
{
	_name = DEFAULT_NAME;
	_pTab = new int[DEFAULT_TAB_SIZE];
	_tableLength = DEFAULT_TAB_SIZE;
	std::cout << NO_PARAM_CTOR_TEXT << _name << std::endl;
}

Table::Table(std::string name, int tableLength)
{
	if (tableLength <= 0)
	{
		tableLength = DEFAULT_TAB_SIZE;
	}

	std::cout << PARAM_TEXT << name << std::endl;
	_name = name;
	_pTab = new int[tableLength];
	_tableLength = tableLength;
}

Table::Table(const Table &pcOther)
{
	_name = pcOther._name + COPY_SUFFIX_TEXT;
	_tableLength = pcOther._tableLength;
	_pTab = new int[_tableLength];
	for (int i = 0; i < pcOther._tableLength; i++)
	{
		_pTab[i] = pcOther._pTab[i];
	}
	std::cout << COPY_TEXT << _name << std::endl;
}

Table::Table(bool isTesting)
{
	if (!isTesting)
	{
		Table();
	}

	_name = "Tester";
	_tableLength = 4;
	_pTab = new int[_tableLength];
	for (int i = 0; i < _tableLength; i++)
	{
		_pTab[i] = i + 1;
	}
}

Table::~Table()
{
	std::cout << DELETE_TEXT << _name << std::endl;
	delete[] _pTab;
}

void Table::setName(std::string name)
{
	_name = name;
}

bool Table::setTabSize(int length)
{
	if (length <= 0)
	{
		return false;
	}

	delete[] _pTab;
	_pTab = new int[length];
	_tableLength = length;

	return true;
}

void Table::addOneAndCopy(Table *&table)
{
	const int ADD_NUMBER = 1;

	table = new Table(_name, _tableLength + 1);

	for (int i = 0; i < _tableLength; i++)
	{
		table->_pTab[i] = _pTab[i];
	}
	table->_pTab[_tableLength] = ADD_NUMBER;
}

void Table::display()
{
	std::cout << NAME_DISPLAY_TEXT << _name << std::endl;
	std::cout << TABLE_LENGTH_TEXT << _tableLength << std::endl;
	std::cout << "Elementy: ";
	for (int i = 0; i < _tableLength; i++)
	{
		std::cout << _pTab[i] << " ";
	}
}

Table *Table::pcClone()
{
	Table *pcClone = new Table(_name, _tableLength);

	for (int i = 0; i < _tableLength; i++)
	{
		pcClone->_pTab[i] = _pTab[i];
	}

	return pcClone;
}