#pragma once

#include <vector>
#include <string>

using namespace std;

// CDlgStrategyEditor �Ի���

class CDlgStrategyEditor : public CDialog
{
	DECLARE_DYNAMIC(CDlgStrategyEditor)

public:
	CDlgStrategyEditor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStrategyEditor();

// �Ի�������
	enum { IDD = IDD_DLG_STRATEGY };

	void SetStrategies(vector<string>* strategies);

	int GetCycle(){ return m_cycle; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CListBox m_listbox;
	CComboBox m_combobox;
	int m_cycle;
	vector<string>* m_strategies;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnCbnSelchangeComboCycle();
};
