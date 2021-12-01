#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#import "msado15.dll" no_namespace rename("EOF", "adoEOF")
//#import "C:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF","adoEOF")


class ACCSCC
{
protected:
	
	/*
	*
	*作用: 将Unicode->ANSI,宽字节转多字节
	* 参数1: Unicode字符串
	* 参数2: char数组;
	* 参数3: 要转换的长度
	*/
	BOOL zhuanChar(CString sj, char* shuzu, int len = 60);
public://表
	CString yongHuId[10];//数据库字段id表
	CString yongHuJl[11];//数据库字段JiLu表
	CString jinCheng2[24];
	CString fXjc[10];
	CString bMingDan[1];

	CString mingDanBiao;
	CString jinCheng1Biao;
	CString jinChengBiao;
	CString idBiao;
	CString jiLuBiao;
	CString jinCheng2Biao;
	CString fXjinCheng;
public:
	ACCSCC();
	~ACCSCC();
	//int ci;
	

	
public://数据库连接,关闭
	/*如果频繁访问数据库，并要返回很多记录集，那么应该使用全局_ConnectionPtr接口创建一个数据库连接*/
	_ConnectionPtr m_pConnection; //连接对象指针
	_RecordsetPtr  m_pRecordset;  //声明记录集指针
	_CommandPtr    m_CommandPtr;  //该接口返回一个记录集

	/*
	* 连接数据库
	*/
	BOOL lianJieKaiGuan;//数据库是否连接
	BOOL lianJieAccscc();
	BOOL lianJieAccscc(const char* luJing);

	/*
	* 作用: 关闭数据库连接
	* 注意: 由于初始化COM库调用的是AfxOleInit，这种方法初始化COM库的优点就在于资源的释放也是自动进行的，所以不必担心资源泄漏的问题。
	*/
	void guanBiShuJuKu();

public://增加
	/*增加插入数据*/
	BOOL zengJia(CString biao, CString ziDuan, CString shuJu);

	/*
	*/
	BOOL zegJia(CString biao);
public://修改
	/*修改数据*/
	BOOL xiuGai(CString biao, CString ziDuan, CString shuJu, CString xiuGaiZiDuan, CString zDshuJu);

	/*未验证*/
	BOOL xiuGai(CString biao, CString ziDuan, CString shuJu, CString xiuGaiShuJu);
public://删除
	/*删除*/
	BOOL shanChu(CString biao, CString ziDuan, CString shuJu);
	BOOL shanChu(CString biao);
public://查询

	/*
	* 
	* 作用: 查询指定数据是否在表内指定字段存在
	* 参数1: 表
	* 参数2: 查找的字段
	* 参数3: 查找的数据
	* 返回值:成功返回1,失败返回0,错误返回3,有数据但不是要查找的数据返回2;查询的是空值将返回4
	*/
	unsigned chaXun(CString biao, CString ziDuan, CString shuJu);
	int chaXun(CString biao, CString ziDuan, int shuJu);

	/*
	*
	* 作用: 查询指定数据是否在表内指定字段存在
	* 参数1: 表
	* 参数2: 查找的字段
	* 参数3: 查找的数据
	* 返回值:成功返回TRUE,失败返回FALSE
	*/
	BOOL chaXunBMD(CString biao, CString ziDuan, CString shuJu);

	/*
	*
	* 作用: 查询指定字段是否有空值数据存在,一般用在新表
	* 参数1: 表
	* 参数2: 字段
	* 返回值:出错或没有数据返回FALSE,不是空值返回TRUE
	*/
	BOOL chaXunBK(CString biao, CString ziDuan);

	/*
	*
	* 作用: 查询指定字段是否有空值数据存在,一般用在新表
	* 参数1: 表
	* 参数2: 字段
	* 返回值:出错或没有数据返回FALSE,是空值返回TRUE
	*/
	BOOL chaXunK(CString biao, CString ziDuan);

	/*
	*
	* 作用: 查询指定数据是否存为空,不为空有几条
	* 参数1: 表
	* 参数2: 字段
	* 返回值:成功返回查到的条数,失败返回0
	*/
	unsigned chaXun(CString biao, CString ziDuan);


	/*
	* 函数: getShuJu
	* 作用: 获取指定字段下的所有数据
	* 参数1: 表
	* 参数2: 字段
	* 参数3: 定位的字段
	* 参数4: 要获取数据的字段
	* 返回值: 一个2级指针,指向1个二维char数组,wu[][];其中wu[0][0]作用是记录分配了几个2级内存,从wu[1]开始才是返回的值;没有数据返回空指针
	* 重要: 此函数调用后需要释放内存
	* 格式如下;  char** wu;
	        for (int i=0;i<a;i++)//a=wu[0][0]的值;
			{
				delete[] wu[i];
			}
			delete[] wu;
	*/
	char** getShuJu(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan);

	/*
	* 函数: getShuJu
	* 作用: 获取a字段下的a值那行对应的b字段的值
	* 参数1: 表
	* 参数2: 定位a字段
	* 参数3: 定位的a值
	* 参数4: 要获取数据的字段
	* 参数5: 接收返回值的wchar_t数组
	* 返回值: BOOL类型,成功返回TRUE
	* 注意:如果结果有多个,返回其中的一个
	*/
	BOOL   getShuJu(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan, wchar_t* shuzu);///*未解决多条数据的保存*/
	/*未解决多条数据的保存*/
	BOOL   getShuJu(CString biao, CString muBiaoziDuan, wchar_t* shuzu);

	/*
	* 函数: getShuJu
	* 作用: 获取a字段下的a值那行对应的b字段的值
	* 参数1: 表
	* 参数2: 定位a字段
	* 参数3: 定位的a值
	* 参数4: 要获取数据的b字段
	* 返回值: 返回获取到的int值
	*/
	unsigned int getShuJuRQ(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan);

	/*获取进程模块列表信息*/
	void bianLiMoKuai();
	/*获取进程模块详细信息并建立新线程比对,并杀死进程*/
	void bianLiJinCheng(DWORD dwPID);
	/*获取进程列表*/
	BOOL huoQuJinChengLieBiao(CString biao, BOOL s = FALSE);
	BOOL huoQuJinChengLieBiao_lieBiao(CString biao, LPVOID IPtr, BOOL s = FALSE);//出错
	wchar_t** huoQuJinChengLieBiao(int** a);

	void quChongAccScc(CString ba, CString bb, CString zda, CString zdb);

	/*多线程传参*/
	typedef struct jCjingCheng
	{
		DWORD Pid;
		CString exeMing;
		CString exePath;

		char    ming[266];
		char    path[MAX_PATH];//260
   }JC;
public://进程
	BOOL shaSiJinCheng(DWORD pid);
	BOOL qiDongJinCheng(CString exePath);


};

DWORD WINAPI jingChengChuLi(void* a);//查到新PID后的处理线程,这个线程为可能会同时运行的多线程
DWORD WINAPI sDjingCheng(LPVOID dwPID);
UINT sDjC(LPVOID pParam);