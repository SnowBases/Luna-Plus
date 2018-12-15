// MainFrm.h : CMainFrame Ŭ������ �������̽�
//
#pragma once

#include "CoolDialogBar.h"

#include "MHFileMng.h"
#include "MHFileEx.h"

#include "NewPackingToolDoc.h"
#include "NewPackingToolView.h"

#include "FileListDlg.h"
#include "OutPutDlg.h"


#define SNAP_WIDTH 120 //the width of the combo box
#define IDC_SNAP_COMBO 90001

class CMainToolBar : public CToolBar 
{
public:
	CComboBox m_wndSnap;
};


class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư��
protected:
	//CSplitterWnd m_wndSplitter;
public:

// �۾�
public:

// ������
public:
	//virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CStatusBar		m_wndStatusBar;
	CMainToolBar    m_wndToolBar;
	//CReBar		m_wndReBar;
	//CDialogBar	m_wndDlgBar;

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL DestroyWindow();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnUseAES();
	afx_msg void OnScriptTest();

	void	ChangeFile(int index, LPCTSTR filename);
	void	AddFile(LPCTSTR filename);
	void	SelChange(int index);
	void	MoveLine(int line);

	void	ResetOutStr();
	void	AddOutStr(LPCTSTR str);

	int		GetCurIndex();

public:
	bool			m_bUseAES;
	CFileListDlg	m_cFileListDlg;
	CCoolDialogBar	m_wndFileListBar;

	COutPutDlg		m_cOutPutDlg;
	CCoolDialogBar	m_wndOutPutBar;

	int				m_ReservationViewIndex;
};

inline int CMainFrame::GetCurIndex()
{
	CNewPackingToolView* pView = (CNewPackingToolView*)this->GetActiveView();

	return pView->GetCurIndex();
}