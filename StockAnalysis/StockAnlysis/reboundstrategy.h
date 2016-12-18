#pragma once

#include "Strategy.h"
#include "maline.h"
#include "macd.h"

class ReboundStrategy : public Strategy
{
public:
	ReboundStrategy(const DataHandler& datahandler);
	~ReboundStrategy(void);

public:
	virtual void Initialize();

	virtual ACTION Trigger(const Quot& quot);

	virtual void ReInitialize(const DataHandler& datahandler);

	MALine* GetMALine() { return maLine_; }

	MALine* GetMALongTerm() { return maLongTerm; }

private:
	MALine* maLine_;

	MALine* maLongTerm; // ���ڱ�������

	int lastClose_; // ���µ����̼�

	int latestLow_; // �������ͼ�

	deque<int> values;

	MACD* macd_;

	int lastHigh_;};
