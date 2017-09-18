#pragma once
#include "resource.h"
#include "ImageButton.h"

// CAlarmSet �Ի���

class CAlarmSet : public CDialogEx
{
	DECLARE_DYNAMIC(CAlarmSet)

public:
	CAlarmSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAlarmSet();

// �Ի�������
	enum { IDD = IDD_ALARM_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	CListCtrl m_PedestrianList;
	CImageButton  m_add;
	CImageButton  m_alter;
	CImageButton  m_delete;
};
