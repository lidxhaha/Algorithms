

//时间复杂度O(sqrt(n))
// 0和1既非素数也非合数
bool isPrime(int n){
    assert(n >= 2);
	for (int x = 2; x*x <= n; x++)
		if (n%x == 0)
			return false;
	return true;
}