#include "StdAfx.h"
#include "BreakAllMAs.h"

BreakAllMAs::BreakAllMAs(void)
{
}

BreakAllMAs::~BreakAllMAs(void)
{
	foreach(vtMAs, it, vector<MALine*>)
	{
		delete *it;
	}
}

void BreakAllMAs::SetMA(set<int>& mas)
{
	foreach(mas, it, set<int>)
	{
		MALine* ma = new MALine(*it);
     	vtMAs.push_back(ma);
	}
}

void BreakAllMAs::Calculate(const Quot& quot)
{
	set<int> cycles; 

	// ����ÿ������ 
	foreach(vtMAs, it, vector<MALine*>)
	{
		(*it)->Calculate(quot);

		if ((*it)->getMAItems().size() > (*it)->cycle())
		{
			cycles.insert((*it)->cycle());
		}
	}

	// ����������о��߶��Ѵ������˳� 
	if (cycles.size() < vtMAs.size())
	{
		return;
	}

	// �������
	string strDate(quot.Datetime);

	// �����Ƿ��Խ���о���
	foreach(vtMAs, it, vector<MALine*>)
	{
		int price = (*it)->GetLatestClose();

		if ((quot.Close > price) && (quot.Open < price))
		{
			set<int>::iterator itSet = cycles.find((*it)->cycle());
			if (itSet != cycles.end())
			{
				cycles.erase(itSet);		
			}
		}
	}

	// �����Խ���о��ߣ������ڱ���
	if (cycles.size() == 0)
	{
		vtDate.push_back(strDate);
	}
}
