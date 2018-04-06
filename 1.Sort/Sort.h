

// 排序算法可以从理论上证明其时间复杂度不会低于NlogN

// 选择排序,时间复杂度稳定在O（n*n),额外空间复杂度O（1），不稳定排序
// 不稳定原因：序列5 8 5 2 9，我们知道第一遍选择第1个元素5会和2交换，
// 那么原序列中2个5的相对前后顺序就被破坏了，所以选择排序不是一个稳定的排序算法。
template<typename T>
void selectionSort(T arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		// 寻找[i,n)区间里的最小值
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[minIndex])
				minIndex = j;
		}
		swap(arr[i], arr[minIndex]);
	}
}