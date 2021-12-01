#pragma once
class shiJian
{


public:
	CTime m_time;//时间类
	/*
	*
	* 作用: 获取时间
	*/
	void huoQuShiJian();

	/*获取当前时间日期  的时间戳;返回16xx,xxxx,xx*/
	unsigned  getDangQianShiJianCuo();

	int setShiJianCuo(char* str_time);






	BOOL getDangQianShiJianCuo(CString *a);//
	CString getDQshiJianCuo();//

	void leixingdaxiao();
};

