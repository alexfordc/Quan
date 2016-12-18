#pragma once

#include <map>
#include <string>
#include <vector>
#include "FrameworkCls.h"
#include "StockDataStructures.h"
#include "Utilities.h"
#include "Strategy.h"
#include "maline.h"

using namespace std;
using namespace fmkcls;


// Ʒ��
class Product : public Observable
{
public:
	Product(const char* code, const char* name = "");
	~Product(void);

public:
	// ��ȡ����
	void Load();

	// ��������
	void Save();

	// ��Ʊ����
	string code() { return code_; }

	//
	string name() { return name_; }

	vector<Quot>& GetQuotations() { return quotations_; }

	// ��ȡ���鿪ʼ����
	string GetBeginDate();

	// ��ȡ�����������
	string GetEndDate();

	// ��ȡͶ��������
	double GetIncreaseRate(); 

	// ������������
	void UpdateLatestQuot(const Quot& quot);

protected:

private:
	// ��Ʊ����
	string code_;

	string name_;

	// �����б�
	vector<Quot> quotations_;

	AccessLock lock_;

	DataHandler datahandler_;
};
