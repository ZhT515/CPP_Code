#include<iostream>
using namespace std;

int Swap(int& a, int& b)			//������������൱��ָ�룬ֱ����Ա���
{
	int temp = a;
	a = b;
	b = temp;
}

int& Add(int a, int b = 10)		//ʵ���г���������������ˣ����������÷���
{
	int c = a + b;
	//static int c						�Ͳ������٣����ھ�̬��
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
	int ret = Add(2,3);			//���ص�ʱC�ı�����c�Ѿ����٣�����Խ����
}