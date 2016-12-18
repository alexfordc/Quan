#include "StdAfx.h"
#include "macdstrategy.h"
#include "Configuration.h"

MACDStrategy::MACDStrategy(const DataHandler& datahandler) 
: Strategy(datahandler), macd_(0), last_macd_(INVALID_VALUE), buyPrice(INVALID_VALUE), lowPrice_(INVALID_VALUE)
{
}

MACDStrategy::~MACDStrategy(void)
{
	if (macd_)
	{
		delete macd_;
	}
}

void MACDStrategy::Initialize()
{
	macd_ = new MACD(12, 26, 9);
	name_ = "MACD";
}

Strategy::ACTION MACDStrategy::Trigger(const Quot& quot)
{
	// ����ָ��
	macd_->Calculate(quot);

	vector<MACDExtremePoint>& posExtPts = macd_->GetPosExtremePoints();

	vector<MACDExtremePoint>& negExtPts = macd_->GetNegExtremePoints();

	vector<MACDExtremePoint>& extPts = macd_->GetExtremePoints();

	if (macd_->GetCount() <= 1 || posExtPts.size() < 2 || negExtPts.size() < 2)
	{
		return Strategy::NONE;
	}

	MACDItem& last_one = macd_->getLastOne();

	MACDItem& latest_one = macd_->getLatestOne();

	//
	ACTION action = Strategy::NONE;

	// ��㣺
	// ǰ�����������������һ�ν��
	// �½�����
	// ֮ǰ�лس�macd����Ĺ��� 

	// ����
	// ǰ�������ν���һ������
	// ��������
	// �лس�����Ĺ���


	// 1. ��һ��difС�����µ�dif
	// 2. ��һ��difС����һ��dea

	if (last_one.dif < latest_one.dif && last_one.dif < last_one.dea 
		&& latest_one.dif > latest_one.dea && last_one.dif < 0)   
	{
		if (negExtPts[negExtPts.size()-1].macd > negExtPts[negExtPts.size()-2].macd && negExtPts[negExtPts.size()-1].close < negExtPts[negExtPts.size()-2].close
			/*&& negExtPts[negExtPts.size()-1].macd > -2*/)
		{
			action = BUY;
			buyPrice = quot.Close;
			lowPrice_ = quot.Low;
		}
	}
	else if (last_one.dif > latest_one.dif && last_one.dif > last_one.dea 
		&& latest_one.dif < latest_one.dea && last_one.dif > 0)
	{
		if (posExtPts[posExtPts.size()-1].macd < posExtPts[posExtPts.size()-2].macd && posExtPts[posExtPts.size()-1].close > posExtPts[posExtPts.size()-2].close)
		{
			action = SELL;
		}
	}
	/*
	else if (buyPrice != INVALID_VALUE)
	{
		// �ﵽֹӯ����ֹ���
		if ((quot.Close-buyPrice)*100/buyPrice >= Configuration::getInstance().getStopLoss() || lowPrice_ > quot.Low)
		{
			buyPrice = INVALID_VALUE;
			lowPrice_ = INVALID_VALUE;
			action = SELL;
		}
	}
	*/
	else
	{

	}

	return action;
}

void MACDStrategy::ReInitialize(const DataHandler& datahandler)
{
	if (macd_)
	{
		delete macd_;
	}

	macd_ = new MACD(12, 26, 9);
}