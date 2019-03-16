#include "Manager.h"

Manager::Manager(string &inputPath)
{
	inF.open(inputPath);
	if(inF.is_open())
		haveInputFile = true;
}

bool Manager::AddInputFile(string name)
{
	inF.close();
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

void Counter(Dictionary* it, int &cnt)
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
	if (word[0] == '\0')
		return false;
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

bool Manager::AddToDict(string &word)
{
	if (CheckWord(word))
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
		wordCnt++;
		return true;
	}
	return false;
}

int Manager::GetData()
{
	int startCnt = wordCnt;
	string word;
	if (haveInputFile)
	{
		while (!inF.eof())
		{
			inF >> word;
			AddToDict(word);
		}
	}
	return wordCnt - startCnt;
}

void PrintData(string &word, Dictionary* it, ofstream &outF)
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

void Finder(string &word, Dictionary* it, bool &found, int i = 0)
{
	if (it == nullptr || found == true)
	{
		return;
	}
	for (Node* letter = it->head; letter != nullptr; letter = letter->next)
	{
		if (letter->letter == word[i])
		{
			if (word[i + 1] == '\0' && letter->EOW == true)
			{
				found = true;
				return;
			}
			Finder(word, letter->letters, found, i + 1);
		}
	}
}

bool Manager::FindWord(string &word)
{
	bool found = false;
	Finder(word, mainNodes, found);
	return found;
}

void correctorA(string &word, Dictionary* it, string &correct, bool &found)	//one incorrect letter
{
	if (it == nullptr || found == true)
	{
		return;
	}
	for (Node* letter = it->head; letter != nullptr; letter = letter->next)
	{
		if (!found)
		{
			correct.push_back(letter->letter);
			if (letter->EOW && correct.size() == word.size())
			{
				bool oneIncorrect = false, fits = true;
				for (int i = 0; i < correct.size(); i++)
				{
					if (word[i] == correct[i]) continue;
					else if (word[i] != correct[i] && oneIncorrect == false) oneIncorrect = true;
					else
					{
						fits = false;
						break;
					}
				}
				found = fits;
			}
			correctorA(word, letter->letters, correct, found);
		}
		if (!found)
		{
			correct.pop_back();
		}
	}
}

void correctorB(string &word, Dictionary* it, string &correct, bool &found)	//one lost letter
{
	if (it == nullptr || found == true)
	{
		return;
	}
	for (Node* letter = it->head; letter != nullptr; letter = letter->next)
	{
		if (!found)
		{
			correct.push_back(letter->letter);
			if (letter->EOW && correct.size() == word.size() + 1)
			{
				bool oneExtra = false, fits = true;
				for (int i = 0, j = 0; i < correct.size(); )
				{
					if (word[j] == correct[i])
					{
						i++; 
						j++;
						continue;
					}
					else if (word[j] != correct[i] && oneExtra == false)
					{
						i++;
						oneExtra = true;
					}
					else
					{
						fits = false;
						break;
					}
				}
				found = fits;
			}
			correctorB(word, letter->letters, correct, found);
		}
		if (!found)
		{
			correct.pop_back();
		}
	}
}

void correctorC(string &word, Dictionary* it, string &correct, bool &found)	// one extra letter
{
	if (it == nullptr || found == true)
	{
		return;
	}
	for (Node* letter = it->head; letter != nullptr; letter = letter->next)
	{
		if (!found)
		{
			correct.push_back(letter->letter);
			if (letter->EOW && correct.size() + 1 == word.size())
			{
				bool oneLost = false, fits = true;
				for (int i = 0, j = 0; i < correct.size(); )
				{
					if (word[j] == correct[i])
					{
						i++;
						j++;
						continue;
					}
					else if (word[j] != correct[i] && oneLost == false)
					{
						j++;
						oneLost = true;
					}
					else
					{
						fits = false;
						break;
					}
				}
				found = fits;
			}
			correctorC(word, letter->letters, correct, found);
		}
		if (!found)
		{
			correct.pop_back();
		}
	}
}

string Manager::correctorD(string &word, Dictionary* it)	// one mistake incorrect/lost/extra letter
{
	string correct;
	bool found = false;
	correctorA(word, mainNodes, correct, found);
	if (!found)
	{
		correctorB(word, mainNodes, correct, found);
	}
	if (!found)
	{
		correctorC(word, mainNodes, correct, found);
	}
	return correct;
}

void correctorE(string &word, Dictionary* it, string &correct)
{
}

string Manager::FindCorrect(string &word, int i)
{
	if (!FindWord(word))
	{
		string correct;
		switch (i)
		{
			case 1:
			{
				bool found = false;
				correctorA(word, mainNodes, correct, found);
				break;
			}
			case 2:
			{
				bool found = false;
				correctorB(word, mainNodes, correct, found);
				break;
			}
			case 3:
			{
				bool found = false;
				correctorC(word, mainNodes, correct, found);
				break;
			}
			case 4:
			{
				correct = correctorD(word, mainNodes);
				break;
			}
			case 5:
			{
				correctorE(word, mainNodes, correct);
				break;
			}
		}
		return correct;
	}
	else
	{
		return word;
	}
}


