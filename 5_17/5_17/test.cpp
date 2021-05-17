#include<iostream>

using std::cout;
using std::endl;


void TestFunc(int a, int b = 10, int c = 30)
{
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
}

int	Add(int a, int b)								//函数重载，参数（类型，个数，顺序）不同就可
{
	return a + b;
}

double Add(double a, double b)
{
	return a + b;
}

long Add(long a, long b)
{
	return a + b;
}

int main()
{
	int a = 10;
	int* p = &a;
	cout << a << "," << p << endl;			//自动识别类型(函数重载+运算符重载)

	std::cin >> a;							//输入
	cout << a << "," << *p << endl;

	char str[30];
	std::cin >> str;						//自动识别类型
	cout << str << endl;

	TestFunc(1);							//部分缺省
	TestFunc(1, 2);
	TestFunc(1, 2, 3);

	cout << Add(1, 2) << endl;
	cout << Add(1.01, 2.02) << endl;
	cout << Add(1L, 2L) << endl;

	return 0;
}