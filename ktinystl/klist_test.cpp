#ifndef KTINYSTL_KLIST_TEST_CPP
#define KTINYSTL_KLIST_TEST_CPP


#include <list>
#include <iostream>
#include "klist.h"


void static testListPushBack()
{
	int testCount = 10000;
	KList<int> kList;
	std::list<int>list;
	for (int i = 0; i < testCount; i++)
	{
		kList.push_back(i);
		list.push_back(i);
	}
	auto kiter = kList.begin();
	auto iter = list.begin();
	while (kiter != kList.end())
	{
		if (*kiter != *iter)
		{
			std::cout << " push_back error!" << std::endl;
			return;
		}
		kiter++;
		iter++;
	}
	std::cout << "push_back success!" << std::endl;
}

void static testListInsert()
{
	int testCount = 1000;
	KList<int> kList;
	std::list<int>list;
	for (int i = 0; i < testCount; i++)
	{
		kList.push_back(i);
		list.push_back(i);
	}
	int testNum = 1000;
	for (int i = 0; i < 1000; i++)
	{
		kList.insert(kList.begin(), testNum);
		list.insert(list.begin(), testNum);
	}
	for (int i = 0; i < 1000; i++)
	{
		kList.insert(--kList.end(), testNum);
		list.insert(--list.end(), testNum);
	}
	auto kiter = kList.begin();
	auto iter = list.begin();
	while (kiter != kList.end())
	{
		if (*kiter != *iter)
		{
			std::cout << " insert error!" << std::endl;
			return;
		}
		kiter++;
		iter++;
	}
	std::cout << "insert success!" << std::endl;
}

void static testListErase()
{
	int testCount = 1000;
	KList<int> kList;
	std::list<int>list;
	for (int i = 0; i < testCount; i++)
	{
		kList.push_back(i);
		list.push_back(i);
	}
	int testNum = 1000;
	for (int i = 0; i < 100; i++)
	{
		kList.erase(kList.begin());
		list.erase(list.begin());
	}
	for (int i = 0; i < 100; i++)
	{
		kList.erase(--kList.end());
		list.erase(--list.end());
	}
	auto kiter = kList.begin();
	auto iter = list.begin();
	while (kiter != kList.end())
	{
		if (*kiter != *iter)
		{
			std::cout << " erase error!" << std::endl;
			return;
		}
		kiter++;
		iter++;
	}
	std::cout << "erase success!" << std::endl;
}

void static testListPopBack()
{
	int testCount = 1000;
	KList<int> kList;
	std::list<int>list;
	for (int i = 0; i < testCount; i++)
	{
		kList.push_back(i);
		list.push_back(i);
	}
	for (int i = 0; i < 100; i++)
	{
		kList.pop_back();
		list.pop_back();
	}
	auto kiter = kList.begin();
	auto iter = list.begin();
	while (kiter != kList.end())
	{
		if (*kiter != *iter)
		{
			std::cout << " pop_back error!" << std::endl;
			return;
		}
		kiter++;
		iter++;
	}
	std::cout << "pop_back success!" << std::endl;
}
void static testListUnique()
{
	int testCount = 1000;
	KList<int> kList;
	std::list<int>list;
	for (int i = 0; i < testCount; i++)
	{
		kList.push_back(i / 3);
		list.push_back(i / 3);
	}
	kList.unique();
	list.unique();
	auto kiter = kList.begin();
	auto iter = list.begin();
	while (kiter != kList.end())
	{
		if (*kiter != *iter)
		{
			std::cout << " Unique error!" << std::endl;
			return;
		}
		kiter++;
		iter++;
	}
	std::cout << "Unique success!" << std::endl;
}

void static testList()
{
	std::cout << "*****************************KList************************" << std::endl;
	testListPushBack();
	testListInsert();
	testListErase();
	testListPopBack();
	testListUnique();
	std::cout << "**********************************************************" << std::endl;
}


#endif KTINYSTL_KLIST_TEST_CPP