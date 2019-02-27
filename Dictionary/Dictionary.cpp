#include "Dictionary.h"

#if _DEBUG
	#include <iostream>
#endif

bool Dictionary_class::CheckWord(string &word)
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

int Dictionary_class::GetWords()
{
	string word;
	int addedCnt = 0;
	if (_inputF.is_open())
	{
		while (!_inputF.eof())
		{
			_inputF >> word;
			/*if (CheckWord(word))
			{*/
				_storage->Add(word);
				addedCnt++;
#if _DEBUG
				if(addedCnt % 1000 == 0)
					std::cout << addedCnt << endl;
#endif
			//}
		}
	}
	return addedCnt;
}

void Dictionary_class::PrintWords()
{
	for (auto it = _storage->Head(); it != nullptr; it = it->Next())
	{
		_outputF << it->Data() << endl;
	}
}

Dictionary_class::Dictionary_class(string inputPath, string outputPath)
{
	_inputF.open(inputPath);
	_outputF.open(outputPath);
	_storage = new SortedList_class<string>;
}

Dictionary_class::~Dictionary_class()
{
	_inputF.close();
	_outputF.close();
}

int Dictionary_class::Create()
{
	int addedCnt = GetWords();
	PrintWords();
	return addedCnt;
}
