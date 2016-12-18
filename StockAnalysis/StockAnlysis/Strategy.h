#pragma once

#include "Utilities.h"
#include "StockDataStructures.h"

//
const double AMOUNT = 100000;

// ROI��Ϣ
struct ROIInfo
{
	int period; // ����
	float roi;  // ������
};

// ������Ϣ
struct TradeInfo
{
	int period; // ����
	float roi;  // ������
	string buy_date; // ��������
	string sell_date;// ��������

	double buy_price; // ����۸�
	double sell_price; // �����۸�
};

// ���Լ�����
struct StrategyResult
{
	// ��Ʊ����
	string code_;

	// ��������
	float roi_;

	// �������б�
	vector<ROIInfo> rois_;

	// ������б�
	vector<string> buyPoints_;

	// �������б�
	vector<string> sellPoints_;

	// ������Ϣ
	vector<TradeInfo> tradeInfos;

	// ����������
	vector<ROIInfo>& rois()
	{
		return rois_;
	}

	StrategyResult(): roi_(0.0)
	{

	}

	//
	vector<TradeInfo>& GetTradeInfos()
	{
		return tradeInfos;
	}
	
	//
	string GetAllBuy() const
	{
		string str;

		foreach(buyPoints_, it, vector<string>)
		{
			str += *it;

			str += ",";
		}

		if (!str.empty())
		{
			str = str.substr(0, str.length() - 1);
		}

		return str;
	}

	//
	string GetAllSell() const
	{
		string str;

		foreach(sellPoints_, it, vector<string>)
		{
			str += *it;

			str += ",";
		}

		if (!str.empty())
		{
			str = str.substr(0, str.length() - 1);
		}

		return str;
	}

	//
	string GetAllTrades() const
	{
		string str;

		foreach(tradeInfos, it, vector<TradeInfo>)
		{
			stringstream ss;

			ss<<it->buy_date<<":"<<CommonUtil::FormatDouble(it->buy_price)<<":"<<it->sell_date<<":"<<CommonUtil::FormatDouble(it->sell_price)<<":"<<it->period<<":"<<CommonUtil::FormatDouble(it->roi);

			str += ss.str();

			str += ",";

			ss.clear();
		}

		if (!str.empty())
		{
			str = str.substr(0, str.length() - 1);
		}

		return str;
	}

	// ������� 
	float GetMaxGain() const
	{
		float roi = 0;

		if (!rois_.empty())
		{
			roi = rois_[0].roi;

			foreach(rois_, it, vector<ROIInfo>)
			{
				roi = max(roi, it->roi);
			}
		}

		return roi;

	}

	// ���س�
	float GetMaxLoss() const
	{
		float roi = 0;

		if (!rois_.empty())
		{
			roi = rois_[0].roi;

			foreach(rois_, it, vector<ROIInfo>)
			{
				roi = min(roi, it->roi);
			}
		}

		return roi;
	}

	// ���������
	int GetNumOfPosGain() const
	{
		int ret = 0;

		foreach(rois_, it, vector<ROIInfo>)
		{
			if (it->roi > 0)
			{
				ret++;
			}
		}

		return ret;
	}

	// �����������ƽ������
	int GetPeriod() const
	{
		int period = 0;
		int count = 0;

		if (!rois_.empty())
		{
			foreach(rois_, it, vector<ROIInfo>)
			{
				if (it->roi > 0)
				{
					period += it->period;
					count++;
				}
			}
		}

		if (count > 0)
		{
			return period/count;
		}
		else
		{
			return 0;
		}
	}

	// �õ����һ�����������
	string GetLastBuyDate() const
	{
		if (buyPoints_.size() > 0)
		{
			return buyPoints_[buyPoints_.size()-1];
		}
		else
		{
			return "";
		}
	}

	// �����������ƽ��ֵ 
	double GetAveragePosROI() const
	{
		double roi = 0;
		int count = 0;

		if (!rois_.empty())
		{
			foreach(rois_, it, vector<ROIInfo>)
			{
				if (it->roi > 0)
				{
					roi += it->roi;
					count++;
				}
			}
		}

		if (count > 0)
		{
			return roi/count;
		}
		else
		{
			return 0;
		}
	}

	// �������
	size_t GetNumOfBuy() const
	{
		return buyPoints_.size();
	}

	// ��������
	size_t GetNumOfSell() const
	{
		return sellPoints_.size();
	}

	// �õ����״���
	size_t GetNumOfTrade() const
	{
		return buyPoints_.size();
	}

	// �õ���������
	double GetRateOfPosGain() const
	{
		if (!buyPoints_.empty())
		{
			return (double)GetNumOfPosGain()*100/GetNumOfBuy();
		}
		else
		{
			return 0.0;
		}
	}

	//
	float GetROI() const
	{
		return roi_;
	}

	bool CanBuy() const
	{
		if (!buyPoints_.empty())
		{
			Date d = Date::Today();
			Date dateLastBuy;
			dateLastBuy.fromStringYYYYMMDD(buyPoints_[buyPoints_.size()-1].c_str());

			return (d == dateLastBuy)?true:false;
		}
		else
		{
			return false;
		}
	}

	bool CanSell() const
	{
		if (!buyPoints_.empty())
		{
			Date d = Date::Today();
			Date dateLastBuy;
			dateLastBuy.fromStringYYYYMMDD(buyPoints_[buyPoints_.size()-1].c_str());

			return (d == dateLastBuy)?true:false;
		}
		else
		{
			return false;
		}
	}

	bool CanHold() const
	{
		return buyPoints_.size()>sellPoints_.size()?true:false;
	}

	int GetCurrentStatus() const
	{
		int ret = -1;

		if (CanBuy())
		{
			ret = 0; //"����"; 
		}
		else if (CanSell())
		{
			ret = 1; //"����";
		}
		else if (CanHold())
		{
			ret = 2; //"����";
		}
		else
		{
			ret = 3; //"�ղ�";
		}

		return ret;
	}


};

//
class StrategyEventListener
{
public:
	virtual void DoOnBuy(const Quot& quot) = 0;

	virtual void DoOnSell(const Quot& quot) = 0;
};

//
class Strategy 
{
public:
	Strategy(const DataHandler& datahandler);
	virtual ~Strategy(void);

public:
	static Strategy* Create(const char* strategyname, const DataHandler& datahandler);


	// �������Ͷ���
	enum ACTION
	{
		BUY,
		SELL,
		NONE
	};

	enum STATE
	{
		S_BUY,
		S_SELL,
		S_NONE
	};

	virtual void Initialize() = 0;
	
	virtual ACTION Trigger(const Quot& quot) = 0;

	virtual void ReInitialize(const DataHandler& datahandler) = 0;

    virtual void set_event_listener(StrategyEventListener* value)
	{
		event_listener_ = value;
	}

	// ����ֹ���
	int stop_loss_point() { return stop_loss_point_; }

	void setstop_loss_point(const int value) { stop_loss_point_ = value; }

	// ��������
	string name() const { return name_; }

protected:
	void DoOnBuy(const Quot& quot);

	void DoOnSell(const Quot& quot);

	StrategyEventListener* event_listener_;

	int stop_loss_point_; // ֹ���, �ٷֱ�

	string name_;

	int latestClose_; // ���µ����̼�

private:
};
