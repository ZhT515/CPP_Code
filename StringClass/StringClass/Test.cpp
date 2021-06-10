#include<iostream>
#include<string>
using namespace std;


//npos == 4290000000

//size_t == un int
//int main()
//{
//	char str[] = "中国";
//	cout << strlen(str) << endl;
//
//	wchar_t wch;		//宽字节，2b,能更好表示
//
//	return 0;
//}

int main()
{
	/*****************构造**********************/
	string s1;				//无参
	string s2("zhtzhtzht");		//带参
	string s3(s2);			//拷贝构造

	string s4 = "zhtzhtzhtzht";

	//substring ,给多了或者给string::npos 都是走到尾
	string s5(s4, 3, 5);	//从3开始5个

	cout << s5 << endl;

	string s6("123456", 3);			//取前三个构造

	cout << s6 << endl;

	/*************三种遍历***************/
	//1.下标+【】
	for (size_t i = 0; i < s2.size(); i++)
	{
		cout << s2[i] << " ";
	}

	cout <<endl;

	//2.迭代器,可以写
	//[begin(),end()) end()返回的是最后一个下一个位置
	//counst 只能用counst_iterator 遍历，只读不可写	
	//counst 对象就自动是counst迭代器
	string::iterator it = s2.begin();		//正向
	while (it != s2.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	string::reverse_iterator rit = s2.rbegin();		//反向
	while (rit != s2.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;

	//3. C++11 提供 范围FOR
	//依次取容器中的数据，赋值给E,自动判断结束
	for (auto e : s2)
	{
		cout << e << " ";
	}
	cout << endl;

	s3.push_back('a');			//尾插一个字符
	s3.push_back('b');

	s3.append("qqqqq");			//尾插字符串
	cout << s3 << endl;

	s3.append(s2);				//尾插对象，也可以迭代器
	cout << s3 << endl;

	//+=
	//实际最喜欢的
	s3 += ' ';
	s3 += "zzzaa";
	s3 += s2;
	cout << s3 << endl;

	//尽量少用，底层用数组实现
	s3.insert(0, " ztzt ");		//指定位置插入，可实现头插
	s3.insert(3, " qqqq ");
	cout << s3 << endl;

	s3.erase(0, 1);		//头删
	s3.erase(3, 5);		//第三个位置删5个

	cout << s3 << endl;

	s3.erase(3);		//第三个后全删
	s3.erase();			//从0到npos全删，默认是0开始

	cout << s3 << endl;

	string s7(s2);

	cout << s7.size() << endl;
	cout << s7.capacity() << endl;			//空间大小

	s7.clear();								//清空

	cout << s7.size() << endl;
	cout << s7.capacity() << endl;

	string s8;
	cout << s8.size() << endl;
	cout << s8.capacity() << endl;

	s8.resize(20,'x');		//插入n个x,默认\0；已有的话追加，把总空间变成指定的

	cout << s8.size() << endl;
	cout << s8.capacity() << endl;

	s8.reserve(50);					//不影响已有的

	cout << s8.size() << endl;
	cout << s8.capacity() << endl;

	cout << s8 << endl;					//重载的<<
	cout << s8.c_str() << endl;			//c的方式，配合C使用的接口

	string filename = "test.cpp";
	//找文件后缀
	size_t pos = filename.find('.');		//找位置  rfind反着找

	if (pos != string::npos)
	{
		string suff = filename.substr(pos);
	}


	return 0;
}