#pragma once
// 最大堆类
template<typename Item>
class MaxHeap
{
public:
	MaxHeap(int capacity)
	{
		data = new Item[capacity + 1]; // 存储空间是capacity,但是元素个数是count
		count = 0;
		this->capacity = capacity;
	}  //+1很关键

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

	// 时间复杂度是log(n)级别的
	void insert(Item item) {
		assert(count + 1 <= capacity); // 保证不超过容量
		data[count + 1] = item;
		count++;
		shiftUp(count);
	}

	// 时间复杂度是log(n)级别的
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
	// 将k位置的元素向上移动
	void shiftUp(int k) {
		while (data[k] > data[k / 2] && k >= 2) //考虑数组越界
		{
			swap(data[k], data[k / 2]);
			k /= 2;
		}
	}

	// 将k位置的元素向下移动
	void shiftDown(int k) {
		while (2 * k <= count) //在有左孩子的情况下
		{
			int j = 2 * k;
			if (j + 1 <= count && data[j + 1] > data[j]) //有右孩子,且右孩子更大
				j += 1;
			if (data[k] >= data[j])
				break;
			swap(data[k], data[j]); // 这里也可以考虑在排序中用到的“swap优化”
			k = j;
		}
	}
};

// 将n个元素逐个插入到一个空堆中，算法复杂度是O（nlogn），额外空间复杂度是O(nlogn)
template<typename T>
void heapSort1(T arr[], int n) {
	MaxHeap<T> maxheap = MaxHeap<T>(n);
	for (int i = 0; i < n; i++)
		maxheap.insert(arr[i]);
	for (int i = n - 1; i >= 0; i--)
		arr[i] = maxheap.extractMax();
}

// 从建堆方式上进行优化,用heapify建堆法。
// heapify建堆法，时间复杂度是O（n)，额外空间复杂度是O（n)
template<typename T>
void heapSort2(T arr[], int n) {
	MaxHeap<T> maxheap = MaxHeap<T>(arr, n);
	for (int i = n - 1; i >= 0; i--)
		arr[i] = maxheap.extractMax();
}


template<typename T>
void __shiftDown(T arr[], int n, int k) {
	while (2 * k + 1 < n) //在有左孩子的情况下 ； 现在是从零开始，改为小于
	{
		int j = 2 * k + 1;
		if (j + 1 < n && arr[j + 1] > arr[j]) //有右孩子,且右孩子更大
			j += 1;
		if (arr[k] >= arr[j])
			break;
		swap(arr[k], arr[j]); // 这里也可以考虑在排序中用到的“swap优化”
		k = j;
	}

}

// 不用类了，原地堆排序,额外空间复杂度为O(1)
// 时间节省在不用开辟新的空间以及不用对新的空间进行操作
// 用时：heapSort3 < heapSort2 < heapSort1
template <typename T>
void heapSort3(T arr[], int n) {
	// 建堆的过程,heapify
	for (int i = (n - 1) / 2; i >= 0;i--) {
		__shiftDown(arr, n, i); 
	}
	for (int i = n - 1; i > 0;i--) {
		swap(arr[0], arr[i]);
		__shiftDown(arr, i, 0);
	}
}


//索引最大堆类
template<typename Item>
class IndexMaxHeap
{
public:
	IndexMaxHeap(int capacity)
	{
		data = new Item[capacity + 1]; // 存储空间是capacity,但是元素个数是count
		indexes = new int[capacity + 1];
		reverse = new int[capacity + 1];
		for (int i = 0; i <= capacity;i++){
			reverse[i] = 0;
		}
		count = 0;
		this->capacity = capacity;
	}  //+1很关键

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

	// 传入的i对用户而言，是从0索引的。但在堆里的i是从1开始的。
	void insert(int i, Item item) {
		assert(count + 1 <= capacity); // 保证不超过容量
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
		reverse[indexes[count]] = 0; // 删除了该元素，则该元素的reverse值为0
		count--;
		shiftDown(1);
		return ret;
	}

	int extractMaxIndex() {
		assert(count > 0);

		int ret = indexes[1] - 1; // 考虑到外部用户的索引从0开始
		swap(indexes[1], indexes[count]);
		reverse[indexes[1]] = 1;
		reverse[indexes[count]] = 0; // 删除了该元素，则该元素的reverse值为0
		count--;
		shiftDown(1);
		return ret;
	}
	bool contain(int i) {
		assert(i + 1 >= 1 && i + 1 <= capacity);
		return reverse[i + 1] != 0; // 又一次利用了reverse,所以在构造函数中是要对其进行初始化的。
	}
	Item getItem(int i) {
		assert(contain(i));
		return data[i + 1];
	}

	// 时间复杂度O（n+logn）,即O（n)级别的
	void change(int i, Item newItem) {
		assert(contain(i)); // 注意：i必须要在堆里，而在capacity的范围内不能代表在堆中
		i += 1;
		data[i] = newItem;
		// 找到indexes[j] = i, j表示data[i]在堆中的位置。
		// 之后shiftUp(j),再shiftDown(j) (实际中这两个操作只执行了一个)
		/* O（n)时间复杂度
		for (int j = 1; j <= count;j++)
		{
			if (indexes[j] == i) {
				shiftUp(j);
				shiftDown(j);
				return;
			}
		}*/
		//换成时间复杂度更优的解法,O(1)时间复杂度。
		int j = reverse[i];
		shiftUp(j);
		shiftDown(j);
		return;
	}
private:
	Item * data;
	int * indexes;
	int * reverse; // 性质：indexes[i] = j; 则应该 reverse[j] = i;
	               // 此外还有 indexes[reverse[i]] = i; reverse[indexes[i]] = i;
	int count;
	int capacity;
	// 将k位置的元素向上移动
	void shiftUp(int k) {
		while (data[indexes[k]] > data[indexes[k / 2]] && k >= 2) //考虑数组越界
		{
			swap(indexes[k], indexes[k / 2]);

			reverse[indexes[k / 2]] = k / 2; //比较绕，但是有趣！
			reverse[indexes[k]] = k;

			k /= 2;
		}
	}

	// 将k位置的元素向下移动
	void shiftDown(int k) {
		while (2 * k <= count) //在有左孩子的情况下
		{
			int j = 2 * k;
			if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]]) //有右孩子,且右孩子更大
				j += 1;
			if (data[k] >= data[j])
				break;
			swap(indexes[k], indexes[j]); // 这里也可以考虑在排序中用到的“swap优化”
			reverse[indexes[k]] = k;
			reverse[indexes[j]] = j;
			k = j;
		}
	}
};



