#pragma once
/********************************************************************
	created:	2015/05/14
	created:	14:5:2015   15:33
	filename: 	e:\Quan\StockAnlysis\StockAnlysis\BreakAllMAs.h
	file path:	e:\Quan\StockAnlysis\StockAnlysis
	file base:	BreakAllMAs
	file ext:	h
	author:		Jerry Li
	
	purpose:	�ҵ�ͻ�����о��ߵ���K�ߵ��㷨
*********************************************************************/

#include "Algorithm.h"
#include <vector>
#include <set>
#include "MALine.h"


using namespace std;

class BreakAllMAs :
	public Algorithm
{
public:
	BreakAllMAs(void);
public:
	~BreakAllMAs(void);

	void SetMA(set<int>& mas);

	void Calculate(const Quot& quot);

	vector<string> vtDate;

	vector<MALine*> vtMAs;
};
