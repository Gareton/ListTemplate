// main.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "ListTemplate.h"


int main()
{
	lt::List<int> mylist;

	for (int i = 0; i < 10; i++)
	{
		mylist.insert(mylist.end(), i);
	}

	lt::List<int> mylistcopy(mylist);

	std::cout << mylistcopy << std::endl;

	mylistcopy.clear();

	std::cout << mylistcopy << std::endl;

	std::cout << std::endl;

    return 0;
}

