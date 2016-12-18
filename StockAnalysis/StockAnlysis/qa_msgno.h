#ifndef _QA_MSGNO_h
#define _QA_MSGNO_h

#include "StockDataStructures.h"
#include <map>

using namespace std;

// ���Լ������ʱ����
const int QAM_STRATEGY_DONE = WM_USER + 1;

// ���ý�������Χ
const int QAM_PROGRESS_SETRANGE = WM_USER + 2;

// ���ý�����λ��
const int QAM_PROGRESS_SETPOS = WM_USER + 3;

// ���ý������
const int QAM_PROGRESS_DONE = WM_USER + 4;

// ��������
const int QAM_QUOTATION_LATEST = WM_USER + 5;

// Ʒ��������Ϣ
const int QAM_PRODUCT_TRADE = WM_USER + 6;

// Ʒ��������Ϣ


// ���½�����
struct MsgProgressSetRange
{
	string title;
	int minimize;
	int maximize;
};

// ���½���
struct MsgProgressSetPos
{
	string prompt;
	int pos;
};

// �������
struct MsgProgressDone
{
	string prompt;
};

// ���²��Լ���Ľ��
struct MsgStrategyDone
{
	string code;   // ��Ʊ����
	double roi;    // ������
	int shortterm; // ���ھ���
	int longterm;  // ���ھ���
};

// �������
struct MsgRecvQuotation
{
	map<string, Quot> quotations; //code: ��Ʊ����, quot: ����
};

// Ʒ��������Ϣ
struct MsgProductTrade
{
	unsigned char flag; // 0: ���� 1: ����
	string code; // ��Ʊ����
    Quot quot;   // ����
};

#endif