#ifndef KTINYSTL_KQUEUE_TEST_CPP
#define KTINYSTL_KQUEUE_TEST_CPP


#include <queue>
#include <iostream>

#include "kqueue.h"



void static testQueuePushAndPop()
{
	int testCount = 10;
	KQueue<int> kQue;
	std::queue<int>que;
	for (int i = 0; i < testCount; i++)
	{
		kQue.push(i);
		que.push(i);
		if (kQue.size() != que.size())
		{
			std::cout << " size() error!" << std::endl;
			std::cout << kQue.size() << "!=" << que.size() << std::endl;
			return;
		}
	}
	while (que.empty())
	{
		if (que.front() != kQue.front())
		{
			std::cout << " push error!" << std::endl;
			std::cout << que.front() << "!=" << kQue.front() << std::endl;
			return;
		}
		que.pop();
		kQue.pop();
	}
	std::cout << "push and pop success!" << std::endl;
}

void static testQueue()
{
	std::cout << "*****************************KQUEUE***********************" << std::endl;
	testQueuePushAndPop();
	std::cout << "**********************************************************" << std::endl;
}


#endif KTINYSTL_KQUEUE_TEST_CPP