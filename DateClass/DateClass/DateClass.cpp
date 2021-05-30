#include"Date.h"

inline int GetDay(int year, int month)									//���ص���������ڣ�Ƶ��������������	
{
	static int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };		//12���µ�����,ֻ����һ�Σ����ھ�̬��
	int day = days[month - 1];
	if (month == 2 && (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0) )		//�ж�����
	{
		day = 29; 
	}
	return day;
}

Date::Date(int year, int month, int day)				//ָ������,ȱʡ����ֻ����һ���ط�����
{
	if (year >= 0
		&& month <= 12 && month >= 1
		&& day > 0 && day <= GetDay(year, month))		//�ж����ڵĺϷ���
	{
		_year = year;
		_month = month;
		_day = day;
	}
	else
	{
		cout << " no " << endl;
		assert(false);
	}

}
void Date::Print()
{
	cout << _year << "��" << _month << "��" << _day << "��" << endl;
}

Date& Date::operator+=(int day)						//
{
	if (day < 0)									//day<0
	{
		_day -= -day;
	}
	else
	{
		_day += day;

		while (_day > GetDay(_year, _month))			//�ж�day�Ƿ�Ϸ������Ϸ����·�+1���·ݳ�������1����++��
		{
			_day -= GetDay(_year, _month);
			_month++;
			if (_month > 12)
			{
				_month = 1;
				_year++;
			}
		}
	}

	return *this;
}

Date Date::operator+(int day)			//��Ҫ����һ���µĶ��󣬷����������
{
	Date ret(*this);					//ʹ��Ĭ�Ͽ������캯����ǳ������

	ret += day;					//ֱ�ӽ��и���,ֱ�Ӳ������󣬲�Ҫ������Ա��

	return ret;

}

Date& Date::operator-=(int day)
{
	if (day < 0)								//������
	{
		_day += -day;
	}
	else										
	{
		_day -= day;

		while (_day <= 0)
		{
			_month--;							//��-�£���ΪҪ����һ�����㣬
			if (_month < 0)						//�߼��ο�+=
			{
				_month = 12;
				_year--;
			}
			_day += GetDay(_year, _month);
		}
	}

	return *this;
}

Date Date::operator-(int day)
{
	Date ret(*this);

	ret -= day;

	return ret;
}



//Date:: ������
bool Date::operator>(const Date& d)const
{
	if (_year < d._year)
	{
		return false;
	}
	else if (_year > d._year)
	{
		return true;
	}
	else
	{
		if (_month < d._month)
		{
			return false;
		}
		else if (_month > d._month)
		{
			return true;
		}
		else
		{
			if (_day > d._day)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

}
bool Date::operator<(const Date& d)const
{
	if (_year > d._year)
	{
		return false;
	}
	else if (_year < d._year)
	{
		return true;
	}
	else
	{
		if (_month > d._month)
		{
			return false;
		}
		else if (_month < d._month)
		{
			return true;
		}
		else
		{
			if (_day < d._day)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
bool Date::operator==(const Date& d)const
{
	if (*this > d || *this < d)
		return false;
	else
		return true;
}
bool Date::operator<=(const Date& d)const
{
	if (*this > d)
		return false;
	else
		return true;
}
bool Date::operator>=(const Date& d)const
{
	if (*this < d)
		return false;
	else
		return true;
}
bool Date::operator!=(const Date& d)const
{
	if (*this == d)
		return false;
	else
		return true;
}

Date& Date::operator++()
{
	*this += 1;

	return *this;
}
Date Date::operator++(int)
{
	Date ret(*this);
	*this += 1;					//���ﲻ�ܶ�ret��������ΪҪ������ֵ��thisʵ����Ҫ�ӣ���Ϊ�˷���һ����֮ǰ�����Է���һ��ret

	return ret;
}

Date& Date::operator--()
{
	*this -= 1;

	return *this;
}

Date Date::operator--(int)
{
	Date ret(*this);
	*this -= 1;

	return ret;
}

int Date::operator-(const Date& d)			//�������ˣ�Ȼ������������䣬++i�Ϳ��ԡ�
{
	int flag = 1;					//�ж�����������Ĭ��Ϊ��
	Date max = *this;				//Ĭ��dС���������ȡ���ַ�ʽ������while����ڱ������
	Date min = d;

	if (*this < d)
	{
		max = d;				//�����������һ�ֱ�﷨,�����ظ����������ظ�������ݾͽ�ԭ����������Ϊ���ս��
		min = *this;
		flag = -1;
	}


	int n = 0;

	while (max > min)
	{
		++n;
		++(min);
	}

	return n * flag;			//��С*����
}