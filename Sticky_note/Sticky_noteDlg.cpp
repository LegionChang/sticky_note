
// Sticky_noteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Sticky_note.h"
#include "Sticky_noteDlg.h"
#include "afxdialogex.h"
#include "NoteDlg.h"


/****************************自定义参数******************************/
CNoteDlg * myNoteList[MAXNOTE];
int noteCount;
CString iniFilePath = L"..\\Debug\\MyNote.ini";
/****************************自定义函数******************************/
void saveNoteInfo(int noteNum, CNoteDlg * pNote);
void readNoteInfo(CSticky_noteDlg * curWindow);


CSticky_noteDlg::CSticky_noteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSticky_noteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSticky_noteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSticky_noteDlg, CDialogEx)
	ON_MESSAGE(WM_SYSTEMTRAY, &CSticky_noteDlg::OnSystemtray)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_Add_New_Note, &CSticky_noteDlg::OnAddNewNote)
	ON_COMMAND(ID_Del_All_Note, &CSticky_noteDlg::OnDelAllNote)
	ON_COMMAND(ID_Show_All_Note, &CSticky_noteDlg::OnShowAllNote)
	ON_COMMAND(ID_myHelp, &CSticky_noteDlg::Onmyhelp)
	ON_COMMAND(ID_myAbout, &CSticky_noteDlg::Onmyabout)
	ON_COMMAND(ID_myExit, &CSticky_noteDlg::Onmyexit)
END_MESSAGE_MAP()


// CSticky_noteDlg 消息处理程序



BOOL CSticky_noteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	/********************************设置系统托盘**************************/
	NotifyIcon.cbSize=sizeof(NOTIFYICONDATA);
	NotifyIcon.hIcon=m_hIcon;
	NotifyIcon.hWnd=m_hWnd;
	lstrcpy(NotifyIcon.szTip,_T("便利贴"));
	NotifyIcon.uCallbackMessage=WM_SYSTEMTRAY;
	NotifyIcon.uFlags=NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD,&NotifyIcon);

	// TODO: 在此添加额外的初始化代码

	/************这里以后需要从文件中读取，然后赋值**************/
	noteCount = 0;
	readNoteInfo(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSticky_noteDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

		CDialogEx::OnSysCommand(nID, lParam);

} 

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSticky_noteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSticky_noteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*********************系统托盘响应函数**************************/
afx_msg LRESULT CSticky_noteDlg::OnSystemtray(WPARAM wParam, LPARAM lParam)
{  
	switch(lParam)     
	{    
	case WM_LBUTTONDOWN:
	case  WM_RBUTTONDOWN:
		{       
			CMenu myTrayMenu;
			CPoint ptMouse;
			myTrayMenu.LoadMenu(IDR_MENU1);
			CMenu * pMyTrayMenu = myTrayMenu.GetSubMenu(0);
			GetCursorPos(&ptMouse);
			SetForegroundWindow();
			pMyTrayMenu->TrackPopupMenu(TPM_RIGHTBUTTON, ptMouse.x, ptMouse.y, this);	
 			myTrayMenu.DestroyMenu();
 			pMyTrayMenu->DestroyMenu();
		}
		break;
	} 
	return 0;
}

/*********************新建一个便利贴**************************/
void CSticky_noteDlg::OnAddNewNote()
{
	// TODO: 在此添加命令处理程序代码
	CNoteDlg * pNoteDlg = new CNoteDlg;
	pNoteDlg->Create(IDD_NOTE, this);
	pNoteDlg->ShowWindow(SW_SHOW);
	myNoteList[noteCount] = pNoteDlg;
	noteCount++;
	
}

/*********************删除所有便利贴**************************/
void CSticky_noteDlg::OnDelAllNote()
{
	// TODO: 在此添加命令处理程序代码
	for (int i=0; i<noteCount; ++i)
	{
		myNoteList[i]->SendMessage(WM_CLOSE);
		myNoteList[i] = NULL;
	}
	noteCount = 0;
}

/*********************显示所有便利贴**************************/
void CSticky_noteDlg::OnShowAllNote()
{
	// TODO: 在此添加命令处理程序代码
	for (int i=0; i<noteCount; ++i)
	{
		if (myNoteList[i]->m_HideFlag == L"1")
		{
			myNoteList[i]->ShowWindow(SW_SHOW);
			myNoteList[i]->m_HideFlag = L"0";
		}
	}
}

/*********************帮助**************************/
void CSticky_noteDlg::Onmyhelp()
{
	// TODO: 在此添加命令处理程序代码
}

/*********************关于**************************/
void CSticky_noteDlg::Onmyabout()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(L"程序：便利贴\n作者：刘畅\n单位：中南民族大学", L"关于");
}

/*********************退出**************************/
void CSticky_noteDlg::Onmyexit()
{
	// TODO: 在此添加命令处理程序代码
	DeleteFile(iniFilePath);

	CString totalCount;
	totalCount.Format(L"%d", noteCount);
	WritePrivateProfileString(L"便签数目", L"便签数", totalCount, iniFilePath);

	for (int i=0; i<noteCount; ++i)
	{
		saveNoteInfo(i, myNoteList[i]);
	}
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

/*********************导入一个便签到ini文件**************************/
void saveNoteInfo(int noteNum, CNoteDlg * pNote)
{
	CString noteNo;
	noteNo.Format(L"便签%d", noteNum);

	CRect noteRect;
	pNote->GetWindowRect(noteRect);
	CString notePos, noteContent;
	notePos.Format(L"%.4d,%.4d,%.4d,%.4d",noteRect.left, noteRect.top, noteRect.Width(), noteRect.Height());
	pNote->m_NotePos = notePos;
	pNote->GetDlgItem(IDC_EDIT1)->GetWindowText(noteContent);
	pNote->m_NoteContent = noteContent;

	CString noteBGC, noteTxtC;
	noteBGC.Format(L"%.3d,%.3d,%.3d", GetRValue(pNote->m_BGColor), GetGValue(pNote->m_BGColor), GetBValue(pNote->m_BGColor));
	noteTxtC.Format(L"%.3d,%.3d,%.3d", GetRValue(pNote->m_TxtColor), GetGValue(pNote->m_TxtColor), GetBValue(pNote->m_TxtColor));

	WritePrivateProfileString(noteNo, L"内容",		pNote->m_NoteContent,	iniFilePath);
	WritePrivateProfileString(noteNo, L"提醒",		pNote->m_NoticeFlag,	iniFilePath);
	WritePrivateProfileString(noteNo, L"时间",		pNote->m_NoteTime,		iniFilePath);
	WritePrivateProfileString(noteNo, L"隐藏",		pNote->m_HideFlag,		iniFilePath);
	WritePrivateProfileString(noteNo, L"位置",		pNote->m_NotePos,		iniFilePath);
	WritePrivateProfileString(noteNo, L"背景颜色",	noteBGC,				iniFilePath);
	WritePrivateProfileString(noteNo, L"字体颜色",	noteTxtC,				iniFilePath);
	WritePrivateProfileString(noteNo, L"标题",		pNote->m_NoteTitle,		iniFilePath);

}

/**************************读取便签******************************/
void readNoteInfo(CSticky_noteDlg * curWindow)
{
	CString noteNo;
	CString totalNoteNum;
	GetPrivateProfileString(L"便签数目", L"便签数", L"", totalNoteNum.GetBuffer(255), 255, iniFilePath);
	totalNoteNum.ReleaseBuffer();

	int intNoteNum = _ttoi(totalNoteNum);
	for (int i=0; i<intNoteNum; ++i)
	{
		CNoteDlg * pNoteDlg = new CNoteDlg;
		pNoteDlg->Create(IDD_NOTE, curWindow);
		pNoteDlg->ShowWindow(SW_HIDE);
		myNoteList[noteCount] = pNoteDlg;
		noteCount++;
		
		CString readNoteNo;
		readNoteNo.Format(L"便签%d", i);

		CString readNoteContent;
		CString readNoticeFlag;
		CString readNoteTime;
		CString readHideFlag;
		CString readNotePos;
		CString s_readBGColor;
		CString s_readTxtColor;
		CString readNoteTitle;	

		COLORREF clr_readBGColor;	
		COLORREF clr_readTxtColor;

		GetPrivateProfileString(readNoteNo, L"内容", L"", readNoteContent.GetBuffer(255), 255, iniFilePath);
		readNoteContent.ReleaseBuffer();
		pNoteDlg->m_NoteContent = readNoteContent;
		pNoteDlg->GetDlgItem(IDC_EDIT1)->SetWindowText(myNoteList[i]->m_NoteContent);

		GetPrivateProfileString(readNoteNo, L"提醒", L"", readNoticeFlag.GetBuffer(255), 255, iniFilePath);
		readNoticeFlag.ReleaseBuffer();
		pNoteDlg->m_NoticeFlag = readNoticeFlag;

		GetPrivateProfileString(readNoteNo, L"时间", L"", readNoteTime.GetBuffer(255), 255, iniFilePath);
		readNoteTime.ReleaseBuffer();
		pNoteDlg->m_NoteTime = readNoteTime;
		if (pNoteDlg->m_NoticeFlag == L"1")
		{
			CTime curTime = CTime::GetCurrentTime();
			CString strCurTime;
			strCurTime = curTime.Format("%Y%m%d%H%M%S");
			if (strCurTime < pNoteDlg->m_NoteTime)
			{
				pNoteDlg->SetTimer(1, 1000, NULL);
			} else {
				pNoteDlg->ShowWindow(SW_SHOW);
				pNoteDlg->m_HideFlag = L"0";
				pNoteDlg->m_NoticeFlag = L"0";
			}
		}

		GetPrivateProfileString(readNoteNo, L"隐藏", L"", readHideFlag.GetBuffer(255), 255, iniFilePath);
		readHideFlag.ReleaseBuffer();
		pNoteDlg->m_HideFlag = readHideFlag;
		if (pNoteDlg->m_HideFlag == L"1")
		{
			pNoteDlg->ShowWindow(SW_HIDE);
		} else {
			pNoteDlg->ShowWindow(SW_SHOW);
		}

		GetPrivateProfileString(readNoteNo, L"位置", L"", readNotePos.GetBuffer(255), 255, iniFilePath);
		readNotePos.ReleaseBuffer();
		pNoteDlg->m_NotePos = readNotePos;
		int noteLight, noteTop, noteWidth, noteHight;
		_stscanf(pNoteDlg->m_NotePos,L"%4d,%4d,%4d,%4d",&noteLight, &noteTop, &noteWidth, &noteHight);
		pNoteDlg->SetWindowPos(NULL, noteLight, noteTop, noteWidth, noteHight, NULL);


		GetPrivateProfileString(readNoteNo, L"背景颜色", L"", s_readBGColor.GetBuffer(255), 255, iniFilePath);
		s_readBGColor.ReleaseBuffer();
		DWORD noteRed,noteGreen,noteBlue;
		_stscanf(s_readBGColor,L"%3d,%3d,%3d",&noteRed,&noteGreen,&noteBlue);
		COLORREF bgColor = RGB(noteRed,noteGreen,noteBlue);
		pNoteDlg->m_BGColor = bgColor;


		GetPrivateProfileString(readNoteNo, L"字体颜色", L"", s_readTxtColor.GetBuffer(255), 255, iniFilePath);
		s_readTxtColor.ReleaseBuffer();
		DWORD textRed,textGreen,textBlue;
		_stscanf(s_readTxtColor,L"%3d,%3d,%3d",&textRed,&textGreen,&textBlue);
		COLORREF textBGColor = RGB(textRed,textGreen,textBlue);
		pNoteDlg->m_TxtColor = textBGColor;

		GetPrivateProfileString(readNoteNo, L"标题", L"", readNoteTitle.GetBuffer(255), 255, iniFilePath);
		readNoteTitle.ReleaseBuffer();
		pNoteDlg->m_NoteTitle = readNoteTitle;
		pNoteDlg->SetWindowText(myNoteList[i]->m_NoteTitle);
	}
}


