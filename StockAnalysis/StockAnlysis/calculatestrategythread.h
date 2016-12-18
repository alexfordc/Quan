#pragma once

#include "FrameworkCls.h"
#include "Product.h"
#include "Utilities.h"
#include "crossMA_result_reader.h"
#include <boost/thread.hpp>

using namespace fmkcls;

#define  LOG_DEBUG	std::cout
#define  LOG_ENDL   std::endl     

class CalculateStrategyThread
{
public:
	virtual ~CalculateStrategyThread(void);

	//
	static void Run(int sector, HWND hwnd_progress, const DataHandler& datahandler, int cycle);

	static void Run(const vector<Instrument>& instruments, HWND hwnd_progress, const DataHandler& datahandler, int cycle);

	// ���ò���
	static void SetStrategy(const vector<string>& strategies);

	// ����
	void Execute();

	// ��ֹ
	static void Terminate();

	// ���Լ�����
	static ShareVector<StrategyResult> s_strategyresults;

	// �߳�ȫ����ֹ
	static bool getTerminated();

protected:
	CalculateStrategyThread(HWND hwnd_progress, ShareQueue<Instrument>* instruments, 
		const DataHandler& datahandler, int cycle, CrossMAResultReader* reader);

	virtual void ExecuteStrategy(Product* product);

	static DWORD WINAPI CalculateStrategyProc(void* lpParam);

	static vector<string> strategies_;

	static bool s_terminated_;

	static ShareVector<CalculateStrategyThread*> s_threads_;  

	static ShareQueue<Instrument> s_queue_instrument_;

	static CrossMAResultReader reader_;

	HWND hwnd_progress_;
	int cycle_;
	ShareQueue<Instrument>* instruments_;
	DataHandler datahandler_;
};

// ���̼߳�����
class ThreadExecutor
{
public:
	ThreadExecutor(const vector<Instrument>& instruments, HWND hwnd_progress, const DataHandler& datahandler, int cycle);

	virtual ~ThreadExecutor();

	// ��ʼ���Լ����߳� 
	void start();

	// ���������߳�
	void stop();

protected:
	virtual void doExecute(const char* code, const vector<Quot>& quots) = 0;
private:
	void executeThread();

	HWND hwnd_progress_;
	int cycle_;
	ShareQueue<Instrument> instruments_;
	DataHandler datahandler_;
	bool terminated_;
	boost::thread_group group_;
};

// ���Լ�����
class StrategyExecutor
{
public:
	StrategyExecutor(const vector<Instrument>& instruments, const vector<string>& strategies, HWND hwnd_progress, const DataHandler& datahandler, int cycle);

	~StrategyExecutor();

	// ��ʼ���Լ����߳� 
	void start();

	// ���������߳�
	void stop();

	// ���Լ�����
	ShareVector<StrategyResult>& getStrategyResult(); 

private:
	void executeThread();

	HWND hwnd_progress_;
	int cycle_;
	ShareQueue<Instrument> instruments_;
	vector<string> strategies_;
	DataHandler datahandler_;
	bool terminated_;
	ShareVector<StrategyResult> strategyresults_; // ���Լ�����
};

// ���˼����� 
class FilterExecutor
{
public:
	//FilterExecutor();


};