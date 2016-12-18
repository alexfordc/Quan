#pragma once
/********************************************************************
	created:	2015/06/04
	created:	4:6:2015   17:43
	filename: 	e:\Quan\StockAnlysis\StockAnlysis\TurnPoint.h
	file path:	e:\Quan\StockAnlysis\StockAnlysis
	file base:	TurnPoint
	file ext:	h
	author:		Jerry Li
	
	purpose:	����ת�۵����
*********************************************************************/

#include "algorithm.h"

//
struct TurnPointItem
{
	int direction; // ����0������ 1���µ� 2: δ֪
	int close; // �۸�
};


//
class TurnPoint :
	public Algorithm
{
public:
	TurnPoint(void);
public:
	~TurnPoint(void);

	// �������Ͷ���
	enum TREND{ UP = 0, DOWN, UNKNOWN};

	virtual void Calculate(const Quot& quot);

	// �õ���ǰ������
	TREND getCurrentTrend()  { return trend_; }

	// ���ü۸�䶯������ֵ�����ڹ���΢С�ļ۸�仯
	void setOffset(const int value) { offset_ = value; }

	// �õ���ǰ�ļ۸�
	int close() { return close_; }

	//
	TurnPointItem GetTurnPoint(const char* date);

	//
	void AddTurnPoint(const char* date, const TurnPointItem& item);

private:
	TREND trend_;

	int offset_;

	int close_;

	string lastdate_;

	map<string, TurnPointItem> turnpoints_;
};
