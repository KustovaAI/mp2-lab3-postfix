#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T *pMem;
	int size;
	int top;
public:
	TStack(int _size)
	{
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
			throw size;
		pMem = new T[size];
	}
	~TStack()
	{
		delete[] pMem;
	}
	void Push(const T val);
	T Pop();
	bool IsFull();
	bool IsEmpty();
	T GetTopElement();
};



template <class T>
bool TStack<T>::IsEmpty()
{
	return top == -1;
}

template <class T>
bool TStack<T>::IsFull()
{
	return top == size - 1;
}

template <class T>
void TStack<T>::Push(const T val)
{
	if (IsFull()) throw val;
	pMem[++top] = val;
}

template <class T>
T TStack<T>::Pop()
{
	if (IsEmpty() == 1) throw "negative";
	return pMem[top--];
}

template <class T>
T TStack<T>::GetTopElement()
{
	
	if (this->IsEmpty())
		throw "negative";

	return pMem[top];
};
#endif
