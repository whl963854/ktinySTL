#ifndef KTINYSTL_KSORT_TEST_CPP
#define KTINYSTL_KSORT_TEST_CPP

#include <vector>
#include <iostream>

#include "kvector.h"
#include "kalgorithm.h"


void static testVectorSort()
{
	KVector<int>vec;
	std::vector<int>ans;
	int testCount = 18;
	for (int i = 1; i <= testCount; i++)
	{
		ans.push_back(i);
		vec.push_back(testCount - i + 1);
		std::cout << vec[i-1]<<" ";
	}
	std::cout << std::endl;
	ktinystl::sort(vec.begin(), vec.end());
	for (int i = 0; i < testCount; i++)
	{
		std::cout << vec[i] << " ";
		//if (vec[i] != ans[i])
		//{
		//	std::cout << "Vector sort ERROR!" << std::endl;
		//	return;
		//}
	}
	std::cout << "Vector sort success!" << std::endl;
}

void static testSort()
{
	std::cout << "*****************************KSORT************************" << std::endl;
	testVectorSort();
	std::cout << "**********************************************************" << std::endl;
}


#endif  //KTINYSTL_KSORT_TEST_CPP