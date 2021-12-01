#include "pch.h"
#include "shiJian.h"

//#include <time.h>
/*
	struct tm
	{
		int tm_sec;   // 分-[0,60]之后的秒数，包括闰秒
		int tm_min;   // 小时后的几分钟- [0,59]
		int tm_hour;  // 自午夜起数小时- [0,23]
		int tm_mday;  // 月日- [1,31]
		int tm_mon;   // 一月以来的月份- [0,11]
		int tm_year;  // 自1900年以来
		int tm_wday;  // 自星期日以来的天数- [0,6]
		int tm_yday;  // 1月1日以来的天数- [0,365]
		int tm_isdst; // 夏令时标志
		//1天86400秒
		//验证时间到期 可以单独对比年,月,日
	};
	*/
void shiJian::huoQuShiJian()
{
	m_time = CTime::GetCurrentTime();    //获取当前时间日期  的时间戳
	CString a;
	a = m_time.Format(L"%Y-%m-%d / %H:%M:%S  %A");
	AfxMessageBox(a);
	a.Format(L"%u", m_time.GetTime());// GetTime() 将返回当前 CTime 对象与1970年1月1日之间的秒数
	AfxMessageBox(a);//生成当前时间的时间戳
}

unsigned  shiJian::getDangQianShiJianCuo()
{
	m_time = CTime::GetCurrentTime();    //获取当前时间日期  的时间戳
	unsigned long sjc = m_time.GetTime();
	return sjc;
}

int shiJian::setShiJianCuo(char* str_time)
{//时间格式:  2021:12:31 00:00:00 //1640880000
	struct tm stm;
	int iY, iM, iD, iH, iMin, iS;
	//2021:12:31 00:00:00
	memset(&stm, 0, sizeof(stm));//清零
	iY = atoi(str_time);//字符串转整数
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

	/*printf("%d-%0d-%0d %0d:%0d:%0d\n", iY, iM, iD, iH, iMin, iS);*/   //标准时间格式例如：2016:08:02 12:12:30
	return (int)mktime(&stm);//将本地时间转换为时间戳
}

BOOL shiJian::getDangQianShiJianCuo(CString* a)
{
	m_time = CTime::GetCurrentTime();    //获取当前时间日期  的时间戳
	//CString a;
	*a = m_time.Format(L"%Y-%m-%d / %H:%M:%S  %A     BOOL");
	AfxMessageBox(*a);
	(*a).Format(L"%u", m_time.GetTime());// GetTime() 将返回当前 CTime 对象与1970年1月1日之间的秒数
	AfxMessageBox(*a);//生成当前时间的时间戳
	return 0;
}

CString shiJian::getDQshiJianCuo()
{
	m_time = CTime::GetCurrentTime();    //获取当前时间日期  的时间戳
	CString a;
	a = m_time.Format(L"%Y-%m-%d / %H:%M:%S  %A     cs");
	AfxMessageBox(a);
	a.Format(L"%u", m_time.GetTime());// GetTime() 将返回当前 CTime 对象与1970年1月1日之间的秒数
	AfxMessageBox(a);//生成当前时间的时间戳
	return a;
}

void shiJian::leixingdaxiao()
{
	using namespace std;
	cout << "type: \t\t" << "************size**************" << endl;
	cout << "bool: \t\t" << "所占字节数：" << sizeof(bool);
	cout << "\t最大值：" << (numeric_limits<bool>::max)();
	cout << "\t\t最小值：" << (numeric_limits<bool>::min)() << endl;
	cout << "char: \t\t" << "所占字节数：" << sizeof(char);
	cout << "\t最大值：" << (numeric_limits<char>::max)();
	cout << "\t\t最小值：" << (numeric_limits<char>::min)() << endl;
	cout << "signed char: \t" << "所占字节数：" << sizeof(signed char);
	cout << "\t最大值：" << (numeric_limits<signed char>::max)();
	cout << "\t\t最小值：" << (numeric_limits<signed char>::min)() << endl;
	cout << "unsigned char: \t" << "所占字节数：" << sizeof(unsigned char);
	cout << "\t最大值：" << (numeric_limits<unsigned char>::max)();
	cout << "\t\t最小值：" << (numeric_limits<unsigned char>::min)() << endl;
	cout << "wchar_t: \t" << "所占字节数：" << sizeof(wchar_t);
	cout << "\t最大值：" << (numeric_limits<wchar_t>::max)();
	cout << "\t\t最小值：" << (numeric_limits<wchar_t>::min)() << endl;
	cout << "short: \t\t" << "所占字节数：" << sizeof(short);
	cout << "\t最大值：" << (numeric_limits<short>::max)();
	cout << "\t\t最小值：" << (numeric_limits<short>::min)() << endl;
	cout << "int: \t\t" << "所占字节数：" << sizeof(int);
	cout << "\t最大值：" << (numeric_limits<int>::max)();
	cout << "\t最小值：" << (numeric_limits<int>::min)() << endl;
	cout << "unsigned: \t" << "所占字节数：" << sizeof(unsigned);
	cout << "\t最大值：" << (numeric_limits<unsigned>::max)();
	cout << "\t最小值：" << (numeric_limits<unsigned>::min)() << endl;
	cout << "long: \t\t" << "所占字节数：" << sizeof(long);
	cout << "\t最大值：" << (numeric_limits<long>::max)();
	cout << "\t最小值：" << (numeric_limits<long>::min)() << endl;
	cout << "unsigned long: \t" << "所占字节数：" << sizeof(unsigned long);
	cout << "\t最大值：" << (numeric_limits<unsigned long>::max)();
	cout << "\t最小值：" << (numeric_limits<unsigned long>::min)() << endl;

	cout << "long long: \t" << "所占字节数：" << sizeof(long long);
	cout << "\t最大值：" << (numeric_limits<long long>::max)();
	cout << "\t最小值：" << (numeric_limits<long long>::min)() << endl;
	cout << "unsigned long long: " << "所占字节数：" << sizeof(unsigned long long);
	cout << "\t最大值：" << (numeric_limits<unsigned long long>::max)();
	cout << "\t最小值：" << (numeric_limits<unsigned long long>::min)() << endl;

	cout << "double: \t" << "所占字节数：" << sizeof(double);
	cout << "\t最大值：" << (numeric_limits<double>::max)();
	cout << "\t最小值：" << (numeric_limits<double>::min)() << endl;
	cout << "long double: \t" << "所占字节数：" << sizeof(long double);
	cout << "\t最大值：" << (numeric_limits<long double>::max)();
	cout << "\t最小值：" << (numeric_limits<long double>::min)() << endl;
	cout << "float: \t\t" << "所占字节数：" << sizeof(float);
	cout << "\t最大值：" << (numeric_limits<float>::max)();
	cout << "\t最小值：" << (numeric_limits<float>::min)() << endl;
	cout << "size_t: \t" << "所占字节数：" << sizeof(size_t);
	cout << "\t最大值：" << (numeric_limits<size_t>::max)();
	cout << "\t最小值：" << (numeric_limits<size_t>::min)() << endl;
	cout << "string: \t" << "所占字节数：" << sizeof(string) << endl;
	// << "\t最大值：" << (numeric_limits<string>::max)() << "\t最小值：" << (numeric_limits<string>::min)() << endl;
	cout << "type: \t\t" << "************size**************" << endl;
}
