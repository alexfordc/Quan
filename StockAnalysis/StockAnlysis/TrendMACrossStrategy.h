#pragma once

#include "strategy.h"
#include "TrendMALine.h"
#include "maline.h"
#include "macd.h"

class TrendMACrossStrategy :
	public Strategy
{
public:
	TrendMACrossStrategy(const DataHandler& datahandler);
	virtual ~TrendMACrossStrategy(void);

public:
	virtual void Initialize();

	virtual ACTION Trigger(const Quot& quot);

	virtual void ReInitialize(const DataHandler& datahandler);

	MALine* GetMAShortTerm() { return maShortTerm; }

	TrendMALine* GetMALongTerm() { return maLongTerm; }

	// true: ��ʾ��������
	bool isUpTrend();

private: 
	MALine* maShortTerm;// ���ھ��� 

	TrendMALine* maLongTerm; // ���ھ���

	MALine* maSafeTerm; // �������� 

	int threshold_; // �����ߵĲ�������

	int lastHigh_; // ��һ����߼�

	int shortterm_; // ���ھ��� 

	int longterm_;  // ���ھ���

	MACD* macd_;
};
