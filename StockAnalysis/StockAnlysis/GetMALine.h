#pragma once
/********************************************************************
	created:	2015/05/14
	created:	14:5:2015   15:44
	filename: 	e:\Quan\StockAnlysis\StockAnlysis\GetMALine.h
	file path:	e:\Quan\StockAnlysis\StockAnlysis
	file base:	GetMALine
	file ext:	h
	author:		Jerry Li
	
	purpose:	�����ƶ�ƽ���ߵ��㷨
*********************************************************************/

#include "algorithm.h"

// �����ƶ�ƽ����
class GetMALine :
	public Algorithm
{
public:
	GetMALine(int nCycle);
public:
	~GetMALine(void);

	void calculate(const Quot& quot);

	int getCycle() { return cycle_; }

	map<string, int> MAs;

private:
	int cycle_;
	int sumofclose_;
	int sumofvol_;

	deque<Quot> values;
};
