#include<iostream>

using std::cout;
using std::endl;


void TestFunc(int a, int b = 10, int c = 30)
{
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
}

int	Add(int a, int b)								//�������أ����������ͣ�������˳�򣩲�ͬ�Ϳ�
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
	cout << a << "," << p << endl;			//�Զ�ʶ������(��������+���������)

	std::cin >> a;							//����
	cout << a << "," << *p << endl;

	char str[30];
	std::cin >> str;						//�Զ�ʶ������
	cout << str << endl;

	TestFunc(1);							//����ȱʡ
	TestFunc(1, 2);
	TestFunc(1, 2, 3);

	cout << Add(1, 2) << endl;
	cout << Add(1.01, 2.02) << endl;
	cout << Add(1L, 2L) << endl;

	return 0;
}