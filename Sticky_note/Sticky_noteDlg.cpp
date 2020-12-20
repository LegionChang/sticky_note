
// Sticky_noteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sticky_note.h"
#include "Sticky_noteDlg.h"
#include "afxdialogex.h"
#include "NoteDlg.h"


/****************************�Զ������******************************/
CNoteDlg * myNoteList[MAXNOTE];
int noteCount;
CString iniFilePath = L"..\\Debug\\MyNote.ini";
/****************************�Զ��庯��******************************/
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


// CSticky_noteDlg ��Ϣ�������



BOOL CSticky_noteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	/********************************����ϵͳ����**************************/
	NotifyIcon.cbSize=sizeof(NOTIFYICONDATA);
	NotifyIcon.hIcon=m_hIcon;
	NotifyIcon.hWnd=m_hWnd;
	lstrcpy(NotifyIcon.szTip,_T("������"));
	NotifyIcon.uCallbackMessage=WM_SYSTEMTRAY;
	NotifyIcon.uFlags=NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD,&NotifyIcon);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	/************�����Ժ���Ҫ���ļ��ж�ȡ��Ȼ��ֵ**************/
	noteCount = 0;
	readNoteInfo(this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSticky_noteDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

		CDialogEx::OnSysCommand(nID, lParam);

} 

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSticky_noteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSticky_noteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*********************ϵͳ������Ӧ����**************************/
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

/*********************�½�һ��������**************************/
void CSticky_noteDlg::OnAddNewNote()
{
	// TODO: �ڴ���������������
	CNoteDlg * pNoteDlg = new CNoteDlg;
	pNoteDlg->Create(IDD_NOTE, this);
	pNoteDlg->ShowWindow(SW_SHOW);
	myNoteList[noteCount] = pNoteDlg;
	noteCount++;
	
}

/*********************ɾ�����б�����**************************/
void CSticky_noteDlg::OnDelAllNote()
{
	// TODO: �ڴ���������������
	for (int i=0; i<noteCount; ++i)
	{
		myNoteList[i]->SendMessage(WM_CLOSE);
		myNoteList[i] = NULL;
	}
	noteCount = 0;
}

/*********************��ʾ���б�����**************************/
void CSticky_noteDlg::OnShowAllNote()
{
	// TODO: �ڴ���������������
	for (int i=0; i<noteCount; ++i)
	{
		if (myNoteList[i]->m_HideFlag == L"1")
		{
			myNoteList[i]->ShowWindow(SW_SHOW);
			myNoteList[i]->m_HideFlag = L"0";
		}
	}
}

/*********************����**************************/
void CSticky_noteDlg::Onmyhelp()
{
	// TODO: �ڴ���������������
}

/*********************����**************************/
void CSticky_noteDlg::Onmyabout()
{
	// TODO: �ڴ���������������
	MessageBox(L"���򣺱�����\n���ߣ�����\n��λ�����������ѧ", L"����");
}

/*********************�˳�**************************/
void CSticky_noteDlg::Onmyexit()
{
	// TODO: �ڴ���������������
	DeleteFile(iniFilePath);

	CString totalCount;
	totalCount.Format(L"%d", noteCount);
	WritePrivateProfileString(L"��ǩ��Ŀ", L"��ǩ��", totalCount, iniFilePath);

	for (int i=0; i<noteCount; ++i)
	{
		saveNoteInfo(i, myNoteList[i]);
	}
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

/*********************����һ����ǩ��ini�ļ�**************************/
void saveNoteInfo(int noteNum, CNoteDlg * pNote)
{
	CString noteNo;
	noteNo.Format(L"��ǩ%d", noteNum);

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

	WritePrivateProfileString(noteNo, L"����",		pNote->m_NoteContent,	iniFilePath);
	WritePrivateProfileString(noteNo, L"����",		pNote->m_NoticeFlag,	iniFilePath);
	WritePrivateProfileString(noteNo, L"ʱ��",		pNote->m_NoteTime,		iniFilePath);
	WritePrivateProfileString(noteNo, L"����",		pNote->m_HideFlag,		iniFilePath);
	WritePrivateProfileString(noteNo, L"λ��",		pNote->m_NotePos,		iniFilePath);
	WritePrivateProfileString(noteNo, L"������ɫ",	noteBGC,				iniFilePath);
	WritePrivateProfileString(noteNo, L"������ɫ",	noteTxtC,				iniFilePath);
	WritePrivateProfileString(noteNo, L"����",		pNote->m_NoteTitle,		iniFilePath);

}

/**************************��ȡ��ǩ******************************/
void readNoteInfo(CSticky_noteDlg * curWindow)
{
	CString noteNo;
	CString totalNoteNum;
	GetPrivateProfileString(L"��ǩ��Ŀ", L"��ǩ��", L"", totalNoteNum.GetBuffer(255), 255, iniFilePath);
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
		readNoteNo.Format(L"��ǩ%d", i);

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

		GetPrivateProfileString(readNoteNo, L"����", L"", readNoteContent.GetBuffer(255), 255, iniFilePath);
		readNoteContent.ReleaseBuffer();
		pNoteDlg->m_NoteContent = readNoteContent;
		pNoteDlg->GetDlgItem(IDC_EDIT1)->SetWindowText(myNoteList[i]->m_NoteContent);

		GetPrivateProfileString(readNoteNo, L"����", L"", readNoticeFlag.GetBuffer(255), 255, iniFilePath);
		readNoticeFlag.ReleaseBuffer();
		pNoteDlg->m_NoticeFlag = readNoticeFlag;

		GetPrivateProfileString(readNoteNo, L"ʱ��", L"", readNoteTime.GetBuffer(255), 255, iniFilePath);
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

		GetPrivateProfileString(readNoteNo, L"����", L"", readHideFlag.GetBuffer(255), 255, iniFilePath);
		readHideFlag.ReleaseBuffer();
		pNoteDlg->m_HideFlag = readHideFlag;
		if (pNoteDlg->m_HideFlag == L"1")
		{
			pNoteDlg->ShowWindow(SW_HIDE);
		} else {
			pNoteDlg->ShowWindow(SW_SHOW);
		}

		GetPrivateProfileString(readNoteNo, L"λ��", L"", readNotePos.GetBuffer(255), 255, iniFilePath);
		readNotePos.ReleaseBuffer();
		pNoteDlg->m_NotePos = readNotePos;
		int noteLight, noteTop, noteWidth, noteHight;
		_stscanf(pNoteDlg->m_NotePos,L"%4d,%4d,%4d,%4d",&noteLight, &noteTop, &noteWidth, &noteHight);
		pNoteDlg->SetWindowPos(NULL, noteLight, noteTop, noteWidth, noteHight, NULL);


		GetPrivateProfileString(readNoteNo, L"������ɫ", L"", s_readBGColor.GetBuffer(255), 255, iniFilePath);
		s_readBGColor.ReleaseBuffer();
		DWORD noteRed,noteGreen,noteBlue;
		_stscanf(s_readBGColor,L"%3d,%3d,%3d",&noteRed,&noteGreen,&noteBlue);
		COLORREF bgColor = RGB(noteRed,noteGreen,noteBlue);
		pNoteDlg->m_BGColor = bgColor;


		GetPrivateProfileString(readNoteNo, L"������ɫ", L"", s_readTxtColor.GetBuffer(255), 255, iniFilePath);
		s_readTxtColor.ReleaseBuffer();
		DWORD textRed,textGreen,textBlue;
		_stscanf(s_readTxtColor,L"%3d,%3d,%3d",&textRed,&textGreen,&textBlue);
		COLORREF textBGColor = RGB(textRed,textGreen,textBlue);
		pNoteDlg->m_TxtColor = textBGColor;

		GetPrivateProfileString(readNoteNo, L"����", L"", readNoteTitle.GetBuffer(255), 255, iniFilePath);
		readNoteTitle.ReleaseBuffer();
		pNoteDlg->m_NoteTitle = readNoteTitle;
		pNoteDlg->SetWindowText(myNoteList[i]->m_NoteTitle);
	}
}


