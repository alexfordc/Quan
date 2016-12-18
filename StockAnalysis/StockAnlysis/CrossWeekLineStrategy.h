#pragma once
#include "strategy.h"
#include "weekline.h"

class CrossWeekLineStrategy :
	public Strategy
{
public:
	CrossWeekLineStrategy(const DataHandler& datahandler);
	virtual ~CrossWeekLineStrategy(void);

public:
	virtual void Initialize();

	virtual ACTION Trigger(const Quot& quot);

private: 
	double amount_; // ���

	double position_; // ��ǰ��λ

	int latestClose_; // ���µ����̼�

	int lastVolume_;   // ��һ���ɽ���

	int lastHigh_;  // ǰһ����ߵ�

	vector<Quot> week_line_data_;

	WeekLine* weekline_;
};
