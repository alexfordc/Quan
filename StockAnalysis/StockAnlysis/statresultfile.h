#pragma once

#include "Strategy.h"

class StatResultFile
{
public:
	StatResultFile(void);
public:
	~StatResultFile(void);

	// ���ļ��м���
	void Load(vector<StrategyResult>& results, const char* filename);

	// ��������ָ���ļ�
	void Save(const vector<StrategyResult>& results, const char* filename);

};
