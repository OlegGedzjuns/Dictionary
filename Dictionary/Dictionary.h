#pragma once

#include <string>
#include <fstream>
#include "Collections.h"

using namespace std;
using namespace SortedList;

class Dictionary_class
{
private:
	ifstream _inputF;
	ofstream _outputF;
	SortedList_class<string>* _storage;

	bool CheckWord(string &word);
	int GetWords();
	void PrintWords();
public:
	Dictionary_class(string inputPath, string outputPath);
	~Dictionary_class();

	int Create();
};

