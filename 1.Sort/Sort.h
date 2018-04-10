
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

// 插入排序，在小数据量或者近乎有序时表现较好，这时第二层循环计算量很少，最优可以退化到O（n)级别。
// 稳定排序,额外空间复杂度O（1）
template<typename T>
void insertionSort(T arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		// 寻找arr[i]合适的插入位置
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
		{
			swap(arr[j], arr[j - 1]); // 要注意的是一次交换其实是三次赋值，插入排序的优化的点就在这里。
		}
	}
}

/*  用 while也可以
template<typename T>
void insertionSort(T arr[], int n) {
	for (int i = 1; i < n; i++) {
		int j = i;
		while (arr[j] < arr[j - 1] && j >= 1) {
			swap(arr[j], arr[j - 1]);
			j--;
		}
	}
}
*/



// 优化版的插入排序
template<typename T>
void insertionSort2(T arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		// 寻找arr[i]合适的插入位置
		T e = arr[i];
		int j;
		for (j = i; j > 0 && e < arr[j - 1]; j--)//注意e是和arr[j-1]来比较
		{
			arr[j] = arr[j - 1];
		}
		arr[j] = e;
	}
}

//冒泡排序 
template<typename T>
void bubbleSort(T arr[], int n)
{
	// 冒泡排序对n个数排序，外层循环只要n - 1次 （当n-1个数已经在合适的位置时，自然n个数都在合适位置）
	for (int i = 0; i < n - 1; i++)  // 外层循环每进行一次，就有一个数在合适的位置
		for (int j = 0; j < n - 1 - i; j++)
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
}

// 希尔排序
// 希尔排序是经过优化之后更加高效的插入排序，其时间复杂度是O（n^1.3)
// 也称为缩小增量排序
template<typename T>
void shellSort(T arr[], int n)
{
	// 自己写的很丑陋的希尔排序
	/*
	for (int d = n / 2; d >= 1; d = d / 2)
	{
		for (int i = 0; i <= d; i++)
			for (int j = i + d; j < n; j += d)
				for (int k = j;  k >= d; k -= d)
				  if  (arr[k -d ] > arr[k])
			    	 swap(arr[k], arr[k - d]);
	}*/
	// 别人写的很优雅的希尔排序
	
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
	           //从第gap个元素，逐个对其所在组进行直接插入排序操作
		//cout << endl << gap << endl;
        for (int i = gap; i < n; i++) // 对这一行的理解至关重要
		{
		
			for  (int j=i;j - gap >= 0 && arr[j] < arr[j - gap];j-=gap)
			{
						//插入排序采用交换法
						swap(arr[j-gap], arr[j]);
	
			}	
		}
	
	}
}


// 快排和归并排序的本质是一个二叉树的深度优先遍历过程
// 快排和归并排序很像对一个二叉树的后序遍历或前序遍历

// 归并排序


template<typename T>
void __merge(T arr[], int l, int mid, int r)
{
	T* aux = new T[r - l + 1];
	for (int i = l; i <= r; i++)
	{
		aux[i - l] = arr[i];
	}

	int i = l, j = mid + 1;
	// 访问aux时注意aux的偏置
	for (int k = l; k <= r; k++) 
	{
		if (i > mid)
		{
			arr[k] = aux[j - l];
			j++;
		}
		else if (j > r)
		{
			arr[k] = aux[i - l];
			i++;
		}
		else if (aux[i - l] < aux[j - l])
		{
			arr[k] = aux[i - l];
			i++;
		}
		else
		{
			arr[k] = aux[i - l];
			j++;
		}
	}
	delete[] aux;
}

// 归并排序用到的递归函数，对arr[l...r]的范围进行排序。
template<typename T>
void __mergeSort(T arr[], int l, int r)
{
	// [l,r]是闭区间
	// 这才是最最最最最最标准的递归过程。
	if (l >= r) { return; } // 在数据量较小时，插入排序会比归并排序快（考虑时间复杂度前面的系数）
							// 所以可以将返回条件设为 l-r<15,然后此时对这15个数据再用插入排序
	                        // 其实数据量越少，近乎有序的概率就越高。
	int mid = (l + r) / 2;
	__mergeSort(arr, l, mid);  // 递
	__mergeSort(arr, mid + 1, r);  // 递
	if (arr[mid] > arr[mid + 1])  // 这是一个优化的点
	{
		__merge(arr, l, mid, r);  // 归
	}

}


// 归并排序函数
// __开头的函数从意义（而不是语法）上来说是指会被其他函数调用的函数，而不是被用户直接调用
// 的函数，即其本身的存在是为了辅助其他函数的。
template<typename T>
void mergeSort(T arr[], int n)
{
	__mergeSort(arr, 0, n - 1);
}



// 自己写的一个整体的一目了然的归并排序
// 只用一个子函数就实现了归并排序
template<typename T>
void test_mergeSort(T arr[], int n) {

	if (n <= 1)
		return;
	T * temp = new T[n];
	if (n % 2 == 0) // 对奇数还是偶数的判断很重要
    {
		mergeSort(arr, n / 2);
		mergeSort(arr + n / 2, n / 2);
	}
	else
	{
		mergeSort(arr, n / 2);
		mergeSort(arr + n / 2, n / 2 + 1);
	}
    
    if (arr[n / 2 - 1] < arr[n / 2 ]) // 这是一个优化的点，另一个优化的点在于数据小到一定程度用插入排序
    {
       delete [] temp;
	   return;	
    }

	int i = 0, j = n / 2, k = 0; // i,j分别是原数组的两段的待考察位置，k是新数组中待放数据的位置。
	while (k < n) {
		if (i < n / 2 && j < n)
		{
			if (arr[i] < arr[j])
				temp[k++] = arr[i++];
			else
				temp[k++] = arr[j++];
		}
		else if (i < n / 2)
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];

	}

	for (int i = 0; i < n; i++)
		arr[i] = temp[i];
	delete[] temp;
}




// 自底向上的归并排序，这种排序方法并没有用到数组的那种通过索引直接找到值的操作，
// 所以这个比较适用于对链表这种数据结构的排序。
template<typename T>
void mergeSortBU(T arr[], int n) //bottom up  自底向上的来做归并排序，不是递归了，而是一种迭代。
{
	for (int sz = 1; sz <= n; sz += sz)
		for (int i = 0; i + sz< n; i += sz + sz)
			// 对arr[i...i+sz-1]和arr[i+sz...i+2*sz-1]
			__merge(arr, i, i + sz - 1, min(i + sz + sz - 1,n-1));
}

//随机快速排序
template<typename T>
void quickSort(T arr[], int n)
{
	
	if (n <= 1)
	{
		return;
	}
	//srand(time(NULL));
	int index = rand() % n;
	swap(arr[0], arr[index]);
	T head = arr[0];
	int i, j=0;
	for (i = 1;i < n;i++)
	{
	  if (arr[i] < head )
		{
			swap(arr[j + 1], arr[i]);
				j++;
		}
	}
	swap(arr[j], arr[0]);
	quickSort(arr, j + 1);
	quickSort(arr + j + 1, n - j - 1);

}

// 两路快排，将数据分成小于等于head的一组和大于等于head的一组，注意等于head的元素是
// 均匀分布在左右两组中的，避免了两组的过度失衡。
template<typename T>
void quickSort2(T arr[], int n)
{
	if (n <= 1)
		return;
	int index = rand() % n;
	swap(arr[0], arr[index]);
	T head = arr[0];
	int i = 1, j = n - 1;
	while (true)
	{
		while (i <= n - 1 && arr[i] < head) i++;  //一定要注意数组可能越界
		while (j >= 1 && arr[j] > head) j--;
		if (i > j) break;
		swap(arr[i], arr[j]);
		i++;
		j--;
	}
	swap(arr[0], arr[--j]);
	quickSort2(arr, i + 1);
	quickSort2(arr + i + 1, n - i - 1);
}


// 三路快排，将数组分成 小于head, 等于head, 大于head 三组
// 等于head的一组不再参与递归，小于head和大于head的这两组进行下一次的递归。
// 这样避免了对等于head的部分进行重复操作，数组很大但值很少时，很有用。
// 这种排序最常用的原因在于，在处理有大量重复键值的数组时，这种排序最快，一般数组时，这种
// 排序的速度也能得到保证。一般会好于归并排序（虽然都是nlogn）。
template<typename T>
void quickSort3(T arr[], int n)
{
	if (n <= 1)
		return;
	int index = rand() % n;
	swap(arr[0], arr[index]);
	T head = arr[0];

	int i = 1;
	int lt = 0, gt = n;
	while (i < gt && i <= n - 1)
	{
		if (arr[i] == head) i++;
		else if (arr[i] < head)
		{
			swap(arr[i], arr[lt + 1]);
			i++;
			lt++;
		}
		else
		{
			swap(arr[i], arr[gt - 1]);
			//  i++; // 很关键，很容易忽略，这个时候i是不需要自增的。
			gt--;
		}
	}
	swap(arr[0], arr[lt]);
	lt--;

	quickSort3(arr, lt + 1); //注意这两个的长度的计算 
	quickSort3(arr + gt, n - gt);
}