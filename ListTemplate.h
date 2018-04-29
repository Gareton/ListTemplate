#ifndef ListTemplate
#define ListTemplate

#include "stdafx.h"
#include <iostream>
#include <assert.h>

template <class T>
class List
{
public:
	List(size_t size = 0);
	~List();
	void insert(T data, const int &node);
	/*
	T destroy(const int &node);
	T getdata(const int &node);
	void print();
	static int getcount();
	*/
private:
	//bool isEmpty();
	T data;
	List<T> *nextptr;
	static int count;
};


using namespace std;

template <class T>
using Listptr = List<T> *;

template <class T>
int List<T>::count = 0;

template <class T>
List<T>::List(size_t size)
{
	if (size != 0)
	{
		nextptr = new List<T>;
		if (nextptr != NULL)
		{
			++count;
			Listptr<T> currentPtr = nextptr;

			for (size_t i = 1; i < size && currentPtr != nullptr; i++, count++)
			{
				currentPtr->nextptr = new List<T>;
				assert(currentPtr->nextptr != nullptr);
				currentPtr = currentPtr->nextptr;
			}
		}
	}
}

template <class T>
List<T>::~List()
{
	if (nextptr != nullptr)
	{
		--count;
		delete nextptr;
	}
}

template <class T>
void List<T>::insert(T data, const int &node)
{
	Listptr<T> &currentptr = nextptr;

	for (int i = 1; i < node - 1 && currentptr != NULL; i++)
	{
		&currentptr = currentptr->nextptr;
	}

	if (node <= 1)
	{
		Listptr<T> newptr = new List;
		assert(newptr != nullptr);
		newptr->data = data;
		newptr->nextPtr = currentptr;
		currentptr = newptr;
	}
	else
	{
		Listptr<T> &priveousptr = currentptr;
		&currentptr = currentptr->nextptr;
		Listptr<T> newptr = new List;
		assert(newptr != nullptr);
		newptr->data = data;
		priveousptr->nextptr = newptr;
		newptr->nextptr = currentptr;
	}
}

/*
template <class T>
T List<T>::destroy(const int &node)
{}

template <class T>
T List<T>::getdata(const int &node)
{}

template <class T>
void List<T>::print()
{}

template <class T>
int List<T>::getcount()
{
}

template <class T>
bool List<T>::isEmpty()
{

}
*/
#endif