#include<iostream>
#include<string>
using namespace std;


//npos == 4290000000

//size_t == un int
//int main()
//{
//	char str[] = "�й�";
//	cout << strlen(str) << endl;
//
//	wchar_t wch;		//���ֽڣ�2b,�ܸ��ñ�ʾ
//
//	return 0;
//}

int main()
{
	/*****************����**********************/
	string s1;				//�޲�
	string s2("zhtzhtzht");		//����
	string s3(s2);			//��������

	string s4 = "zhtzhtzhtzht";

	//substring ,�����˻��߸�string::npos �����ߵ�β
	string s5(s4, 3, 5);	//��3��ʼ5��

	cout << s5 << endl;

	string s6("123456", 3);			//ȡǰ��������

	cout << s6 << endl;

	/*************���ֱ���***************/
	//1.�±�+����
	for (size_t i = 0; i < s2.size(); i++)
	{
		cout << s2[i] << " ";
	}

	cout <<endl;

	//2.������,����д
	//[begin(),end()) end()���ص������һ����һ��λ��
	//counst ֻ����counst_iterator ������ֻ������д	
	//counst ������Զ���counst������
	string::iterator it = s2.begin();		//����
	while (it != s2.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	string::reverse_iterator rit = s2.rbegin();		//����
	while (rit != s2.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;

	//3. C++11 �ṩ ��ΧFOR
	//����ȡ�����е����ݣ���ֵ��E,�Զ��жϽ���
	for (auto e : s2)
	{
		cout << e << " ";
	}
	cout << endl;

	s3.push_back('a');			//β��һ���ַ�
	s3.push_back('b');

	s3.append("qqqqq");			//β���ַ���
	cout << s3 << endl;

	s3.append(s2);				//β�����Ҳ���Ե�����
	cout << s3 << endl;

	//+=
	//ʵ����ϲ����
	s3 += ' ';
	s3 += "zzzaa";
	s3 += s2;
	cout << s3 << endl;

	//�������ã��ײ�������ʵ��
	s3.insert(0, " ztzt ");		//ָ��λ�ò��룬��ʵ��ͷ��
	s3.insert(3, " qqqq ");
	cout << s3 << endl;

	s3.erase(0, 1);		//ͷɾ
	s3.erase(3, 5);		//������λ��ɾ5��

	cout << s3 << endl;

	s3.erase(3);		//��������ȫɾ
	s3.erase();			//��0��nposȫɾ��Ĭ����0��ʼ

	cout << s3 << endl;

	string s7(s2);

	cout << s7.size() << endl;
	cout << s7.capacity() << endl;			//�ռ��С

	s7.clear();								//���

	cout << s7.size() << endl;
	cout << s7.capacity() << endl;

	string s8;
	cout << s8.size() << endl;
	cout << s8.capacity() << endl;

	s8.resize(20,'x');		//����n��x,Ĭ��\0�����еĻ�׷�ӣ����ܿռ���ָ����

	cout << s8.size() << endl;
	cout << s8.capacity() << endl;

	s8.reserve(50);					//��Ӱ�����е�

	cout << s8.size() << endl;
	cout << s8.capacity() << endl;

	cout << s8 << endl;					//���ص�<<
	cout << s8.c_str() << endl;			//c�ķ�ʽ�����Cʹ�õĽӿ�

	string filename = "test.cpp";
	//���ļ���׺
	size_t pos = filename.find('.');		//��λ��  rfind������

	if (pos != string::npos)
	{
		string suff = filename.substr(pos);
	}


	return 0;
}