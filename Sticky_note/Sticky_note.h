
// Sticky_note.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSticky_noteApp:
// �йش����ʵ�֣������ Sticky_note.cpp
//

class CSticky_noteApp : public CWinApp
{
public:
	CSticky_noteApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSticky_noteApp theApp;