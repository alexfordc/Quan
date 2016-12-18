#pragma once

#include "Strategy.h"
#include "Utilities.h"
#include "StockDataStructures.h"

// ���Լ�����
class StrategyCalculator
{
public:
	StrategyCalculator(void);

	~StrategyCalculator(void);

public:
	void Calculate(const vector<Quot>& quots);	

	void ReCalculate(const vector<Quot>& quots, const DataHandler& datahandler);

	void Calculate(const Quot& quot);

	// ���Ӳ��� 
	void AddStrategy(const char* strategyname, const DataHandler& datahandler);

	// ɾ������
	void RemoveStrategy(const char* strategyname);

	// ��ղ���
	void Clear();

	vector<string>& buyPoints() { return result_.buyPoints_; }

	vector<string>& sellPoints() { return result_.sellPoints_; }

	// ���������
	virtual float GetROI();

	// ����������
	vector<ROIInfo>& rois();

	// ������� 
	float GetMaxGain();

	// ���س�
	float GetMaxLoss();

	// ���������
	int GetNumOfPosGain();

	// �������
	int GetNumOfBuy();

	// ��������
	int GetNumOfSell();

	// �õ����״���
	int GetNumOfTrade();

	// �õ���������
	float GetRateOfPosGain();

	// �Ƿ���ڸò���
	bool IsExisting(const char* name);
	
	//
	vector<Strategy*>& strategies() { return strategies_; }

	//
	StrategyResult& result() { return result_; }

private:
	//
	vector<Strategy*> strategies_;

	// ��ǰ��λ
	double position_;

	// ��ǰ���
	double amount_;

	//
	StrategyResult result_;
};

