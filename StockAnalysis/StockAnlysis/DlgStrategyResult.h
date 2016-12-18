#pragma once

#include "Strategy.h"


// CDlgStrategyResult �Ի���

class CDlgStrategyResult : public CDialog
{
	DECLARE_DYNAMIC(CDlgStrategyResult)

public:
	CDlgStrategyResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStrategyResult();

// �Ի�������
	enum { IDD = IDD_DIALOG_RESULT };

	void SetStrategyResults(const vector<StrategyResult>& results);

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	void InitializeList();

	CListCtrl m_list;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLvnColumnclickListResult(NMHDR *pNMHDR, LRESULT *pResult);
};
