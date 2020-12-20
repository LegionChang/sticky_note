#pragma once
#include "afxwin.h"


// CNoteDlg 对话框

class CNoteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNoteDlg)

public:
	CRect m_rect;

	/*******************存储*******************/
	CString m_NoteContent;	//内容
	CString m_NoticeFlag;	//提醒标志，默认为0
	CString m_NoteTime;		//设定时间，默认值设定为lc2020120379lc(即未设定时间)
	CString m_HideFlag;		//隐藏标志，默认为0
	CString m_NotePos;		//标签位置
	COLORREF m_BGColor;		//背景颜色
	COLORREF m_TxtColor;	//字体颜色
	CString m_NoteTitle;	//标题

	/**************************************************************/
	CNoteDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNoteDlg();


// 对话框数据
	enum { IDD = IDD_NOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();


	/*************系统自动生成区**************/
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

	/***************************快捷键设置**********************/
	HACCEL hotKey;

	afx_msg void OnTimer(UINT_PTR nIDEvent);

};
