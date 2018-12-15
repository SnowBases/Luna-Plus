#pragma once

class CTooltipMsgConverter
{
	// 100312 ShinJS --- ToolTipMsg ����� ����
	std::map< DWORD, int > m_mapToolTipMsgKeyWord;

public:
	CTooltipMsgConverter(void);
	~CTooltipMsgConverter(void);

	// 100315 ShinJS --- ��밡�� ���Ÿ�Կ� ���� Msg ��ȯ
	const char* GetSkillEquipTypeText( const ACTIVE_SKILL_INFO* const pActiveSkillInfo, char* msg, size_t msgSize );
	const char* GetSkillWeaponTypeText( const BUFF_SKILL_INFO* const pBuffSkillInfo, char* msg, size_t msgSize  );
	const char* GetSkillArmorTypeText( const BUFF_SKILL_INFO* const pBuffSkillInfo, char* msg, size_t msgSize  );

	// 100316 ShinJS --- �Ҹ�����Ʈ�� ���� Msg ��ȯ
	const char* GetConsumePointTypeText( const ACTIVE_SKILL_INFO* const pActiveSkillInfo, char* msg, size_t msgSize  );

	// 100315 ShinJS --- ���� ���ǿ� ���� Msg ��ȯ
	const char* GetBuffConditionTypeText( const BUFF_SKILL_INFO* const pBuffSkillInfo, char* msg, size_t msgSize  );
	const char* GetBuffCountTypeText( const BUFF_SKILL_INFO* const pBuffSkillInfo, char* msg, size_t msgSize , const int nCurrentCount=0 );


	// 100312 ShinJS --- ToolTipMsg ����� ��ȯ �߰�
	// �������ڿ����̺� ������ �ʱ�ȭ�Ѵ�.
	void InitToolTipMsgKeyWordTable();
	// ���ڿ����� �������� ã�´�.
	BOOL GetToolTipMsgKeyWordFromText( std::string& strMsg, std::string& keyword, std::string::size_type& keywordStart, std::string::size_type& keywordSize );
	// ���������Type���κ��� ��ȯ�� ���ڿ��� ��ȯ�Ѵ�.
	const char* GetTextFromToolTipMsgKeyWordType( DWORD& dwToolTipIndex, int keywordType, char* txt, size_t txtSize, int prevKeyWordType = 0 );
	// Script���ڿ����� �������� ��ȯ�Ѵ�.
	void ConvertToolTipMsgKeyWordFormText( DWORD dwToolTipIndex, std::string& strMsg, std::string::size_type startPos = 0, int prevKeyWordType = 0 );
};
