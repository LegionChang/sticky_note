
// Sticky_noteDlg.h : ͷ�ļ�
//

#pragma once

// CSticky_noteDlg �Ի���
class CSticky_noteDlg : public CDialogEx
{
// ����
public:
	CSticky_noteDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_STICKY_NOTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	afx_msg LRESULT OnSystemtray(WPARAM wParam, LPARAM lParam);

	// ���ɵ���Ϣӳ�亯��
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
