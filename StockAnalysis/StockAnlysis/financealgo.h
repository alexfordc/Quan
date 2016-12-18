#pragma once

#include <vector>
#include <deque>

using namespace std;

namespace finance_algo
{
	// �����㷨 
	class MA
	{
	public:
		MA(int cycle);

		~MA(void);

	public:
		void Calculate(const double value);

		int cycle() { return cycle_; }

		double GetLatestValue(); // ������һ������

		double GetLastValue(); // ���ǰһ������

		vector<double>& items();

	private:
		int cycle_;

		double sumofvalue_;

		vector<double> items_;

		deque<double> values_;
	};

	// ������б�ʼ���
	/*
	begin: ��ʼ�۸�
	end: �����۸�
    timespan: ʱ����
	*/
	float GetTrendLineRate(const float begin, const float end, const int timespan);
}
