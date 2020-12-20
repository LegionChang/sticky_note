
// Sticky_noteDlg.h : 头文件
//

#pragma once

// CSticky_noteDlg 对话框
class CSticky_noteDlg : public CDialogEx
{
// 构造
public:
	CSticky_noteDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_STICKY_NOTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	afx_msg LRESULT OnSystemtray(WPARAM wParam, LPARAM lParam);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	NOTIFYICONDATA NotifyIcon;
public:
	afx_msg void OnAddNewNote();
	afx_msg void OnDelAllNote();
	afx_msg void OnShowAllNote();
	afx_msg void Onmyhelp();
	afx_msg void Onmyabout();
	afx_msg void Onmyexit();

};
