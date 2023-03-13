#ifndef KTINYSTL_KSTACK_TEST_CPP
#define KTINYSTL_KSTACK_TEST_CPP


#include <stack>
#include <iostream>

#include "kstack.h"



void static testStackPushAndPop()
{
	int testCount = 10;
	KStack<int> kStack;
	std::stack<int>stk;
	for (int i = 0; i < testCount; i++)
	{
		kStack.push(i);
		stk.push(i);
		if (kStack.size() != stk.size())
		{
			std::cout << " size() error!" << std::endl;
			std::cout << kStack.size() << "!=" << stk.size() << std::endl;
			return;
		}
	}
	while (stk.empty())
	{
		if (stk.top() != kStack.top())
		{
			std::cout << " push error!" << std::endl;
			std::cout << stk.top() << "!=" << kStack.top() << std::endl;
			return;
		}
		stk.pop();
		kStack.pop();
	}
	std::cout << "push and pop success!" << std::endl;
}

void static testStack()
{
	std::cout << "*****************************KSTACK***********************" << std::endl;
	testStackPushAndPop();
	std::cout << "**********************************************************" << std::endl;
}


#endif KTINYSTL_KSTACK_TEST_CPP