#include "StdAfx.h"
#include "strategycalculator.h"
#include <set>

using namespace std;

StrategyCalculator::StrategyCalculator(void)
:position_(0.0), amount_(AMOUNT)
{
}

StrategyCalculator::~StrategyCalculator(void)
{
	Clear();
}

void StrategyCalculator::Calculate(const vector<Quot>& quots)
{
	if (strategies_.empty())
	{
		return;
	}

	//
	double position = 0.0; // ��λ
	double amount = AMOUNT; // ��ʼ�ʽ�
	float latestAmount = AMOUNT;

	// ���������
	result_.buyPoints_.clear();

	result_.sellPoints_.clear();

	result_.roi_ = 0;

	result_.rois_.clear();

	TradeInfo tradeinfo;
	tradeinfo.buy_date = "";

	// ��������
	foreach(quots, it, vector<Quot>)
	{
		set<string> buys;
		set<string> sells;

		foreach(strategies_, itStrategy, vector<Strategy*>)
		{
			Strategy::ACTION action = (*itStrategy)->Trigger(*it);

			switch (action)
			{
			case Strategy::SELL:
				sells.insert((*itStrategy)->name());
				break;
			case Strategy::BUY:
				buys.insert((*itStrategy)->name());
				break;
			case Strategy::NONE:
				break;
			default:
				break;
			}
		}

		// ���в��Է��������ź�
		if (buys.size() == strategies_.size())
		{
			if (position <= 0.0)
			{
				position = amount/it->Close;

				result_.buyPoints_.push_back(it->getDatetime());

				tradeinfo.buy_date = it->getDatetime();

				tradeinfo.buy_price = it->getClose();
			}
		}

		// ���в��Է��������ź�
		if (sells.size() == strategies_.size())
		{
			if (position > 0.0)
			{
				double curramount = position*it->Close;

				if (amount > 0)
				{
					Date dBuy, dSell;
					dBuy.fromStringYYYYMMDD(result_.buyPoints_[result_.buyPoints_.size()-1].c_str());
					dSell.fromStringYYYYMMDD(it->Datetime);

					ROIInfo info;
					info.period = dSell - dBuy;
					info.roi = (curramount - amount)*100/amount;

					result_.rois_.push_back(info);

					if (tradeinfo.buy_price != INVALID_VALUE)
					{
						tradeinfo.sell_date = it->getDatetime();
						tradeinfo.sell_price = it->getClose();
						tradeinfo.roi = info.roi;
						tradeinfo.period = info.period;

						result_.GetTradeInfos().push_back(tradeinfo);

						tradeinfo.buy_date = "";
					}
				}

				amount = curramount;

				position = 0.0;

				result_.sellPoints_.push_back(it->getDatetime());
			}
		}
	}

	// ���гֲ�
	if (position > 0.0)
	{
		result_.roi_ = (quots[quots.size()-1].Close*position-AMOUNT)*100/AMOUNT;
	}
	else
	{
		result_.roi_ = (float)(amount - AMOUNT)*100/AMOUNT;
	}

	//
	if (!tradeinfo.buy_date.empty())
	{
		Date dBuy, dSell;
		dBuy.fromStringYYYYMMDDHHNNSS(tradeinfo.buy_date.c_str());
		dSell.fromStringYYYYMMDDHHNNSS(quots[quots.size()-1].getDatetime().c_str());

		tradeinfo.sell_date = "����";
		tradeinfo.sell_price = quots[quots.size()-1].getClose();
		tradeinfo.roi = (tradeinfo.sell_price-tradeinfo.buy_price)*100/tradeinfo.buy_price;
		tradeinfo.period = dSell - dBuy;

		result_.GetTradeInfos().push_back(tradeinfo);
	}
}

void StrategyCalculator::Calculate(const Quot& quot)
{
}

// ����������
vector<ROIInfo>& StrategyCalculator::rois()
{
	return result_.rois();
}

// ������� 
float StrategyCalculator::GetMaxGain()
{
	return result_.GetMaxGain();

}

// ���س�
float StrategyCalculator::GetMaxLoss()
{
	return result_.GetMaxLoss();
}

// ���������
int StrategyCalculator::GetNumOfPosGain()
{
	return result_.GetNumOfPosGain();
}

// �������
int StrategyCalculator::GetNumOfBuy()
{
	return result_.buyPoints_.size();
}

// ��������
int StrategyCalculator::GetNumOfSell()
{
	return result_.sellPoints_.size();
}

// �õ����״���
int StrategyCalculator::GetNumOfTrade()
{
	return result_.buyPoints_.size();
}

// �õ���������
float StrategyCalculator::GetRateOfPosGain()
{
	if (!result_.buyPoints_.empty())
	{
		return (double)GetNumOfPosGain()*100/GetNumOfBuy();
	}
	else
	{
		return 0.0;
	}
}

float StrategyCalculator::GetROI()
{
	return result_.roi_;
}

void StrategyCalculator::AddStrategy(const char* strategyname, const DataHandler& datahandler)
{
	foreach(strategies_, it, vector<Strategy*>)
	{
		if ((*it)->name() == string(strategyname))
		{
			return;
		}
	}

	Strategy* strategy = Strategy::Create(strategyname, datahandler);

	strategies_.push_back(strategy);
}

void StrategyCalculator::RemoveStrategy(const char* strategyname)
{
	for(vector<Strategy*>::iterator it = strategies_.begin(); it != strategies_.end(); it++)
	{
		if ((*it)->name() == string(strategyname))
		{
			Strategy* p = *it;
			
			delete p;

			strategies_.erase(it);

			break;
		}
	}
}

void StrategyCalculator::Clear()
{
	foreach(strategies_, it, vector<Strategy*>)
	{
		Strategy* p = *it;

		delete p;
	}

	strategies_.clear();
}

void StrategyCalculator::ReCalculate(const vector<Quot>& quots, const DataHandler& datahandler)
{
	foreach(strategies_, it, vector<Strategy*>)
	{
		Strategy* p = *it;

		p->ReInitialize(datahandler);
	}

	Calculate(quots);
}

bool StrategyCalculator::IsExisting(const char* name)
{
	bool bret = false;

	foreach(strategies_, it, vector<Strategy*>)
	{
		if ((*it)->name() == string(name))
		{
			bret = true;
			break;
		}
	}

	return bret;
}

