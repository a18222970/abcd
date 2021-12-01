#pragma once
#if _SUO_PING_GONGGONG_
#define _SUO_PING_GONGGONG_
#else



class SuoPingGongJu
{
private://完全私有的，有当前类中的成员能访问到。

protected://是受保护的，只有当前类的成员与继承该类的类才能访问

	//WORD wVersionRequested;
	//WSADATA wsaData;
	SOCKET sockSrv;
	int iLen;

	/*
	* 函数: wangLuoJianCe
	* 作用: 检测网络是否连通,这个只是检测网卡是否有连接
	* 返回值: FALSE 无发连接,TRUE 可以连接
	*/
	BOOL wangLuoJianCe();
public://多线程
	CWinThread* pThread;
	
public://公共
	SuoPingGongJu();
	/*
	* 函数: huoQuLuJing
	* 作用: 获取程序自身根文件夹
	* 参数: 用于保存取得的路径
	*/
	void huoQuLuJing(CString path);

	/*
	* 
	* 作用: 
	* 参数: 类
	*/
	void xianShiKongJian(CDialogEx a);


	/*
	* 函数: ziFuChuanChangDu
	* 作用: 计算Unicode类型(宽字符串,1个字符占2个字节)字符串的长度,包括结尾的00
	* 参数: 用CString类型定义的字符串, CString a =L"husdhdkd";
	*/
	int ziFuChuanChangDu(const wchar_t* a);

	/*
	* 作用: 连接服务器端
	*/
	BOOL lianJieFuWuQiDuan(const char* ip);

	/*
	* 作用: 断开与TCP服务器的连接
	*/
	void duanKaiFuWuDuan();

	/*
	* 作用: 给TCP服务器发送信息
	*/
	int faSong();

	/* ziFuZhuanHuan_K_A
	* 作用: Unicode下CString转换为char *
	* 参数: CString类型字符串
	* 返回值: 新开辟的动态内存指针地址
	* 注意: 使用此函数后需要用 delete[] 接受指针  来释放内存,不然会内存溢出
	*/
	char* ziFuZhuanHuan_K_A(CString k);

	/*
	* 函数:
	* 作用: 将字符串转换为json格式
	* 参数1: const char*类型字符串,这里为控制服务器的指令
	* 参数2: const char*类型字符串,这里为控制服务器的指令的校验码
	* 参数3: int类型,这里为控制服务器要动作的分类,比如验证登陆就是1,
	* 返回值: 转换后的json格式的字符串
	*/
	const char* json_shengCheng(const char* zhiLing, const char* jiaoYan, int leiXing);

	BOOL tcpfaShuJU(const char* a);








};

//extern BOOL duoXianChenQiTing;//多线程启停开关
UINT _cdecl ThreadFunc_aa(LPVOID lpParam);//多线程
UINT _cdecl TCPlianjie(LPVOID lpParam);//多线程
unsigned WINAPI TCPjieShou(void* arg);//多线程
unsigned WINAPI TCPfaSong(void* arg);//多线程
#endif