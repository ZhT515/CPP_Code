#include<iostream>
using namespace std;

class Date
{
public:

	Date(int year = 1900, int month = 1, int day = 1)			//构造函数
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "1" << endl;
	}

	Date(Date& d)						//拷贝构造函数，不可以Date(Date d)会造成无限递归
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
		cout << "2" << endl;
	}

	//编译器会增加一个隐含的指针，就叫this		void Init(Date *this , int year,int month, int day)
	void Print(int year,int month, int day)
	{
		
		this->_year = year;
		this->_month = month;
		this->_day = day;
		cout << _year << endl;

	}

	~Date()														//析构函数
	{
		cout << "3" << endl;
	}

private:
	int _year;		//对象的命名风格
	int _month;
	int _day;
};

int main()
{
	Date d1;
	d1.Print(2021, 5, 25);			//处理成了d1.Init(&d1 , 2021, 5, 25);

	Date d2;
	d2.Print(2021, 5, 27);

	Date d3(d1);
	return 0;
}