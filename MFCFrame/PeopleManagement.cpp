// PeopleManagement.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Frame.h"
#include "PeopleManagement.h"


// CPeopleManagement �Ի���

IMPLEMENT_DYNAMIC(CPeopleManagement, CDialogEx)

CPeopleManagement::CPeopleManagement(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPeopleManagement::IDD, pParent)
{
	
}

CPeopleManagement::~CPeopleManagement()
{
}

void CPeopleManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPeopleManagement, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPeopleManagement ��Ϣ�������


void CPeopleManagement::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rcClient;
	GetClientRect(rcClient);
	dc.FillSolidRect (rcClient,RGB(240,248,251));
}


int CPeopleManagement::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	return 0;
}


void CPeopleManagement::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	
}
