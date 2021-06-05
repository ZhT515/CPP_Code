#include<iostream>


//泛化编程 - 模板

//函数模板
//template<typename T>		//也可以
template<class T>		//一般用T,typede 简称
void Swap(T& x1, T& x2)
{
	T tmp = x1;
	x1 = x2;
	x2 = tmp;
}
//模板不支持分离编译一个在.h,一个.cpp
namespace zht					//建立命名空间
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
	template<class T>		//在外面声明，外面定义需要再次声明模板
	size_t vector<T>::size()
	{
		return _size;
	}
}



int main()
{
	int a = 3, b = 6;
	Swap(a, b);				//用的是两个函数

	double c = 3.666, d = 6.666;
	Swap(c, d);				//编译器进行了模板的实例化，、
	//编译器进行推理，推出类型，是隐式实例化

	//显式，《》是实际类型
	Swap<double>(c, d);


	zht::vector<int> v1;		//只能显式
}	