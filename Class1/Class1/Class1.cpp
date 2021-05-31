#include<iostream>
using namespace std;

/*
cout ��ostream��Ķ���
cin ��istream��Ķ���
*/

class Date
{
	friend ostream& operator<< (ostream& out,const Date& d);					//��Ԫ���������Է���˽�е�
	friend istream& operator>> (istream& in, Date& d);
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

ostream& operator<< (ostream & out,const Date&d)				//��Ϊȫ�֣�������λ��			
{
	out << d._year << "-" << d._month << "-" << d._day;

	return out;
}

istream& operator>> (istream& in, Date& d)						//<<>>�����������������������غ������
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