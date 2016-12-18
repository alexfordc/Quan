#include "StdAfx.h"
#include "TushareDataLoader.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/format.hpp>     
#include <boost/tokenizer.hpp>     
#include <boost/algorithm/string.hpp>  

using namespace std;

TushareDataLoader::TushareDataLoader(void)
:lastclose_(INVALID_VALUE)
{
}

TushareDataLoader::~TushareDataLoader(void)
{
}

void TushareDataLoader::extract(const char* strFileName, vector<Quot>& stockTradeInfos)
{
	string line, field;    //lineΪÿ�����ݣ�fieldΪÿ���ֶ�

	//���ļ�
	ifstream in;
	in.open(strFileName);    //�Զ��Ÿ���

	//�����ļ�����
	if(in.is_open())
	{
		// remove the first row because it's column headers
		getline(in, line);

		//ѭ��ȡ��ÿһ������
		while(getline(in,line))
		{
			//��һ�еĶ���ֶ�ȡ��
			vector<string> RowContext;

			boost::split(RowContext, line, boost::is_any_of(","));

			if (RowContext.size() < 6)
			{
				continue;
			}

			string strDate = RowContext[0];

			Quot info;

			info.setDatetime(strDate.c_str());

			string strTmp = RowContext[1];

			info.Open = atof(strTmp.c_str())*100;

			strTmp = RowContext[2];
			info.High = atof(strTmp.c_str())*100;

			strTmp = RowContext[3];
			info.Close = atof(strTmp.c_str())*100;

			strTmp = RowContext[4];
			info.Low = atof(strTmp.c_str())*100;

			strTmp = RowContext[5];
			info.Volume = atoi(strTmp.c_str());

			info.LastClose = lastclose_;

			lastclose_ = info.Close;

			stockTradeInfos.push_back(info);

			notifyObservers(&info);
		}

		// �ر��ļ�
		in.close();
	}
	else
	{
		//�ļ���ʧ��
		cout << "���ļ�" << strFileName << "ʧ�ܣ�" << endl;
	}
}
