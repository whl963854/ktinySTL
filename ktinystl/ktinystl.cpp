﻿#include <iostream>

#include <vld.h>
#include "kvector_test.cpp"
#include "klist_test.cpp"
#include "kdeque_test.cpp"
#include "kstack_test.cpp"
#include "kqueue_test.cpp"
#include "ksort_test.cpp"

int main()
{
	testVector();
	testList();
	testDeque();
	testStack();
	testQueue();
	testSort();
	return 0;
}
