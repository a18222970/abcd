#pragma once
class TCPfuWu
{



public:
	unsigned TCPfaSong(char* json);
	/*
	* 函数: zhuanJsonJ
	* 作用: 将字符转换为json格式字符串
	* 参数1: char数组的指针
	* 参数2: 告诉服务器操作类型
	* 参数3: 告诉服务器功能名字;也是登陆的账号
	* 参数4: 校验码,登陆的密码
	* 参数5: 指定接收的数组长度,默认600字节
	* 返回值: 成功返回TRUE;失败返回 FALSE
	*/
	BOOL zhuanJsonJ(char* shuzu, int leiXing, char* gongNeng, char* jiaoYan, int len=600);

	/*
	* 作用: 将json格式字符串,转为C格式字符串
	*/
	int zhuanJsonC(char* shuzu, char* gongNeng, char* jiaoYan, int len = 600);

	/*
	* 
	*/
	BOOL shuZuBiJiao(char* a, char* b, int c);



	/*重要: 使用此函数后需要用 delete[] 接受指针  来释放内存,不然会内存溢出
	*
	*作用: 将Unicode->ANSI,宽字节转多字节
	*/
	char* zhuanChar(CString sj);

	/*
	*
	*作用: 将Unicode->ANSI,宽字节转多字节
	* 参数1: Unicode字符串
	* 参数2: char数组;
	* 参数3: 要转换的长度
	*/
	BOOL zhuanChar(CString sj, char* shuzu, int len = 60);
};

UINT _cdecl TCPlianjie(LPVOID lpParam);//多线程
unsigned WINAPI TCPfaSong();
unsigned WINAPI TCPjieShou(void* arg);