#pragma once

#include <map>
#include <string>

extern "C"{
#include "./Lua/LuaLibrary/lua.h"
#include "./Lua/LuaLibrary/lualib.h"
#include "./Lua/LuaLibrary/lauxlib.h"
}

typedef int (*LuaGlueFuncType)(lua_State* pLuaState);

#define LuaGlue					extern "C" int
#define LuaGlueRegistType		std::map< std::string, LuaGlueFuncType >

class CSimpleLua
{
	const TCHAR* const m_LuaErrorFuncName;
	TCHAR m_FileName[MAX_PATH];
	BOOL m_bInit;
	BOOL m_bHasLuaErrorFunc;

	lua_State* m_LuaState;
    int m_nBaseStackNum;
	int m_nResultStackNum;
	int m_nParameterCnt;

	std::map< DWORD, std::string > m_mapLuaFuncList;
public:
	CSimpleLua(void);
	CSimpleLua(LPCTSTR filename);
	virtual ~CSimpleLua(void);

	BOOL InitLua();
	void Close();

	const lua_State* const GetLuaState() const { return m_LuaState; }

	// Lua Script Load
	BOOL Load( LPCTSTR filename );
	// Lua �Լ��� ���
	BOOL ExtractLuaFunc( LPCTSTR filename );

	LPCTSTR GetLuaScriptname() const { return m_FileName; }

    // �������� ������
	BOOL GetGlobalBoolean( LPCTSTR val, BOOL& boolean );
	BOOL GetGlobalBoolean( LPCTSTR val );
	BOOL GetGlobalNumber( LPCTSTR val, double& num );
	double GetGlobalNumber( LPCTSTR val );
	LPCTSTR GetGlobalString( LPCTSTR val );
	std::string GetGlobalStringWithSTLString( LPCTSTR val );
	LPCTSTR GetGlobalString( LPCTSTR val, LPTSTR str, size_t strLen );
	BOOL GetGlobalTableFieldNumber( LPCTSTR table, LPCTSTR field, double& num );
	double GetGlobalTableFieldNumber( LPCTSTR table, LPCTSTR field );
	LPCTSTR GetGlobalTableFieldString( LPCTSTR table, LPCTSTR field, LPTSTR str, size_t strLen );

    // Stack ���� �Լ�
	inline BOOL CheckStackToAdd( int nAddCnt=1 ) const;
	void ClearStack();
	BOOL AddNumberInStack( double num );
	BOOL AddNumberInStack( int num );
	BOOL AddStringInStack( LPCTSTR str );
	double GetNumberInStack( int nPos );
	LPCTSTR GetStringInStack( int nPos );
	BOOL IsNumberInStack( int nResultPos ) const;
	BOOL IsStringInStack( int nResultPos ) const;
	
	// lua_pcall ����(���ϰ��� ����)
	BOOL Execute( int nReturnCnt );

	// �Լ��̸�, ��������"%d%f%s", ����� ����, ����� ����"%d%f%s", ����/���....
	// ����� %s�� ��� ����� ����ҿ� �������ũ�⸦ �־����!
	BOOL ExecuteFunc( LPCTSTR func, LPCTSTR parameter, int nReturnCnt, LPCTSTR returnParameter, ... );

	// ��� ��ũ��Ʈ ���� �����ϴ� �Լ����� �Ǵ�
	BOOL IsLuaFuuc( LPCTSTR funcname ) const;
	BOOL HasResult() const { return m_nResultStackNum > 0; }

	// ��Ʊ۷��Լ� ���
	BOOL AddLuaGlueFunc( LuaGlueRegistType glueType );
	BOOL AddLuaGlueFunc( LPCTSTR glueFuncname, LuaGlueFuncType glueFunc );

	// LuaStack ������ �����â�� ���
	void OutputStackInfo();
};



#define SIMPLELUAMGR	CSimpleLuaManager::GetInstance()
class CSimpleLuaManager
{
	std::map< DWORD, CSimpleLua >	m_mapSimpleLua;
public:
	CSimpleLuaManager();
	~CSimpleLuaManager();
	
	static CSimpleLuaManager* GetInstance() { static CSimpleLuaManager mgr;		return &mgr; }

	BOOL CreateSimpleLua( LPCTSTR scriptname );
	BOOL RemoveSimpleLua( LPCTSTR scriptname );
	BOOL RemoveSimpleLua( DWORD dwHashCode );

	const size_t GetSimpleLuaCount() const { return m_mapSimpleLua.size(); }
	BOOL IsAdded( DWORD dwHashCode ) const;
	BOOL IsAdded( LPCTSTR scriptname ) const;
	CSimpleLua& GetSimpleLua( LPCTSTR name );
	CSimpleLua& GetSimpleLua( DWORD dwHashCode );

	DWORD GetSimpleLuaIndex( LPCTSTR scriptname ) const { return GetHashCodeFromTxt( scriptname ); }
	LPCTSTR GetSimpleLuaScriptname( DWORD dwHashCode );
};