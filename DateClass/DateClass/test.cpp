#include"Date.h"

void Test1()
{
	Date d1(2021, 5, 29);
	d1.Print();

	Date d2(2100, 2, 29);
	d2.Print();
}

void Test2()			//+
{
	Date d1(2008, 2, 3);

	d1 += 60;
	d1.Print();

	Date d2(2021, 12, 29);

	d2 += 100;
	d2.Print();


	Date d3(2021, 12, 29);

	Date d4 = d3 + 100;
	d4.Print();
}

void Test3()			//-
{
	Date d1(2021, 5, 29);

	d1 -= 10;
	d1.Print();

	Date d2(2021, 12, 29);

	d2 -= 100;
	d2.Print();


	Date d3(2021, 12, 29);
	Date d4 = d3 - 100;
	d4.Print();
}

void Test4()			//++/--
{
	Date d1(2021, 5, 29);

	d1 -= 10;
	d1.Print();

	Date d2(2021, 12, 29);

	++d2;					//«∞÷√
	d2.Print();

	--d2;					//«∞÷√
	d2.Print();

	d2++;
	d2.Print();

	d2--;
	d2.Print();

}

void Test5()			//<>=
{
	Date d1(2021, 5, 29);
	Date d2(2021, 5, 30);

	if(d2 > d1)
		d2.Print();
	else
		d1.Print();
	Date d3(2021, 5, 29);
	Date d4(2021, 5, 29);

	if (d3 > d4)
		d2.Print();
	else
		cout << "no >" << endl;

}

void Test6()			//<>=
{
	Date d1(2021, 5, 29);
	Date d2(2021, 6, 29);

	if (d2 < d1)
		d2.Print();
	else
		d1.Print();
	Date d3(2021, 5, 29);
	Date d4(2021, 3, 29);

	if (d3 < d4)
		d2.Print();
	else
		cout << "no <" << endl;

}

void Test7()			
{
	Date d1(2021, 5, 29);
	Date d2(2021, 6, 29);

	cout << d2 - d1 << endl;
	cout << d1 - d2 << endl;
}

int main()
{
	Test2();
}