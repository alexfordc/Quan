#pragma once

#include "Strategy.h"
#include "financealgo.h"

using namespace finance_algo;

class VolumeCrossStrategy : public Strategy
{
public:
	VolumeCrossStrategy(const DataHandler& datahandler);
	~VolumeCrossStrategy(void);

public:
	virtual void Initialize();

	virtual void ReInitialize(const DataHandler& datahandler) {}

	virtual ACTION Trigger(const Quot& quot);

private: 
	int lastHigh_; // ��һ����߼�

	int shortterm_; // ���ھ��� 

	int longterm_;  // ���ھ���

	MA* ma_shortterm_;

	MA* ma_longterm_;
};
