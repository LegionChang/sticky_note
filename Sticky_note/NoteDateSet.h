#pragma once
#include "afxdtctl.h"


// NoteDateSet �Ի���

class NoteDateSet : public CDialogEx
{
	DECLARE_DYNAMIC(NoteDateSet)

public:
	NoteDateSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NoteDateSet();

// �Ի�������
	enum { IDD = IDD_NOTEDATEDSEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkPop();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CDateTimeCtrl m_NoteDate;
	CDateTimeCtrl m_NoteTime;
};
