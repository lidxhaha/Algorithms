template<typename T>
class MyVector {

private:
	T * data;
	int capacity; // 存储数组中可以容纳的最大的元素个数
	int size;     // 存储数组中的元素个数

	// resize的时间复杂度是O(n)
	void resize(int newCapacity) {
		assert(newCapacity >= size);
		T *newData = new T[newCapacity];
		for (int i = 0; i < size; i++)
			newData[i] = data[i];
		delete[] data;
		data = newData;
		capacity = newCapactiy;
	}
public:
	MyVector() {
		data = new T[10];
		capacity = 10;
		size = 0;
	}

	~MyVector() {
		delete[] data;
	}

	// 经均摊后，时间复杂度为O(1)
	void push_back(T e) {

	  //assert(size < capacity);

       // 假设某次push_back时，调用了时间复杂度为O(n）的resize，那么是否认为push_back的时间复杂度为O(n)？
       // 不，这需要进行均摊时间复杂度分析，push_back的时间复杂度仍然是O(1)
       // 随着不断resize，均摊后push_back的时间复杂度仍为O(1),但是此时的O(1)已经比之前的O(1)的时间耗费要大了。 
		if (size == capacity)
			resize(2 * capacity);
		data[size++] = e;
	}

	// 经均摊后，时间复杂度为O(1)
	T pop_back() {
		assert(size > 0);
		T ret = data[size - 1];
		size--;
		if (size == capacity / 4) // 为了避免复杂度震荡的操作,使其更好地均摊。
			resize(capacity / 2);
		return ret;
	}
};

// 在临界点不停删除添加元素，则添加元素和删除元素都是O(n)级别的操作，产生了复杂度震荡。