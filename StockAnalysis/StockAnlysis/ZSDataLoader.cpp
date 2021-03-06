#include "StdAfx.h"
#include "ZSDataLoader.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

ZSDataLoader::ZSDataLoader(void)
:lastclose_(INVALID_VALUE)
{
}

ZSDataLoader::~ZSDataLoader(void)
{
}

void ZSDataLoader::extract(const char* strFileName, vector<Quot>& stockTradeInfos)
{
	string line, field;    //line为每行内容，field为每个字段

	//打开文件
	ifstream in;
	in.open(strFileName);    //以逗号隔开

	//处理文件内容
	if(in.is_open())
	{
		// remove the first row because it's column headers
		getline(in, line);

		//循环取出每一行数据
		while(getline(in,line))
		{
			istringstream stream(line);

			//将一行的多个字段取出
			vector<string> RowContext;

			//以‘,’读取每个字段
			while(getline(stream, field, ','))
			{
				//存入
				RowContext.push_back(field);
			}

			if (RowContext.size() < 6)
			{
				continue;
			}

			string strDate = RowContext[0];

			Quot info;

			info.setDatetime(strDate.c_str());

			/*
			int n = convert<string, int>(strDate);

			if (n < 20080101 || n > 20131231)
			{
				continue;
			}
			*/

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

			//strTmp = RowContext[6];
			//info.AdjClose = atof(strTmp.c_str())*100;

			info.LastClose = lastclose_;

			lastclose_ = info.Close;

			stockTradeInfos.push_back(info);

			notifyObservers(&info);
		}

		// 关闭文件
		in.close();
	}
	else
	{
		//文件打开失败
		cout << "打开文件" << strFileName << "失败！" << endl;
	}
}
