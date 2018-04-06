#pragma once
#include<ctime>

// �����㷨���Դ�������֤����ʱ�临�ӶȲ������NlogN

// ѡ������,ʱ�临�Ӷ��ȶ���O��n*n),����ռ临�Ӷ�O��1�������ȶ�����
// ���ȶ�ԭ������5 8 5 2 9������֪����һ��ѡ���1��Ԫ��5���2������
// ��ôԭ������2��5�����ǰ��˳��ͱ��ƻ��ˣ�����ѡ��������һ���ȶ��������㷨��
template<typename T>
void selectionSort(T arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		// Ѱ��[i,n)���������Сֵ
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[minIndex])
				minIndex = j;
		}
		swap(arr[i], arr[minIndex]);
	}
}

// ����������С���������߽�������ʱ���ֽϺã���ʱ�ڶ���ѭ�����������٣����ſ����˻���O��n)����
// �ȶ�����,����ռ临�Ӷ�O��1��
template<typename T>
void insertionSort(T arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		// Ѱ��arr[i]���ʵĲ���λ��
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
		{
			swap(arr[j], arr[j - 1]); // Ҫע�����һ�ν�����ʵ�����θ�ֵ������������Ż��ĵ�������
		}
	}
}

/*  �� whileҲ����
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



// �Ż���Ĳ�������
template<typename T>
void insertionSort2(T arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		// Ѱ��arr[i]���ʵĲ���λ��
		T e = arr[i];
		int j;
		for (j = i; j > 0 && e < arr[j - 1]; j--)//ע��e�Ǻ�arr[j-1]���Ƚ�
		{
			arr[j] = arr[j - 1];
		}
		arr[j] = e;
	}
}

//ð������ 
template<typename T>
void bubbleSort(T arr[], int n)
{
	// ð�������n�����������ѭ��ֻҪn - 1�� ����n-1�����Ѿ��ں��ʵ�λ��ʱ����Ȼn�������ں���λ�ã�
	for (int i = 0; i < n - 1; i++)  // ���ѭ��ÿ����һ�Σ�����һ�����ں��ʵ�λ��
		for (int j = 0; j < n - 1 - i; j++)
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
}

// ϣ������
// ϣ�������Ǿ����Ż�֮����Ӹ�Ч�Ĳ���������ʱ�临�Ӷ���O��n^1.3)
// Ҳ��Ϊ��С��������
template<typename T>
void shellSort(T arr[], int n)
{
	// �Լ�д�ĺܳ�ª��ϣ������
	/*
	for (int d = n / 2; d >= 1; d = d / 2)
	{
		for (int i = 0; i <= d; i++)
			for (int j = i + d; j < n; j += d)
				for (int k = j;  k >= d; k -= d)
				  if  (arr[k -d ] > arr[k])
			    	 swap(arr[k], arr[k - d]);
	}*/
	// ����д�ĺ����ŵ�ϣ������
	
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
	           //�ӵ�gap��Ԫ�أ�����������������ֱ�Ӳ����������
		//cout << endl << gap << endl;
        for (int i = gap; i < n; i++) // ����һ�е����������Ҫ
		{
		
			for  (int j=i;j - gap >= 0 && arr[j] < arr[j - gap];j-=gap)
			{
						//����������ý�����
						swap(arr[j-gap], arr[j]);
	
			}	
		}
	
	}
}


// ���ź͹鲢����ı�����һ����������������ȱ�������
// ���ź͹鲢��������һ���������ĺ��������ǰ�����

// �鲢����

// ��arr[l...mid] ��arr[mid+1 ...r]�����ֽ��й鲢�ľ���ʵ��
// Ҫע���о��Ķ��������������һ��Ƭ��, ÿ�εݹ��޸ĵĶ������е�һ��Ƭ�Σ�
//  �������ĵ����ݽṹ��һĿ��Ȼ
template<typename T>
void __merge(T arr[], int l, int mid, int r)
{
	T* aux = new T[r - l + 1];
	for (int i = l; i <= r; i++)
	{
		aux[i - l] = arr[i];
	}

	int i = l, j = mid + 1;
	// ����auxʱע��aux��ƫ��
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

// �鲢�����õ��ĵݹ麯������arr[l...r]�ķ�Χ��������
template<typename T>
void __mergeSort(T arr[], int l, int r)
{
	// ������������������׼�ĵݹ���̡�
	if (l >= r) { return; } // ����������Сʱ�����������ȹ鲢����죨����ʱ�临�Ӷ�ǰ���ϵ����
							// ���Կ��Խ�����������Ϊ l-r<15,Ȼ���ʱ����15���������ò�������
	                        // ��ʵ������Խ�٣���������ĸ��ʾ�Խ�ߡ�
	int mid = (l + r) / 2;
	__mergeSort(arr, l, mid);  // ��
	__mergeSort(arr, mid + 1, r);  // ��
	if (arr[mid] > arr[mid + 1])  // ����һ���Ż��ĵ�
	{
		__merge(arr, l, mid, r);  // ��
	}

}


// �鲢������
// __��ͷ�ĺ��������壨�������﷨������˵��ָ�ᱻ�����������õĺ����������Ǳ��û�ֱ�ӵ���
// �ĺ��������䱾��Ĵ�����Ϊ�˸������������ġ�
template<typename T>
void mergeSort(T arr[], int n)
{
	__mergeSort(arr, 0, n - 1);
}


// �Ե����ϵĹ鲢�����������򷽷���û���õ����������ͨ������ֱ���ҵ�ֵ�Ĳ�����
// ��������Ƚ������ڶ������������ݽṹ������
template<typename T>
void mergeSortBU(T arr[], int n) //bottom up  �Ե����ϵ������鲢���򣬲��ǵݹ��ˣ�����һ�ֵ�����
{
	for (int sz = 1; sz <= n; sz += sz)
		for (int i = 0; i + sz< n; i += sz + sz)
			// ��arr[i...i+sz-1]��arr[i+sz...i+2*sz-1]
			__merge(arr, i, i + sz - 1, min(i + sz + sz - 1,n-1));
}

//�����������
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

// ��·���ţ������ݷֳ�С�ڵ���head��һ��ʹ��ڵ���head��һ�飬ע�����head��Ԫ����
// ���ȷֲ������������еģ�����������Ĺ���ʧ�⡣
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
		while (i <= n - 1 && arr[i] < head) i++;  //һ��Ҫע���������Խ��
		while (j >= 1 && arr[j] > head) j--;
		if (i > j) break;
		swap(arr[i], arr[j]);
		i++;
		j--;
	}
	swap(arr[0], arr[j]);
	quickSort2(arr, j + 1);
	quickSort2(arr + j + 1, n - j - 1);
}


// ��·���ţ�������ֳ� С��head, ����head, ����head ����
// ����head��һ�鲻�ٲ���ݹ飬С��head�ʹ���head�������������һ�εĵݹ顣
// ���������˶Ե���head�Ĳ��ֽ����ظ�����������ܴ�ֵ����ʱ�������á�
// ����������õ�ԭ�����ڣ��ڴ����д����ظ���ֵ������ʱ������������죬һ������ʱ������
// ������ٶ�Ҳ�ܵõ���֤��һ�����ڹ鲢������Ȼ����nlogn����
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
			//  i++; // �ܹؼ��������׺��ԣ����ʱ��i�ǲ���Ҫ�����ġ�
			gt--;
		}
	}
	swap(arr[0], arr[lt]);
	lt--;

	quickSort3(arr, lt + 1); //ע���������ĳ��ȵļ��� 
	quickSort3(arr + gt, n - gt);
}

// ��һ������������Եĺ�����Ҫ��ʱ�临�Ӷ���nlogn��
// ���ù鲢�����˼·
template<typename T>
void reverseOrder(T arr[], int n)
{

}

// �������е�m���Ԫ�أ�Ҫ��ʱ�临�Ӷ���O(n)
// ���ÿ���partion˼·
template<typename T>
void mOrder(T arr[], int n, int m)
{

}





