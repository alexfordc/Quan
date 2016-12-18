#pragma once

#include "Utilities.h"
#include "FrameworkCls.h"

using namespace fmkcls;

//
class CrossMAResultItem : public RowInfo
{
public:
	string GetCode() const
	{
		return fields[0];
	}

	int GetShortTerm() const
	{
		return convert<string, int>(fields[1]);
	}

	int GetLongTerm() const
	{
		return convert<string, int>(fields[2]);
	}

	double GetChange() const
	{
		return convert<string, double>(fields[3]);
	}

	double GetROI() const
	{
		return convert<string, double>(fields[4]);
	}

	// ������� 
	double GetMaxGain() const
	{
		return convert<string, double>(fields[5]);
	}

	// ���س�
	double GetMaxLoss() const
	{
		return convert<string, double>(fields[6]);
	}

	// ���������
	int GetNumOfPosGain() const
	{
		return convert<string, int>(fields[7]);
	}

	//
	int GetNumOfBuy() const
	{
		return convert<string, int>(fields[8]);
	}
	
	//
	int GetNumOfSell() const
	{
		return convert<string, int>(fields[9]);
	}

	// 
	double GetRateOfPosGain() const
	{
		int numofgain = GetNumOfPosGain();
		
		int numofbuy = GetNumOfBuy();

		if (numofbuy > 0)
		{
			return (double)numofgain*100/numofbuy;
		}
		else
		{
			return 0;
		}
	}

	bool operator==(const CrossMAResultItem& value)
	{
		return (GetCode()==value.GetCode())?true:false;
	}

	bool Empty()
	{
		return (fields.size()<=0)?true:false;
	}
};

// ��ȡ���߽�������� 
class CrossMAResultReader
{
public:
	CrossMAResultReader(void);
	~CrossMAResultReader(void);
public:
	// ���ļ��м���
	void Load(const char* filename);

	// �Ƿ����
	bool IsExisting(const char* code);

	// �ҵ�һ��
	CrossMAResultItem GetItem(const char* code);

	// ����һ��������
	void AddItem(const CrossMAResultItem& item);

	// ���
	void Clear();

	// ��������ָ���ļ�
	void Save(const char* filename);

private:
	vector<CrossMAResultItem> items_;

	AccessLock lock_;
};
