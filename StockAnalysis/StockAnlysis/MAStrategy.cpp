#include "StdAfx.h"
#include "MAStrategy.h"
#include "Utilities.h"
#include "Configuration.h"
#include "TrendMALine.h"


MAStrategy::MAStrategy(const DataHandler& datahandler)
: Strategy(datahandler), lastClose_(INVALID_VALUE), latestLow_(INVALID_VALUE),macd_(0),
lastHigh_(INVALID_VALUE)
{

}

MAStrategy::~MAStrategy(void)
{
	if (maLine_)
	{
		delete maLine_;
	}

	if (maLongTerm)
	{
		delete maLongTerm;
	}
}

void MAStrategy::Initialize()
{
	maLine_ = new TrendMALine(g_Configuration.getMeanCycle(), g_Configuration.getThreshold());
	maLongTerm = new MALine(g_Configuration.getAdjustCycle());

	macd_ = new MACD(12, 26, 9);

	name_ = "MA";
}

Strategy::ACTION MAStrategy::Trigger(const Quot& quot)
{
	//
	macd_->Calculate(quot);

	// �������
	maLine_->Calculate(quot);

	// ���㳤�ڱ�������
	maLongTerm->Calculate(quot);

	// ������߼�
	if (lastHigh_ != INVALID_VALUE)
	{
		lastHigh_ = max(lastHigh_, quot.High);
	}

	//
	float change = 0;
	if (lastHigh_ != 0 && lastHigh_ != INVALID_VALUE)
	{
		change = (lastHigh_ - quot.Close)*100/lastHigh_;
	}

	// �õ����µľ��߼۸�
	int maClose =  maLine_->GetLatestClose();

	// �޾��߼۸�ʱ�˳�
	if (maClose == INVALID_VALUE)
	{
		lastClose_ = quot.Close;

		return NONE;
	}

	ACTION action = NONE;

	int nStopLossRate = g_Configuration.getStopLoss();

	// �����ǰ���̼�С�ڻ��ߵ��ھ��߼۸���׼���׳�
	if ((((quot.High > maClose && quot.Close <= maClose)
		|| (maLine_->GetLastClose() <= lastClose_ && quot.Close < maLine_->GetLatestClose()))
		&& quot.Close < quot.Open)
		/*|| change >= nStopLossRate*/)
	{
		lastHigh_ = INVALID_VALUE;

		action =   SELL;
	}
	else 
	{
		// �����ǰû�в�λ�����룬Ҫ����߼۸��ڳ��ڱ�������֮��
		if (((quot.Close > maClose && quot.Low <= maClose) // ���̼۸��ھ��߼۸�
			|| (maLine_->GetLastClose() >= lastClose_ && quot.Close > maLine_->GetLatestClose()))
			&& quot.Close > quot.Open
			) 
		{
			lastHigh_ = quot.High;

			action = BUY;
		}
	}

	lastClose_ = quot.Close;

	return action;
}

void MAStrategy::ReInitialize(const DataHandler& datahandler)
{
	if (maLine_)
	{
		delete maLine_;
	}

	if (maLongTerm)
	{
		delete maLongTerm;
	}

	int shortterm_ = datahandler.GetItem<int>("shortterm", g_Configuration.getMeanCycle());
	int longterm_ = datahandler.GetItem<int>("longterm", g_Configuration.getAdjustCycle());
	int stop_loss_point_ = datahandler.GetItem<int>("stoplossrate", g_Configuration.getStopLoss());

	maLine_ = new TrendMALine(shortterm_, g_Configuration.getThreshold());
	maLongTerm = new MALine(longterm_);

	values.clear();
}