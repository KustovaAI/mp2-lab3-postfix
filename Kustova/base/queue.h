
#pragma once
#include <string>
#include "Tasks.h"
using namespace std;

const int MaxQueueSize = 100;

template <class T>
class TQueue
{
	T *pMem;
	int MemSize;	//размер выделенной памяти
	int DataCount;		//к-во запомненных в очереди элементов
	int Last;		//индекс последнего элемента очереди
	int First;		//индекс первого элемента
public:

	TQueue(int _size)
	{
		MemSize = _size;
		DataCount = 0;
		Last = -1;
		First = 0;
		if ((MemSize < 1) || (MemSize > MaxQueueSize))
			throw MemSize;
		pMem = new T[MemSize];
	}
	~TQueue()
	{
		delete[] pMem;
	}
	void Push(const T val);
	bool IsFull();
	T Get_notion_by_index(int ind); 
	bool IsEmpty();
	int GetNextIndex(int index);
	T GetFirst(); 
	T Get();
	void Sort(Tasks a[]);
};



template <class T>
bool TQueue<T>::IsEmpty()
{
	if (DataCount == 0)
		return true;
	else return false;
}

template <class T>
bool TQueue<T>::IsFull()
{
	if (DataCount == MemSize)
		return true;
	else return false;
}

template <class T>
void TQueue<T>::Push(const T val)
{
	if (IsFull()) throw val;
	if (Last == MemSize - 1)
		Last = 0;
	else Last++;
	pMem[Last] = val;
	DataCount++;
}

template <class T>
int TQueue<T>::GetNextIndex(int index)
{
	return ++index % MemSize;
}

template <class T>
T TQueue<T>::Get()
{
	if (IsEmpty() == 1) throw "negative";
		T tmp = pMem[First];
		DataCount--;
		First = GetNextIndex(First);
		return tmp;
}

template<class T>
void TQueue<T>::Sort(Tasks a[])
{
	T temp;
	for (int i = 0; i < DataCount; i++)
	{
		for (int j = 0; j < DataCount - i - 1; j++)
		{
			if ((a[Get_notion_by_index(j)].Getpriority() != 0) && (a[Get_notion_by_index(j + 1)].Getpriority() != 0) && (a[Get_notion_by_index(j)].Getpriority() > a[Get_notion_by_index(j + 1)].Getpriority()))
			{
				temp = pMem[j];
				pMem[j] = pMem[j + 1];
				pMem[j + 1] = temp;
			}
		}
	}

}

template<class T>
T TQueue<T>::GetFirst()
{
	if (IsEmpty() == 1) throw "negative";
	return pMem[First];
}

template<class T>
inline T TQueue<T>::Get_notion_by_index(int ind)
{
	if (IsEmpty() == 1) throw "negative";
	return pMem[ind];
}