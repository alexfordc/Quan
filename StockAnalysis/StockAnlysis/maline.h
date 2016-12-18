#pragma once
/********************************************************************
	created:	2015/05/14
	created:	14:5:2015   15:44
	filename: 	e:\Quan\StockAnlysis\StockAnlysis\MALine.h
	file path:	e:\Quan\StockAnlysis\StockAnlysis
	file base:	MALine
	file ext:	h
	author:		Jerry Li
	
	purpose:	�����ƶ�ƽ���ߵ��㷨
*********************************************************************/

#include "algorithm.h"

// �����ƶ�ƽ����
class MALine : public Algorithm
{
public:
	MALine(int nCycle);

	virtual ~MALine(void);

public:
	enum MATRENDTYPE
	{
		MA_UP,
		MA_DOWN,
		MA_UNKNOWN
	};

	virtual void Calculate(const Quot& quot);

	int cycle() const { return cycle_; }

	int GetLatestClose(); // ������һ������

	int GetLastClose(); // ���ǰһ������

	int GetCurrTrendType();

	bool isUp() { return (GetCurrTrendType()==MA_UP)?true:false; }

	vector<int>& getMAItems();

protected:
	int cycle_;
	int sumofclose_;
	int sumofvol_;

	MATRENDTYPE maTrendType_;

	vector<int> vtMAItem;

	deque<Quot> values;
};
