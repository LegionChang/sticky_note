// SetTitleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Sticky_note.h"
#include "SetTitleDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "NoteDlg.h"

// SetTitleDlg 对话框

IMPLEMENT_DYNAMIC(SetTitleDlg, CDialogEx)

SetTitleDlg::SetTitleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetTitleDlg::IDD, pParent)
{

}

SetTitleDlg::~SetTitleDlg()
{
}

void SetTitleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SetTitleDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SetTitleDlg::OnBnClickedOk)
END_MESSAGE_MAP()



void SetTitleDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* pSetTitleEdit;
	pSetTitleEdit = (CEdit*) GetDlgItem(IDC_EDIT1);
	CString str;
	pSetTitleEdit-> GetWindowText(str);
	this->GetParent()->SetWindowText(str);
	CNoteDlg * pParentNote = (CNoteDlg *)GetParent();
	pParentNote->m_NoteTitle = str;
	str.ReleaseBuffer();
	CDialogEx::OnOK();
}
