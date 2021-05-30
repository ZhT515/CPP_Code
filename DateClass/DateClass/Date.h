#pragma once
#include<iostream>
#include<cassert>

using std::cout;
using std::endl;
using std::cin;

class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1);				//1.���캯����ȫȱʡ��
	void Print();		//��ӡ

	//�������������죬��ֵ���أ����Բ�д��Ĭ������
	//stack��д

	//��������أ����ڼӼ�
	Date& operator+=(int day);			//+=֮��day���ʵ�廹�Ǵ��ڵģ����Կ��Է�������
	Date operator+(int day);

	Date& operator-=(int day);
	Date operator-(int day);

	//()Ϊ����ǰ��++������(int)��Ϊ�˹������أ�����++;
	Date& operator++();								//++d ǰ�ÿ������ã���Ϊ���ȼ��Լ������ٷ���
	Date operator++(int);							//d++ ��intռλ,����Ҫ��ʵ��

	Date& operator--();
	Date operator--(int);

	// ���������
	bool operator>(const Date& d)const;
	bool operator<(const Date& d)const;
	bool operator==(const Date& d)const;
	bool operator<=(const Date& d)const;
	bool operator>=(const Date& d)const;
	bool operator!=(const Date& d)const;

	// ����-���� ��������
	int operator-(const Date& d);

private:				//˽��
	int _year;
	int _month;
	int _day;
};