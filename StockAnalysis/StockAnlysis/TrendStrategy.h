#pragma once

#include "strategy.h"
#include "TrendMALine.h"
#include "maline.h"



//�����¼�����
class TrendEventListener : public StrategyEventListener
{
public:
	virtual void DoOnBuy(const Quot& quot);

	virtual void DoOnSell(const Quot& quot);
};

// ���Ʋ���
class TrendStrategy :
	public Strategy
{
public:
	TrendStrategy(const DataHandler& datahandler);
	virtual ~TrendStrategy(void);

public:
	// �������Ͷ���
	enum TREND
	{
		TR_UP,
		TR_DOWN,
		TR_UNKNOWN
	};

	virtual void Initialize();

	virtual void ReInitialize(const DataHandler& datahandler) {}

	virtual ACTION Trigger(const Quot& quot);

	TrendMALine* GetTrendMaLine();

	MALine* GetMALongTerm();

private:
	void buy();

	void sell();

	int crossAvgLine(Quot& quot);

	bool isNewHighVol(const Quot& quot);

	//
	double getDrift(string begin, string end);

	int gain_;

	int buyPrice_;

	int sellPrice_;

	int prev_volume_;

	TREND currTrend_;  // ��ǰ����

	string lastdate_;

	int first_high_;

	int first_low_;

	int latesthigh_;

	int latestlow_;

	Quot prevHigh_; // ǰһ���ߵ�

	Quot prevLow_;  // ǰһ���͵� 

	double driftRate_;

	int latestClose_; // �������̼�

	int last_close_; // 

	int last_high_;

	// ����΢С�����ľ���
	TrendMALine* maTrend;

	// �����߱���
	MALine* maLongTerm;

	//
	int trendterm_; // ����������

	int safeterm_;  // ��ȫ������

	int threshold_; // ������ֵ
};
