#include<iostream>
using namespace std;

int Swap(int& a, int& b)			//引用左参数，相当于指针，直接面对本质
{
	int temp = a;
	a = b;
	b = temp;
}

int& Add(int a, int b = 10)		//实际中出了作用域就销毁了，不能用引用返回
{
	int c = a + b;
	//static int c						就不会销毁，存在静态区
	return c;
}


int Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

char Swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

long Swap(long *a, long *b)
{
	long temp = *a;
	*a = *b;
	*b = temp;
}

float Swap(float *a, float *b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}


int main()
{
	int ret = Add(2,3);			//返回的时C的别名，c已经销毁，所以越界了
}