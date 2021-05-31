#include<iostream>
using namespace std;

/*
cout 是ostream类的对象
cin 是istream类的对象
*/

class Date
{
	friend ostream& operator<< (ostream& out,const Date& d);					//友元函数，可以访问私有的
	friend istream& operator>> (istream& in, Date& d);
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

ostream& operator<< (ostream & out,const Date&d)				//设为全局，避免抢位置			
{
	out << d._year << "-" << d._month << "-" << d._day;

	return out;
}

istream& operator>> (istream& in, Date& d)						//<<>>是输入输出运算符，所以重载后就用了
{
	in>> d._year >> d._month >> d._day;
	
	return in;
}

int main()
{
	Date d1;
	cin >> d1;

	Date d2;
	cin >> d1;

	cout << d1 <<endl<< d2<<endl;

	
}