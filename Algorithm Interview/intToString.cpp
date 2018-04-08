
// 这是要求int不能为0和负数的
string intToString(int num) {
	string s = "";
	while (num) {
		s += '0' + num % 10;
		num /= 10;
	}
	string temp = "";
	for (int i = s.size() - 1; i >= 0; i--)
		temp += s[i];  //是不能用temp[i] = s[i]的，这是因为temp.size()为0，如果temp的size和s一样，那么可以这样用。
	return temp;

}

//如果要考虑0和负数

string intToString(int num) {
	if (num == 0)
		return "0";
	int flag = 0;
	if (num < 0)
	{
		num = -num;
		flag = 1;
	}
	string s = "";
	while (num) {
		s += '0' + num % 10;
		num /= 10;
	}
	string temp = "";
	if (flag)
		 temp += "-";
	
	for (int i = s.size() - 1; i >= 0; i--)
		temp += s[i];  //是不能用temp[i] = s[i]的
	return temp;

}
