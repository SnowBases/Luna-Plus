// stdafx.h : �� ������� �ʰ� ���� ����ϴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Windows ������� ���� ������ �ʴ� ������ ���ܽ�ŵ�ϴ�.
#endif

// �Ʒ� ������ �÷������� �켱�ϴ� �÷����� ������� �ϴ� ��� ���� ���Ǹ� �����Ͻʽÿ�.
// �ٸ� �÷����� ���Ǵ� �ش� ���� �ֽ� ������ MSDN�� �����Ͻʽÿ�.
#ifndef WINVER				// Windows 95 �� Windows NT 4 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define WINVER 0x0400		// Windows 98�� Windows 2000 ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_WINNT		// Windows NT 4 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_WINNT 0x0500		// Windows 98�� Windows 2000 ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif						

#ifndef _WIN32_WINDOWS		// Windows 98 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_WINDOWS 0x0410 // Windows Me ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_IE			// IE 4.0 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_IE 0x0400	// IE 5.0 ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ���
#include <afxext.h>         // MFC �ͽ��ټ�
#include <afxdisp.h>        // MFC Automation classes
#include <afxisapi.h>

#include <afxdtctl.h>		// Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC ����
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows ���� ��Ʈ�ѿ� ���� MFC ����
#endif // _AFX_NO_AFXCMN_SUPPORT

void OutputDebug( char* pMsg, ... );
void OutputFile( char* szFileName, char* pMsg, ... );

void ChangeLunaGameString( CString& strFilename );
CString GetChangedLunaGameString( CString strFilename );
void RemoveNotAvailibleFilename( CString& strFilename );
LPCWSTR MultiToWideChar( LPCTSTR string );
void OutputMessageBox( char* pMsg, ... );
DWORD GetHashCodeFromTxt( const char* txt );
void AddComma( char* pBuf );
char* AddComma( unsigned long long dwMoney );

//
#pragma warning( disable : 4267 )

// GameData
#include "../../4DyuchiGRX_common/typedef.h"
#include "../../4DyuchiGXGFunc/global.h"
#include "../../4DyuchiGRX_common/IExecutive.h"
#include "../../4DyuchiGRX_common/IRenderer.h"
#include "../../4DyuchiGRX_common/math.inl"


#include "../../[lib]yhlibrary/yhlibrary.h"
#include "../../[lib]yhlibrary/HashTable.h"
#include "../../[lib]yhlibrary/cLinkedList.h"
#include "../../[lib]yhlibrary/PtrList.h"
#include "../../[lib]yhlibrary/IndexGenerator.h"

#undef DEBUG
#undef ASSERT

DWORD gCurTime;

#include "../../[CC]Header/protocol.h"
#include "../../[CC]Header/CommonDefine.h"
#include "../../[CC]Header/CommonGameDefine.h"
#include "../../[CC]Header/CommonStruct.h"

#define _CLIENT_
#define _CLIENT_RESOURCE_FIELD_
#include "../../[CC]Header/GameResourceStruct.h"
#include "../../[CC]Header/ClientGameDefine.h"


#include <map>
#include <set>
#include <list>
#include <hash_map>
#include <hash_set>
#include <queue>
#include <string>

#include "MINIDUMP.h"
#include "./Lua/SimpleLua.h"
#include "./CxImage/ximage.h"