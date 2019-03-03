#include "Manager.h"

Manager::Manager(string &inputPath)
{
	inF.open(inputPath);
	if(inF.is_open())
		haveInputFile = true;
}

bool Manager::AddInputFile(string name)
{
	inF.open(name);
	if (inF.is_open())
	{
		haveInputFile = true;
	}
	return haveInputFile;
}

bool Manager::AddOutputFile(string name)
{
	outF.open(name);
	if (outF.is_open())
	{
		haveOutputFile = true;
	}
	return haveOutputFile;
}

void Counter(Dictionary* it, int& cnt)
{
	if (it == nullptr)
	{
		return;
	}
	for (Node* letter = it->head; letter != nullptr; letter = letter->next)
	{
		if (letter->EOW)
		{
			cnt++;
		}
		Counter(letter->letters, cnt);
	}
}

int Manager::CountWords()
{
	wordCnt = 0;
	Counter(mainNodes, wordCnt);
	return wordCnt;
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

int Manager::GetData()
{
	string word;
	if (haveInputFile)
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
	}
	int startCnt = wordCnt;
	CountWords();
	return wordCnt - startCnt;
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

bool Manager::PrinToFile()
{
	if (haveOutputFile)
	{
		string buf;
		PrintData(buf, mainNodes, outF);
		return true;
	}
	else
	{
		return false;
	}
}


