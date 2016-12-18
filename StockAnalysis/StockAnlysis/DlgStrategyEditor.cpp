// DlgStrategyEditor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StockAnlysis.h"
#include "DlgStrategyEditor.h"


const string STRATEGYNAMES[] =
{
	"CrossMA",
	"CrossMACD",
	"MACD",
	"Trend",
	"TrendCrossMA",
	"VolumeCross",
	"MA",
	"NewHigh",
	"Rebound",
	"MAOffset"
};

// CDlgStrategyEditor �Ի���

IMPLEMENT_DYNAMIC(CDlgStrategyEditor, CDialog)

CDlgStrategyEditor::CDlgStrategyEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStrategyEditor::IDD, pParent)
{

}

CDlgStrategyEditor::~CDlgStrategyEditor()
{
}

void CDlgStrategyEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Control(pDX, IDC_COMBO_CYCLE, m_combobox);
	DDX_CBIndex(pDX, IDC_COMBO_CYCLE, m_cycle);
}


BEGIN_MESSAGE_MAP(CDlgStrategyEditor, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgStrategyEditor::OnLbnSelchangeList1)
	ON_CBN_SELCHANGE(IDC_COMBO_CYCLE, &CDlgStrategyEditor::OnCbnSelchangeComboCycle)
END_MESSAGE_MAP()


// CDlgStrategyEditor ��Ϣ�������
BOOL CDlgStrategyEditor::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��ʼ����ʾ�б�
	m_listbox.AddString("���߽������");
	m_listbox.AddString("MACD�������");
	m_listbox.AddString("���ײ���");
	m_listbox.AddString("�����߲���");
	m_listbox.AddString("���ƾ��߽������");
	m_listbox.AddString("�ɽ������߽������");
	m_listbox.AddString("���߲���");
	m_listbox.AddString("�¸��µͲ���");
	m_listbox.AddString("��������");
	m_listbox.AddString("����ƫ�Ʋ���");

	//
	m_combobox.AddString("����");
	m_combobox.AddString("����");
	m_combobox.AddString("����");

	m_cycle = 0;
	m_combobox.SetCurSel(m_cycle);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgStrategyEditor::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strategies->clear();

	for (int i = 0; i < m_listbox.GetCount(); i++)
	{
		if (m_listbox.GetSel(i))
		{
			m_strategies->push_back(STRATEGYNAMES[i]);
		}
	}
}

void CDlgStrategyEditor::SetStrategies(vector<string>* strategies)
{
	m_strategies = strategies;
}

void CDlgStrategyEditor::OnCbnSelchangeComboCycle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}
