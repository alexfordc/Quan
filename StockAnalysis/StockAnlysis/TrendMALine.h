#pragma once

#include "algorithm.h"
#include "TurnPoint.h"
#include "maline.h"


class TrendMALine :
	public MALine
{
public:
	TrendMALine(int cycle, int delta);
public:
	~TrendMALine(void);

	// ����
	virtual void Calculate(const Quot& quot);

	// �õ����¼�
	int GetLatestClose();

	// �õ���һ���۸�
	int GetLastClose();

	// �õ���һ����߼�
	int latest_high();

	// �õ�һ����ͼ�
	int latest_low();

	// ��һ���ߵ������
	string date_of_latesthigh();

	// ��һ���͵������
	string date_of_latestlow();

	// ����ת��
	bool getChanged() { return changed_; }

	TurnPoint* turnpoints() { return &turnPoint_; }

	int cycle() { return cycle_; }

private:
	int latest_high_;
	int latest_low_;
	string date_of_latesthigh_;
	string date_of_latestlow_;
	int detal_;
	int cycle_;
	int sumofclose_;
	int sumofvol_;
	int firstValue;
	int prevValue_;
	bool changed_;
	int quotNumber_;
	int trend_;

	TurnPoint turnPoint_;
};
