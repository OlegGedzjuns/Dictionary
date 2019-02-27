#pragma once

///////////////////////////////////////////////////////
// Open source collections templates library         //
// https://github.com/SecyrBb/CollectionsLibrary.git //
///////////////////////////////////////////////////////

namespace LinkedList
{
template <class T>
	class ListElement_class
	{
// VARIABLES HERE
	private:
		T _data;
		ListElement_class<T>* _next = nullptr;
	public:
		T& Data() { return _data; }
		ListElement_class<T>*& Next() { return _next; }
// CONSTRUCTORS HERE
		ListElement_class(T data)
		{
			Data() = data;
		}
		ListElement_class(T data, ListElement_class* next)
		{
			Data() = data;
			Next() = next;
		}
// METHODES HERE
	};

template <class T>
	class LinkedList_class
	{
// VARIABLES HERE:
	private:
		ListElement_class<T>* _lastPtr = nullptr;
		int _lastPos = -1;
		ListElement_class<T>* _tail = nullptr;
		ListElement_class<T>* _head = nullptr;
		int _size = 0;
	public:
		ListElement_class<T>*& Tail() { return _tail; }
		ListElement_class<T>*& Head() { return _head; }

// CONSTRUCTORS HERE
		LinkedList_class() { }
		LinkedList_class(LinkedList_class<T>* &source)
		{
			CopyFrom(source);
		}

// METHODES HERE
		ListElement_class<T>* PushBack(T data)
		{
			if (_size == 0)	// List is empty
			{
				ListElement_class<T>* item = new ListElement_class<T>(data);
				_size++;
				Head() = item;
				Tail() = item;
				return item;
			}
			else
			{
				Tail()->Next() = new ListElement_class<T>(data);
				Tail() = Tail()->Next();	
				_size++;
				return Tail();
			}
		}
		ListElement_class<T>* PushBack(ListElement_class<T>* &item)
		{
			return PushBack(item->Data());	//we push copy of data
		}
		void PushBack(LinkedList_class<T>* &source)
		{
			for (auto it = source->Head(); it != nullptr; it = it->Next())	//TODO: change to iterator
			{
				PushBack(it->Data());
			}
		}
		ListElement_class<T>* PushFront(T data)
		{
			if (_size == 0) //list is empty, we can use PushBack methode
			{
				return PushBack(data);
			}
			else
			{
				ListElement_class<T>* item = new ListElement_class<T>(data);
				item->Next() = Head();
				Head() = item;
				_size++;
				if (_lastPos >= 0)	//TODO: change to iterator
				{
					_lastPos++;
				}
				return Head();
			}
		}
		ListElement_class<T>* PushFront(ListElement_class<T>* &item)
		{
			return PushFront(item->Data());	//we push copy of data
		}
		void PushFront(LinkedList_class<T>* &source)
		{
			int i = 0;
			for (auto it = source->Head(); it != nullptr; it = it->Next(), i++)	//TODO: change to iterator
			{
				PushAt(i, it->Data());
			}
		}
		ListElement_class<T>* PushAt(int index, T data)
		{
			if (index <= 0)
			{
				PushFront(data);
			}
			else if (index >= _size)
			{
				PushBack(data);
			}
			else
			{
				if (_lastPos <= index - 1 && _lastPos != -1)	// we can start finding our pos not from the begining
				{
					while (_lastPos < index - 1)	// find our position
					{
						_lastPtr = _lastPtr->Next();
						_lastPos++;
					}
					ListElement_class<T>* item = new ListElement_class<T>(data, _lastPtr->Next());
					_lastPtr->Next() = item;
					_size++;
					return item;
				}
				else
				{
					_lastPtr = Head();	// if we use _lastPtr first time, we need to initialise it
					_lastPos = 0;
					return PushAt(index, data);
				}
			}
		}
		ListElement_class<T>* PushAt(int index, ListElement_class<T>* &item)
		{
			return PushAt(index, item->Data());	//we push copy of data
		}
		void PushAt(int index, LinkedList_class<T>* &source)
		{
			for (auto it = source->Head(); it != nullptr; it = it->Next(), index++)	//TODO: change to iterator
			{
				PushAt(index, it->Data());
			}
		}
		bool PopBack()
		{
			if (_size > 1)
			{
				while (_lastPos < _size - 2)	//need to find element before element to delete
				{
					if (_lastPos < 0)
					{
						_lastPos = 0;
						_lastPtr = Head();
					}
					_lastPtr = _lastPtr->Next();
					_lastPos++;
				}
				delete _lastPtr->Next();
				_lastPtr->Next() = nullptr;
				_size--;
				return true;
			}
			else if (_size == 1)
			{
				return PopFront();	// we have only Head, can't use PopBack algorithm
			} 
			else
			{
				return false;	// nothing to delete
			}
		}
		bool PopFront()
		{
			if (_size > 0)
			{
				ListElement_class<T>* item = Head(); // pointer to head element
				Head() = Head()->Next();	// move head pointer
				_size--;
				_lastPos--;	// if it was initialised position changed
				delete item;
				return true;
			}
			else
			{
				return false;	// nothing to delete
			}
		}
		bool PopAt(int index)
		{
			if (_size > 0)
			{
				if (index >= _size - 1)
				{
					return PopBack();
				}
				else if (index <= 0)
				{
					return PopFront();
				}
				else
				{
					if (_lastPos <= index - 1 && _lastPos >= 0)
					{
						while (_lastPos < index - 1)	// moving to position before deleting
						{
							_lastPtr = _lastPtr->Next();
							_lastPos++;
						}
						ListElement_class<T>* item = _lastPtr->Next();	// element to delete
						_lastPtr->Next() = _lastPtr->Next()->Next();	// change next pointer
						delete item;
						_size--;
						return true;
					}
					else
					{
						_lastPos = 0;
						_lastPtr = Head();	// if we use _lastPtr first time, we need to initialise it
						return PopAt(index);
					}
				}
			}
			else
			{
				return false;
			}
		}
		void CopyTo(LinkedList_class<T>*& dest)
		{
			//	TODO: change to iterator
			for (_lastPos = 0, _lastPtr = Head(); _lastPos < _size; _lastPos++, _lastPtr = _lastPtr->Next())
			{
				dest->PushBack(_lastPtr->Data());
			}
			_lastPos = -1;
			_lastPtr = nullptr;
		}
		void CopyFrom(LinkedList_class<T>*& source)
		{
			// creates list using data from another list (using in copy constructor)
			Clear();	// we ned to delete all data before filling
			for (auto it = source->Head(); it != nullptr; it = it->Next())	// TODO: change to iterator
			{
				PushBack(it->Data());
			}
		}
		bool Clear()
		{
			if (_size <= 0) return false;
			while (PopFront());	// PopFront will return false when no data
			_size = 0;
			_lastPos = -1;
			_lastPtr = nullptr;
			return true;
		}
		int GetSize()
		{
			return _size;
		}
	};
}

namespace SortedList
{
template <class T>
	class SortedListElement_class
	{
		// VARIABLES HERE
	private:
		T _data;
		SortedListElement_class<T>* _next = nullptr;
	public:
		T& Data() { return _data; }
		SortedListElement_class<T>*& Next() { return _next; }
		// CONSTRUCTORS HERE
		SortedListElement_class(T data)
		{

			Data() = data;
		}
		SortedListElement_class(T data, SortedListElement_class* next)
		{
			Data() = data;
			Next() = next;
		}
		// METHODES HERE
	};

template <class T>
	class SortedList_class
	{
// VARIABLES HERE:
	private:
		SortedListElement_class<T>* _lastPtr = nullptr;
		int _lastPos = -1;
		SortedListElement_class<T>* _tail = nullptr;
		SortedListElement_class<T>* _head = nullptr;
		int _size = 0;
	public:
		SortedListElement_class<T>*& Tail() { return _tail; }
		SortedListElement_class<T>*& Head() { return _head; }
// CONSTRUCTORS HERE
// METHODES HERE
	private:
		int _PushBack(T data)
		{
			Tail()->Next() = new SortedListElement_class<T>(data);
			Tail() = Tail()->Next();
			_size++;
			return _size - 1;
		}
		int _PushFront(T data)
		{
			SortedListElement_class<T>* item = new SortedListElement_class<T>(data);
			item->Next() = Head();
			Head() = item;
			_size++;
			if (_lastPos >= 0)	//TODO: change to iterator
			{
				_lastPos++;
			}
			return 0;
		}
		int _PushAt(int index, T data)
		{
			if (index <= 0)
			{
				return _PushFront(data);
			}
			else if (index >= _size)
			{
				return _PushBack(data);
			}
			else
			{
				if (_lastPos <= index - 1 && _lastPos != -1)	// we can start finding our pos not from the begining
				{
					while (_lastPos < index - 1)	// find our position
					{
						_lastPtr = _lastPtr->Next();
						_lastPos++;
					}
					SortedListElement_class<T>* item = new SortedListElement_class<T>(data, _lastPtr->Next());
					_lastPtr->Next() = item;
					_size++;
					return index;
				}
				else
				{
					_lastPtr = Head();	// if we use _lastPtr first time, we need to initialise it
					_lastPos = 0;
					return _PushAt(index, data);
				}
			}
		}
	public:
		int Add(T data)
		{
			if (_size <= 0)
			{
				SortedListElement_class<T>* item = new SortedListElement_class<T>(data);
				_size++;
				Head() = item;
				Tail() = item;
				_lastPos = 0;
				_lastPtr = Head();
				return 0;
			}
			int i = 0;
			for (auto it = Head(); it != nullptr; it = it->Next(), i++)
			{
				if (data <= it->Data())
				{
					if (data == it->Data())
					{
						return -1;
					}
					else
					{
						break;
					}
				}
			}
			return _PushAt(i, data);
		}
		bool PopFront()
		{
			if (_size > 0)
			{
				SortedListElement_class<T>* item = Head(); // pointer to head element
				Head() = Head()->Next();	// move head pointer
				_size--;
				_lastPos--;	// if it was initialised position changed
				delete item;
				return true;
			}
			else
			{
				return false;	// nothing to delete
			}
		}
		bool Clear()
		{
			if (_size <= 0) return false;
			while (PopFront());	// PopFront will return false when no data
			_size = 0;
			_lastPos = -1;
			_lastPtr = nullptr;
			return true;
		}
		bool Find(T data)
		{
			for (auto it = Head(); it != nullptr; it = it->Next())
			{
				if (it->Data() == data)
				{
					return true;
				}
			}
			return false;
		}
		int GetSize()
		{
			return _size;
		}
	};
}
	