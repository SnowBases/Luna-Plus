// NewPackingTool.h : NewPackingTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"       // �� ��ȣ

#include "ScriptTest.h"
#include "ScriptTestStr.h"

// CNewPackingToolApp:
// �� Ŭ������ ������ ���ؼ��� NewPackingTool.cpp�� �����Ͻʽÿ�.
//

class CNewPackingToolApp : public CWinApp
{
public:
	CNewPackingToolApp();


// ������
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL	OnIdle(LONG lCount);
	afx_msg void	OnScriptTest();

public:
	int			m_nTabCount;
	BOOL		m_bTabFlag;
};

extern CNewPackingToolApp theApp;
