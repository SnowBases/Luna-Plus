#pragma once
#include "afxcmn.h"

// CFileListDlg ��ȭ �����Դϴ�.
struct stFileListItem
{
	BOOL modify;
	int curPos;

	stFileListItem()
		: modify(FALSE), curPos(0)
	{
	}
};

class CFileListDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileListDlg)

public:
	CFileListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFileListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FILELIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	BOOL		m_bInit;
	CListCtrl	m_cFileList;

public:
	void			ResetAll();
	virtual BOOL	OnInitDialog();
	afx_msg void	OnSize(UINT nType, int cx, int cy);

	void			UpdateList();
	int				AddFile(LPCTSTR filename);
	BOOL			ChangeFile(int index, LPCTSTR filename);
	afx_msg void	OnLvnItemchangedFilelist(NMHDR *pNMHDR, LRESULT *pResult);

	void			SaveEditStats(int index, CEditView* pView);
	void			LoadEditStats(int index, CEditView* pView);

	afx_msg void	OnScriptTest();
};
