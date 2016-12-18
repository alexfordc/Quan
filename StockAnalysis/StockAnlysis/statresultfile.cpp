#include "StdAfx.h"
#include "statresultfile.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "instrumentmanager.h"

using namespace std;

StatResultFile::StatResultFile(void)
{
}

StatResultFile::~StatResultFile(void)
{
}

void StatResultFile::Load(vector<StrategyResult>& results, const char* filename)
{
	string line, field;    //lineΪÿ�����ݣ�fieldΪÿ���ֶ�

	//���ļ�
	ifstream in;
	in.open(filename);    //�Զ��Ÿ���

	//�����ļ�����
	if(in.is_open())
	{
		//ѭ��ȡ��ÿһ������
		while(getline(in,line))
		{
			istringstream stream(line);

			//��һ�еĶ���ֶ�ȡ��
			vector<string> rows;

			//�ԡ�,����ȡÿ���ֶ�
			while(getline(stream, field, '	'))
			{
				//����
				rows.push_back(field);
			}

			if (rows.size() < 10)
			{
				continue;
			}

			StrategyResult sr;
			
			results.push_back(sr);
		}

		// �ر��ļ�
		in.close();
	}
	else
	{
		//�ļ���ʧ��
		cout << "���ļ�ʧ�ܣ�";
	}
}

void StatResultFile::Save(const vector<StrategyResult>& results, const char* filename)
{
	// д���ļ�
	ofstream os(filename, ios::out);

	if (os)
	{
		stringstream ssHeader;

		ssHeader<<"Code,Name,ROI,MaxGain,MaxLoss,NumOfPosGain,NumOfBuy,NumOfSell,Period,AveragePosROI,RateOfPosGain,LastBuyDate,CurrentStatus,AllBuy,AllSell,AllTrades";

	    os<<ssHeader.str()<<endl;

		ssHeader.clear();

		foreach(results, it, vector<StrategyResult>)
		{
			stringstream ss;

			ss<<it->code_<<","<<g_InstrumentMgr.GetInstrument(it->code_.c_str()).Name<<","<<CommonUtil::FormatDouble(it->GetROI())<<","<<CommonUtil::FormatDouble(it->GetMaxGain())
				<<","<<CommonUtil::FormatDouble(it->GetMaxLoss())
				<<","<<it->GetNumOfPosGain()<<","<<it->GetNumOfBuy()<<","<<it->GetNumOfSell() <<","<<it->GetPeriod()<<","
				<<CommonUtil::FormatDouble(it->GetAveragePosROI())<<","<<CommonUtil::FormatDouble(it->GetRateOfPosGain())
				<<","<<it->GetLastBuyDate() <<","<<it->GetCurrentStatus()<<","<<it->GetAllBuy()<<","<<it->GetAllSell()<<","<<it->GetAllTrades();

			os<<ss.str()<<endl;

			ss.clear();
		}

		os.close();
	}
}