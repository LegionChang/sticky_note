#pragma once


// SetTitleDlg �Ի���

class SetTitleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SetTitleDlg)

public:
	SetTitleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetTitleDlg();

// �Ի�������
	enum { IDD = IDD_SETTITLEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
};
