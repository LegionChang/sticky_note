// NoteDateSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sticky_note.h"
#include "NoteDateSet.h"
#include "afxdialogex.h"
#include "NoteDlg.h"


// NoteDateSet �Ի���

IMPLEMENT_DYNAMIC(NoteDateSet, CDialogEx)

NoteDateSet::NoteDateSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(NoteDateSet::IDD, pParent)
{

}

NoteDateSet::~NoteDateSet()
{
}

void NoteDateSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DTP_DATE, m_NoteDate);
	DDX_Control(pDX, IDC_DTP_TIME, m_NoteTime);
}


BEGIN_MESSAGE_MAP(NoteDateSet, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_POP, &NoteDateSet::OnBnClickedChkPop)
	ON_BN_CLICKED(IDC_BUTTON2, &NoteDateSet::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &NoteDateSet::OnBnClickedButton1)
END_MESSAGE_MAP()


// NoteDateSet ��Ϣ�������


BOOL NoteDateSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_DTP_DATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DTP_TIME)->EnableWindow(FALSE);

	CNoteDlg * pParentNote = (CNoteDlg *)GetParent();
	if (pParentNote->m_NoticeFlag == L"1")
	{
		((CButton *)GetDlgItem(IDC_CHK_POP))->SetCheck(BST_CHECKED);
		GetDlgItem(IDC_DTP_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_DTP_TIME)->EnableWindow(TRUE);

		DWORD year, month, date, hours, minutes, seconds;
		_stscanf(pParentNote->m_NoteTime,L"%4d%2d%2d%2d%2d%2d",&year, &month, &date, &hours, &minutes, &seconds);

		//CString sreadTime;
		CTime readTime(year, month, date, hours, minutes, seconds);
		//sreadTime = readTime.Format("%Y%m%d%H%M%S");
		//AfxMessageBox(L"����ǰ��" + sreadTime);
		
		m_NoteDate.SetTime(&readTime);
		m_NoteTime.SetTime(&readTime);

		//sreadTime = readTime.Format("%Y%m%d%H%M%S");
		//AfxMessageBox(L"���ú�" + sreadTime);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void NoteDateSet::OnBnClickedChkPop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( ((CButton *)GetDlgItem(IDC_CHK_POP))->GetCheck() == BST_CHECKED )
	{
		GetDlgItem(IDC_DTP_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_DTP_TIME)->EnableWindow(TRUE);
	}
	
}

//ȷ��
void NoteDateSet::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CNoteDlg * pParentNote = (CNoteDlg *)GetParent();

	CTime noteDate, noteTime;
	m_NoteDate.GetTime(noteDate);
	m_NoteTime.GetTime(noteTime);
	CString strDate = noteDate.Format(L"%Y%m%d");
	CString strTime = noteTime.Format(L"%H%M%S");
	pParentNote->m_NoteTime = strDate + strTime;

	if (pParentNote->m_NoticeFlag != L"1")//û���ù�����
	{
		if ( ((CButton *)GetDlgItem(IDC_CHK_POP))->GetCheck() == BST_CHECKED )
		{
			pParentNote->m_NoticeFlag = L"1";
			CDialogEx::OnOK();
		} else {
			this->SendMessage(WM_CLOSE);
		}
	} else {//���ù�������
		CDialogEx::OnOK();
	}
}

//ȡ��
void NoteDateSet::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->SendMessage(WM_CLOSE);
}



