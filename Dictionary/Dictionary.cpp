#include "Dictionary.h"

Dictionary* Dictionary::_PushBack(Node* letter)
{
	letter->letters = new Dictionary;
	tail->next = letter;
	tail = tail->next;
	size++;
	return letter->letters;
}

Dictionary* Dictionary::_PushFront(Node* letter)
{
	letter->letters = new Dictionary;
	letter->next = head;
	head = letter;
	size++;
	return letter->letters;
}

Dictionary* Dictionary::_PushAt(int index, Node* letter)
{
	if (index <= 0)
	{
		return _PushFront(letter);
	}
	else if (index >= size)
	{
		return _PushBack(letter);
	}
	else
	{
		Node* it = head;
		for (int i = 0; i < index - 1; i++, it = it->next);
		letter->next = it->next;
		it->next = letter;
		size++;
		letter->letters = new Dictionary;
		return letter->letters;
	}
}

Dictionary* Dictionary::Add(Node* letter)
{
	if (size <= 0)
	{
		size++;
		head = letter;
		tail = letter;
		letter->letters = new Dictionary;
		return letter->letters;
	}
	int i = 0;
	for (Node* it = head; it != nullptr; it = it->next, i++)
	{
		if (letter->letter <= it->letter)
		{
			if (letter->letter == it->letter)
			{
				if (letter->EOW == true && it->EOW == false)
				{
					it->EOW = true;
				}
				return it->letters;
			}
			else
			{
				break;
			}
		}
	}
	return _PushAt(i, letter);
}
