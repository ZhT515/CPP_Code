#include<iostream>
using namespace std;

class Date
{
public:

	Date(int year = 1900, int month = 1, int day = 1)			//���캯��
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "1" << endl;
	}

	Date(Date& d)						//�������캯����������Date(Date d)��������޵ݹ�
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
		cout << "2" << endl;
	}

	//������������һ��������ָ�룬�ͽ�this		void Init(Date *this , int year,int month, int day)
	void Print(int year,int month, int day)
	{
		
		this->_year = year;
		this->_month = month;
		this->_day = day;
		cout << _year << endl;

	}

	~Date()														//��������
	{
		cout << "3" << endl;
	}

private:
	int _year;		//������������
	int _month;
	int _day;
};

int main()
{
	Date d1;
	d1.Print(2021, 5, 25);			//�������d1.Init(&d1 , 2021, 5, 25);

	Date d2;
	d2.Print(2021, 5, 27);

	Date d3(d1);
	return 0;
}