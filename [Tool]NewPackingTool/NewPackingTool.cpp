// NewPackingTool.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "NewPackingTool.h"
#include "MainFrm.h"

#include "NewPackingToolDoc.h"
#include "NewPackingToolView.h"
#include ".\newpackingtool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNewPackingToolApp

BEGIN_MESSAGE_MAP(CNewPackingToolApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	//ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_SCRIPT_TEST, OnScriptTest)
END_MESSAGE_MAP()


// CNewPackingToolApp ����

CNewPackingToolApp::CNewPackingToolApp()
	: m_nTabCount(0), m_bTabFlag(FALSE)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CNewPackingToolApp ��ü�Դϴ�.

CNewPackingToolApp theApp;

// CNewPackingToolApp �ʱ�ȭ

BOOL CNewPackingToolApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControls()�� �ʿ��մϴ�. 
	// InitCommonControls()�� ������� ������ â�� ���� �� �����ϴ�.

	InitCommonControls();

	CWinApp::InitInstance();

	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.
	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	// ����, ������ â �� �� ������ ���� ������ �մϴ�.

	// @@@ �������α׷��� ���� �������� ã���� ����.
	// Path ����!

	CString ScriptTestPath;

	TCHAR Init_path[MAX_PATH];
	GetModuleFileName(NULL, Init_path, MAX_PATH);

	TCHAR strDir[_MAX_DIR];
	TCHAR strDrv[_MAX_DRIVE];

	_tsplitpath( Init_path, strDrv, strDir, NULL, NULL );

	ScriptTestPath = strDrv;
	ScriptTestPath += strDir;
	ScriptTestPath += _T("ScriptTest.xml");

	g_ScriptTest.LoadXml(ScriptTestPath);

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CNewPackingToolDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CNewPackingToolView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// ����ٿ� ������ ����� ����ġ�մϴ�. ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	// SDI ���� ���α׷������� ProcessShellCommand �Ŀ� �̷��� ȣ���� �߻��ؾ� �մϴ�.

	char cmd[MAX_PATH] = {0,};
	size_t nCmdLen = strlen( AfxGetApp()->m_lpCmdLine );
	if ( nCmdLen )
	{
		strcpy( cmd, AfxGetApp()->m_lpCmdLine+1 );
		cmd[nCmdLen-2] = 0;

		//OpenFile(cmd);

		//UpdateData( FALSE );
	}

	m_pMainWnd->DragAcceptFiles(TRUE);

	CMainFrame*  pFrame = (CMainFrame*)AfxGetMainWnd();
	CNewPackingToolView* pView   = (CNewPackingToolView*)pFrame->GetActiveView();
	CEdit*  pEdit   = &(pView->GetEditCtrl());

	const UINT max_uint_size = (UINT)-1;
	pEdit->SetLimitText( max_uint_size );

	return TRUE;
}



// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CNewPackingToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CNewPackingToolApp �޽��� ó����


BOOL CNewPackingToolApp::OnIdle(LONG lCount)
{
	static CMainFrame*  pFrame = (CMainFrame*)AfxGetMainWnd();  // ������
	static CStatusBar*  pStatusBar =  (CStatusBar*)pFrame->GetDescendantWindow(AFX_IDW_STATUS_BAR); // ���¹ٿ� ���� ������  
	//static CChildFrame* pChild;  // ���ϵ� �����ӿ� ���� ������
	static CNewPackingToolView*    pView;   // �信 ���� ������
	static CEdit*           pEdit;   // ����Ʈ ��Ʈ�ѿ� ���� ������

	static CString str;       
	static int posStart;     // Sel�� ���� ���� ��ġ
	static int posEnd;      // Sel�� �� ���� ��ġ
	static int posFirst;     // ������ ù ���� ��ġ
	static int posPrev;     // ���� ���� ��ġ, ���ڿ��� ���õ� ���
	// ���� �������� ������ �������� �˱����� �ʿ�  
	static int nCurLine;   // ���� ���� ��
	static int nCurCol;    // ���� �÷� ��
	static char buf[1024];

	int i;
	int n;

	//pChild  = (CChildFrame*)pFrame->GetActiveFrame();
	pView   = (CNewPackingToolView*)pFrame->GetActiveView();
	pEdit   = &(pView->GetEditCtrl());

	switch(lCount)
	{
	case 0:
	case 1:

		CWinApp::OnIdle(lCount);
		return TRUE;

	case 2:  // ���¹ٿ� ���� ���� �÷� ���� ǥ���Ѵ�.

		if (!pStatusBar) return TRUE;
		if (!pEdit)
		{
			str.Format("Ln ??, Col ??");
			pStatusBar->SetPaneText(1, str);

			return TRUE;
		}

		pEdit->GetSel(posStart, posEnd);
		if (posStart == posEnd)        // ���ڿ��� ���õ��� �ʾ�����...
		{
			posFirst = pEdit->LineIndex();
			nCurLine = pEdit->LineFromChar() + 1;
			nCurCol = posStart - posFirst + 1;
			posPrev = posStart;
		}
		else                                  // ���ڿ��� ���õ� ������
		{
			if (posStart < posPrev)    // ���� �������� ����������
			{
				nCurLine = pEdit->LineFromChar(posStart) + 1;
				posFirst = pEdit->LineIndex(nCurLine - 1);
				nCurCol = posStart - posFirst + 1;    // ���� �÷���
			}
			// ���� ���� ��ġ
			else     // ������ �������� ����������
			{
				nCurLine = pEdit->LineFromChar(posEnd) + 1;
				posFirst = pEdit->LineIndex(nCurLine - 1);
				nCurCol = posEnd - posFirst + 1;      // ���� �÷���
			}
			// �� ���� ��ġ
		}

		str.Format(_T("Ln %d, Col %d"), nCurLine, nCurCol);
		pStatusBar->SetPaneText(1, str);
		// ���¹ٿ� ���� ����, �÷� ǥ��
		return TRUE;

	case 3:     // �ڵ� �鿩����

		if (!pEdit) return TRUE;

		pEdit->GetSel(posStart, posEnd);
		posFirst = pEdit->LineIndex();

		if ((m_bTabFlag == TRUE) && (posStart == posFirst))
		{
			for(i = 0; i < m_nTabCount; i++)    // ���� ������ �� ����ŭ
			{                                               // ���� ä���.
				pEdit->ReplaceSel("\t");
			}
			m_nTabCount = 0;
			m_bTabFlag = FALSE;               // �ٽ� �÷��׸� ��������
		}
		else       // �� �÷��װ� �����̸� ���� ������ �о�ͼ�
		{           // ���� �� ���ڰ� �� �� ������ ����Ѵ�.
			n = pEdit->GetLine(pEdit->LineFromChar(), buf, 1024);
			i = 0;
			while(i < n && buf[i] == '\t') i++;

			m_nTabCount = i;
		}

		return TRUE;

	case 4:     // Ÿ��Ʋ�� '*' ǥ��

		if (!pEdit) return FALSE;

		if (pEdit->GetModify())       // ������ ����Ǿ����� 
		{
			str = pView->GetDocument()->GetTitle();
			if (str.Right(1) != '*')  // '*' ǥ�ð� �Ǿ����� ������
			{
				str += '*';
				pView->GetDocument()->SetTitle(str);
			}
		}

		return FALSE;   // �� �̻� Idle Ÿ�� �۾��� ����
	}

	return FALSE;


	//return CWinApp::OnIdle(lCount);
}

void CNewPackingToolApp::OnScriptTest()
{
	static CMainFrame*  pFrame = (CMainFrame*)AfxGetMainWnd();

	pFrame->OnScriptTest();
}