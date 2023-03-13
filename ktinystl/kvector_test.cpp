#ifndef KTINYSTL_KVECTOR_TEST_CPP
#define KTINYSTL_KVECTOR_TEST_CPP


#include <vector>
#include <iostream>

#include "kvector.h"


void static testVectorPushBack()
{
	int testCount = 2000;
	KVector<int> kVec;
	std::vector<int>vec;
	for (int i = 0; i < testCount; i++)
	{
		kVec.push_back(i);
		vec.push_back(i);
	}

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (kVec[i] != vec[i])
		{
			std::cout << "push_back error!" << std::endl;
			return;
		}
	}
	std::cout << "push_back success!" << std::endl;
}

void static testVectorInsert()
{
	int testCount = 2000;
	KVector<int> kVec;
	std::vector<int>vec;
	for (int i = 0; i < testCount; i++)
	{
		kVec.push_back(i);
		vec.push_back(i);
	}
	int testNum = 1000;
	for (int i = 0; i < testCount; i++)
	{
		kVec.insert(kVec.begin(), testNum);
		vec.insert(vec.begin(), testNum);
	}
	for (int i = 0; i < testCount; i++)
	{
		kVec.insert(kVec.end() - 1, testNum);
		vec.insert(vec.end() - 1, testNum);
	}
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (kVec[i] != vec[i])
		{
			std::cout << "insert error!" << std::endl;
			return;
		}
	}
	std::cout << "insert success!" << std::endl;
}

void static testVectorErase()
{
	int testCount = 1000;
	KVector<int> kVec;
	std::vector<int>vec;
	for (int i = 0; i < testCount; i++)
	{
		kVec.push_back(i);
		vec.push_back(i);
	}
	int testNum = 1000;
	for (int i = 0; i < 100; i++)
	{
		kVec.erase(kVec.begin());
		vec.erase(vec.begin());
	}
	for (int i = 0; i < 100; i++)
	{
		kVec.erase(kVec.end() - 1);
		vec.erase(vec.end() - 1);
	}
	for (size_t i = 0; i < vec.size(); i++)
	{
		//std::cout <<"i: "<<i<<"   "<< vec[i] << " " << kVec[i] << " " <<std::endl;
		if (kVec[i] != vec[i])
		{
			std::cout << " erase error!" << std::endl;
			return;
		}
	}
	std::cout << "erase success!" << std::endl;
}

void static testVectorPopBack()
{
	int testCount = 1000;
	KVector<int> kVec;
	std::vector<int>vec;
	for (int i = 0; i < testCount; i++)
	{
		kVec.push_back(i);
		vec.push_back(i);
	}
	for (int i = 0; i < 100; i++)
	{
		kVec.pop_back();
		vec.pop_back();
	}
	int testNum = 1000;
	for (size_t i = 0; i < vec.size(); i++)
	{
		//std::cout <<"i: "<<i<<"   "<< vec[i] << " " << kVec[i] << " " <<std::endl;
		if (kVec[i] != vec[i])
		{
			std::cout << " pop_back error!" << std::endl;
			return;
		}
	}
	std::cout << "pop_back success!" << std::endl;
}


void static testVector()
{
	std::cout << "***************************KVector************************" << std::endl;
	testVectorPushBack();
	testVectorInsert();
	testVectorErase();
	testVectorPopBack();
	std::cout << "**********************************************************" << std::endl;
}

#endif KTINYSTL_KVECTOR_TEST_CPP