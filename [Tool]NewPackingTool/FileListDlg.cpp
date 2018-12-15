// FileListDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NewPackingTool.h"
#include "FileListDlg.h"
#include ".\filelistdlg.h"

#include "MainFrm.h"

// CFileListDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CFileListDlg, CDialog)
CFileListDlg::CFileListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileListDlg::IDD, pParent), m_bInit(FALSE)
{
}

CFileListDlg::~CFileListDlg()
{
}

void CFileListDlg::ResetAll()
{
	int nColumnCount = m_cFileList.GetItemCount();

	int i;
	for (i=0; i<nColumnCount; ++i)
	{
		stFileListItem* item = (stFileListItem*)(m_cFileList.GetItemData(i));

		delete item;
	}
}

void CFileListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILELIST, m_cFileList);
}


BEGIN_MESSAGE_MAP(CFileListDlg, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FILELIST, OnLvnItemchangedFilelist)
	ON_COMMAND(ID_SCRIPT_TEST, OnScriptTest)
END_MESSAGE_MAP()


// CFileListDlg �޽��� ó�����Դϴ�.

BOOL CFileListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bInit = TRUE;

	CRect sz;
	GetClientRect(sz);
	sz.DeflateRect(7,6);

	m_cFileList.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	m_cFileList.InsertColumn(0, _T("FileNameList"), LVCFMT_LEFT,sz.Width());

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CFileListDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (!m_bInit)
		return;

	CRect sz;
	GetClientRect(sz);
	sz.DeflateRect(5,5);

	m_cFileList.MoveWindow(sz);
}

void CFileListDlg::UpdateList()
{

}

int CFileListDlg::AddFile(LPCTSTR filename)
{
	if (m_cFileList.GetItemCount() > 0)
	{
		static CMainFrame*  pFrame = (CMainFrame*)AfxGetMainWnd();
		CNewPackingToolView* pView = (CNewPackingToolView*)pFrame->GetActiveView();

		SaveEditStats (pView->m_curIndex, pView);
	}

	int nColumnCount = m_cFileList.GetItemCount();

	m_cFileList.InsertItem(nColumnCount, filename);
	
	stFileListItem* item = new stFileListItem;
	m_cFileList.SetItemData(nColumnCount, (DWORD_PTR)(item));

	m_cFileList.SetItemState( nColumnCount, LVIS_SELECTED, LVIS_SELECTED );    // ȸ�� ��
	m_cFileList.EnsureVisible( nColumnCount, FALSE );                          // ��ũ��

	UpdateList();

	return nColumnCount;
}

BOOL CFileListDlg::ChangeFile(int index, LPCTSTR filename)
{
	if (m_cFileList.GetItemCount() <= index)
		return FALSE;

	m_cFileList.SetItemText(index, 0, filename);

	return TRUE;
}

void CFileListDlg::OnLvnItemchangedFilelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if ( pNMLV->uNewState != (LVIS_SELECTED | LVIS_FOCUSED) )
		return;

	//if ( pNMLV->uChanged != LVIF_STATE) 
	//	return;

	int nSelectItem = pNMLV->iItem;

	if (-1 == nSelectItem)
		return;
    
	CMainFrame*  pFrame = (CMainFrame*)AfxGetMainWnd();
	CNewPackingToolView* pView = (CNewPackingToolView*)pFrame->GetActiveView();

	SaveEditStats (pView->m_curIndex, pView);

	pFrame->SelChange(nSelectItem);

	LoadEditStats (nSelectItem, pView);

	*pResult = 0;
}

void CFileListDlg::SaveEditStats(int index, CEditView* pView)
{
	if (index < 0)
		return;

	ASSERT(index < m_cFileList.GetItemCount());

	stFileListItem* item = (stFileListItem*)(m_cFileList.GetItemData(index));
	item->modify = pView->GetEditCtrl().GetModify();
	item->curPos = pView->GetEditCtrl().GetSel();
}

void CFileListDlg::LoadEditStats(int index, CEditView* pView)
{
	ASSERT(index < m_cFileList.GetItemCount());

	stFileListItem* item = (stFileListItem*)(m_cFileList.GetItemData(index));
	pView->GetEditCtrl().SetModify(item->modify);
	pView->GetEditCtrl().SetSel(item->curPos);
}

void CFileListDlg::OnScriptTest()
{
	static CMainFrame*  pFrame = (CMainFrame*)AfxGetMainWnd();

	pFrame->OnScriptTest();
}