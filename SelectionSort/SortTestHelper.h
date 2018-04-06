#pragma once
// �������ʵ�ֶ�д������
#include<iostream>
#include<string>
#include<ctime>
#include<cassert>
#include <algorithm> 
using namespace std;
namespace SortTestHelper {
	// ������n��Ԫ�ص�������飬ÿ��Ԫ�ص������Χ��[rangeL, rangeR]
	int * generateRandomArray(int n, int rangeL, int rangeR)
	{
		assert(rangeL <= rangeR); // ����������ֹ���������
		int *arr = new int[n];
		srand(time(NULL));
		for (int i = 0; i < n; i++)
		{
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		}
		return arr;        
	}

	template<typename T>
	bool isSorted(T arr[], int n) // ����С������������ȷ��
	{
		for (int i = 0; i < n - 1; i++)
			if (arr[i] > arr[i + 1])
				return false;
		return true;
	}

	template<typename T>
	// ����������ָ�봫�룬�����õ��Ǻ���ָ��
	//����ָ��Ķ����ʽΪ return_type(*var_name)(arg_list);
	// Ҫ�붨��һ������ָ�룬����Ҫָ�������Ĳ����Լ�����ֵ�����������������޹ؽ�Ҫ�ġ�
	void testSort(string sortName, void(*sort)(T[], int), T arr[], int n)
	{
		clock_t startTime = clock(); // clock_t��ctime�����
		sort(arr, n);
		clock_t endTime = clock();
		assert(isSorted(arr, n));
		// endTime - startTime�Ľ�����ص��������˶��ٸ�ʱ������
		cout << sortName << ":" << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
	
	}

	int * copyIntArray(int a[], int n)
	{
		int * arr = new int[n]; // copy��std�����һ�������������ڴ渴��
		copy(a, a + n, arr); // Դ�����ͷָ�룬βָ�룬�Լ�Ŀ�������ͷָ�롣
		return arr;
	}

	// Ŀ����Ϊ����֤�ڽ���������������棬�������������ҪԶ����ѡ������
	// ������Ϊ���������������ʣ���������Ȼ��O��n*n)�����㷨������ʱ���Ժ���nlog(n)�����㷨
	// ��������£�������������ʱ���ڲ�ѭ���̶�ִֻ��һ�Σ���ô���������ΪO��n)�����㷨��
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

