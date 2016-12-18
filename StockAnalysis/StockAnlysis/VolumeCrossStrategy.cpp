#include "StdAfx.h"
#include "VolumeCrossStrategy.h"
#include "Configuration.h"

VolumeCrossStrategy::VolumeCrossStrategy(const DataHandler& datahandler)
: Strategy(datahandler)
{
	shortterm_ = datahandler.GetItem<int>("shortterm", g_Configuration.getMeanCycle());
	longterm_ = datahandler.GetItem<int>("longterm", g_Configuration.getAdjustCycle());
}

VolumeCrossStrategy::~VolumeCrossStrategy(void)
{
	if (ma_shortterm_)
	{
		delete ma_shortterm_;
	}

	if (ma_longterm_)
	{
		delete ma_longterm_;
	}
}

void VolumeCrossStrategy::Initialize()
{
	ma_shortterm_ = new MA(shortterm_);
	ma_longterm_ = new MA(longterm_);
	name_ = "VolumeCross";
}

Strategy::ACTION VolumeCrossStrategy::Trigger(const Quot& quot)
{
	ma_shortterm_->Calculate(quot.Volume);

	ma_longterm_->Calculate(quot.Volume);

	// �õ����µľ��߼۸�
	double short_latest = ma_shortterm_->GetLatestValue();

	//
	double long_latest = ma_longterm_->GetLatestValue();

	// �޾���ֵʱ�˳�
	if (short_latest == INVALID_VALUE || long_latest == INVALID_VALUE)
	{
		latestClose_ = quot.Close;

		return NONE;
	}


	Strategy::ACTION action = NONE;

	// ������������������볤�ھ��߽��棬������
	if (ma_shortterm_->GetLatestValue() > ma_shortterm_->GetLastValue()   // ��ǰ���ڼ۸����ǰ�۸�
		&& ma_shortterm_->GetLatestValue() > ma_longterm_->GetLatestValue() // ��ǰ���ڼ۸���ڵ�ǰ���ڼ۸�
		&& ma_shortterm_->GetLastValue() < ma_longterm_->GetLatestValue())// ǰ���ڼ۸����ǰ���ڼ۸�
	{
		action = BUY;

		//LOG("����, ����: %s, �۸�: %d, ��ǰ���: %.2f, ��λ: %.2f", quot.Date, quot.Close, amount_, position_);
	}
	else if (ma_longterm_->GetLatestValue() <= ma_longterm_->GetLastValue() // ��ǰ���ڼ۸����ǰ�۸�
		&& ma_shortterm_->GetLatestValue() < ma_longterm_->GetLatestValue()  // ��ǰ���ڼ۸���ڵ�ǰ���ڼ۸�
		&& ma_shortterm_->GetLastValue() > ma_longterm_->GetLastValue()) // ��ǰ���ڼ۸����ǰ���ڼ۸�
	{
		action = SELL;

		//LOG("����, ����: %s, �۸�: %d, ��ǰ���: %.2f, ��λ: %.2f", quot.Date, quot.Close, amount_, position_);
	}

	return action;
}