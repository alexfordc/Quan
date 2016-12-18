#ifndef _CONFIGURATION_
#define _CONFIGURATION_

#include <string>
#include "Utilities.h"

using namespace std;


//
class Configuration : public Singleton<Configuration>, public Observable
{
	friend class Singleton<Configuration>;

public:
	// ���ļ��ж�ȡ����
	void Load(const char* filename);

	// д���ļ�
	void Save();

	// retrieve the url of downloading history data
	string getHistoryDataUrl(const char* strMarket, const char* strCode);

    // retrieve the path for saving the history data file
	string getHitoryDataStorePath();

	void SetHitoryDataStorePath(const char* value);

	// ��ȡ�����ļ�·��
	string GetInstrumentFilePath();

	void SetInstrumentFilePath(const char* value);

	// ��ȡ���ݱ���·��
	string GetSaveFilePath();

	void SetSaveFilePath(const char* value);

	// retrieves the cycle of mean
	int getMeanCycle();

	void setMeanCycle(const int value);

	// 
	int getAdjustCycle();

	void setAdjustCycle(const int value);

	//
	int getThreshold();

	void setThreshold(const int value);

	//
	int getStopLoss();

	void setStopLoss(const int value);

	// ��ȡ���ƶ��еĴ�С
	int getTrendArraySize();

	//
	int safeMA_cycle(); 

	void setsafeMA_cycle(const int value);

	// ��ȡ�����б�
	void GetMALines(vector<int>& mas);

	// ���þ����б� 
	void SetMALines(const vector<int>& mas);

	//
	int getOffset();

	void setOffset(const int value);

	//
	DataHandler& getDataHandler();

protected:
	Configuration(void);
	~Configuration(void);

private:
	int trendArraySize;

	DataHandler datahandler_;

	string filename_;
};

extern Configuration& g_Configuration;

#endif