#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxtempl.h>
#include <afxmt.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls

#endif // _AFX_NO_AFXCMN_SUPPORT

#define STL_USING_ALL
#include "STL.h"
#include <winsock2.h>
#include <sys/stat.h>
#include <process.h>
#include <tchar.h>

#include "FtpProtocolCode.h"
#include "FtpClient.h"

// CxImage library: http://www.xdp.it/cximage.htm
//
// MFC���� ������ cximage599c_full_unicode ������ �ٿ�޾� CxImageMFCDLL ������Ʈ�� �������Ͽ� ����.
#include "CxImage/ximage.h"
#include "../[Lib]ZipArchive/ZipArchive.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

void PutLog( const TCHAR*, ... );


class CLog
{
public:
	CLog();
	~CLog();

	static const CLog& GetInstance();

	void Put( const TCHAR*, ... ) const;
};