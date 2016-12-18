#pragma once

#include "Utilities.h"
#include "StockDataStructures.h"
#include "Product.h"
#include "FrameworkCls.h"
#include "crossMA_result_reader.h"
#include "QuotationReceiver.h"
#include "qa_msgno.h"

using namespace fmkcls;


//
class QuanAnalyzer : public Singleton<QuanAnalyzer>, public QuotationEventListener
{
	friend class Singleton<QuanAnalyzer>;
public:
	// ��ʼ��
	void Init(HWND hwnd);

	// ��ȡһ��Ʒ�ֶ���
	Product* GetProduct(const char* code);

	// ɾ��һ��Ʒ��
	void RemoveProduct(const char* code);

	// Ϊһ��Ʒ����Ӳ���
	// code: Ʒ�ִ���
	// strategyName: ��������
	Product* AddStrategy(const char* code, const char* strategyName);
	
	// ��ʼ��ȡ����
	void StartQuotReceiver();

	// ֹͣ��������
	void StopQuotReceiver();

	//
	bool IsQuotReceiverRunning();

	//
	CrossMAResultItem GetCrossMAResultItem(const char* code);

	//
	void Load(const char* filename);

	//
	void Save(const char* filename);

	// ��������
	virtual void DoOnRecv(const map<string, Quot>& quotations);

protected:
	QuanAnalyzer(void);

	~QuanAnalyzer(void);

private:
	// ����һ��Ʒ��
	Product* LoadProduct(const char* code, const char* filename);

	typedef vector<Instrument> VTINSTRUMENT;
	typedef map<string, Product*> MAPPRODUCT; 

	MAPPRODUCT mapProduct; // ��Ʊ�����б�

	VTINSTRUMENT vtInstrument[7]; // ��Ʊ�����б�

	FileLoggerWriter fileLogWriter;

	HWND hwnd_progress_;

	ShareQueue<Instrument>* queue_instrument_;

	// ��ȡ�Ѿ�д���ļ���Ʒ��
	CrossMAResultReader crossma_reader_;

	// ���������
	QuotationReceiver* quotation_receiver_;

	//
	HWND hwnd_;
};

extern QuanAnalyzer& g_QuanAnalyer;