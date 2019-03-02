#include "Manager.h"

#include <iostream>

using namespace std;

Manager::Manager(string &inputPath)
{
	inF.open(inputPath);
}

bool Manager::CheckWord(string &word)
{
	for (int i = 0; word[i] != '\0'; i++)
	{
		if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') || word[i] == '\'')
		{
			if (word[i] < 'a' && word[i] != '\'')
			{
				word[i] += ('a' - 'A');
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

void Manager::AddToDict(string &word)
{
	Dictionary* ptr = mainNodes;
	for (int i = 0; i < word.size(); i++)
	{
		Node* letter = new Node;
		letter->letter = word[i];
		if (i == word.size() - 1)
		{
			letter->EOW = true;
		}
		ptr = ptr->Add(letter);
	}
}

void Manager::GetData()
{
	string word;
	if (inF.is_open())
	{
		int i = 0;
		while (!inF.eof())
		{
			inF >> word;
			if (CheckWord(word))
			{
				AddToDict(word);
				i++;
			}
		}
		cout << "Found " << i << " words in file" << endl;
	}
}

void PrintData(string &word, Dictionary* it, ofstream& outF)
{
	if (it == nullptr)
	{
		return;
	}
	for (Node* letter = it->head; letter != nullptr; letter = letter->next)
	{
		word.push_back(letter->letter);
		if (letter->EOW)
		{
			outF << word << endl;
		}
		PrintData(word, letter->letters, outF);
		word.pop_back();
	}
}

void Manager::PrinToFile()
{
	outF.open("Result.txt");
	string buf;
	PrintData(buf, mainNodes, outF);
	cin.get();
}


