// DlgProgress.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StockAnlysis.h"
#include "DlgProgress.h"
#include "qa_msgno.h"
#include "CalculateCrossMA.h"


// CDlgProgress �Ի���

IMPLEMENT_DYNAMIC(CDlgProgress, CDialog)

CDlgProgress::CDlgProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProgress::IDD, pParent)
{

}

CDlgProgress::~CDlgProgress()
{
}

void CDlgProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, m_progressctrl);
}


BEGIN_MESSAGE_MAP(CDlgProgress, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDlgProgress::OnBnClickedCancel)
	ON_MESSAGE(QAM_PROGRESS_SETRANGE, OnQAM_Progress_SetRange)
	ON_MESSAGE(QAM_PROGRESS_SETPOS, OnQAM_Progress_SetPos)
	ON_MESSAGE(QAM_PROGRESS_DONE, OnQAM_Progress_Done)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgProgress ��Ϣ�������

BOOL CDlgProgress::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	m_progressctrl.SetRange(0, maximum());

	m_isCanceled = FALSE;

	//
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgProgress::UpdateProgress(int progress)
{
	m_progressctrl.SetPos(progress);
}

bool CDlgProgress::IsCanceled()
{
	return m_isCanceled;
}

void CDlgProgress::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_isCanceled = TRUE;

	// ��ֹ���м����߳�
	CalculateCrossMA::Terminate();

	ShowWindow(SW_HIDE);
}

void CDlgProgress::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_isCanceled = TRUE;

	//__super::OnClose();

	ShowWindow(SW_HIDE);
}

void CDlgProgress::Done()
{
	ShowWindow(SW_HIDE);
}

void CDlgProgress::PostNcDestroy()
{
	delete this;
}

LRESULT CDlgProgress::OnQAM_Progress_SetRange(WPARAM wParam, LPARAM lParam)
{
	auto_ptr<MsgProgressSetRange> msg((MsgProgressSetRange*)wParam);

	m_progressctrl.SetRange32(msg->minimize, msg->maximize);

	m_progressctrl.SetStep(1);

	SetWindowText(msg->title.c_str());	

	ShowWindow(SW_SHOW);

	return 0;
}

LRESULT CDlgProgress::OnQAM_Progress_SetPos(WPARAM wParam, LPARAM lParam)
{
	auto_ptr<MsgProgressSetPos> msg((MsgProgressSetPos*)wParam);

	//m_progressctrl.SetPos(msg->pos);
	m_progressctrl.StepIt();

	SetWindowText(msg->prompt.c_str());	

	return 0;
}

LRESULT CDlgProgress::OnQAM_Progress_Done(WPARAM wParam, LPARAM lParam)
{
	auto_ptr<MsgProgressDone> msg((MsgProgressDone*)wParam);

	SetWindowText(msg->prompt.c_str());	

	ShowWindow(SW_HIDE);

	return 0;
}