#pragma once
#include "afxwin.h"


// COutPutDlg ��ȭ �����Դϴ�.

class COutPutDlg : public CDialog
{
	DECLARE_DYNAMIC(COutPutDlg)

public:
	COutPutDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~COutPutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OUTPUT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void MoveLine();
	afx_msg void OnScriptTest();

	void Reset();
	void AddOutStr(LPCTSTR str);

public:
	BOOL		m_bInit;
	CEdit		m_cOutput;

	CString		m_strOut;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
