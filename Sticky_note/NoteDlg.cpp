// NoteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sticky_note.h"
#include "NoteDlg.h"
#include "afxdialogex.h"
#include "SetTitleDlg.h"
#include "NoteDateSet.h"

/****************************�Զ������******************************/
int numOfNote = -1;//��ʾnote���±꣬��Ϊ-1ʱ��ʾ��note�Ѿ���ɾ����û����

/****************************ʹ���ⲿ����******************************/
extern CNoteDlg * myNoteList[MAXNOTE];
extern int noteCount;

// CNoteDlg �Ի���

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


// CNoteDlg ��Ϣ�������


void CNoteDlg::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	delete this;
	CDialogEx::PostNcDestroy();
}

/***********************��������������**************************/
void CNoteDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

/***********************���ڱ�������������**************************/
	GetClientRect(&m_rect); //��ȡ�Ի���Ĵ�С

/***************************��ݼ�����**********************/
	hotKey=::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MENU1));


/***********************��ʼ�����ڱ���**************************/
	CString strCurTime; //��ȡϵͳʱ�� ����
	CTime curTime;
	curTime=CTime::GetCurrentTime();
	strCurTime=curTime.Format("%A,%b, %d,%Y ");
	SetWindowTextW(strCurTime);

/***********************��ʼ������**************************/
	m_NoticeFlag = L"0";
	m_NoteTime = L"lc2020120379lc";
	m_HideFlag = L"0";
	m_BGColor  = RGB(255, 255, 0);
	m_TxtColor = RGB(0, 0, 0);
	m_NoteTitle = strCurTime;



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/***********************��������ɫ�ı�**************************/
HBRUSH CNoteDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
	{
		pDC->SetTextColor(m_TxtColor);
		pDC->SetBkColor(m_BGColor);
		hbr = ::CreateSolidBrush(m_BGColor);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

/***********************��д������Ϣ**************************/
BOOL CNoteDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	/***************************��ݼ�����**********************/
	if(::TranslateAccelerator(GetSafeHwnd(),hotKey,pMsg))
		return   true;

	/***************************�ػ�����Ҽ���Ϣ**********************/
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

/***********************��ǩ������ɫ**************************/
void CNoteDlg::OnChangeNoteBGC()
{
	// TODO: �ڴ���������������
	CColorDialog colorDialog;
	if( colorDialog.DoModal() == IDOK )
	{
		m_BGColor = colorDialog.GetColor();
	}
}

/***********************��ǩ�ı���ɫ**************************/
void CNoteDlg::OnChangeTxtC()
{
	// TODO: �ڴ���������������
	CColorDialog colorDialog;
	if( colorDialog.DoModal() == IDOK )
	{
		m_TxtColor = colorDialog.GetColor();
	}

}

/***********************���ñ�ǩ����**************************/
void CNoteDlg::OnSetNoteTitle()
{
	// TODO: �ڴ���������������
	SetTitleDlg setTitleDlg;
	setTitleDlg.DoModal();
}

/***********************���ر�ǩ**************************/
void CNoteDlg::OnHideThisNote()
{
	// TODO: �ڴ���������������
	this->m_HideFlag = L"1";
	this->ShowWindow(SW_HIDE);

}

/***********************ɾ����ǩ**************************/
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

/***********************����ʱ��**************************/
void CNoteDlg::OnSetNoteDate()
{
	// TODO: �ڴ���������������
	CString preNoticeFlag = m_NoticeFlag;

	NoteDateSet myNoteDateSetDlg;
	if (myNoteDateSetDlg.DoModal() == IDOK)
	{
		//AfxMessageBox(L"����1�Ŷ�ʱ��");
		if (preNoticeFlag == L"1")
		{
			KillTimer(1);
		}
		SetTimer(1, 1000, NULL);

	}
}

/***********************����**************************/
void CNoteDlg::OnNoteCX()
{
	// TODO: �ڴ���������������
	m_NoteEdit.Undo();
}

/***********************����**************************/
void CNoteDlg::OnNoteJQ()
{
	// TODO: �ڴ���������������
	m_NoteEdit.Cut();
}

/***********************����**************************/
void CNoteDlg::OnNoteFZ()
{
	// TODO: �ڴ���������������
	m_NoteEdit.Copy();
}

/***********************ճ��**************************/
void CNoteDlg::OnNoteZT()
{
	// TODO: �ڴ���������������
	m_NoteEdit.Paste();
}

/***********************ȫѡ**************************/
void CNoteDlg::OnNoteSelAll()
{
	// TODO: �ڴ���������������
	m_NoteEdit.SetSel(0, -1);

}

/***********************��ʱ����**************************/
void CNoteDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
			//AfxMessageBox(L"���ˣ�");
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


