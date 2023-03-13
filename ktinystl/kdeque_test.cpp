#ifndef KTINYSTL_KDEQUE_TEST_CPP
#define KTINYSTL_KDEQUE_TEST_CPP


#include <deque>
#include <iostream>

#include "kdqueue.h"


void static testDequePushBack()
{
	int testCount = 10;
	KDQueue<int> kDeque;
	std::deque<int>deq;
	for (int i = 0; i < testCount; i++)
	{
		kDeque.push_back(i);
		deq.push_back(i);
		if (kDeque.size() != deq.size())
		{
			std::cout << " size() error!" << std::endl;
			std::cout << kDeque.size() << "!=" << deq.size() << std::endl;
			return;
		}
	}
	auto kiter = kDeque.begin();
	auto iter = deq.begin();
	while (kiter != kDeque.end())
	{
		if (*kiter != *iter)
		{
			std::cout << " push_back error!" << std::endl;
			std::cout << *kiter << "!=" << *iter << std::endl;
			return;
		}
		kiter++;
		iter++;
	}
	std::cout << "push_back success!" << std::endl;
}

void static testDequeInsert()
{
	int testCount = 1000;
	KDQueue<int> kDeque;
	std::deque<int>deq;
	for (int i = 0; i < testCount; i++)
	{
		kDeque.push_back(i);
		deq.push_back(i);
	}
	int testNum = 1000;
	std::cout << "insert front " << std::endl;
	for (int i = 0; i < testCount; i++)
	{
		kDeque.insert(++kDeque.begin(), testNum);
		deq.insert(++deq.begin(), testNum);
	}
	std::cout << "insert end " << std::endl;
	for (int i = 0; i < testCount; i++)
	{
		kDeque.insert(--kDeque.end(), testNum);
		deq.insert(--deq.end(), testNum);
	}
	auto kiter = kDeque.begin();
	auto iter = deq.begin();
	while (kiter != kDeque.end())
	{
		if (*kiter != *iter)
		{
			std::cout << "insert error!" << std::endl;
			std::cout << *kiter << "!=" << *iter << std::endl;
			return;
		}
		kiter++;
		iter++;
	}
	std::cout << "insert success!" << std::endl;
}

void static testDequeErase()
{
	int testCount = 1000;
	KDQueue<int> kDeque;
	std::deque<int>deq;
	for (int i = 0; i < testCount; i++)
	{
		kDeque.push_back(i);
		deq.push_back(i);
	}
	int testNum = 1000;
	for (int i = 0; i < 100; i++)
	{
		kDeque.erase(kDeque.begin());
		deq.erase(deq.begin());
	}
	for (int i = 0; i < 100; i++)
	{
		kDeque.erase(--kDeque.end());
		deq.erase(--deq.end());
	}
	auto kiter = kDeque.begin();
	auto iter = deq.begin();
	while (kiter != kDeque.end())
	{
		if (*kiter != *iter)
		{
			std::cout << "erase error!" << std::endl;
			std::cout << *kiter << "!=" << *iter << std::endl;
			return;
		}
		kiter++;
		iter++;
	}
	std::cout << "erase success!" << std::endl;
}

void static testDequePopBack()
{
	int testCount = 1000;
	KDQueue<int> kDeque;
	std::deque<int>deq;
	for (int i = 0; i < testCount; i++)
	{
		kDeque.push_back(i);
		deq.push_back(i);
	}
	for (int i = 0; i < 100; i++)
	{
		kDeque.pop_back();
		deq.pop_back();
	}
	auto kiter = kDeque.begin();
	auto iter = deq.begin();
	while (kiter != kDeque.end())
	{
		if (*kiter != *iter)
		{
			std::cout << "pop_back error!" << std::endl;
			std::cout << *kiter << "!=" << *iter << std::endl;
			return;
		}
		kiter++;
		iter++;
	}
	std::cout << "pop_back success!" << std::endl;
}

void static testDeque()
{
	std::cout << "*****************************KDQueue**********************" << std::endl;
	testDequePushBack();
	testDequeInsert();
	testDequeErase();
	testDequePopBack();
	std::cout << "**********************************************************" << std::endl;
}


#endif KTINYSTL_KDEQUE_TEST_CPP