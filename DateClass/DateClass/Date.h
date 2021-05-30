#pragma once
#include<iostream>
#include<cassert>

using std::cout;
using std::endl;
using std::cin;

class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1);				//1.构造函数，全缺省。
	void Print();		//打印

	//析构，拷贝构造，赋值重载，可以不写，默认生成
	//stack才写

	//运算符重载，日期加减
	Date& operator+=(int day);			//+=之后，day这个实体还是存在的，所以可以返回引用
	Date operator+(int day);

	Date& operator-=(int day);
	Date operator-(int day);

	//()为空是前置++，增加(int)是为了构成重载，后置++;
	Date& operator++();								//++d 前置可以引用，因为是先加自己身上再返回
	Date operator++(int);							//d++ 用int占位,不需要给实参

	Date& operator--();
	Date operator--(int);

	// 运算符重载
	bool operator>(const Date& d)const;
	bool operator<(const Date& d)const;
	bool operator==(const Date& d)const;
	bool operator<=(const Date& d)const;
	bool operator>=(const Date& d)const;
	bool operator!=(const Date& d)const;

	// 日期-日期 返回天数
	int operator-(const Date& d);

private:				//私有
	int _year;
	int _month;
	int _day;
};