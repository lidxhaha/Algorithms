#pragma once
// 将定义和实现都写在这里
#include<iostream>
#include<string>
#include<ctime>
#include<cassert>
#include <algorithm> 
using namespace std;
namespace SortTestHelper {
	// 生成有n个元素的随机数组，每个元素的随机范围是[rangeL, rangeR]
	int * generateRandomArray(int n, int rangeL, int rangeR)
	{
		assert(rangeL <= rangeR); // 如果出错就终止程序的运行
		int *arr = new int[n];
		srand(time(NULL));
		for (int i = 0; i < n; i++)
		{
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		}
		return arr;        
	}

	template<typename T>
	bool isSorted(T arr[], int n) // 检测从小到大的排序的正确性
	{
		for (int i = 0; i < n - 1; i++)
			if (arr[i] > arr[i + 1])
				return false;
		return true;
	}

	template<typename T>
	// 将排序函数的指针传入，这里用的是函数指针
	//函数指针的定义格式为 return_type(*var_name)(arg_list);
	// 要想定义一个函数指针，必须要指明函数的参数以及返回值，而函数的名称是无关紧要的。
	void testSort(string sortName, void(*sort)(T[], int), T arr[], int n)
	{
		clock_t startTime = clock(); // clock_t是ctime里面的
		sort(arr, n);
		clock_t endTime = clock();
		assert(isSorted(arr, n));
		// endTime - startTime的结果返回的是运行了多少个时钟周期
		cout << sortName << ":" << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
	
	}

	int * copyIntArray(int a[], int n)
	{
		int * arr = new int[n]; // copy是std里面的一个函数，进行内存复制
		copy(a, a + n, arr); // 源数组的头指针，尾指针，以及目标数组的头指针。
		return arr;
	}

	// 目的是为了验证在近乎有序的数组里面，插入排序的性能要远好于选择排序
	// 正是因为插入排序的这个性质，所以其虽然是O（n*n)排序算法，但有时可以好于nlog(n)排序算法
	// 极限情况下，当数据是有序时，内层循环固定只执行一次，那么插入排序变为O（n)排序算法。
	int  * generateNearlyOrderedArray(int n, int swapTimes)
	{
		int *arr = new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = i;
		srand(time(NULL));
		for (int i = 0; i < swapTimes; i++)
		{
			int posx = rand() % n;
			int posy = rand() % n;
			swap(arr[posx], arr[posy]);
		}
		return arr;
	}


}

