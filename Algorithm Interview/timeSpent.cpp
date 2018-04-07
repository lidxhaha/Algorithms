
#include <ctime>

void timeSpent(){

	clock_t startTime = clock();

	// add test code here

	clock_t endTime = clock();

     // 输出的时间以秒为单位
	cout <<"Time Spent is: "<< double(endTime - startTime)/CLOCKS_PER_SEC<<endl;
}