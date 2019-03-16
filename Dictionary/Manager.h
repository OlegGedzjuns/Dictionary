#pragma once

#include <fstream>
#include <string>
#include <algorithm>
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
	bool AddToDict(string &word);
	int GetData();

	friend void PrintData(string &word, Dictionary* it, ofstream& outF);
	bool PrinToFile();

	friend void Finder(string &word, Dictionary* it, bool &found, int i);
	bool FindWord(string &word);

	friend void correctorA(string &word, Dictionary* it, string &correct, bool &found);
	friend void correctorB(string &word, Dictionary* it, string &correct, bool &found);
	friend void correctorC(string &word, Dictionary* it, string &correct, bool &found);
	string correctorD(string &word, Dictionary* it);

	friend int LevenshteinDist(string &s1, string &s2);
	friend void correctorE(string &word, Dictionary* it, string &correct, string &buf, int &min);
	string FindCorrect(string &word, int i);
};

