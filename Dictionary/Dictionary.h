#pragma once

class Dictionary;

class Node
{
public:
	char letter = '\0';
	bool EOW = false;
	Dictionary* letters = nullptr;
	Node* next = nullptr;
};

class Dictionary
{
public:
	int size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
private:
	Dictionary* _PushBack(Node* letter);
	Dictionary* _PushFront(Node* letter);
	Dictionary* _PushAt(int index, Node* letter);
public:
	Dictionary* Add(Node* letter);
};

