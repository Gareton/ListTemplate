#include "stdafx.h"
#include <iostream>
#include "ListTemplate.h"

using namespace std;

int List<T>::count = 0;

template <class T>
List<T>::List(size_t size)
{
	if (size != 0)
	{
		nextptr = new List<T>;
		if (nextPtr != NULL)
		{
			++count;
			Listptr currentPtr = nextptr;

			for (int i = 1; i < size && currentPtr != nullptr; i++, count++)
			{
				currentPtr->nextptr = new List<T>;
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
		delete nextptr[];
	}
}

template <class T>
void List<T>::insert(T data, const int &node)
{
		Listptr &currentptr = nextptr;

		for (int i = 1; i < node - 1 && currentptr != NULL; i++)
		{
			&currentptr = currentptr->nextptr;
		}

		if (node <= 1)
		{
			Listptr temp_ptr = currentptr;
			Listptr newptr = new List;
			newptr->data = data;
			currentptr = newptr;
			currentptr->nextptr = temp_ptr;
		}
		else
		{
			Listptr &priveousptr = currentptr;
			Listptr temp_ptr = currentptr->nextptr;
			Listptr newptr = new List;
			newptr->data = data;
			currentptr->nextptr = newptr;
			newptr->nextptr = temp_ptr;
			previousptr = 
		}
}

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