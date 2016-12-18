#pragma once

#include "tchart.h"
#include "seriestextsource.h"
#include "teecommander.h"
#include "Product.h"

// CDlgChart �Ի���

class CDlgChart : public CDialog
{
	DECLARE_DYNAMIC(CDlgChart)

public:
	CDlgChart(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChart();

// �Ի�������
	enum { IDD = IDD_DLG_CHART };

	void SetProduct(Product* product);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL CDlgChart::OnInitDialog();


	DECLARE_MESSAGE_MAP()

	CTChart	m_chart;

	Product* m_product;
};
