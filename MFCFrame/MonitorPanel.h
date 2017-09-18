#pragma once
#include "resource.h"
#include "SideBar.h"
#include "VideoPanel.h"
#include "ImageButton.h"

// CMonitorPanel �Ի���

class CMonitorPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CMonitorPanel)

public:
	CMonitorPanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMonitorPanel();

// �Ի�������
	enum { IDD = IDD_MONITORPANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
private:
	CSideBar m_sidebar;
	CVideoPanel m_videoPanel;
	CImageButton m_expand;
	BOOL m_expandSidebar;
	CImage m_imgRight;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
