// DlgStrategyResult.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StockAnlysis.h"
#include "DlgStrategyResult.h"
#include "instrumentmanager.h"


// ���������
const int ID_CODE = 0;   // ��Ʊ����
const int ID_NAME = 1;   // ��Ʊ����
const int ID_STRATEGY_ROI = 2; // ������������
const int ID_STRATEGY_MAXGAIN = 3; // �������������
const int ID_STRATEGY_MAXLOSS = 4; // �������س�
const int ID_STRATEGY_NUM_OF_POSGAIN = 5; // ���������
const int ID_STRATEGY_RATE_OF_POSGAIN = 6; // ��������� 
const int ID_STRATEGY_NUM_OF_BUY = 7; // �������
const int ID_STRATEGY_NUM_OF_SELL = 8; // ��������
const int ID_STATUS = 9;   // ����״̬

// CDlgStrategyResult �Ի���

IMPLEMENT_DYNAMIC(CDlgStrategyResult, CDialog)

CDlgStrategyResult::CDlgStrategyResult(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStrategyResult::IDD, pParent)
{

}

CDlgStrategyResult::~CDlgStrategyResult()
{
}

void CDlgStrategyResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_RESULT, m_list);
}


BEGIN_MESSAGE_MAP(CDlgStrategyResult, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_RESULT, &CDlgStrategyResult::OnLvnColumnclickListResult)
END_MESSAGE_MAP()


// CDlgStrategyResult ��Ϣ�������

BOOL CDlgStrategyResult::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��ʼ����ʾ�б�
	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_list.SetExtendedStyle(dwStyle); //������չ���

	InitializeList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgStrategyResult::InitializeList()
{
	m_list.DeleteAllItems();

	while (m_list.DeleteColumn(0)){}

	m_list.InsertColumn(ID_CODE, "��Ʊ����", 0, 60);
	m_list.InsertColumn(ID_NAME, "��Ʊ����", 0, 100);
	m_list.InsertColumn(ID_STRATEGY_ROI, "������������%", 0, 110);
	m_list.InsertColumn(ID_STRATEGY_MAXGAIN, "�������������%", 0, 110);
	m_list.InsertColumn(ID_STRATEGY_MAXLOSS, "�������س�%", 0, 110);
	m_list.InsertColumn(ID_STRATEGY_NUM_OF_POSGAIN, "���������", 0, 110);
	m_list.InsertColumn(ID_STRATEGY_RATE_OF_POSGAIN, "���������%", 0, 110);
	m_list.InsertColumn(ID_STRATEGY_NUM_OF_BUY, "�������", 0, 110);
	m_list.InsertColumn(ID_STRATEGY_NUM_OF_SELL, "��������", 0, 110);
	m_list.InsertColumn(ID_STATUS, "����״̬", 0, 200);
}

void CDlgStrategyResult::SetStrategyResults(const vector<StrategyResult>& results)
{
	m_list.DeleteAllItems();

	int i = 0;

	foreach(results, it, vector<StrategyResult>)
	{
		CString str;

		m_list.InsertItem(i, it->code_.c_str());

		m_list.SetItemText(i, ID_NAME, g_InstrumentMgr.GetInstrument(it->code_.c_str()).Name.c_str());

		str.Format("%.2f", it->GetROI());
		m_list.SetItemText(i, ID_STRATEGY_ROI, str);

		str.Format("%.2f", it->GetMaxGain());
		m_list.SetItemText(i, ID_STRATEGY_MAXGAIN, str);

		str.Format("%.2f", it->GetMaxLoss());
		m_list.SetItemText(i, ID_STRATEGY_MAXLOSS, str);

		str.Format("%d", it->GetNumOfPosGain());
		m_list.SetItemText(i, ID_STRATEGY_NUM_OF_POSGAIN, str);

		str.Format("%.2f", it->GetRateOfPosGain());
		m_list.SetItemText(i, ID_STRATEGY_RATE_OF_POSGAIN, str);

		str.Format("%d", it->GetNumOfBuy());
		m_list.SetItemText(i, ID_STRATEGY_NUM_OF_BUY, str);

		str.Format("%d", it->GetNumOfSell());
		m_list.SetItemText(i, ID_STRATEGY_NUM_OF_SELL, str);

		if (it->CanBuy())
		{
			str = "����";
		}
		else if (it->CanSell())
		{
			str = "����";
		}
		else if (it->CanHold())
		{
			str = "����";
		}
		else
		{
			str = "�ղ�";
		}

		m_list.SetItemText(i, ID_STATUS, str);

		i++;
	}
}
void CDlgStrategyResult::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_list.GetSafeHwnd())
	{
		m_list.MoveWindow(5, 5, cx-10, cy-10);
	}
}

struct COMPAREDATA  
{  
	CListCtrl *plist;//���ڴ洢�б�ؼ���ָ��  
	int col;//���ڴ洢Ҫ�������е����  
};//�ص�����������������Ӧ�����ݽṹ�������Զ��壬����Ҫ����������

BOOL bSort = FALSE;

int CALLBACK MylistCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	COMPAREDATA * MyData = (COMPAREDATA*)lParamSort;  

	int col = MyData->col;//���������ݸ�col,�����жϵ���˵ڼ��� 

	//ȡ����ַ���  
	CString strItem1, strItem2;  
	strItem1 = MyData->plist->GetItemText(lParam1,col);  
	strItem2 = MyData->plist->GetItemText(lParam2,col);//���Ҫ�Ƚϵ��ַ�	

	if (bSort)
	{
		return strItem1.CompareNoCase(strItem2);
	}
	else
	{
		return strItem2.CompareNoCase(strItem1);
	}
}

void CDlgStrategyResult::OnLvnColumnclickListResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	COMPAREDATA data;  
	data.col = pNMLV->iSubItem;//ȡ��  
	data.plist = &m_list;//ȡ�б�ָ�� 

	bSort=!bSort;//����ÿ��һ���оͱ�һ�Σ�����̶������Ǿ�ȥ�����  

	//�����б������Ա�����  
	for(int i=0; i<m_list.GetItemCount(); i++)  
	{  
		m_list.SetItemData(i, i);  
	}  

	m_list.SortItems(MylistCompare,(LPARAM)&data);  

	*pResult = 0;
}
