#pragma once
#include "afxwin.h"


// CNoteDlg �Ի���

class CNoteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNoteDlg)

public:
	CRect m_rect;

	/*******************�洢*******************/
	CString m_NoteContent;	//����
	CString m_NoticeFlag;	//���ѱ�־��Ĭ��Ϊ0
	CString m_NoteTime;		//�趨ʱ�䣬Ĭ��ֵ�趨Ϊlc2020120379lc(��δ�趨ʱ��)
	CString m_HideFlag;		//���ر�־��Ĭ��Ϊ0
	CString m_NotePos;		//��ǩλ��
	COLORREF m_BGColor;		//������ɫ
	COLORREF m_TxtColor;	//������ɫ
	CString m_NoteTitle;	//����

	/**************************************************************/
	CNoteDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNoteDlg();


// �Ի�������
	enum { IDD = IDD_NOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();


	/*************ϵͳ�Զ�������**************/
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnChangeNoteBGC();
	afx_msg void OnChangeTxtC();
	afx_msg void OnSetNoteTitle();
	afx_msg void OnHideThisNote();
	afx_msg void OnDelThisNote();
	afx_msg void OnSetNoteDate();
	afx_msg void OnNoteCX();
	afx_msg void OnNoteJQ();
	afx_msg void OnNoteFZ();
	afx_msg void OnNoteZT();
	afx_msg void OnNoteSelAll();
	CEdit m_NoteEdit;

	/***************************��ݼ�����**********************/
	HACCEL hotKey;

	afx_msg void OnTimer(UINT_PTR nIDEvent);

};
