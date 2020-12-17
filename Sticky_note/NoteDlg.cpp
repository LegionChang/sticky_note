// NoteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Sticky_note.h"
#include "NoteDlg.h"
#include "afxdialogex.h"
#include "SetTitleDlg.h"
#include "NoteDateSet.h"

/****************************自定义参数******************************/
int numOfNote = -1;//表示note的下标，当为-1时表示该note已经被删除或还没创建

/****************************使用外部参数******************************/
extern CNoteDlg * myNoteList[MAXNOTE];
extern int noteCount;

// CNoteDlg 对话框

IMPLEMENT_DYNAMIC(CNoteDlg, CDialogEx)

CNoteDlg::CNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNoteDlg::IDD, pParent)
{

}

CNoteDlg::~CNoteDlg()
{
}

void CNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_NoteEdit);
}

BEGIN_MESSAGE_MAP(CNoteDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
//	ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_32790, &CNoteDlg::OnChangeNoteBGC)
ON_COMMAND(ID_32791, &CNoteDlg::OnChangeTxtC)
ON_COMMAND(ID_32792, &CNoteDlg::OnSetNoteTitle)
ON_COMMAND(ID_32786, &CNoteDlg::OnHideThisNote)
ON_COMMAND(ID_32787, &CNoteDlg::OnDelThisNote)
ON_COMMAND(ID_32789, &CNoteDlg::OnSetNoteDate)
ON_COMMAND(ID_32795, &CNoteDlg::OnNoteCX)
ON_COMMAND(ID_32797, &CNoteDlg::OnNoteJQ)
ON_COMMAND(ID_32798, &CNoteDlg::OnNoteFZ)
ON_COMMAND(ID_32799, &CNoteDlg::OnNoteZT)
ON_COMMAND(ID_32801, &CNoteDlg::OnNoteSelAll)
ON_WM_TIMER()
//ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CNoteDlg 消息处理程序


void CNoteDlg::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;
	CDialogEx::PostNcDestroy();
}

/***********************便利贴窗口拉伸**************************/
void CNoteDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CWnd *pWnd;
	pWnd=GetDlgItem(IDC_EDIT1); 
	if(pWnd!=NULL)
	{
		CRect recEdit;
		GetClientRect(recEdit);
		pWnd->MoveWindow(recEdit);
	}
}

BOOL CNoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

/***********************用于便利贴窗口拉伸**************************/
	GetClientRect(&m_rect); //获取对话框的大小

/***************************快捷键设置**********************/
	hotKey=::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MENU1));


/***********************初始化窗口标题**************************/
	CString strCurTime; //获取系统时间 　　
	CTime curTime;
	curTime=CTime::GetCurrentTime();
	strCurTime=curTime.Format("%A,%b, %d,%Y ");
	SetWindowTextW(strCurTime);

/***********************初始化变量**************************/
	m_NoticeFlag = L"0";
	m_NoteTime = L"lc2020120379lc";
	m_HideFlag = L"0";
	m_BGColor  = RGB(255, 255, 0);
	m_TxtColor = RGB(0, 0, 0);
	m_NoteTitle = strCurTime;



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

/***********************便利贴颜色改变**************************/
HBRUSH CNoteDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
	{
		pDC->SetTextColor(m_TxtColor);
		pDC->SetBkColor(m_BGColor);
		hbr = ::CreateSolidBrush(m_BGColor);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

/***********************重写各种消息**************************/
BOOL CNoteDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	/***************************快捷键设置**********************/
	if(::TranslateAccelerator(GetSafeHwnd(),hotKey,pMsg))
		return   true;

	/***************************截获鼠标右键消息**********************/
	if(pMsg->message==WM_RBUTTONDOWN)
	{
		CRect noteRect;
		::GetWindowRect(GetDlgItem(IDC_EDIT1)->GetSafeHwnd(),&noteRect);
		POINT pt;
		::GetCursorPos(&pt);
		if (PtInRect(&noteRect,pt))
		{
			CMenu rClickMenu;
			CMenu *pNoteMenu;
			rClickMenu.LoadMenu(IDR_MENU1);
			pNoteMenu = rClickMenu.GetSubMenu(1);
			CPoint point;
			GetCursorPos(&point);
			pNoteMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this);
			pNoteMenu->DestroyMenu();
			rClickMenu.DestroyMenu();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

/***********************便签背景颜色**************************/
void CNoteDlg::OnChangeNoteBGC()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog colorDialog;
	if( colorDialog.DoModal() == IDOK )
	{
		m_BGColor = colorDialog.GetColor();
	}
}

/***********************便签文本颜色**************************/
void CNoteDlg::OnChangeTxtC()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog colorDialog;
	if( colorDialog.DoModal() == IDOK )
	{
		m_TxtColor = colorDialog.GetColor();
	}

}

/***********************设置便签标题**************************/
void CNoteDlg::OnSetNoteTitle()
{
	// TODO: 在此添加命令处理程序代码
	SetTitleDlg setTitleDlg;
	setTitleDlg.DoModal();
}

/***********************隐藏便签**************************/
void CNoteDlg::OnHideThisNote()
{
	// TODO: 在此添加命令处理程序代码
	this->m_HideFlag = L"1";
	this->ShowWindow(SW_HIDE);

}

/***********************删除便签**************************/
void CNoteDlg::OnDelThisNote()
{
	myNoteList[noteCount] = NULL;
	bool moveHere = false;
	for (int i=0; i<noteCount; ++i)
	{
		if (myNoteList[i]->GetSafeHwnd() == this->GetSafeHwnd())
		{
			myNoteList[i] = NULL;

			this->SendMessage(WM_CLOSE);
			moveHere = true;
		}
		if (moveHere)
		{
			myNoteList[i] = myNoteList[i+1];
		}
	}
	noteCount--;
}

/***********************设置时间**************************/
void CNoteDlg::OnSetNoteDate()
{
	// TODO: 在此添加命令处理程序代码
	CString preNoticeFlag = m_NoticeFlag;

	NoteDateSet myNoteDateSetDlg;
	if (myNoteDateSetDlg.DoModal() == IDOK)
	{
		//AfxMessageBox(L"设置1号定时器");
		if (preNoticeFlag == L"1")
		{
			KillTimer(1);
		}
		SetTimer(1, 1000, NULL);

	}
}

/***********************撤销**************************/
void CNoteDlg::OnNoteCX()
{
	// TODO: 在此添加命令处理程序代码
	m_NoteEdit.Undo();
}

/***********************剪切**************************/
void CNoteDlg::OnNoteJQ()
{
	// TODO: 在此添加命令处理程序代码
	m_NoteEdit.Cut();
}

/***********************复制**************************/
void CNoteDlg::OnNoteFZ()
{
	// TODO: 在此添加命令处理程序代码
	m_NoteEdit.Copy();
}

/***********************粘贴**************************/
void CNoteDlg::OnNoteZT()
{
	// TODO: 在此添加命令处理程序代码
	m_NoteEdit.Paste();
}

/***********************全选**************************/
void CNoteDlg::OnNoteSelAll()
{
	// TODO: 在此添加命令处理程序代码
	m_NoteEdit.SetSel(0, -1);

}

/***********************定时闹钟**************************/
void CNoteDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == 1)
	{
		CTime curTime = CTime::GetCurrentTime();
		CString strCurTime;
		strCurTime = curTime.Format("%Y%m%d%H%M%S");
		//AfxMessageBox(strCurTime + L":" + m_NoteTime);
		//AfxMessageBox(m_NoteTime+L"\n20201210160000");
		if (strCurTime == m_NoteTime)
		{
			KillTimer(1);
			//AfxMessageBox(L"到了！");
			if (m_HideFlag == L"1")
			{
				this->ShowWindow(SW_SHOW);
				m_HideFlag = L"0";
			}
			m_NoticeFlag  = L"0";
			m_NoteTime = L"lc2020120379lc";
		}
	}
 	
 	CDialogEx::OnTimer(nIDEvent);
}


