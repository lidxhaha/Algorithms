#pragma once
// ������
template<typename Item>
class MaxHeap
{
public:
	MaxHeap(int capacity)
	{
		data = new Item[capacity + 1]; // �洢�ռ���capacity,����Ԫ�ظ�����count
		count = 0;
		this->capacity = capacity;
	}  //+1�ܹؼ�

	MaxHeap(Item arr[], int n) {
		data = new Item[n + 1];
		capacity = n;
		for (int i = 0; i < n; i++){
			data[i + 1] = arr[i];
		}
		 count = n;
		 for (int i = count / 2; i >= 1;i--) {
			 shiftDown(i);
		}
	}

	~MaxHeap() { delete[] data; }

	int size() {
		return count;
	}

	bool isEmpty() {
		return count == 0;
	}

	// ʱ�临�Ӷ���log(n)�����
	void insert(Item item) {
		assert(count + 1 <= capacity); // ��֤����������
		data[count + 1] = item;
		count++;
		shiftUp(count);
	}

	// ʱ�临�Ӷ���log(n)�����
	Item extractMax() {
		assert(count > 0);
		Item ret = data[1];
		swap(data[1], data[count]);
		count--;
		shiftDown(1);
		return ret;
	}

private:
	Item * data;
	int count;
	int capacity;
	// ��kλ�õ�Ԫ�������ƶ�
	void shiftUp(int k) {
		while (data[k] > data[k / 2] && k >= 2) //��������Խ��
		{
			swap(data[k], data[k / 2]);
			k /= 2;
		}
	}

	// ��kλ�õ�Ԫ�������ƶ�
	void shiftDown(int k) {
		while (2 * k <= count) //�������ӵ������
		{
			int j = 2 * k;
			if (j + 1 <= count && data[j + 1] > data[j]) //���Һ���,���Һ��Ӹ���
				j += 1;
			if (data[k] >= data[j])
				break;
			swap(data[k], data[j]); // ����Ҳ���Կ������������õ��ġ�swap�Ż���
			k = j;
		}
	}
};

// ��n��Ԫ��������뵽һ���ն��У��㷨���Ӷ���O��nlogn��������ռ临�Ӷ���O(nlogn)
template<typename T>
void heapSort1(T arr[], int n) {
	MaxHeap<T> maxheap = MaxHeap<T>(n);
	for (int i = 0; i < n; i++)
		maxheap.insert(arr[i]);
	for (int i = n - 1; i >= 0; i--)
		arr[i] = maxheap.extractMax();
}

// �ӽ��ѷ�ʽ�Ͻ����Ż�,��heapify���ѷ���
// heapify���ѷ���ʱ�临�Ӷ���O��n)������ռ临�Ӷ���O��n)
template<typename T>
void heapSort2(T arr[], int n) {
	MaxHeap<T> maxheap = MaxHeap<T>(arr, n);
	for (int i = n - 1; i >= 0; i--)
		arr[i] = maxheap.extractMax();
}


template<typename T>
void __shiftDown(T arr[], int n, int k) {
	while (2 * k + 1 < n) //�������ӵ������ �� �����Ǵ��㿪ʼ����ΪС��
	{
		int j = 2 * k + 1;
		if (j + 1 < n && arr[j + 1] > arr[j]) //���Һ���,���Һ��Ӹ���
			j += 1;
		if (arr[k] >= arr[j])
			break;
		swap(arr[k], arr[j]); // ����Ҳ���Կ������������õ��ġ�swap�Ż���
		k = j;
	}

}

// �������ˣ�ԭ�ض�����,����ռ临�Ӷ�ΪO(1)
// ʱ���ʡ�ڲ��ÿ����µĿռ��Լ����ö��µĿռ���в���
// ��ʱ��heapSort3 < heapSort2 < heapSort1
template <typename T>
void heapSort3(T arr[], int n) {
	// ���ѵĹ���,heapify
	for (int i = (n - 1) / 2; i >= 0;i--) {
		__shiftDown(arr, n, i); 
	}
	for (int i = n - 1; i > 0;i--) {
		swap(arr[0], arr[i]);
		__shiftDown(arr, i, 0);
	}
}


//����������
template<typename Item>
class IndexMaxHeap
{
public:
	IndexMaxHeap(int capacity)
	{
		data = new Item[capacity + 1]; // �洢�ռ���capacity,����Ԫ�ظ�����count
		indexes = new int[capacity + 1];
		reverse = new int[capacity + 1];
		for (int i = 0; i <= capacity;i++){
			reverse[i] = 0;
		}
		count = 0;
		this->capacity = capacity;
	}  //+1�ܹؼ�

	IndexMaxHeap(Item arr[], int n) {
		data = new Item[n + 1];
		capacity = n;
		for (int i = 0; i < n; i++) {
			data[i + 1] = arr[i];
		}
		count = n;
		for (int i = count / 2; i >= 1;i--) {
			shiftDown(i);
		}
	}

	~IndexMaxHeap() { 
		delete[] data;
		delete[] indexes;
		delete[] reverse;
	}

	int size() {
		return count;
	}

	bool isEmpty() {
		return count == 0;
	}

	// �����i���û����ԣ��Ǵ�0�����ġ����ڶ����i�Ǵ�1��ʼ�ġ�
	void insert(int i, Item item) {
		assert(count + 1 <= capacity); // ��֤����������
		assert(i + 1 >= 1 && i + 1 <= capacity);
		i += 1;
		data[i] = item;
		indexes[count + 1] = i;
		reverse[i] = count + 1;
		count++;
		shiftUp(count);
	}

	Item extractMax() {
		assert(count > 0);

		Item ret = data[indexes[1]];
		swap(indexes[1], indexes[count]);
		reverse[indexes[1]] = 1;
		reverse[indexes[count]] = 0; // ɾ���˸�Ԫ�أ����Ԫ�ص�reverseֵΪ0
		count--;
		shiftDown(1);
		return ret;
	}

	int extractMaxIndex() {
		assert(count > 0);

		int ret = indexes[1] - 1; // ���ǵ��ⲿ�û���������0��ʼ
		swap(indexes[1], indexes[count]);
		reverse[indexes[1]] = 1;
		reverse[indexes[count]] = 0; // ɾ���˸�Ԫ�أ����Ԫ�ص�reverseֵΪ0
		count--;
		shiftDown(1);
		return ret;
	}
	bool contain(int i) {
		assert(i + 1 >= 1 && i + 1 <= capacity);
		return reverse[i + 1] != 0; // ��һ��������reverse,�����ڹ��캯������Ҫ������г�ʼ���ġ�
	}
	Item getItem(int i) {
		assert(contain(i));
		return data[i + 1];
	}

	// ʱ�临�Ӷ�O��n+logn��,��O��n)�����
	void change(int i, Item newItem) {
		assert(contain(i)); // ע�⣺i����Ҫ�ڶ������capacity�ķ�Χ�ڲ��ܴ����ڶ���
		i += 1;
		data[i] = newItem;
		// �ҵ�indexes[j] = i, j��ʾdata[i]�ڶ��е�λ�á�
		// ֮��shiftUp(j),��shiftDown(j) (ʵ��������������ִֻ����һ��)
		/* O��n)ʱ�临�Ӷ�
		for (int j = 1; j <= count;j++)
		{
			if (indexes[j] == i) {
				shiftUp(j);
				shiftDown(j);
				return;
			}
		}*/
		//����ʱ�临�Ӷȸ��ŵĽⷨ,O(1)ʱ�临�Ӷȡ�
		int j = reverse[i];
		shiftUp(j);
		shiftDown(j);
		return;
	}
private:
	Item * data;
	int * indexes;
	int * reverse; // ���ʣ�indexes[i] = j; ��Ӧ�� reverse[j] = i;
	               // ���⻹�� indexes[reverse[i]] = i; reverse[indexes[i]] = i;
	int count;
	int capacity;
	// ��kλ�õ�Ԫ�������ƶ�
	void shiftUp(int k) {
		while (data[indexes[k]] > data[indexes[k / 2]] && k >= 2) //��������Խ��
		{
			swap(indexes[k], indexes[k / 2]);

			reverse[indexes[k / 2]] = k / 2; //�Ƚ��ƣ�������Ȥ��
			reverse[indexes[k]] = k;

			k /= 2;
		}
	}

	// ��kλ�õ�Ԫ�������ƶ�
	void shiftDown(int k) {
		while (2 * k <= count) //�������ӵ������
		{
			int j = 2 * k;
			if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]]) //���Һ���,���Һ��Ӹ���
				j += 1;
			if (data[k] >= data[j])
				break;
			swap(indexes[k], indexes[j]); // ����Ҳ���Կ������������õ��ġ�swap�Ż���
			reverse[indexes[k]] = k;
			reverse[indexes[j]] = j;
			k = j;
		}
	}
};



