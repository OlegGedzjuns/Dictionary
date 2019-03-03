#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

class Manager
{
private:
	ifstream inF;
	ofstream outF;
public:
	int wordCnt = 0;
	bool haveInputFile = false;
	bool haveOutputFile = false;
	Dictionary* mainNodes = new Dictionary;

	Manager() {};
	Manager(string &inputPath);

	bool AddInputFile(string name);
	bool AddOutputFile(string name);
	friend void Counter(Dictionary* it, int &cnt);
	int CountWords();
	bool CheckWord(string &word);
	void AddToDict(string &word);
	int GetData();
	friend void PrintData(string &word, Dictionary* it, ofstream& outF);
	bool PrinToFile();
};

