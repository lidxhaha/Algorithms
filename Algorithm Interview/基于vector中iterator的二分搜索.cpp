#include<iostream>
#include <cmath>
#include <vector>
using namespace std;

// 关键：指向不同的vector的元素的迭代器不能做比较，所以子函数用引用
vector<int>::iterator  binarySearch(vector<int>& data, int target) {
	auto begin = data.begin(), end = data.end();
	decltype(begin) middle;
	while (begin < end) {
		middle = begin + (end - begin) / 2;
		if (*middle == target)
			return middle;
		else if (*middle < target)
			begin = middle + 1;
		else
			end = middle;
	}
	return data.end();

}

int main() {
	
	vector<int> data = { 1,2,3,4,5 };
	auto result = binarySearch(data, 6);
	if (result == data.end()) 
		cout << "no result found!" << endl;
	else
		cout << (*result) << endl;
	
	getchar();
	return 0;
}
