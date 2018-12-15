#include "StdAfx.h"
#include ".\tooltipmsgconverter.h"
#include "LunaGameDataExtracter.h"
#include "LunaGameDataExtracterDlg.h"


// 100312 ShinJS --- ToolTipMsg ����� Type
enum eToolTipMsgKeyWordType{
	eToolTipMsgKeyWordType_None = 0,

	// struct SKILL_INFO �� ����
	eToolTipMsgKeyWordType_Skill_Index,
	eToolTipMsgKeyWordType_Skill_Name,
	eToolTipMsgKeyWordType_Skill_Tooltip,
	eToolTipMsgKeyWordType_Skill_Image,
	eToolTipMsgKeyWordType_Skill_Kind,
	eToolTipMsgKeyWordType_Skill_Level,

	// struct ACTIVE_SKILL_INFO �� ����
	eToolTipMsgKeyWordType_ActiveSkill,
	eToolTipMsgKeyWordType_ActiveSkill_Money,
	eToolTipMsgKeyWordType_ActiveSkill_Life_Percent,
	eToolTipMsgKeyWordType_ActiveSkill_Life_Plus,
	eToolTipMsgKeyWordType_ActiveSkill_Mana_Percent,
	eToolTipMsgKeyWordType_ActiveSkill_Mana_Plus,
	eToolTipMsgKeyWordType_ActiveSkill_EquipType,
	eToolTipMsgKeyWordType_ActiveSkill_OperatorEffect,
	eToolTipMsgKeyWordType_ActiveSkill_TargetEffect,
	eToolTipMsgKeyWordType_ActiveSkill_SkillEffect,
	eToolTipMsgKeyWordType_ActiveSkill_AnimationTime,
	eToolTipMsgKeyWordType_ActiveSkill_CastingTime,
	eToolTipMsgKeyWordType_ActiveSkill_DelayType,
	eToolTipMsgKeyWordType_ActiveSkill_DelayTime,
	eToolTipMsgKeyWordType_ActiveSkill_CoolTime,
	eToolTipMsgKeyWordType_ActiveSkill_Target,
	eToolTipMsgKeyWordType_ActiveSkill_Range,
	eToolTipMsgKeyWordType_ActiveSkill_Area,
	eToolTipMsgKeyWordType_ActiveSkill_AreaTarget,
	eToolTipMsgKeyWordType_ActiveSkill_AreaData,
	eToolTipMsgKeyWordType_ActiveSkill_Unit,
	eToolTipMsgKeyWordType_ActiveSkill_UnitDataType,
	eToolTipMsgKeyWordType_ActiveSkill_UnitData,
	eToolTipMsgKeyWordType_ActiveSkill_Success,
	eToolTipMsgKeyWordType_ActiveSkill_Cancel,
	eToolTipMsgKeyWordType_ActiveSkill_TrainPoint,
	eToolTipMsgKeyWordType_ActiveSkill_TrainMoney,
	eToolTipMsgKeyWordType_ActiveSkill_Buff1,
	eToolTipMsgKeyWordType_ActiveSkill_Buff2,
	eToolTipMsgKeyWordType_ActiveSkill_Buff3,
	eToolTipMsgKeyWordType_ActiveSkill_Buff4,
	eToolTipMsgKeyWordType_ActiveSkill_Buff5,
	eToolTipMsgKeyWordType_ActiveSkill_BuffRate1,
	eToolTipMsgKeyWordType_ActiveSkill_BuffRate2,
	eToolTipMsgKeyWordType_ActiveSkill_BuffRate3,
	eToolTipMsgKeyWordType_ActiveSkill_BuffRate4,
	eToolTipMsgKeyWordType_ActiveSkill_BuffRate5,
	eToolTipMsgKeyWordType_ActiveSkill_RequiredBuff,
	eToolTipMsgKeyWordType_ActiveSkill_IsMove,
	eToolTipMsgKeyWordType_ActiveSkill_RequiredPlayerLevel,
	eToolTipMsgKeyWordType_ActiveSkill_ConsumeItemIndex,
	eToolTipMsgKeyWordType_ActiveSkill_ConsumeItemCount,
	eToolTipMsgKeyWordType_ActiveSkill_ConsumePointType,
	eToolTipMsgKeyWordType_ActiveSkill_ConsumePointValue,
	eToolTipMsgKeyWordType_ActiveSkill_IsBattle,
	eToolTipMsgKeyWordType_ActiveSkill_IsPeace,
	eToolTipMsgKeyWordType_ActiveSkill_mIsMove,
	eToolTipMsgKeyWordType_ActiveSkill_IsStop,

	// BUFF_SKILL_INFO �� ����
	eToolTipMsgKeyWordType_BuffSkill,
	eToolTipMsgKeyWordType_BuffSkill_Money,
	eToolTipMsgKeyWordType_BuffSkill_WeaponType,
	eToolTipMsgKeyWordType_BuffSkill_ArmorType,
	eToolTipMsgKeyWordType_BuffSkill_DelayTime,
	eToolTipMsgKeyWordType_BuffSkill_SkillEffect,
	eToolTipMsgKeyWordType_BuffSkill_Status,
	eToolTipMsgKeyWordType_BuffSkill_StatusDataType,
	eToolTipMsgKeyWordType_BuffSkill_StatusData,
	eToolTipMsgKeyWordType_BuffSkill_ConditonType,
	eToolTipMsgKeyWordType_BuffSkill_ConditionOperation,
	eToolTipMsgKeyWordType_BuffSkill_ConditionValue,
	eToolTipMsgKeyWordType_BuffSkill_Count,
	eToolTipMsgKeyWordType_BuffSkill_RuleBattle,
	eToolTipMsgKeyWordType_BuffSkill_RulePeace,
	eToolTipMsgKeyWordType_BuffSkill_RuleMove,
	eToolTipMsgKeyWordType_BuffSkill_RuleStop,
	eToolTipMsgKeyWordType_BuffSkill_RuleRest,
	eToolTipMsgKeyWordType_BuffSkill_Die,
	eToolTipMsgKeyWordType_BuffSkill_CountType,
	eToolTipMsgKeyWordType_BuffSkill_IsEndTime,
	eToolTipMsgKeyWordType_BuffSkill_EventSkillIndex,
	eToolTipMsgKeyWordType_BuffSkill_Item1,
	eToolTipMsgKeyWordType_BuffSkill_Item2,
	eToolTipMsgKeyWordType_BuffSkill_ItemCount1,
	eToolTipMsgKeyWordType_BuffSkill_ItemCount2,

	// ITEM_INFO �� ����
	eToolTipMsgKeyWordType_Item,
	eToolTipMsgKeyWordType_Item_Name,
};

// 100312 ShinJS --- ToolTipMsg ����� ����
struct stToolTipMsgKeyWordData{
	char* KeyWord;
	eToolTipMsgKeyWordType eType;
	DWORD dwHashCode;
};

// 100312 ShinJS --- ToolTipMsg ����� Table
stToolTipMsgKeyWordData ToolTipMsgKeyWordTable[] = {

	// struct SKILL_INFO �� ����
	{ "$Index$", eToolTipMsgKeyWordType_Skill_Index, 0 },
	{ "$Name$", eToolTipMsgKeyWordType_Skill_Name, 0 },
	{ "$Tooltip$", eToolTipMsgKeyWordType_Skill_Tooltip, 0 },
	{ "$Image$", eToolTipMsgKeyWordType_Skill_Image, 0 },
	{ "$Kind$", eToolTipMsgKeyWordType_Skill_Kind, 0 },
	{ "$Level$", eToolTipMsgKeyWordType_Skill_Level, 0 },

	// struct ACTIVE_SKILL_INFO �� ����
	{ "$Money$", eToolTipMsgKeyWordType_ActiveSkill_Money, 0 },
	{ "$LifePercent$", eToolTipMsgKeyWordType_ActiveSkill_Life_Percent, 0 },
	{ "$LifePlus$", eToolTipMsgKeyWordType_ActiveSkill_Life_Plus, 0 },
	{ "$ManaPercent$", eToolTipMsgKeyWordType_ActiveSkill_Mana_Percent, 0 },
	{ "$ManaPlus$", eToolTipMsgKeyWordType_ActiveSkill_Mana_Plus, 0 },
	{ "$EquipType$", eToolTipMsgKeyWordType_ActiveSkill_EquipType, 0 },
	{ "$OperatorEffect$", eToolTipMsgKeyWordType_ActiveSkill_OperatorEffect, 0 },
	{ "$TargetEffect$", eToolTipMsgKeyWordType_ActiveSkill_TargetEffect, 0 },
	{ "$SkillEffect$", eToolTipMsgKeyWordType_ActiveSkill_SkillEffect, 0 },
	{ "$AnimationTime$", eToolTipMsgKeyWordType_ActiveSkill_AnimationTime, 0 },
	{ "$CastingTime$", eToolTipMsgKeyWordType_ActiveSkill_CastingTime, 0 },
	{ "$DelayType$", eToolTipMsgKeyWordType_ActiveSkill_DelayType, 0 },
	{ "$DelayTime$", eToolTipMsgKeyWordType_ActiveSkill_DelayTime, 0 },
	{ "$CoolTime$", eToolTipMsgKeyWordType_ActiveSkill_CoolTime, 0 },
	{ "$Target$", eToolTipMsgKeyWordType_ActiveSkill_Target, 0 },
	{ "$Range$", eToolTipMsgKeyWordType_ActiveSkill_Range, 0 },
	{ "$Area$", eToolTipMsgKeyWordType_ActiveSkill_Area, 0 },
	{ "$AreaTarget$", eToolTipMsgKeyWordType_ActiveSkill_AreaTarget, 0 },
	{ "$AreaData$", eToolTipMsgKeyWordType_ActiveSkill_AreaData, 0 },
	{ "$Unit$", eToolTipMsgKeyWordType_ActiveSkill_Unit, 0 },
	{ "$UnitDataType$", eToolTipMsgKeyWordType_ActiveSkill_UnitDataType, 0 },
	{ "$UnitData$", eToolTipMsgKeyWordType_ActiveSkill_UnitData, 0 },
	{ "$Success$", eToolTipMsgKeyWordType_ActiveSkill_Success, 0 },
	{ "$Cancel$", eToolTipMsgKeyWordType_ActiveSkill_Cancel, 0 },
	{ "$TrainPoint$", eToolTipMsgKeyWordType_ActiveSkill_TrainPoint, 0 },
	{ "$TrainMoney$", eToolTipMsgKeyWordType_ActiveSkill_TrainMoney, 0 },
	{ "$Buff1$", eToolTipMsgKeyWordType_ActiveSkill_Buff1, 0 },
	{ "$Buff2$", eToolTipMsgKeyWordType_ActiveSkill_Buff2, 0 },
	{ "$Buff3$", eToolTipMsgKeyWordType_ActiveSkill_Buff3, 0 },
	{ "$Buff4$", eToolTipMsgKeyWordType_ActiveSkill_Buff4, 0 },
	{ "$Buff5$", eToolTipMsgKeyWordType_ActiveSkill_Buff5, 0 },
	{ "$BuffRate1$", eToolTipMsgKeyWordType_ActiveSkill_BuffRate1, 0 },
	{ "$BuffRate2$", eToolTipMsgKeyWordType_ActiveSkill_BuffRate2, 0 },
	{ "$BuffRate3$", eToolTipMsgKeyWordType_ActiveSkill_BuffRate3, 0 },
	{ "$BuffRate4$", eToolTipMsgKeyWordType_ActiveSkill_BuffRate4, 0 },
	{ "$BuffRate5$", eToolTipMsgKeyWordType_ActiveSkill_BuffRate5, 0 },
	{ "$RequiredBuff$", eToolTipMsgKeyWordType_ActiveSkill_RequiredBuff, 0 },
	{ "$IsMove$", eToolTipMsgKeyWordType_ActiveSkill_IsMove, 0 },
	{ "$RequiredPlayerLevel$", eToolTipMsgKeyWordType_ActiveSkill_RequiredPlayerLevel, 0 },
	{ "$ConsumeItemIndex$", eToolTipMsgKeyWordType_ActiveSkill_ConsumeItemIndex, 0 },
	{ "$ConsumeItemCount$", eToolTipMsgKeyWordType_ActiveSkill_ConsumeItemCount, 0 },
	{ "$ConsumePointType$", eToolTipMsgKeyWordType_ActiveSkill_ConsumePointType, 0 },
	{ "$ConsumePointValue$", eToolTipMsgKeyWordType_ActiveSkill_ConsumePointValue, 0 },
	{ "$IsBattle$", eToolTipMsgKeyWordType_ActiveSkill_IsBattle, 0 },
	{ "$IsPeace$", eToolTipMsgKeyWordType_ActiveSkill_IsPeace, 0 },
	{ "$mIsMove$", eToolTipMsgKeyWordType_ActiveSkill_mIsMove, 0 },
	{ "$IsStop$", eToolTipMsgKeyWordType_ActiveSkill_IsStop, 0 },

	// BUFF_SKILL_INFO �� ����
	{ "$BuffMoney$", eToolTipMsgKeyWordType_BuffSkill_Money, 0 },
	{ "$WeaponType$", eToolTipMsgKeyWordType_BuffSkill_WeaponType, 0 },
	{ "$ArmorType$", eToolTipMsgKeyWordType_BuffSkill_ArmorType, 0 },
	{ "$BuffDelayTime$", eToolTipMsgKeyWordType_BuffSkill_DelayTime, 0 },
	{ "$BuffSkillEffect$", eToolTipMsgKeyWordType_BuffSkill_SkillEffect, 0 },
	{ "$Status$", eToolTipMsgKeyWordType_BuffSkill_Status, 0 },
	{ "$StatusDataType$", eToolTipMsgKeyWordType_BuffSkill_StatusDataType, 0 },
	{ "$StatusData$", eToolTipMsgKeyWordType_BuffSkill_StatusData, 0 },
	{ "$ConditonType$", eToolTipMsgKeyWordType_BuffSkill_ConditonType, 0 },
	{ "$ConditionOperation$", eToolTipMsgKeyWordType_BuffSkill_ConditionOperation, 0 },
	{ "$ConditionValue$", eToolTipMsgKeyWordType_BuffSkill_ConditionValue, 0 },
	{ "$Count$", eToolTipMsgKeyWordType_BuffSkill_Count, 0 },
	{ "$RuleBattle$", eToolTipMsgKeyWordType_BuffSkill_RuleBattle, 0 },
	{ "$RulePeace$", eToolTipMsgKeyWordType_BuffSkill_RulePeace, 0 },
	{ "$RuleMove$", eToolTipMsgKeyWordType_BuffSkill_RuleMove, 0 },
	{ "$RuleStop$", eToolTipMsgKeyWordType_BuffSkill_RuleStop, 0 },
	{ "$RuleRest$", eToolTipMsgKeyWordType_BuffSkill_RuleRest, 0 },
	{ "$Die$", eToolTipMsgKeyWordType_BuffSkill_Die, 0 },
	{ "$CountType$", eToolTipMsgKeyWordType_BuffSkill_CountType, 0 },
	{ "$IsEndTime$", eToolTipMsgKeyWordType_BuffSkill_IsEndTime, 0 },
	{ "$EventSkillIndex$", eToolTipMsgKeyWordType_BuffSkill_EventSkillIndex, 0 },
	{ "$Item1$", eToolTipMsgKeyWordType_BuffSkill_Item1, 0 },
	{ "$Item2$", eToolTipMsgKeyWordType_BuffSkill_Item2, 0 },
	{ "$ItemCount1$", eToolTipMsgKeyWordType_BuffSkill_ItemCount1, 0 },
	{ "$ItemCount2$", eToolTipMsgKeyWordType_BuffSkill_ItemCount2, 0 },
	
	// ITEM_INFO �� ����
	{ "$ItemName$", eToolTipMsgKeyWordType_Item_Name, 0 },
};


CTooltipMsgConverter::CTooltipMsgConverter(void)
{
	InitToolTipMsgKeyWordTable();
}

CTooltipMsgConverter::~CTooltipMsgConverter(void)
{
}

const char* CTooltipMsgConverter::GetSkillEquipTypeText( const ACTIVE_SKILL_INFO* const pActiveSkillInfo, char* msg, size_t msgSize  )
{
	if( !pActiveSkillInfo || !msg )
		return NULL;

	char txt[MAX_PATH]={0,};

	if( pActiveSkillInfo->mWeaponType == eWeaponType_None &&
		pActiveSkillInfo->mWeaponAnimationType == eWeaponAnimationType_None &&
		pActiveSkillInfo->mArmorType == eArmorType_None )
	{
		return NULL;
	}

	CLunaGameDataExtracterDlg* pLunaGameDataExtracterDlg = (CLunaGameDataExtracterDlg*)AfxGetApp()->GetMainWnd();
	if( !pLunaGameDataExtracterDlg )
		return NULL;

	switch( pActiveSkillInfo->mWeaponAnimationType )
	{
	case eWeaponAnimationType_OneHand:
		{
			switch( pActiveSkillInfo->mWeaponType )
			{
			case eWeaponType_Sword:
				{
					// �Ѽ� ��
					_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 658 ), pLunaGameDataExtracterDlg->GetSystemMsg( 660 ) );
				}
				break;
			case eWeaponType_Mace:
				{
					// �Ѽ� ���̽�
					_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 658 ), pLunaGameDataExtracterDlg->GetSystemMsg( 662 ) );
				}
				break;
			case eWeaponType_Axe:
				{
					// �Ѽ� ����
					_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 658 ), pLunaGameDataExtracterDlg->GetSystemMsg( 661 ) );
				}
				break;
			default:
				{
					// �Ѽ� ����
					_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 658 ), pLunaGameDataExtracterDlg->GetSystemMsg( 1961 ) );
				}
				break;
			}
		}
		break;
	case eWeaponAnimationType_TwoHand:
		{
			// ��չ���
			switch( pActiveSkillInfo->mWeaponType )
			{
			case eWeaponType_Sword:
				{
					// ��� ��
					_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 659 ), pLunaGameDataExtracterDlg->GetSystemMsg( 660 ) );
				}
				break;
			case eWeaponType_Mace:
				{
					// ��� ���̽�
					_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 659 ), pLunaGameDataExtracterDlg->GetSystemMsg( 662 ) );
				}
				break;
			case eWeaponType_Axe:
				{
					// ��� ����
					_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 659 ), pLunaGameDataExtracterDlg->GetSystemMsg( 661 ) );
				}
				break;
			default:
				{
					// ��� ����
					_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 659 ), pLunaGameDataExtracterDlg->GetSystemMsg( 1961 ) );
				}
				break;
			}
		}
		break;
	case eWeaponAnimationType_TwoBlade:
		{
			// �̵���
			_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 2046 ) );
		}
		break;

	case eWeaponAnimationType_Spear:
		{
			// â
			_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 2047 ) );
		}
		break;

	default:
		{
			switch( pActiveSkillInfo->mWeaponType )
			{
			case eWeaponType_Bow:
				{
					// Ȱ
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 664 ) );
				}
				break;
			case eWeaponType_Gun:
				{
					// ��
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 2048 ) );
				}
				break;
			case eWeaponType_Dagger:
				{
					// �ܰ�
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 663 ) );
				}
				break;
			case eWeaponType_Staff:
				{
					// ������
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 665 ) );
				}
				break;
			case eWeaponType_Sword:
				{
					// ��
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 660 ) );
				}
				break;
			case eWeaponType_Mace:
				{
					// ���̽�
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 662 ) );
				}
				break;
			case eWeaponType_Axe:
				{
					// ����
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 661 ) );
				}
				break;
			case eWeaponType_BothDagger:
				{
					// ��� ����
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 1924 ) );
				}
				break;
			}

			switch( pActiveSkillInfo->mArmorType )
			{
			case eArmorType_Shield:
				{
					// ����
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 695 ) );
				}
				break;
			case eArmorType_Robe:
				{
					// �κ�
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 692 ) );
				}
				break;
			case eArmorType_Leather:
				{
					// ����Ʈ�Ƹ�
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 693 ) );
				}
				break;
			case eArmorType_Metal:
				{
					// ���Ƹ�
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 694 ) );
				}
				break;
			}
		}
		break;
	}

	_tcsncpy( msg, txt, msgSize );
	return msg;
}

const char* CTooltipMsgConverter::GetSkillWeaponTypeText( const BUFF_SKILL_INFO* const pBuffSkillInfo, char* msg, size_t msgSize  )
{
	if( !pBuffSkillInfo || !msg )
		return NULL;

	char txt[MAX_PATH]={0,};

	if( pBuffSkillInfo->mWeaponType == eWeaponType_None &&
		pBuffSkillInfo->mWeaponAnimationType == eWeaponAnimationType_None )
	{
		return NULL;
	}

	CLunaGameDataExtracterDlg* pLunaGameDataExtracterDlg = (CLunaGameDataExtracterDlg*)AfxGetApp()->GetMainWnd();
	if( !pLunaGameDataExtracterDlg )
		return NULL;

	switch( pBuffSkillInfo->mWeaponAnimationType )
	{
	case eWeaponAnimationType_Spear:
		{
			// â
			_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 2047 ) );
		}
		break;
	case eWeaponAnimationType_TwoHand:
		{
			// ��� ����
			_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 659 ), pLunaGameDataExtracterDlg->GetSystemMsg( 1961 ) );
		}
		break;
	case eWeaponAnimationType_OneHand:
		{
			// �Ѽ� ����
			_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 658 ), pLunaGameDataExtracterDlg->GetSystemMsg( 1961 ) );
		}
		break;
	case eWeaponAnimationType_TwoBlade:
		{
			// �̵���
			_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 2046 ) );
		}
		break;

	default:
		{
			switch( pBuffSkillInfo->mWeaponType )
			{
			case eWeaponType_Sword:
				{
					// ��
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 660 ) );
				}
				break;
			case eWeaponType_Mace:
				{
					// ���̽�
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 662 ) );
				}
				break;
			case eWeaponType_Axe:
				{
					// ����
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 661 ) );
				}
				break;
			case eWeaponType_Staff:
				{
					// ������
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 665 ) );
				}
				break;
			case eWeaponType_Bow:
				{
					// Ȱ
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 664 ) );
				}
				break;
			case eWeaponType_Gun:
				{
					// ��
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 2048 ) );
				}
				break;
			case eWeaponType_Dagger:
				{
					// �ܰ�
					_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 663 ) );
				}
				break;
			}
		}
		break;
	}

    _tcsncpy( msg, txt, msgSize );
	return msg;
}

const char* CTooltipMsgConverter::GetSkillArmorTypeText( const BUFF_SKILL_INFO* const pBuffSkillInfo, char* msg, size_t msgSize  )
{
	if( !pBuffSkillInfo || !msg )
		return NULL;

	char txt[MAX_PATH]={0,};

	if( pBuffSkillInfo->mArmorType == eArmorType_None )
	{
		return NULL;
	}

	CLunaGameDataExtracterDlg* pLunaGameDataExtracterDlg = (CLunaGameDataExtracterDlg*)AfxGetApp()->GetMainWnd();
	if( !pLunaGameDataExtracterDlg )
		return NULL;

	switch( pBuffSkillInfo->mArmorType )
	{
	case eArmorType_Robe:
		{
			// �κ�
			_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 692 ) );
		}
		break;
	case eArmorType_Leather:
		{
			// ����Ʈ�Ƹ�
			_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 693 ) );
		}
		break;
	case eArmorType_Metal:
		{
			// ���Ƹ�
			_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 694 ) );
		}
		break;
	case eArmorType_Shield:
		{
			// ����
			_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 695 ) );
		}
		break;
	default:
		{
			// ����
			_stprintf( txt, _T("%s"), pLunaGameDataExtracterDlg->GetSystemMsg( 151 ) );
		}
		break;
	}

	_tcsncpy( msg, txt, msgSize );
	return msg;
}

const char* CTooltipMsgConverter::GetConsumePointTypeText( const ACTIVE_SKILL_INFO* const pActiveSkillInfo, char* msg, size_t msgSize  )
{
	if( !pActiveSkillInfo || !msg )
		return NULL;

	char txt[MAX_PATH]={0,};

	if( pActiveSkillInfo->mConsumePoint.mType == ACTIVE_SKILL_INFO::ConsumePoint::TypeNone )
	{
		return NULL;
	}

	CLunaGameDataExtracterDlg* pLunaGameDataExtracterDlg = (CLunaGameDataExtracterDlg*)AfxGetApp()->GetMainWnd();
	if( !pLunaGameDataExtracterDlg )
		return NULL;

	switch( pActiveSkillInfo->mConsumePoint.mType )
	{
	case ACTIVE_SKILL_INFO::ConsumePoint::TypeGuild:
		{
			_stprintf( txt, _T("%s%d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2096 ), pActiveSkillInfo->mConsumePoint.mValue );		// "�Һ� �������Ʈ: "
		}
		break;
	case ACTIVE_SKILL_INFO::ConsumePoint::TypeFamily:
		{
			_stprintf( txt, _T("%s%d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2097 ), pActiveSkillInfo->mConsumePoint.mValue );		// "�Һ� �йи�����Ʈ: "
		}
		break;
	case ACTIVE_SKILL_INFO::ConsumePoint::TypePlayerKill:
		{
			_stprintf( txt, _T("%s%d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2098 ), pActiveSkillInfo->mConsumePoint.mValue );		// "�Һ� PK����Ʈ: "
		}
		break;
	case ACTIVE_SKILL_INFO::ConsumePoint::TypeExperience:
		{
			_stprintf( txt, _T("%s%d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2099 ), pActiveSkillInfo->mConsumePoint.mValue );		// "�Һ� ����ġ: "
		}
		break;
	}

	_tcsncpy( msg, txt, msgSize );
	return msg;
}

const char* CTooltipMsgConverter::GetBuffConditionTypeText( const BUFF_SKILL_INFO* const pBuffSkillInfo, char* msg, size_t msgSize  )
{
	if( !pBuffSkillInfo, !msg )
		return NULL;

	char txt[MAX_PATH]={0,};

	struct
	{
		const char* operator() ( BUFF_SKILL_INFO::Condition::Operation eOper )
		{
			CLunaGameDataExtracterDlg* pLunaGameDataExtracterDlg = (CLunaGameDataExtracterDlg*)AfxGetApp()->GetMainWnd();
			if( !pLunaGameDataExtracterDlg )
				return "";

			switch( eOper )
			{
			case BUFF_SKILL_INFO::Condition::OperationMoreEqual:	return pLunaGameDataExtracterDlg->GetSystemMsg( 2056 );	// �̻�
			case BUFF_SKILL_INFO::Condition::OperationLessEqual:	return pLunaGameDataExtracterDlg->GetSystemMsg( 2057 );	// ����
			case BUFF_SKILL_INFO::Condition::OperationMore:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2058 );	// �ʰ�
			case BUFF_SKILL_INFO::Condition::OperationLess:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2059 );	// �̸�
			default:		return "";
			}
		}
	}
	GetConditionOperationTxt;

	if( pBuffSkillInfo->mCondition.mType == BUFF_SKILL_INFO::Condition::TypeNone )
	{
		return NULL;
	}

	CLunaGameDataExtracterDlg* pLunaGameDataExtracterDlg = (CLunaGameDataExtracterDlg*)AfxGetApp()->GetMainWnd();
	if( !pLunaGameDataExtracterDlg )
		return NULL;

	switch( pBuffSkillInfo->mCondition.mType )
	{
	case BUFF_SKILL_INFO::Condition::TypeLifePercent:
		{
			_stprintf( txt, _T("%s %.0f%% %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 164 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeLife:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 164 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeLifeMax:
		{
			_stprintf( txt, _T("%s %.0f%% %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 2060 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeLifeRecovery:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 846 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeManaPercent:
		{
			_stprintf( txt, _T("%s %.0f%% %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 165 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeMana:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 165 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeManaMax:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 2061 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeManaRecovery:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 847 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeStrength:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 157 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeIntelligence:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 160 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeDexterity:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 158 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeWisdom:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 161 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeVitality:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 159 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypePhysicalAttack:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 152 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypePhysicalDefense:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 153 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeMagicalAttack:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 155 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeMagicalDefense:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 156 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeCriticalRate:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 842 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeCriticalDamage:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 843 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeAccuracy:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 162 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeEvade:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 841 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	case BUFF_SKILL_INFO::Condition::TypeMoveSpeed:
		{
			_stprintf( txt, _T("%s %.0f %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 840 ), pBuffSkillInfo->mCondition.mValue, GetConditionOperationTxt( pBuffSkillInfo->mCondition.mOperation ) );
		}
		break;
	}

	_tcsncpy( msg, txt, msgSize );
	return msg;
}

const char* CTooltipMsgConverter::GetBuffCountTypeText( const BUFF_SKILL_INFO* const pBuffSkillInfo, char* msg, size_t msgSize , const int nCurrentCount )
{
	if( !pBuffSkillInfo || !msg )
		return NULL;

	char txt[MAX_PATH]={0,};

	if( pBuffSkillInfo->CountType == eBuffSkillCountType_None )
	{
		return NULL;
	}

	CLunaGameDataExtracterDlg* pLunaGameDataExtracterDlg = (CLunaGameDataExtracterDlg*)AfxGetApp()->GetMainWnd();
	if( !pLunaGameDataExtracterDlg )
		return NULL;

	int nCount = ( nCurrentCount != 0 ? nCurrentCount : pBuffSkillInfo->Count );

	switch( pBuffSkillInfo->CountType )
	{
	case eBuffSkillCountType_Dead:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2077 ), nCount );
		}
		break;
	case eBuffSkillCountType_AnyDamageVolumn:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2078 ), nCount );
		}
		break;
	case eBuffSkillCountType_AnyDamage:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2079 ), nCount );
		}
		break;
	case eBuffSkillCountType_AnyHitVolumn:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2080 ), nCount );
		}
		break;
	case eBuffSkillCountType_AnyHit:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2081 ), nCount );
		}
		break;
	case eBuffSkillCountType_PhysicalDamageVolumn:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2082 ), nCount );
		}
		break;
	case eBuffSkillCountType_PhysicalDamage:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2083 ), nCount );
		}
		break;
	case eBuffSkillCountType_PhysicalHitVolumn:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2084 ), nCount );
		}
		break;
	case eBuffSkillCountType_PhysicalHit:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2085 ), nCount );
		}
		break;
	case eBuffSkillCountType_MagicalDamageVolumn:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2086 ), nCount );
		}
		break;
	case eBuffSkillCountType_MagicalDamage:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2087 ), nCount );
		}
		break;
	case eBuffSkillCountType_MagicalHitVolumn:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2088 ), nCount );
		}
		break;
	case eBuffSkillCountType_MagicalHit:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2089 ), nCount );
		}
		break;
	case eBuffSkillCountType_HealVolumn:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2090 ), pBuffSkillInfo->Count );
		}
		break;
	case eBuffSkillCountType_Heal:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2091 ), pBuffSkillInfo->Count );
		}
		break;
	case eBuffSkillCountType_BeHealedVolumn:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2092 ), pBuffSkillInfo->Count );
		}
		break;
	case eBuffSkillCountType_BeHealed:
		{
			_stprintf( txt, _T("%s: %d"), pLunaGameDataExtracterDlg->GetSystemMsg( 2093 ), pBuffSkillInfo->Count );
		}
		break;
	}

	_tcsncpy( msg, txt, msgSize );
	return msg;
}

// �������ڿ����̺� ������ �ʱ�ȭ�Ѵ�.
void CTooltipMsgConverter::InitToolTipMsgKeyWordTable()
{
	const int dwTableSize = sizeof( ToolTipMsgKeyWordTable ) / sizeof( stToolTipMsgKeyWordData );

	for( int i=0 ; i<dwTableSize ; ++i )
	{
		ToolTipMsgKeyWordTable[i].dwHashCode = GetHashCodeFromTxt( ToolTipMsgKeyWordTable[i].KeyWord );

#ifdef _GMTOOL_
		// ���� ����� ���
		if( m_mapToolTipMsgKeyWord.find( ToolTipMsgKeyWordTable[i].dwHashCode ) != m_mapToolTipMsgKeyWord.end() )
		{
			char txt[MAX_PATH]={0,};
			_stprintf( txt, _T("Tooltip �����[%s]�� �ߺ� �Ǿ� �ֽ��ϴ�"), ToolTipMsgKeyWordTable[i].KeyWord );
			MessageBox( NULL, txt, "Warning", MB_OK );
		}
#endif

		m_mapToolTipMsgKeyWord[ ToolTipMsgKeyWordTable[i].dwHashCode ] = (int)ToolTipMsgKeyWordTable[i].eType;
	}
}

// ���ڿ����� �������� ã�´�.
BOOL CTooltipMsgConverter::GetToolTipMsgKeyWordFromText( std::string& strMsg, std::string& keyword, std::string::size_type& keywordStart, std::string::size_type& keywordSize )
{
	std::string substr;
	keywordSize = 0;
	while( ++keywordSize + keywordStart < strMsg.length() )
	{
		if( strMsg[ keywordSize + keywordStart ] == ' ' ||
			strMsg[ keywordSize + keywordStart ] == '\n' ||
			strMsg[ keywordSize + keywordStart ] == '\t' )
		{
			keywordSize = 0;
			return FALSE;
		}

		if( strMsg[ keywordSize + keywordStart ] == '$' )
		{
			keyword = strMsg.substr( keywordStart, ++keywordSize );
			return TRUE;
		}
	}

	return FALSE;
}


// ���������Type���κ��� ��ȯ�� ���ڿ��� ��ȯ�Ѵ�.
const char* CTooltipMsgConverter::GetTextFromToolTipMsgKeyWordType( DWORD& dwToolTipIndex, int keywordType, char* txt, size_t txtSize, int prevKeyWordType )
{
	if( !txt )
		return NULL;

	ZeroMemory( txt, txtSize );

	CLunaGameDataExtracterDlg* pLunaGameDataExtracterDlg = (CLunaGameDataExtracterDlg*)AfxGetApp()->GetMainWnd();
	if( !pLunaGameDataExtracterDlg )
		return "";

	const ACTIVE_SKILL_INFO& activeSkillInfo	= pLunaGameDataExtracterDlg->GetActiveSkillInfo( dwToolTipIndex );
	const BUFF_SKILL_INFO& buffSkillInfo		= pLunaGameDataExtracterDlg->GetBuffSkillInfo( dwToolTipIndex );
	if( activeSkillInfo.Index != dwToolTipIndex && buffSkillInfo.Index != dwToolTipIndex )
		return "";

	// -> Ÿ�� ��ȯ
	if( (eToolTipMsgKeyWordType)prevKeyWordType != eToolTipMsgKeyWordType_None )
	{
		switch( (eToolTipMsgKeyWordType)prevKeyWordType )
		{
		case eToolTipMsgKeyWordType_ActiveSkill_Buff1:
		case eToolTipMsgKeyWordType_ActiveSkill_Buff2:
		case eToolTipMsgKeyWordType_ActiveSkill_Buff3:
		case eToolTipMsgKeyWordType_ActiveSkill_Buff4:
		case eToolTipMsgKeyWordType_ActiveSkill_Buff5:
			{
				const int nArrayIndex = prevKeyWordType - (int)eToolTipMsgKeyWordType_ActiveSkill_Buff1;
				if( nArrayIndex >= MAX_BUFF_COUNT )
					return "";

				const DWORD dwBuffSkillIndex = activeSkillInfo.Buff[ nArrayIndex ];
				dwToolTipIndex = dwBuffSkillIndex;

				return GetTextFromToolTipMsgKeyWordType( dwToolTipIndex, keywordType, txt, txtSize );
			}

		case eToolTipMsgKeyWordType_ActiveSkill_ConsumeItemIndex:
			{
				dwToolTipIndex = activeSkillInfo.mConsumeItem.wIconIdx;
				return GetTextFromToolTipMsgKeyWordType( dwToolTipIndex, keywordType, txt, txtSize );
			}

		case eToolTipMsgKeyWordType_ActiveSkill_RequiredBuff:
			{
				dwToolTipIndex = activeSkillInfo.RequiredBuff;
				return GetTextFromToolTipMsgKeyWordType( dwToolTipIndex, keywordType, txt, txtSize );
			}

		case eToolTipMsgKeyWordType_BuffSkill_EventSkillIndex:
			{
				if( buffSkillInfo.Status != eStatusKind_EventSkillToVictim ||
					buffSkillInfo.Status != eStatusKind_EventSkillToKiller )
					return "";

				dwToolTipIndex  = buffSkillInfo.mEventSkillIndex;
				return GetTextFromToolTipMsgKeyWordType( dwToolTipIndex, keywordType, txt, txtSize );
			}

		case eToolTipMsgKeyWordType_BuffSkill_Item1:
		case eToolTipMsgKeyWordType_BuffSkill_Item2:
			{
				const int nMaxArraySize = sizeof( buffSkillInfo.Item ) / sizeof( *buffSkillInfo.Item );
				const int nArrayIndex = prevKeyWordType - (int)eToolTipMsgKeyWordType_BuffSkill_Item1;
				if( nArrayIndex >= nMaxArraySize )
					return "";

				dwToolTipIndex = buffSkillInfo.Item[ nArrayIndex ];
				return GetTextFromToolTipMsgKeyWordType( dwToolTipIndex, keywordType, txt, txtSize );
			}

		default:
			return "";
		}
	}


	struct{
		void operator() ( char* txt,  float fTotalSec )
		{
			if( !txt )
				return;

			CLunaGameDataExtracterDlg* pLunaGameDataExtracterDlg = (CLunaGameDataExtracterDlg*)AfxGetApp()->GetMainWnd();
			if( !pLunaGameDataExtracterDlg )
				return;

			char time[MAX_PATH]={0,};

			// ��/��/�ʷ� ǥ��
			int hour=0, min=0;
			float sec = fTotalSec;
			if( sec >= 60.f )
			{
				min = (int)(sec / 60.f);
				sec = sec - min * 60.f;
				if( min >= 60.f )
				{
					hour = (int)(min / 60.f);
					min = min - hour * 60;
				}
			}

			if( hour )
			{
				_stprintf( time, pLunaGameDataExtracterDlg->GetSystemMsg( 1410 ), hour );
				strcat( txt, time );
			}
			if( min )
			{
				_stprintf( time, pLunaGameDataExtracterDlg->GetSystemMsg( 1411 ), min );
				strcat( txt, time );
			}
			if( sec )
			{
				_stprintf( time, pLunaGameDataExtracterDlg->GetSystemMsg( 2053 ), sec );
				strcat( txt, time );
			}
		}
	}ConvertHourMinSec;

	
	// struct SKILL_INFO �� ����
	if( keywordType < eToolTipMsgKeyWordType_ActiveSkill )
	{
		switch( (eToolTipMsgKeyWordType)keywordType )
		{
		case eToolTipMsgKeyWordType_Skill_Index:
			{
				if( activeSkillInfo.Index == dwToolTipIndex )
					_stprintf( txt, _T("%d"), activeSkillInfo.Index == dwToolTipIndex ? activeSkillInfo.Index : buffSkillInfo.Index );
				else
					_stprintf( txt, _T("%d"), buffSkillInfo.Index );
			}
			break;
		case eToolTipMsgKeyWordType_Skill_Name:
			{
				return activeSkillInfo.Index == dwToolTipIndex ? activeSkillInfo.Name : buffSkillInfo.Name;
			}
			break;
		case eToolTipMsgKeyWordType_Skill_Tooltip:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.Index == dwToolTipIndex ? activeSkillInfo.Tooltip : buffSkillInfo.Tooltip );
			}
			break;
		case eToolTipMsgKeyWordType_Skill_Image:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.Index == dwToolTipIndex ? activeSkillInfo.Image : buffSkillInfo.Image );
			}
			break;
		case eToolTipMsgKeyWordType_Skill_Kind:
			{
				switch( activeSkillInfo.Index == dwToolTipIndex ? activeSkillInfo.Kind : buffSkillInfo.Kind )
				{
				case SKILLKIND_PHYSIC:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2100 );		// "��Ƽ��(����)"
				case SKILLKIND_MAGIC:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2101 );		// "��Ƽ��(����)"
				case SKILLKIND_PASSIVE:		return pLunaGameDataExtracterDlg->GetSystemMsg( 176 );
				case SKILLKIND_ONOFF:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2102 );		// "���"
				case SKILLKIND_BUFF:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2103 );		// "����"
				}
			}
			break;
		case eToolTipMsgKeyWordType_Skill_Level:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.Index == dwToolTipIndex ? activeSkillInfo.Level : buffSkillInfo.Level );
			}
			break;
		}
	}
	// struct ACTIVE_SKILL_INFO �� ����
	else if( keywordType < eToolTipMsgKeyWordType_BuffSkill )
	{
		switch( (eToolTipMsgKeyWordType)keywordType )
		{
		case eToolTipMsgKeyWordType_ActiveSkill_Money:
			{
				return AddComma( activeSkillInfo.Money );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_Life_Percent:
			{
				_stprintf( txt, _T("%.0f%%"), activeSkillInfo.mLife.mPercent );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_Life_Plus:
			{
				_stprintf( txt, _T("%d"), (int)activeSkillInfo.mLife.mPlus );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_Mana_Percent:
			{
				_stprintf( txt, _T("%.0f%%"), activeSkillInfo.mMana.mPercent );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_Mana_Plus:
			{
				_stprintf( txt, _T("%d"), (int)activeSkillInfo.mMana.mPlus );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_EquipType:
			{
				if( GetSkillEquipTypeText( &activeSkillInfo, txt, txtSize ) == NULL )
					return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����"

				return GetSkillEquipTypeText( &activeSkillInfo, txt, txtSize );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_OperatorEffect:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.OperatorEffect );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_TargetEffect:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.TargetEffect );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_SkillEffect:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.SkillEffect );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_AnimationTime:
			{
				// �ð�(1/1000��)
				ConvertHourMinSec( txt, activeSkillInfo.AnimationTime / 1000.f );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_CastingTime:
			{
				// �ð�(1/1000��)
				ConvertHourMinSec( txt, activeSkillInfo.CastingTime / 1000.f );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_DelayType:
			{
				switch( activeSkillInfo.DelayType )
				{
				case 1:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2105 );		// "���ڸ�"
				case 2:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2106 );		// "��ǥ�̵�"
				}
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_DelayTime:
			{
				// �ð�(1/1000��)
				ConvertHourMinSec( txt, activeSkillInfo.DelayTime / 1000.f );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_CoolTime:
			{
				// �ð�(1/1000��)
				ConvertHourMinSec( txt, activeSkillInfo.CoolTime / 1000.f );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_Target:
			{
				switch( activeSkillInfo.Target )
				{
				case 0:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2107 );		// "Ÿ�پ���"
				case 1:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2108 );		// "Ÿ���ʿ�"
				case 2:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2109 );		// "����Ÿ��"
				case 3:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2110 );		// "����Ÿ��"
				case 4:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2111 );		// "����&Ÿ��"
				}
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_Range:
			{
				_stprintf( txt, _T("%.1fm"), (activeSkillInfo.Range / 100.f) );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_Area:
			{
				switch( activeSkillInfo.Area )
				{
				case TARGET_KIND_SINGLE:
				case TARGET_KIND_SINGLE_CIRCLE:
					return pLunaGameDataExtracterDlg->GetSystemMsg( 2112 );		// "���ϴ��"

				case TARGET_KIND_MULTI:
				case TARGET_KIND_MULTI_CIRCLE:
				case TARGET_KIND_MULTI_RECT:
				case TARGET_KIND_MULTI_ARC:
					return pLunaGameDataExtracterDlg->GetSystemMsg( 2113 );		// "���������"

				case TARGET_KIND_MULTI_MONSTER:
					return pLunaGameDataExtracterDlg->GetSystemMsg( 2114 );		// "���� ��� ����"

				case TARGET_KIND_MULTI_ALL:
					return pLunaGameDataExtracterDlg->GetSystemMsg( 2115 );		// "����/�÷��̾� ��� ����"
				}
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_AreaTarget:
			{
				switch( activeSkillInfo.AreaTarget )
				{
				case eSkillAreaTargetNone:				return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����"
				case eSkillAreaTargetMonster:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2116 );		// "����(��)"
				case eSkillAreaTargetParty:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2117 );		// "��Ƽ��"
				case eSkillAreaTargetFamily:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2118 );		// "�йи���"
				case eSkillAreaTargetGuild:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2119 );		// "����"
				case eSkillAreaTargetAll:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2120 );		// "�ڽ�����"
				case eSkillAreaTargetAllExceptMe:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2121 );		// "�ڽ����� ��� ����"
				}
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_AreaData:
			{
				_stprintf( txt, _T("%.1fm"), (activeSkillInfo.AreaData / 100.f) );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_Unit:
			{
				switch( activeSkillInfo.Unit )
				{
				case UNITKIND_NONE:						return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����"
				case UNITKIND_PHYSIC_ATTCK:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2122 );		// "����������"
				case UNITKIND_MAGIC_ATTCK:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2123 );		// "����������"
				case UNITKIND_LIFE_RECOVER:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2124 );		// "��"
				case UNITKIND_RESURRECTION:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2125 );		// "��Ȱ"
				case UNITKIND_DEBUFF:					return pLunaGameDataExtracterDlg->GetSystemMsg( 2126 );		// "��������"
				case UNITKIND_FAKE_DAMAGE:
				case UNITKIND_PHYSIC_FAKE_DAMAGE:
				case UNITKIND_MAGIC_FAKE_DAMAGE:
					return pLunaGameDataExtracterDlg->GetSystemMsg( 2127 );		// "��¥������"
				case UNITKIND_DECOY:					return pLunaGameDataExtracterDlg->GetSystemMsg( 2128 );		// "���ε�����(��������)"
				case UNITKIND_MANA_RECOVER:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2129 );		// "����ȸ��"
				case UNITKIND_RETURN:					return pLunaGameDataExtracterDlg->GetSystemMsg( 2130 );		// "����(��ȯ)"
				case UNITKIND_SPELLBREAK:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2131 );		// "����극��ũ"
				case UNITKIND_SUMMON:					return pLunaGameDataExtracterDlg->GetSystemMsg( 2132 );		// "��ȯ"
				case UNITKIND_RECALL:					return pLunaGameDataExtracterDlg->GetSystemMsg( 2133 );		// "�÷��̾� ��ȯ"
				}
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_UnitDataType:
			{
				switch( activeSkillInfo.UnitDataType )
				{
				case 0:									return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����"
				case 1:
					{
						switch( activeSkillInfo.Unit )
						{
						case UNITKIND_PHYSIC_ATTCK:		return pLunaGameDataExtracterDlg->GetSystemMsg( 157 );		// "��"
						case UNITKIND_MAGIC_ATTCK:		return pLunaGameDataExtracterDlg->GetSystemMsg( 160 );		// "����"
						}
					}
					break;
				case 2:
					{
						switch( activeSkillInfo.Unit )
						{
						case UNITKIND_PHYSIC_ATTCK:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2134 );		// "���� �������ݷ�"
						case UNITKIND_MAGIC_ATTCK:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2135 );		// "���� �������ݷ�"
						}
					}
					break;
				}
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_UnitData:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.UnitData );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_Success:
			{
				_stprintf( txt, _T("%d%%"), (int)(activeSkillInfo.Success / 10) );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_Cancel:
			{
				_stprintf( txt, _T("%d%%"), (int)(activeSkillInfo.Cancel / 10) );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_TrainPoint:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.TrainPoint );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_TrainMoney:
			{
				return AddComma( activeSkillInfo.TrainMoney );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_BuffRate1:
		case eToolTipMsgKeyWordType_ActiveSkill_BuffRate2:
		case eToolTipMsgKeyWordType_ActiveSkill_BuffRate3:
		case eToolTipMsgKeyWordType_ActiveSkill_BuffRate4:
		case eToolTipMsgKeyWordType_ActiveSkill_BuffRate5:
			{
				const int nMaxArraySize = sizeof( activeSkillInfo.BuffRate ) / sizeof( *activeSkillInfo.BuffRate );
				const int nArrayIndex = keywordType - (int)eToolTipMsgKeyWordType_ActiveSkill_BuffRate1;
				if( nArrayIndex >= nMaxArraySize )
					break;

				_stprintf( txt, _T("%d%%"), activeSkillInfo.BuffRate[ nArrayIndex ] );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_IsMove:
			{
				return ( activeSkillInfo.IsMove ? pLunaGameDataExtracterDlg->GetSystemMsg( 2136 ) : pLunaGameDataExtracterDlg->GetSystemMsg( 151 ) );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_RequiredPlayerLevel:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.RequiredPlayerLevel );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_ConsumeItemCount:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.mConsumeItem.Durability );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_ConsumePointType:
			{
				if( GetConsumePointTypeText( &activeSkillInfo, txt, txtSize ) == NULL )
					return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����"

				return GetConsumePointTypeText( &activeSkillInfo, txt, txtSize );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_ConsumePointValue:
			{
				_stprintf( txt, _T("%d"), activeSkillInfo.mConsumePoint.mValue );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_IsBattle:
			{
				return ( activeSkillInfo.mIsBattle ? pLunaGameDataExtracterDlg->GetSystemMsg( 2137 ) : pLunaGameDataExtracterDlg->GetSystemMsg( 2138 ) );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_IsPeace:
			{
				return ( activeSkillInfo.mIsPeace ? pLunaGameDataExtracterDlg->GetSystemMsg( 2137 ) : pLunaGameDataExtracterDlg->GetSystemMsg( 2138 ) );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_mIsMove:
			{
				return ( activeSkillInfo.mIsMove ? pLunaGameDataExtracterDlg->GetSystemMsg( 2137 ) : pLunaGameDataExtracterDlg->GetSystemMsg( 2138 ) );
			}
			break;
		case eToolTipMsgKeyWordType_ActiveSkill_IsStop:
			{
				return ( activeSkillInfo.mIsStop ? pLunaGameDataExtracterDlg->GetSystemMsg( 2137 ) : pLunaGameDataExtracterDlg->GetSystemMsg( 2138 ) );
			}
			break;
		}
	}
	// BUFF_SKILL_INFO �� ����
	else if( keywordType < eToolTipMsgKeyWordType_Item )
	{
		switch( (eToolTipMsgKeyWordType)keywordType )
		{
		case eToolTipMsgKeyWordType_BuffSkill_Money:
			{
				return AddComma( buffSkillInfo.Money );
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_WeaponType:
			{
				if( GetSkillWeaponTypeText( &buffSkillInfo, txt, txtSize ) == NULL )
					return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����"

				return GetSkillWeaponTypeText( &buffSkillInfo, txt, txtSize );
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_ArmorType:
			{
				if( GetSkillArmorTypeText( &buffSkillInfo, txt, txtSize ) == NULL )
					return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����"

				return GetSkillArmorTypeText( &buffSkillInfo, txt, txtSize );
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_DelayTime:
			{
				// �ð�(1/1000��)
				ConvertHourMinSec( txt, buffSkillInfo.DelayTime / 1000.f );
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_SkillEffect:
			{	
				_stprintf( txt, _T("%d"), buffSkillInfo.SkillEffect );
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_Status:
			{
				switch( buffSkillInfo.Status )
				{
				case eStatusKind_None:										return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����"
				case eStatusKind_Str:										return pLunaGameDataExtracterDlg->GetSystemMsg( 157 );		// "��"
				case eStatusKind_Dex:										return pLunaGameDataExtracterDlg->GetSystemMsg( 158 );		// "��ø"
				case eStatusKind_Vit:										return pLunaGameDataExtracterDlg->GetSystemMsg( 159 );		// "ü��"
				case eStatusKind_Int:										return pLunaGameDataExtracterDlg->GetSystemMsg( 160 );		// "����"
				case eStatusKind_Wis:										return pLunaGameDataExtracterDlg->GetSystemMsg( 161 );		// "����"
				case eStatusKind_All:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2139 );		// "��� ����"
				case eStatusKind_PhysicAttack:								return pLunaGameDataExtracterDlg->GetSystemMsg( 152 );		// "���� ���ݷ�"
				case eStatusKind_PhysicDefense:								return pLunaGameDataExtracterDlg->GetSystemMsg( 153 );		// "���� ����"
				case eStatusKind_MagicAttack:								return pLunaGameDataExtracterDlg->GetSystemMsg( 155 );		// "���� ���ݷ�"
				case eStatusKind_MagicDefense:								return pLunaGameDataExtracterDlg->GetSystemMsg( 156 );		// "���� ����"
				case eStatusKind_Accuracy:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2140 );		// "���� ��ġ"
				case eStatusKind_Avoid:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2141 );		// "ȸ�� ��ġ"
				case eStatusKind_CriticalRate:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2142 );		// "���� ũ��Ƽ�� �ߵ� Ȯ��"
				case eStatusKind_Range:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2143 );		// "�����Ÿ�"
				case eStatusKind_MagicCriticalRate:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2144 );		// "���� ũ��Ƽ�� �ߵ� Ȯ��"
				case eStatusKind_CriticalDamage:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2145 );		// "���� ũ��Ƽ�� ������"
				case eStatusKind_MoveSpeed:									return pLunaGameDataExtracterDlg->GetSystemMsg( 840 );		// "�̵��ӵ�"
				case eStatusKind_Block:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2146 );		// "���� �����"
				case eStatusKind_CoolTime:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2147 );		// "��Ÿ��"
				case eStatusKind_CastingProtect:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2148 );		// "���� ���� Ȯ�� ����"
				case eStatusKind_Hide:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2149 );		// "���ڽ�"
				case eStatusKind_Detect:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2150 );		// "����Ʈ"
				case eStatusKind_IncreaseDropRate:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2151 );		// "�����۽���Ȯ��"
				case eStatusKind_DecreaseManaRate:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2152 );		// "�Ҹ� MP"
				case eStatusKind_MaxLife:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2060 );		// "�ִ� HP"
				case eStatusKind_MaxMana:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2061 );		// "�ִ� MP"
				case eStatusKind_LifeRecoverRate:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2153 );		// "HP ȸ����"
				case eStatusKind_ManaRecoverRate:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2154 );		// "MP ȸ����"
				case eStatusKind_LifeRecover:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2155 );		// "HP ����"
				case eStatusKind_ManaRecover:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2156 );		// "MP ����"
				case eStatusKind_Poison:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2157 );		// "��"
				case eStatusKind_Paralysis:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2158 );		// "����"
				case eStatusKind_Stun:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2159 );		// "����"
				case eStatusKind_Slip:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2160 );		// "����"
				case eStatusKind_Freezing:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2161 );		// "���"
				case eStatusKind_Stone:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2162 );		// "��ȭ"
				case eStatusKind_Silence:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2163 );		// "���Ϸ���"
				case eStatusKind_BlockAttack:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2164 );		// "��������"
				case eStatusKind_God:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2165 );		// "������"
				case eStatusKind_Shield:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2166 );		// "��ȣ��"
				case eStatusKind_Bleeding:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2167 );		// "����"
				case eStatusKind_Burning:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2168 );		// "ȭ������"
				case eStatusKind_HolyDamage:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2169 );		// "�ż�����"
				case eStatusKind_MoveStop:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2170 );		// "Ȧ��"
				case eStatusKind_Attract:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2171 );		// "���߰� 1�κ���"
				case eStatusKind_ManaBurn:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2172 );		// "MP �� ���� - (��)������"
				case eStatusKind_Reflect:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2173 );		// "������ �ݻ�"
				case eStatusKind_Absorb:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2174 );		// "������ ���"
				case eStatusKind_DamageToLife:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2175 );		// "���� ������ HP��ȯ"
				case eStatusKind_DamageToMana:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2176 );		// "���� ������ MP��ȯ"
				case eStatusKind_GetLife:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2177 );		// "���� HP"
				case eStatusKind_GetMana:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2178 );		// "���� MP"
				case eStatusKind_GetExp:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2179 );		// "���� EXP"
				case eStatusKind_GetGold:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2180 );		// "���� GOLD"
				case eStatusKind_ProtectExp:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2181 );		// "����г�Ƽ��ȣ"
				case eStatusKind_Attrib_None:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2182 );		// "�� �Ӽ�"
				case eStatusKind_Attrib_Earth:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2183 );		// "�� �Ӽ�"
				case eStatusKind_Attrib_Water:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2184 );		// "�� �Ӽ�"
				case eStatusKind_Attrib_Divine:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2185 );		// "�� �Ӽ�"
				case eStatusKind_Attrib_Wind:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2186 );		// "ǳ �Ӽ�"
				case eStatusKind_Attrib_Fire:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2187 );		// "ȭ �Ӽ�"
				case eStatusKind_Attrib_Dark:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2188 );		// "�� �Ӽ�"
				case eStatusKind_Sword:										return pLunaGameDataExtracterDlg->GetSystemMsg( 660 );		// "��"
				case eStatusKind_Mace:										return pLunaGameDataExtracterDlg->GetSystemMsg( 662 );		// "���̽�"
				case eStatusKind_Axe:										return pLunaGameDataExtracterDlg->GetSystemMsg( 661 );		// "����"
				case eStatusKind_Staff:										return pLunaGameDataExtracterDlg->GetSystemMsg( 665 );		// "������"
				case eStatusKind_Bow:										return pLunaGameDataExtracterDlg->GetSystemMsg( 664 );		// "Ȱ"
				case eStatusKind_Gun:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2048 );		// "��"
				case eStatusKind_Dagger:									return pLunaGameDataExtracterDlg->GetSystemMsg( 663 );		// "�ܰ�"
				case eStatusKind_Spear:										return pLunaGameDataExtracterDlg->GetSystemMsg( 2047 );		// "â"
				case eStatusKind_TwoHanded:									_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 659 ), pLunaGameDataExtracterDlg->GetSystemMsg( 1961 ) );		break;		// ��� ����
				case eStatusKind_TwoBlade:									return pLunaGameDataExtracterDlg->GetSystemMsg( 2046 );		// "�̵���"
				case eStatusKind_OneHanded:									_stprintf( txt, _T("%s %s"), pLunaGameDataExtracterDlg->GetSystemMsg( 658 ), pLunaGameDataExtracterDlg->GetSystemMsg( 1961 ) );		break;		// �Ѽ� ����
				case eStatusKind_RobeArmor:									return pLunaGameDataExtracterDlg->GetSystemMsg( 692 );		// "�κ�"
				case eStatusKind_LightArmor:								return pLunaGameDataExtracterDlg->GetSystemMsg( 693 );		// "����Ʈ�Ƹ�"
				case eStatusKind_HeavyArmor:								return pLunaGameDataExtracterDlg->GetSystemMsg( 694 );		// "���Ƹ�"
				case eStatusKind_ShieldArmor:								return pLunaGameDataExtracterDlg->GetSystemMsg( 695 );		// "����"
				case eStatusKind_NormalSpeedRate:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2189 );		// "�Ϲ� ���� �ӵ�"
				case eStatusKind_PhysicSkillSpeedRate:						return pLunaGameDataExtracterDlg->GetSystemMsg( 2190 );		// "���� ��ų ���� �ӵ�"
				case eStatusKind_MagicSkillSpeedRate:						return pLunaGameDataExtracterDlg->GetSystemMsg( 2191 );		// "���� ��ų ���� �ӵ�"
				case eStatusKind_NormalPhysicSkillSpeedRate:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2192 );		// "�Ϲ� ���� + ���� ��ų ���� �ӵ�"
				case eStatusKind_ConvertHealthWithGivedDamage:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2193 );		// "�� �������� HP�� ��ȯ"
				case eStatusKind_ConvertManaWithGivedDamage:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2194 );		// "�� �������� MP�� ��ȯ"
				case eStatusKind_EventSkillToVictim:						return pLunaGameDataExtracterDlg->GetSystemMsg( 2195 );		// "��� �� ��ų �ߵ�"
				case eStatusKind_EventSkillToKiller:						return pLunaGameDataExtracterDlg->GetSystemMsg( 2196 );		// "�����Ų �ڿ��� ��ų �ߵ�"
				case eStatusKind_EnableTwoBlade:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2197 );		// "�̵��� ��� ����"
				case eStatusKind_UnableUseItem:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2198 );		// "������ ��� ����"
				case eStatusKind_UnableBuff:								return pLunaGameDataExtracterDlg->GetSystemMsg( 2199 );		// "���� ��� ����"
				case eStatusKind_IncreaseExpRate:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2200 );		// "����ġ ���� %";
				case eStatusKind_DamageToManaDamage:						return pLunaGameDataExtracterDlg->GetSystemMsg( 2201 );		// "�����ǵ�"
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_StatusDataType:
			{
				switch( buffSkillInfo.StatusDataType )
				{
				case 0:		return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����"
				case 1:		return "���";
				case 2:		return "%%";
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_StatusData:
			{
				switch( buffSkillInfo.StatusDataType )
				{
				case 0:		
				case 1:	
					{
						_stprintf( txt, _T("%d"), (int)abs( buffSkillInfo.StatusData ) );
					}
					break;
				case 2:
					{
						_stprintf( txt, _T("%.1f%%"), abs( buffSkillInfo.StatusData ) );
					}
					break;
				}
					
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_ConditonType:
			{
				switch( buffSkillInfo.mCondition.mType )
				{
				case BUFF_SKILL_INFO::Condition::TypeNone:							return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����"
				case BUFF_SKILL_INFO::Condition::TypeLifePercent:					return pLunaGameDataExtracterDlg->GetSystemMsg( 2202 );		// "���� HP �ۼ�Ʈ"
				case BUFF_SKILL_INFO::Condition::TypeLife:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2203 );		// "���� HP ��ġ"
				case BUFF_SKILL_INFO::Condition::TypeLifeMax:						return pLunaGameDataExtracterDlg->GetSystemMsg( 2060 );		// "�ִ� HP"
				case BUFF_SKILL_INFO::Condition::TypeLifeRecovery:					return pLunaGameDataExtracterDlg->GetSystemMsg( 846 );		// "HP ȸ��"
				case BUFF_SKILL_INFO::Condition::TypeManaPercent:					return pLunaGameDataExtracterDlg->GetSystemMsg( 2204 );		// "���� MP �ۼ�Ʈ"
				case BUFF_SKILL_INFO::Condition::TypeMana:							return pLunaGameDataExtracterDlg->GetSystemMsg( 2205 );		// "���� MP ��ġ";
				case BUFF_SKILL_INFO::Condition::TypeManaMax:						return pLunaGameDataExtracterDlg->GetSystemMsg( 2061 );		// "�ִ� MP"
				case BUFF_SKILL_INFO::Condition::TypeManaRecovery:					return pLunaGameDataExtracterDlg->GetSystemMsg( 847 );		// "HP ȸ��"
				case BUFF_SKILL_INFO::Condition::TypeStrength:						return pLunaGameDataExtracterDlg->GetSystemMsg( 157 );		// "��"
				case BUFF_SKILL_INFO::Condition::TypeIntelligence:					return pLunaGameDataExtracterDlg->GetSystemMsg( 160 );		// "����"
				case BUFF_SKILL_INFO::Condition::TypeDexterity:						return pLunaGameDataExtracterDlg->GetSystemMsg( 158 );		// "��ø"
				case BUFF_SKILL_INFO::Condition::TypeWisdom:						return pLunaGameDataExtracterDlg->GetSystemMsg( 161 );		// "����"
				case BUFF_SKILL_INFO::Condition::TypeVitality:						return pLunaGameDataExtracterDlg->GetSystemMsg( 159 );		// "ü��"
				case BUFF_SKILL_INFO::Condition::TypePhysicalAttack:				return pLunaGameDataExtracterDlg->GetSystemMsg( 152 );		// "���� ���ݷ�"
				case BUFF_SKILL_INFO::Condition::TypePhysicalDefense:				return pLunaGameDataExtracterDlg->GetSystemMsg( 153 );		// "���� ����"
				case BUFF_SKILL_INFO::Condition::TypeMagicalAttack:					return pLunaGameDataExtracterDlg->GetSystemMsg( 155 );		// "���� ���ݷ�"
				case BUFF_SKILL_INFO::Condition::TypeMagicalDefense:				return pLunaGameDataExtracterDlg->GetSystemMsg( 156 );		// "���� ����"
				case BUFF_SKILL_INFO::Condition::TypeCriticalRate:					return pLunaGameDataExtracterDlg->GetSystemMsg( 842 );		// "ũ��Ƽ�� ��ġ";
				case BUFF_SKILL_INFO::Condition::TypeCriticalDamage:				return pLunaGameDataExtracterDlg->GetSystemMsg( 843 );		// "ũ��Ƽ�� ������";
				case BUFF_SKILL_INFO::Condition::TypeAccuracy:						return pLunaGameDataExtracterDlg->GetSystemMsg( 162 );		// "����"
				case BUFF_SKILL_INFO::Condition::TypeEvade:							return pLunaGameDataExtracterDlg->GetSystemMsg( 162 );		// "����"
				case BUFF_SKILL_INFO::Condition::TypeMoveSpeed:						return pLunaGameDataExtracterDlg->GetSystemMsg( 841 );		// "ȸ��"
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_ConditionOperation:
			{
				switch( buffSkillInfo.mCondition.mOperation )
				{
				case BUFF_SKILL_INFO::Condition::OperationNone:			return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );	// "����"
				case BUFF_SKILL_INFO::Condition::OperationMoreEqual:	return pLunaGameDataExtracterDlg->GetSystemMsg( 2056 );	// �̻�
				case BUFF_SKILL_INFO::Condition::OperationLessEqual:	return pLunaGameDataExtracterDlg->GetSystemMsg( 2057 );	// ����
				case BUFF_SKILL_INFO::Condition::OperationMore:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2058 );	// �ʰ�
				case BUFF_SKILL_INFO::Condition::OperationLess:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2059 );	// �̸�
				case BUFF_SKILL_INFO::Condition::OperationEqual:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2059 );	// ����
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_ConditionValue:
			{
				_stprintf( txt, _T("%d"), (int)buffSkillInfo.mCondition.mValue );
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_Count:
			{
				_stprintf( txt, _T("%d"), buffSkillInfo.Count );
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_RuleBattle:
			{
				switch( buffSkillInfo.mRuleBattle )
				{
				case eBuffSkillActiveRule_Active:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2206 );	// ȿ�� �ߵ�
				case eBuffSkillActiveRule_Delete:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2063 ); // ȿ�� ����
				case eBuffSkillActiveRule_Stop:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2064 ); // ȿ�� ����
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_RulePeace:
			{
				switch( buffSkillInfo.mRulePeace )
				{
				case eBuffSkillActiveRule_Active:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2206 );	// ȿ�� �ߵ�
				case eBuffSkillActiveRule_Delete:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2063 ); // ȿ�� ����
				case eBuffSkillActiveRule_Stop:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2064 ); // ȿ�� ����
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_RuleMove:
			{
				switch( buffSkillInfo.mRuleMove )
				{
				case eBuffSkillActiveRule_Active:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2206 );	// ȿ�� �ߵ�
				case eBuffSkillActiveRule_Delete:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2063 ); // ȿ�� ����
				case eBuffSkillActiveRule_Stop:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2064 ); // ȿ�� ����
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_RuleStop:
			{
				switch( buffSkillInfo.mRuleStop )
				{
				case eBuffSkillActiveRule_Active:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2206 );	// ȿ�� �ߵ�
				case eBuffSkillActiveRule_Delete:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2063 ); // ȿ�� ����
				case eBuffSkillActiveRule_Stop:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2064 ); // ȿ�� ����
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_RuleRest:
			{
				switch( buffSkillInfo.mRuleRest )
				{
				case eBuffSkillActiveRule_Active:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2206 );	// ȿ�� �ߵ�
				case eBuffSkillActiveRule_Delete:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2063 ); // ȿ�� ����
				case eBuffSkillActiveRule_Stop:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2064 ); // ȿ�� ����
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_Die:
			{
				switch( buffSkillInfo.Die  )
				{
				case 0:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2071 );		// "�����"
				case 1:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2072 );		// "������"
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_CountType:
			{
				switch( buffSkillInfo.CountType )
				{
				case eBuffSkillCountType_None:					return pLunaGameDataExtracterDlg->GetSystemMsg( 151 );		// "����";
				case eBuffSkillCountType_Dead:					return pLunaGameDataExtracterDlg->GetSystemMsg( 2077 );		// "ĳ���� ���"
				case eBuffSkillCountType_AnyDamageVolumn:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2078 );		// 	"��� �ǰ� ��ġ"
				case eBuffSkillCountType_AnyDamage:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2079 );		// "��� �ǰ� ȸ��"
				case eBuffSkillCountType_AnyHitVolumn:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2080 );		// "��� ���� ��ġ"
				case eBuffSkillCountType_AnyHit:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2081 );		// "��� ���� ȸ��"
				case eBuffSkillCountType_PhysicalDamageVolumn:	return pLunaGameDataExtracterDlg->GetSystemMsg( 2082 );		// "���� �ǰ� ��ġ"
				case eBuffSkillCountType_PhysicalDamage:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2083 );		// "���� �ǰ� ȸ��"
				case eBuffSkillCountType_PhysicalHitVolumn:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2084 );		// "���� ���� ��ġ"
				case eBuffSkillCountType_PhysicalHit:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2085 );		// "���� ���� ȸ��"
				case eBuffSkillCountType_MagicalDamageVolumn:	return pLunaGameDataExtracterDlg->GetSystemMsg( 2086 );		// "���� �ǰ� ��ġ"
				case eBuffSkillCountType_MagicalDamage:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2087 );		// "���� �ǰ� ȸ��"
				case eBuffSkillCountType_MagicalHitVolumn:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2088 );		// "���� ���� ��ġ"
				case eBuffSkillCountType_MagicalHit:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2089 );		// "���� ���� ȸ��"
				case eBuffSkillCountType_HealVolumn:			return pLunaGameDataExtracterDlg->GetSystemMsg( 2090 );		// "���� �� ��ġ"
				case eBuffSkillCountType_Heal:					return pLunaGameDataExtracterDlg->GetSystemMsg( 2091 );		// "���� �� ȸ��"
				case eBuffSkillCountType_BeHealedVolumn:		return pLunaGameDataExtracterDlg->GetSystemMsg( 2092 );		// "���� ���� ��ġ"
				case eBuffSkillCountType_BeHealed:				return pLunaGameDataExtracterDlg->GetSystemMsg( 2093 );		// "���� ���� ȸ��"
				}
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_IsEndTime:
			{
				return ( buffSkillInfo.IsEndTime ? pLunaGameDataExtracterDlg->GetSystemMsg( 2207 ) : pLunaGameDataExtracterDlg->GetSystemMsg( 752 ) );
			}
			break;
		case eToolTipMsgKeyWordType_BuffSkill_ItemCount1:
		case eToolTipMsgKeyWordType_BuffSkill_ItemCount2:
			{
				const int nMaxArraySize = sizeof( buffSkillInfo.ItemCount ) / sizeof( *buffSkillInfo.ItemCount );
				const int nArrayIndex = keywordType - (int)eToolTipMsgKeyWordType_BuffSkill_Item1;
				if( nArrayIndex >= nMaxArraySize )
					break;

				_stprintf( txt, _T("%d"), buffSkillInfo.ItemCount[ nArrayIndex ] );
			}
			break;
		}
	}
	// Item ������ �̿��ϴ� ���
	else
	{
		const ITEM_INFO& itemInfo = pLunaGameDataExtracterDlg->GetItemInfo( dwToolTipIndex );
		if( itemInfo.ItemIdx != dwToolTipIndex )
			return "";

		switch( (eToolTipMsgKeyWordType)keywordType )
		{
		case eToolTipMsgKeyWordType_Item_Name:
			{
				return itemInfo.ItemName;
			}
			break;
		}
	}

	return txt;
}

// Script���ڿ����� �������� ��ȯ�Ѵ�.
void CTooltipMsgConverter::ConvertToolTipMsgKeyWordFormText( DWORD dwToolTipIndex, std::string& strMsg, std::string::size_type startPos, int prevKeyWordType )
{
	std::string::size_type keywordStart = 0;
	while( ( keywordStart = strMsg.find( "$", startPos ) ) != std::string::npos )
	{
		startPos = keywordStart + 1;

		std::string::size_type keywordSize = 0;
		std::string keyword;
		// ����� ����
		if( GetToolTipMsgKeyWordFromText( strMsg, keyword, keywordStart, keywordSize ) == FALSE )
			continue;
		

		// ����� ����� �˻�
		DWORD dwHashCode = GetHashCodeFromTxt( keyword.c_str() );
		std::map< DWORD, int >::const_iterator mapKeyWordIter = m_mapToolTipMsgKeyWord.find( dwHashCode );
		if( mapKeyWordIter != m_mapToolTipMsgKeyWord.end() )
		{
			strMsg.replace( keywordStart, keywordSize, "" );

			char txt[MAX_PATH]={0,};
			const char* convertStr = GetTextFromToolTipMsgKeyWordType( dwToolTipIndex, mapKeyWordIter->second, txt, MAX_PATH, prevKeyWordType );
			if( convertStr == NULL )
				continue;

			strMsg.insert( keywordStart, convertStr );

			// ������ ���� �˻�
			const char* strPtr = "->";
			const size_t nPtrSize = strlen( strPtr );
			std::string ptrstr = strMsg.substr( keywordStart, nPtrSize );
			if( ptrstr.compare( strPtr ) == 0 )
			{
				strMsg.replace( keywordStart, nPtrSize, "" );

				// ������ ����� ��ȯ
				ConvertToolTipMsgKeyWordFormText( dwToolTipIndex, strMsg, keywordStart, mapKeyWordIter->second );
			}
		}

		if( prevKeyWordType != eToolTipMsgKeyWordType_None ) 
			return;
	}
}
