#include "StdAfx.h"
#include "TrendMACrossStrategy.h"
#include "Configuration.h"

TrendMACrossStrategy::TrendMACrossStrategy(const DataHandler& datahandler)
: Strategy(datahandler), macd_(0)
{
	shortterm_ = datahandler.GetItem<int>("shortterm", g_Configuration.getMeanCycle());
	longterm_ = datahandler.GetItem<int>("longterm", g_Configuration.getAdjustCycle());
	threshold_ = datahandler.GetItem<int>("threshold", g_Configuration.getThreshold());
}

TrendMACrossStrategy::~TrendMACrossStrategy(void)
{
	if (maShortTerm)
	{
		delete maShortTerm;
	}

	if (maLongTerm)
	{
		delete maLongTerm;
	}

	if (macd_)
	{
		delete macd_;
	}
}

void TrendMACrossStrategy::Initialize()
{
	maShortTerm = new MALine(shortterm_);
	maLongTerm = new TrendMALine(longterm_, threshold_);
	macd_ = new MACD(12, 26, 9);
	name_ = "TrendCrossMA";
}

Strategy::ACTION TrendMACrossStrategy::Trigger(const Quot& quot)
{
	//
	macd_->Calculate(quot);

	// ������ھ��� 
	maShortTerm->Calculate(quot);

	// ���㳤�ھ���
	maLongTerm->Calculate(quot);

	// �õ����µĶ��ھ��߼۸�
	int closeShortTerm =  maShortTerm->GetLatestClose();

	// �õ����µĳ��ھ��߼۸�
	int closeLongTerm = maLongTerm->GetLatestClose();

	// �޾��߼۸�ʱ�˳�
	if (closeShortTerm == INVALID_VALUE || closeLongTerm == INVALID_VALUE)
	{
		latestClose_ = quot.Close;

		return NONE;
	}

	// ������߼�
	if (lastHigh_ != INVALID_VALUE)
	{
		lastHigh_ = max(lastHigh_, quot.High);
	}

	//
	int change = 0;

	if (lastHigh_ != 0 && lastHigh_ != INVALID_VALUE)
	{
		change = (lastHigh_ - quot.Close)*100/lastHigh_;
	}

	vector<MACDExtremePoint>& posExtPts = macd_->GetPosExtremePoints();

	vector<MACDExtremePoint>& negExtPts = macd_->GetNegExtremePoints();

	if (macd_->GetCount() <= 1 || posExtPts.size() < 2 || negExtPts.size() < 2)
	{
		return Strategy::NONE;
	}

	ACTION action = NONE;

	// ������������������볤�ھ��߽��棬������
	if (maShortTerm->GetLatestClose() > maShortTerm->GetLastClose()   // ��ǰ���ڼ۸����ǰ�۸�
		&& maShortTerm->GetLatestClose() > maLongTerm->GetLatestClose() // ��ǰ���ڼ۸���ڵ�ǰ���ڼ۸�
		&& maShortTerm->GetLastClose() <= maLongTerm->GetLastClose())// ǰ���ڼ۸����ǰ���ڼ۸�
	{
		if (negExtPts[negExtPts.size()-1].macd > negExtPts[negExtPts.size()-2].macd && negExtPts[negExtPts.size()-1].close < negExtPts[negExtPts.size()-2].close)
		{
			action = BUY;
		}
	}
	else if ((/*maLongTerm->GetLatestClose() <= maLongTerm->GetLastClose() // ��ǰ���ڼ۸����ǰ�۸�
		&&*/ maShortTerm->GetLatestClose() < maLongTerm->GetLatestClose()  // ��ǰ���ڼ۸���ڵ�ǰ���ڼ۸�
		&& maShortTerm->GetLastClose() > maLongTerm->GetLastClose()
		&& maShortTerm->GetLatestClose() < maShortTerm->GetLastClose())
		/*|| change >= stop_loss_point_*/) // ��ǰ���ڼ۸����ǰ���ڼ۸�
	{
		if (posExtPts[posExtPts.size()-1].macd < posExtPts[posExtPts.size()-2].macd && posExtPts[posExtPts.size()-1].close > posExtPts[posExtPts.size()-2].close)
		{
			action = SELL;
		}
	}

	latestClose_ = quot.Close;

	return action;
}

void TrendMACrossStrategy::ReInitialize(const DataHandler& datahandler)
{
	if (maShortTerm)
	{
		delete maShortTerm;
	}

	if (maLongTerm)
	{
		delete maLongTerm;
	}

	if (macd_)
	{
		delete macd_;
	}

	shortterm_ = datahandler.GetItem<int>("shortterm", g_Configuration.getMeanCycle());
	longterm_ = datahandler.GetItem<int>("longterm", g_Configuration.getAdjustCycle());
	threshold_ = datahandler.GetItem<int>("threshold", g_Configuration.getThreshold());

	maShortTerm = new MALine(shortterm_);
	maLongTerm = new TrendMALine(longterm_, threshold_);

	macd_ = new MACD(12, 26, 9);
}

