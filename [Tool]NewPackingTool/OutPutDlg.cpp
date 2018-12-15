// OutPutDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NewPackingTool.h"
#include "OutPutDlg.h"
#include ".\outputdlg.h"

#include "ScriptTestStr.h"
#include "MainFrm.h"
#include "NewPackingToolView.h"

// COutPutDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(COutPutDlg, CDialog)
COutPutDlg::COutPutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COutPutDlg::IDD, pParent), m_bInit(FALSE), m_strOut(_T(""))
{
}

COutPutDlg::~COutPutDlg()
{
}

void COutPutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTPUT_EDIT, m_cOutput);
	DDX_Text(pDX, IDC_OUTPUT_EDIT, m_strOut);
}


BEGIN_MESSAGE_MAP(COutPutDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND(ID_SCRIPT_TEST, OnScriptTest)
	//ON_NOTIFY(NM_DBLCLK, IDC_OUTPUT_EDIT, OnLButtonDblClk);
END_MESSAGE_MAP()


// COutPutDlg �޽��� ó�����Դϴ�.

BOOL COutPutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bInit = TRUE;

	m_strOut += "////////////////////////////////////////////////////////////////////////////\r\n\r\n";
	m_strOut += "   Hello!! New Packing Tool by Iros.\r\n\r\n";
	m_strOut += "////////////////////////////////////////////////////////////////////////////\r\n\r\n";

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void COutPutDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (!m_bInit)
		return;

	CRect sz;
	GetClientRect(sz);
	sz.DeflateRect(5,5);

	m_cOutput.MoveWindow(sz);
}

void COutPutDlg::Reset()
{
	m_strOut = _T("");

	UpdateData(FALSE);
}

void COutPutDlg::AddOutStr(LPCTSTR str)
{
	m_strOut += str;

	UpdateData(FALSE);

	m_cOutput.SetSel(-2,-1); 
}

void COutPutDlg::MoveLine()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int nCurLine = m_cOutput.LineFromChar();

	TCHAR str[1024];
	int len = m_cOutput.LineLength(m_cOutput.LineIndex(nCurLine));

	if (len == 0)
		return;

	m_cOutput.GetLine(nCurLine, str, len);


	TCHAR *token;
	token = strtok( str, g_seps );

	while (token != NULL)
	{
		if (_tcsstr(str, _T("line#")))
		{
			token = strtok( NULL, g_seps );
			if (token)
			{
				int moveLine = _ttoi(token);

				static CMainFrame*  pFrame = (CMainFrame*)AfxGetMainWnd();
				pFrame->MoveLine(moveLine);
			}

			return;
		}

		token = strtok( NULL, g_seps );
	}

	//CDialog::OnLButtonDblClk(nFlags, point);
}

BOOL COutPutDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if ( pMsg->message == WM_LBUTTONDBLCLK )
	{
		if (pMsg->hwnd == GetDlgItem(IDC_OUTPUT_EDIT)->m_hWnd)		
		{
			MoveLine();
		}
	}

	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		//TranslateAccelerator(pMsg);
		//OnScriptTest();
		// Translate the message using accelerator table
		/*ASSERT(m_hAccel);
		if (TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
		{
			return TRUE;
		}*/
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void COutPutDlg::OnScriptTest()
{
	static CMainFrame*  pFrame = (CMainFrame*)AfxGetMainWnd();

	pFrame->OnScriptTest();
}