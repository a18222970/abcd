#pragma once
class shiJian
{


public:
	CTime m_time;//ʱ����
	/*
	*
	* ����: ��ȡʱ��
	*/
	void huoQuShiJian();

	/*��ȡ��ǰʱ������  ��ʱ���;����16xx,xxxx,xx*/
	unsigned  getDangQianShiJianCuo();

	int setShiJianCuo(char* str_time);






	BOOL getDangQianShiJianCuo(CString *a);//
	CString getDQshiJianCuo();//

	void leixingdaxiao();
};

