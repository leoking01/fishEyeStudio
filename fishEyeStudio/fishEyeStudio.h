
// fishEyeStudio.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CfishEyeStudioApp: 
// �йش����ʵ�֣������ fishEyeStudio.cpp
//

class CfishEyeStudioApp : public CWinApp
{
public:
	CfishEyeStudioApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CfishEyeStudioApp theApp;