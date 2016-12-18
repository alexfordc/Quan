#pragma once

#include "strategy.h"
#include "MALine.h"
#include "macd.h"

class CrossMAStrategy :
	public Strategy
{
public:
	CrossMAStrategy(const DataHandler& datahandler);
	virtual ~CrossMAStrategy(void);

public:
	virtual void Initialize();

	virtual ACTION Trigger(const Quot& quot);

	virtual void ReInitialize(const DataHandler& datahandler);

	void setVolumeIncrease(const int value) { volIncrease_ = value; }

	MALine* GetMAShortTerm() { return maShortTerm; }

	MALine* GetMALongTerm() { return maLongTerm; }

	// true: ��ʾ��������
	bool isUpTrend();

private: 
	MALine* maShortTerm;// ���ھ��� 

	MALine* maLongTerm; // ���ھ���

	MALine* maSafeTerm; // �������� 

	int lastVolume_;   // ��һ���ɽ���

	int volIncrease_;   // �ɽ���������

	int lastHigh_;  // ǰһ����ߵ�

	deque<int> trendArray_;// ��ͼ۶���, ���ڼ�������

	int trendArraySize_; //���ƶ��еĴ�С

	int shortterm_; // ���ھ��� 

	int longterm_;  // ���ھ���

	int safeterm_; // ��������

	MACDItem lastMACD_;

	MACDItem latestMACD_;

	int macdstatus_;

	MACD* macd_;
};
