#pragma once
#include"resource.h"
#include "ImageButton.h"
#include"CptionBar.h"
#include "afxwin.h"
// CAddUser �Ի���

class CModUser : public CDialogEx
{
	DECLARE_DYNAMIC(CModUser)

public:
	CModUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModUser();

	// �Ի�������
	enum { IDD = IDD_MOD_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
private:
	CCptionBar  m_caption;
	CImageButton  m_CloseDlg;
	CImageButton  m_AddUserText;
	CImageButton  m_SUserName;
	CImageButton  m_Spassword;
	CImageButton  m_type;
	int m_typedata;
	int strvalue;
	CEdit m_username;
	CEdit m_password;
	CComboBox m_comboxtype;
	CString m_UsernameText;
	CString m_passwordText;
	CString m_typeText;
private:
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};