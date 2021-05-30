#include"Date.h"

inline int GetDay(int year, int month)									//返回当月最大日期，频繁调用所以内联	
{
	static int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };		//12个月的日期,只创建一次，放在静态区
	int day = days[month - 1];
	if (month == 2 && (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0) )		//判断闰年
	{
		day = 29; 
	}
	return day;
}

Date::Date(int year, int month, int day)				//指定类域,缺省函数只能在一个地方出现
{
	if (year >= 0
		&& month <= 12 && month >= 1
		&& day > 0 && day <= GetDay(year, month))		//判断日期的合法性
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
	cout << _year << "年" << _month << "月" << _day << "日" << endl;
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

		while (_day > GetDay(_year, _month))			//判断day是否合法，不合法就月份+1，月份超出就置1，年++；
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

Date Date::operator+(int day)			//需要创建一个新的对象，返回这个对象
{
	Date ret(*this);					//使用默认拷贝构造函数（浅拷贝）

	ret += day;					//直接进行复用,直接操作对象，不要操作成员。

	return ret;

}

Date& Date::operator-=(int day)
{
	if (day < 0)								//减负数
	{
		_day += -day;
	}
	else										
	{
		_day -= day;

		while (_day <= 0)
		{
			_month--;							//先-月，因为要往上一个月算，
			if (_month < 0)						//逻辑参考+=
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



//Date:: 声明域
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
	*this += 1;					//这里不能对ret操作，因为要做返回值，this实际上要加，但为了返回一个加之前，所以返回一个ret

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

int Date::operator-(const Date& d)			//设置两端，然后遍历整个区间，++i就可以。
{
	int flag = 1;					//判断日期正负，默认为正
	Date max = *this;				//默认d小，如果不采取这种方式，下面while会存在编译错误
	Date min = d;

	if (*this < d)
	{
		max = d;				//拷贝构造的另一种表达法,不能重复构建对象，重复定义根据就近原则会以上面的为最终结果
		min = *this;
		flag = -1;
	}


	int n = 0;

	while (max > min)
	{
		++n;
		++(min);
	}

	return n * flag;			//大小*正负
}