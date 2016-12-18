#pragma once

/********************************************************************
	created:	2015/05/23
	created:	23:5:2015   0:16
	filename: 	e:\Quan\StockAnlysis\StockAnlysis\QuotationReceiver.h
	file path:	e:\Quan\StockAnlysis\StockAnlysis
	file base:	QuotationReceiver
	file ext:	h
	author:		Jerry Li
	
	purpose:	��������࣬��������˽������鲢������Ӧ��Ʒ��
*********************************************************************/

#include <string>
#include <vector>
#include "StockDataStructures.h"
#include "FrameworkCls.h"
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace fmkcls;

//
class QuotationEventListener
{
public:
	virtual void DoOnRecv(const map<string, Quot>& quotations) = 0;
};


//
class QuotationReceiver
{
public:
	QuotationReceiver();

	~QuotationReceiver(void);
public:
	// ��ʼ����
	void start(QuotationEventListener* eventlistener, DataHandler& dataHandler);

	// �Ƿ�����
	bool IsRunning();

	// ��ֹ���е������߳�
	void stop();

private:
	void receiveProc();

	AccessLock s_lock_;

private:
	string OpenUrl(const char* url);

	string GetSubBtFind(const char* lpsz, string& strCode);

	int Token(const char* pSep, char* pStr, vector<string>& refvec);

	QuotationEventListener* eventlistener_;

	boost::thread_group thread_group_;

	bool terminated_;

	// ��Ҫ��ȡ�����Ʒ���б�
	ShareQueue<Instrument> instruments_;
};
