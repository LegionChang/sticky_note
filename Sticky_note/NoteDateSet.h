#pragma once
#include "afxdtctl.h"


// NoteDateSet 对话框

class NoteDateSet : public CDialogEx
{
	DECLARE_DYNAMIC(NoteDateSet)

public:
	NoteDateSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~NoteDateSet();

// 对话框数据
	enum { IDD = IDD_NOTEDATEDSEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkPop();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CDateTimeCtrl m_NoteDate;
	CDateTimeCtrl m_NoteTime;
};
