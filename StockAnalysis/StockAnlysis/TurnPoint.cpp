#include "StdAfx.h"
#include "TurnPoint.h"

TurnPoint::TurnPoint(void)
:trend_(UNKNOWN), close_(INVALID_VALUE), lastdate_("")
{
}

TurnPoint::~TurnPoint(void)
{
}

void TurnPoint::Calculate(const Quot& quot)
{
	// �����ǰû���κ����ݵ����˳�
	if (close_ == INVALID_VALUE)
	{
		close_ = quot.Close;

		lastdate_ = quot.getDate();

		return;
	}

	// ����������ļ۸���offset����ķ�Χ�ڣ�����Ϊ�۸�δ�仯
	if (abs(quot.Close - close_)*100/close_ <= offset_)
	{
		lastdate_ = quot.getDate();

		return;
	}

/*
	// ���ݸ������ƽ��д���
	switch (trend_)
	{
	case UP:
		if (quot.Close < close_) // ��ǰΪ�������ƣ� �������ǰ��ǰ������̼۵ͣ�����Ϊ���Ʊ仯
		{
			trend_ = DOWN;

			TurnPointItem tpi;
			tpi.direction = DOWN;
			tpi.close = close_;

			turnpoints_.insert(make_pair(quot.getDate(), tpi));
		}
		break;
	case DOWN:
		if (quot.Close > close_) // ��ǰΪ�µ����ƣ� �������ǰ��ǰ������̼۵ͣ�����Ϊ���Ʊ仯
		{
			trend_ = UP;

			TurnPointItem tpi;
			tpi.direction = UP;
			tpi.close = close_;

			turnpoints_.insert(make_pair(quot.getDate(), tpi));
		}
		break;
	case UNKNOWN: 
		if (quot.Close > close_)
		{
			trend_ = UP;

			TurnPointItem tpi;
			tpi.direction = UP;
			tpi.close = close_;

			turnpoints_.insert(make_pair(quot.getDate(), tpi));
		}
		else if (quot.Close < close_)
		{
			trend_ = DOWN;

			TurnPointItem tpi;
			tpi.direction = DOWN;
			tpi.close = close_;

			turnpoints_.insert(make_pair(quot.getDate(), tpi));
		}

		break;
	default:
		break;
	}
*/

	close_ = quot.Close;

	lastdate_ = quot.getDate();
}

TurnPointItem TurnPoint::GetTurnPoint(const char* date)
{
	TurnPointItem item;
	item.direction = UNKNOWN;
	item.close = INVALID_VALUE;

	map<string, TurnPointItem>::iterator it = turnpoints_.find(string(date));

	if (it != turnpoints_.end())
	{
		item = it->second;
	}

	return item;
}

void TurnPoint::AddTurnPoint(const char* date, const TurnPointItem& item)
{
	turnpoints_.insert(make_pair(string(date), item));
}