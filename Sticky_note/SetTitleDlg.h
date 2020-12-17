#pragma once


// SetTitleDlg 对话框

class SetTitleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SetTitleDlg)

public:
	SetTitleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SetTitleDlg();

// 对话框数据
	enum { IDD = IDD_SETTITLEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
};
