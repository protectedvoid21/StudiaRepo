#pragma once
#include <iostream>
#include <string>

class Table
{
	const std::string DEFAULT_NAME = "Table";
	const int DEFAULT_TAB_SIZE = 10;

	const std::string NO_PARAM_CTOR_TEXT = "bezp: ";
	const std::string NAME_DISPLAY_TEXT = "nazwa: ";
	const std::string DELETE_TEXT = "usuwam: ";
	const std::string PARAM_TEXT = "parametr: ";
	const std::string COPY_TEXT = "kopiuj: ";
	const std::string COPY_SUFFIX_TEXT = "_copy";
	const std::string DESTROY_TEXT = "usuwam: ";
	const std::string TABLE_LENGTH_TEXT = "dlugosc tablicy: ";

	std::string _name;
	int *_pTab;
	int _tableLength;

public:
	Table();
	Table(std::string name, int tableLength);
	Table(const Table &pcOther);
	Table(bool isTesting);
	~Table();
	void display();
	void setName(std::string name);
	bool setTabSize(int length);
	void addOneAndCopy(Table *&table);
	Table *pcClone();
};