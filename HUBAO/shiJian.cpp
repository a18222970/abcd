#include "pch.h"
#include "shiJian.h"

//#include <time.h>
/*
	struct tm
	{
		int tm_sec;   // ��-[0,60]֮�����������������
		int tm_min;   // Сʱ��ļ�����- [0,59]
		int tm_hour;  // ����ҹ����Сʱ- [0,23]
		int tm_mday;  // ����- [1,31]
		int tm_mon;   // һ���������·�- [0,11]
		int tm_year;  // ��1900������
		int tm_wday;  // ������������������- [0,6]
		int tm_yday;  // 1��1������������- [0,365]
		int tm_isdst; // ����ʱ��־
		//1��86400��
		//��֤ʱ�䵽�� ���Ե����Ա���,��,��
	};
	*/
void shiJian::huoQuShiJian()
{
	m_time = CTime::GetCurrentTime();    //��ȡ��ǰʱ������  ��ʱ���
	CString a;
	a = m_time.Format(L"%Y-%m-%d / %H:%M:%S  %A");
	AfxMessageBox(a);
	a.Format(L"%u", m_time.GetTime());// GetTime() �����ص�ǰ CTime ������1970��1��1��֮�������
	AfxMessageBox(a);//���ɵ�ǰʱ���ʱ���
}

unsigned  shiJian::getDangQianShiJianCuo()
{
	m_time = CTime::GetCurrentTime();    //��ȡ��ǰʱ������  ��ʱ���
	unsigned long sjc = m_time.GetTime();
	return sjc;
}

int shiJian::setShiJianCuo(char* str_time)
{//ʱ���ʽ:  2021:12:31 00:00:00 //1640880000
	struct tm stm;
	int iY, iM, iD, iH, iMin, iS;
	//2021:12:31 00:00:00
	memset(&stm, 0, sizeof(stm));//����
	iY = atoi(str_time);//�ַ���ת����
	iM = atoi(str_time + 5);
	iD = atoi(str_time + 8);
	iH = atoi(str_time + 11);
	iMin = atoi(str_time + 14);
	iS = atoi(str_time + 17);

	stm.tm_year = iY - 1900;
	stm.tm_mon = iM - 1;
	stm.tm_mday = iD;
	stm.tm_hour = iH;
	stm.tm_min = iMin;
	stm.tm_sec = iS;

	/*printf("%d-%0d-%0d %0d:%0d:%0d\n", iY, iM, iD, iH, iMin, iS);*/   //��׼ʱ���ʽ���磺2016:08:02 12:12:30
	return (int)mktime(&stm);//������ʱ��ת��Ϊʱ���
}

BOOL shiJian::getDangQianShiJianCuo(CString* a)
{
	m_time = CTime::GetCurrentTime();    //��ȡ��ǰʱ������  ��ʱ���
	//CString a;
	*a = m_time.Format(L"%Y-%m-%d / %H:%M:%S  %A     BOOL");
	AfxMessageBox(*a);
	(*a).Format(L"%u", m_time.GetTime());// GetTime() �����ص�ǰ CTime ������1970��1��1��֮�������
	AfxMessageBox(*a);//���ɵ�ǰʱ���ʱ���
	return 0;
}

CString shiJian::getDQshiJianCuo()
{
	m_time = CTime::GetCurrentTime();    //��ȡ��ǰʱ������  ��ʱ���
	CString a;
	a = m_time.Format(L"%Y-%m-%d / %H:%M:%S  %A     cs");
	AfxMessageBox(a);
	a.Format(L"%u", m_time.GetTime());// GetTime() �����ص�ǰ CTime ������1970��1��1��֮�������
	AfxMessageBox(a);//���ɵ�ǰʱ���ʱ���
	return a;
}

void shiJian::leixingdaxiao()
{
	using namespace std;
	cout << "type: \t\t" << "************size**************" << endl;
	cout << "bool: \t\t" << "��ռ�ֽ�����" << sizeof(bool);
	cout << "\t���ֵ��" << (numeric_limits<bool>::max)();
	cout << "\t\t��Сֵ��" << (numeric_limits<bool>::min)() << endl;
	cout << "char: \t\t" << "��ռ�ֽ�����" << sizeof(char);
	cout << "\t���ֵ��" << (numeric_limits<char>::max)();
	cout << "\t\t��Сֵ��" << (numeric_limits<char>::min)() << endl;
	cout << "signed char: \t" << "��ռ�ֽ�����" << sizeof(signed char);
	cout << "\t���ֵ��" << (numeric_limits<signed char>::max)();
	cout << "\t\t��Сֵ��" << (numeric_limits<signed char>::min)() << endl;
	cout << "unsigned char: \t" << "��ռ�ֽ�����" << sizeof(unsigned char);
	cout << "\t���ֵ��" << (numeric_limits<unsigned char>::max)();
	cout << "\t\t��Сֵ��" << (numeric_limits<unsigned char>::min)() << endl;
	cout << "wchar_t: \t" << "��ռ�ֽ�����" << sizeof(wchar_t);
	cout << "\t���ֵ��" << (numeric_limits<wchar_t>::max)();
	cout << "\t\t��Сֵ��" << (numeric_limits<wchar_t>::min)() << endl;
	cout << "short: \t\t" << "��ռ�ֽ�����" << sizeof(short);
	cout << "\t���ֵ��" << (numeric_limits<short>::max)();
	cout << "\t\t��Сֵ��" << (numeric_limits<short>::min)() << endl;
	cout << "int: \t\t" << "��ռ�ֽ�����" << sizeof(int);
	cout << "\t���ֵ��" << (numeric_limits<int>::max)();
	cout << "\t��Сֵ��" << (numeric_limits<int>::min)() << endl;
	cout << "unsigned: \t" << "��ռ�ֽ�����" << sizeof(unsigned);
	cout << "\t���ֵ��" << (numeric_limits<unsigned>::max)();
	cout << "\t��Сֵ��" << (numeric_limits<unsigned>::min)() << endl;
	cout << "long: \t\t" << "��ռ�ֽ�����" << sizeof(long);
	cout << "\t���ֵ��" << (numeric_limits<long>::max)();
	cout << "\t��Сֵ��" << (numeric_limits<long>::min)() << endl;
	cout << "unsigned long: \t" << "��ռ�ֽ�����" << sizeof(unsigned long);
	cout << "\t���ֵ��" << (numeric_limits<unsigned long>::max)();
	cout << "\t��Сֵ��" << (numeric_limits<unsigned long>::min)() << endl;

	cout << "long long: \t" << "��ռ�ֽ�����" << sizeof(long long);
	cout << "\t���ֵ��" << (numeric_limits<long long>::max)();
	cout << "\t��Сֵ��" << (numeric_limits<long long>::min)() << endl;
	cout << "unsigned long long: " << "��ռ�ֽ�����" << sizeof(unsigned long long);
	cout << "\t���ֵ��" << (numeric_limits<unsigned long long>::max)();
	cout << "\t��Сֵ��" << (numeric_limits<unsigned long long>::min)() << endl;

	cout << "double: \t" << "��ռ�ֽ�����" << sizeof(double);
	cout << "\t���ֵ��" << (numeric_limits<double>::max)();
	cout << "\t��Сֵ��" << (numeric_limits<double>::min)() << endl;
	cout << "long double: \t" << "��ռ�ֽ�����" << sizeof(long double);
	cout << "\t���ֵ��" << (numeric_limits<long double>::max)();
	cout << "\t��Сֵ��" << (numeric_limits<long double>::min)() << endl;
	cout << "float: \t\t" << "��ռ�ֽ�����" << sizeof(float);
	cout << "\t���ֵ��" << (numeric_limits<float>::max)();
	cout << "\t��Сֵ��" << (numeric_limits<float>::min)() << endl;
	cout << "size_t: \t" << "��ռ�ֽ�����" << sizeof(size_t);
	cout << "\t���ֵ��" << (numeric_limits<size_t>::max)();
	cout << "\t��Сֵ��" << (numeric_limits<size_t>::min)() << endl;
	cout << "string: \t" << "��ռ�ֽ�����" << sizeof(string) << endl;
	// << "\t���ֵ��" << (numeric_limits<string>::max)() << "\t��Сֵ��" << (numeric_limits<string>::min)() << endl;
	cout << "type: \t\t" << "************size**************" << endl;
}
