#include<iostream>


//������� - ģ��

//����ģ��
//template<typename T>		//Ҳ����
template<class T>		//һ����T,typede ���
void Swap(T& x1, T& x2)
{
	T tmp = x1;
	x1 = x2;
	x2 = tmp;
}
//ģ�岻֧�ַ������һ����.h,һ��.cpp
namespace zht					//���������ռ�
{
	template<class T>
	class vector
	{
	public:
		size_t size();
	private:
		T* a;
		int _size;

	};
	template<class T>		//���������������涨����Ҫ�ٴ�����ģ��
	size_t vector<T>::size()
	{
		return _size;
	}
}



int main()
{
	int a = 3, b = 6;
	Swap(a, b);				//�õ�����������

	double c = 3.666, d = 6.666;
	Swap(c, d);				//������������ģ���ʵ��������
	//���������������Ƴ����ͣ�����ʽʵ����

	//��ʽ��������ʵ������
	Swap<double>(c, d);


	zht::vector<int> v1;		//ֻ����ʽ
}	