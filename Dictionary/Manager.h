#pragma once

#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

class Manager
{
private:
	int wordCnt = 0;
	ifstream inF;
	ofstream outF;
public:
	Dictionary* mainNodes = new Dictionary;

	Manager() {};
	Manager(string &inputPath);

	bool CheckWord(string &word);
	void AddToDict(string &word);
	void GetData();
	friend void PrintData(string &word, Dictionary* it, ofstream& outF);
	void PrinToFile();
};

