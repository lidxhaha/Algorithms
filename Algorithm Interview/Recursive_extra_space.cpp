

//递归的调用存在空间代价
//以求数组的和为例

//不用递归，空间复杂度O(1)
int sum1(int n){

	assert(n >= 0);
	int ret = 0;
	for (int i = 0; i <= n; i++)
		ret += i;
	return ret;

}


//用递归，空间复杂度O(n),因为递归的深度是n,系统栈中就要装载n个状态。
// 即：递归的深度是多少，递归所占的空间复杂度就是多少。
int sum2(int n){

	assert(n >= 0);
	if(n == 0)
		return 0;
	return n + sum2(n-1);
}