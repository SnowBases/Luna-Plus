#include "StdAfx.h"
#include "AttackManager.h"
#include "Network.h"
#include "PackedData.h"
#include "ServerSystem.h"
#include "CharMove.h"
#include "UserTable.h"
#include "ObjectStateManager.h"
#include "Monster.h"
#include "PartyManager.h"
#include "Party.h"
#include "Player.h"
#include "GuildManager.h"
#include "pet.h"
#include "petmanager.h"

#include "SiegeWarfareMgr.h"

#include "GuildTournamentMgr.h"
#include "ItemManager.h"

#include "..\[CC]Header\CommonCalcFunc.h"
// 080616 LUJ, �̺�Ʈ �߻� �ÿ� ��ų�� �׼��� ���ϱ� ���� ����
#include "Event.h"

CAttackManager::CAttackManager()
{
	// 080121 KTH -- ���ǿ����� ��û���� �⺻ 35%�� ���� �Ѵ�.
	m_PvpDamageRatio = 35;
	m_GTDamageRatio = 10.0f;
}

CAttackManager::~CAttackManager()
{

}

void CAttackManager::sendDieMsg(CObject * pAttacker,CObject* pTarget)
{
	MSG_DWORD2 m2c;
	m2c.Category	= MP_USERCONN;

	if(pTarget->GetObjectKind() & eObjectKind_Monster)
	{
		m2c.Protocol	= MP_USERCONN_MONSTER_DIE;

		m2c.dwObjectID	= pAttacker->GetID();
		m2c.dwData1		= 0;
		m2c.dwData2		= pTarget->GetID();
		
		PACKEDDATA_OBJ->QuickSend(pTarget,&m2c,sizeof(m2c));
	}
	else if(pTarget->GetObjectKind() == eObjectKind_Player)
	{
		m2c.Protocol = MP_USERCONN_CHARACTER_DIE;

		m2c.dwObjectID	= pAttacker->GetID();
		m2c.dwData1		= pAttacker->GetID();
		m2c.dwData2		= pTarget->GetID();
		
		PACKEDDATA_OBJ->QuickSend(pTarget,&m2c,sizeof(m2c));
	}
	else if(pTarget->GetObjectKind() & eObjectKind_Pet)
	{
		// 091110 ONS �� �ִϸ��̼� �߰�
		m2c.Protocol = MP_USERCONN_PET_DIE;

		m2c.dwObjectID	= pAttacker->GetID();
		m2c.dwData1		= pAttacker->GetID();
		m2c.dwData2		= pTarget->GetID();
		
		PACKEDDATA_OBJ->QuickSend(pTarget,&m2c,sizeof(m2c));
	}
}

void CAttackManager::RecoverLife(CObject* pOperator,CObject* pObject, float RecoverLifeVal,RESULTINFO* pResultInfo)
{
	DWORD realAddVal = 0;
	DWORD val = 0;	//KES 070918 val; --> val = 0;  (val�� �����Ⱚ�� ���·� AddLife�� �� ����� �־. RecoverMana()�Լ��� ����)

	// 100219 ShinJS --- ���� ���� ���� 
	// �� ȸ���� = ( ( (���� * 11) + ( ���� * 4 ) + ( ���� * 20 ) ) * ��ų���� ) / 800 + 100
	if( pOperator->GetObjectKind() == eObjectKind_Player )
	{
		CPlayer* pPlayer = (CPlayer*)pOperator;
		val = ( DWORD )( ( ( ( pPlayer->GetWisdom() * 11 ) + ( pPlayer->GetIntelligence() * 4 ) + ( pPlayer->GetLevel() * 20 ) ) * RecoverLifeVal ) / 800.f + 100.f );
	}
	else if( pOperator->GetObjectKind() == eObjectKind_Pet )
	{
		PlayerStat& pStat = ((CPet*)pOperator)->GetStat();
		val = ( DWORD )( ( ( ( pStat.mWisdom.mPlus * 11 ) + ( pStat.mIntelligence.mPlus * 4 ) + ( pOperator->GetLevel() * 20 ) ) * RecoverLifeVal ) / 800.f + 100.f );
	}
	else if(pObject->GetObjectKind() & eObjectKind_Monster)
	{
		val = DWORD(RecoverLifeVal);
	}

	// 080728 KTH -- ������ ��� �϶� ���� ����
	if( SIEGEWARFAREMGR->Is_CastleMap() == FALSE &&
  		SIEGEWARFAREMGR->IsSiegeWarfareZone() &&
  		SIEGEWARFAREMGR->GetState() > eSiegeWarfare_State_Before )
  	{
  		val = DWORD( val * (SIEGEWARFAREMGR->GetDecreaseHealRatio() / 100) );
  		
  		if( val < 1 )
  			val = 1;
  	}

	if(g_pServerSystem->GetMapNum() == GTMAPNUM)
		val = DWORD( val * 0.5f );	// �����ʸ�Ʈ ������ 50%��

	pObject->AddLife( val, &realAddVal, FALSE );
	pResultInfo->HealLife = realAddVal;

	if( pOperator->GetObjectKind() == eObjectKind_Player||
		pOperator->GetObjectKind() == eObjectKind_Pet)
	{
		if(pObject->GetObjectKind() == eObjectKind_Player)
		{
			((CPlayer*)pObject)->AddAggroToMyMonsters(
				int(realAddVal) / 3,
				pOperator->GetID(),
				pResultInfo->mSkillIndex);
		}
		else if(pObject->GetObjectKind() == eObjectKind_Pet)
		{
			((CPet*)pObject)->AddAggroToMyMonsters(
				int(realAddVal) / 3,
				pOperator->GetID(),
				pResultInfo->mSkillIndex);
		}
	}

	// 090204 LUJ, ī��Ʈ ������ �ִ� ��ų�� ������Ʈ�Ѵ�
	pOperator->RemoveBuffCount( eBuffSkillCountType_HealVolumn, val );
	pObject->RemoveBuffCount( eBuffSkillCountType_BeHealedVolumn, val );
}

void CAttackManager::RecoverMana(CObject* pOperator,CObject* pObject, float RecoverManaVal,RESULTINFO* pResultInfo)
{
	DWORD realAddVal = 0;
	DWORD val = 0;

	if( pOperator->GetObjectKind() == eObjectKind_Player )
	{
		// ���� ȸ���� = ( ( (���� * 11) + ( ���� * 4 ) + ( ���� * 20 ) ) * ��ų���� ) / 800 + 100
		CPlayer* pPlayer = (CPlayer*)pOperator;
		val = ( DWORD )( ( ( (pPlayer->GetWisdom() * 11) + ( pPlayer->GetIntelligence() * 4 ) + ( pPlayer->GetLevel() * 20 ) ) * RecoverManaVal ) / 800.f + 100.f );
	}
	else if( pOperator->GetObjectKind() == eObjectKind_Pet )
	{
		PlayerStat& pStat = ((CPet*)pOperator)->GetStat();
		val = ( DWORD )( ( ( ( pStat.mWisdom.mPlus * 11 ) + ( pStat.mIntelligence.mPlus * 4 ) + ( pOperator->GetLevel() * 20 ) ) * RecoverManaVal ) / 800.f + 100.f );
	}
	pObject->AddMana( val, &realAddVal );
	pResultInfo->RechargeMana = realAddVal;
}

void CAttackManager::PhysicAttack( CObject* pAttacker, CObject* pTarget, RESULTINFO* pDamageInfo, float Accuracy, float AddDamage, WORD AddType )
{
	if( !pAttacker || !pTarget )
		return;

	if( pTarget->GetAbnormalStatus()->IsGod )
	{
		return;
	}

	// �⺻ ��ġ ����
	float Avoid = 0;
	float Attack = 0;
	float Defense = 1;
	float Shield = 0;
	float Block = 0;
	float CriticalRate = 0;
	float CriticalDamagePlus = 0;
	float CriticalDamageRate = 0;
	float Strength = 0;
	float OriginalStragnth = 0;
	float RateAddValue = 0;
	float PlusAddValue = 0;
	float Weapon = 1;
	BOOL bLevelPenalty = FALSE;
	// 080910 LUJ, ��� �� ������ ��ġ�� ����ϱ� ���� ����
	float vitality = 0;

	if( pAttacker->GetObjectKind() == eObjectKind_Player )
	{
		CPlayer* pPlayer = (CPlayer*)pAttacker;
		
		Accuracy += pPlayer->GetAccuracy();

		int min = ( int )( pPlayer->GetPhysicAttackMin() );
		int max = ( int )( pPlayer->GetPhysicAttackMax() );

		if( max > min )
		{
			Attack = float( random( min, max ) );
		}
		else
		{
			Attack = float( min );
		}

		CriticalRate = pPlayer->GetCriticalRate();
		CriticalDamagePlus = pPlayer->GetCriticalDamagePlus();
		CriticalDamageRate = pPlayer->GetCriticalDamageRate();

		Weapon = pPlayer->GetItemBaseStats().mPhysicAttack.mPlus;
		OriginalStragnth = (float)pPlayer->GetRealStrength();
		// 100112 ONS �������ݿ� ������.
		Strength		 = (float)pPlayer->GetStrength();

		bLevelPenalty = TRUE;
	}
	else if( pAttacker->GetObjectKind() & eObjectKind_Monster )
	{
		CMonster* pMonster = (CMonster*)pAttacker;
		const BASE_MONSTER_LIST& baseMonsterList = pMonster->GetSMonsterList();

		float accuracy = baseMonsterList.Accuracy + pMonster->GetBuffStatus()->Accuracy;
		if( accuracy > 0 )
		{
			Accuracy = accuracy;
		}

		float min = baseMonsterList.AttackPhysicalMin + pMonster->GetBuffStatus()->PhysicAttack;
		float max = baseMonsterList.AttackPhysicalMax + pMonster->GetBuffStatus()->PhysicAttack;

		if( min < 0 ) min = 0;
		if( max < 0 ) max = 0;

		Attack = random( min, max );
			
		float criticalRate = baseMonsterList.CriticalPercent + pMonster->GetBuffStatus()->CriticalRate;

		if( criticalRate )
		{
			CriticalRate = criticalRate;
		}
	
		CriticalDamageRate = pMonster->GetBuffStatus()->CriticalDamage;
	}
	else if( pAttacker->GetObjectKind() == eObjectKind_Pet )
	{
		CPet* pPet = ( CPet* )pAttacker;

		PlayerStat& pStat = pPet->GetStat();
		Accuracy += pStat.mAccuracy.mPlus;

		int iMax	=	(int)pPet->GetPhysicAttackMax();
		int	iMin	=	(int)pPet->GetPhysicAttackMin();

		float	fTempAttack	=	0.0f;

		if( iMax > iMin )
		{
			fTempAttack = float( random( iMin, iMax ) );
		}
		else
		{
			fTempAttack = float( iMin );
		}

		Attack	=	( pPet->CalcPhysicAttack( fTempAttack ) ) * PETMGR->GetFriendlyPenalty( pPet );

		Strength = pStat.mStrength.mPlus;
		Weapon	=	pPet->GetItemStat().mPhysicAttack.mPlus;

		ITEMBASE* pitembase = pPet->GetWearedItem( ePetEquipSlot_Weapon );

		if( pitembase )
		{
			ITEM_INFO* piteminfo = ITEMMGR->GetItemInfo( pitembase->wIconIdx );

			if( piteminfo )
			{
				Weapon = float(piteminfo->PhysicAttack);
			}
		}

		CriticalRate = pStat.mCriticalRate.mPlus;
		CriticalDamageRate = pStat.mCriticalDamage.mPlus;

		bLevelPenalty = TRUE;
	}
	else
	{
		ASSERT(0);
	}

	if( pTarget->GetObjectKind() == eObjectKind_Player )
	{
		CPlayer* pPlayer = (CPlayer*)pTarget;
		
		Avoid = pPlayer->GetAvoid();
		Defense = pPlayer->GetPhysicDefense();
		Block = pPlayer->GetBlock();

		// 080910 LUJ, �÷��̾ ������ ������ ������ ������
		Shield		= float( pPlayer->GetShieldDefense() );
		vitality	= float( pPlayer->GetVitality() );

		if( pAttacker->GetObjectKind() == eObjectKind_Player )	//���� ������ ���
		{
			CPlayer* pAttackPlayer = (CPlayer*)pAttacker;
			if( pAttackPlayer->IsPKMode() )		//PK������ ����� ��������
				pAttackPlayer->SetPKStartTimeReset();

			if( pPlayer->IsPKMode() )			//PK������ ������� �¾�����
				pPlayer->SetPKStartTimeReset();
		}

	}
	// 090316 LUJ, Ż���� ���߽�ų �� ����. ����! ���� ���θ� ��Ʈ ����� �˻��Ѵ�.
	//			���� ������ �񱳹��� ��ġ�� ���, ���ͷ� üũ�Ǿ� ���ݹް� �ȴ�.
	else if( pTarget->GetObjectKind() == eObjectKind_Vehicle )
	{
		pDamageInfo->bDodge = TRUE;
		pDamageInfo->RealDamage = 0;
		return;
	}
	else if( pTarget->GetObjectKind() & eObjectKind_Monster )
	{
		CMonster* pMonster = (CMonster*)pTarget;
		const BASE_MONSTER_LIST& baseMonsterList = pMonster->GetSMonsterList();

		float avoid = baseMonsterList.Avoid + pMonster->GetBuffStatus()->Avoid;
		if( avoid > 0 )
			Avoid = avoid;
		Defense = max(baseMonsterList.PhysicalDefense + pMonster->GetBuffStatus()->PhysicDefense, 0);
	}
	else if( pTarget->GetObjectKind() == eObjectKind_Pet )
	{
		CPet* pPet = (CPet*)pTarget;
		PlayerStat& pStat = pPet->GetStat();

		vitality = pStat.mVitality.mPlus;
		Avoid = pStat.mEvade.mPlus;
		Defense = pStat.mPhysicDefense.mPlus;
		Block = 0;

		Defense *= PETMGR->GetFriendlyPenalty( pPet );
		if( pAttacker->GetObjectKind() == eObjectKind_Player )	//���� ������ ���
		{
			CPlayer* pAttackPlayer = (CPlayer*)pAttacker;
			if( pAttackPlayer->IsPKMode() )		//PK������ ����� ��������
				pAttackPlayer->SetPKStartTimeReset();
		}
	}
	else
	{
		ASSERT(0);
	}

	// ��׷ο� ���� ȸ�� �г�Ƽ
	const DWORD dwAggroNum = pTarget->GetAggroNum();
	if( dwAggroNum >= 3 )
	{
		const float fAggroPanalty = (float)pow( (double)( dwAggroNum - 2 ), 2 );
		Avoid = max( Avoid * ( 1 - ( fAggroPanalty * 0.01f ) ), 0 );
	}

	// ���߷� = 85 + ���� - ȸ��
	const float ACC = 85.f + Accuracy - Avoid;
	if( ACC < float( ( rand() % 100 ) + 1 ) )
	{
		pDamageInfo->bDodge = TRUE;
		pDamageInfo->RealDamage = 0;
		return;
	}

	// ��׷ο� ���� ���� �г�Ƽ
	if( dwAggroNum >= 6 )
	{
		const float fAggroPanalty = (float)pow( (double)( dwAggroNum - 5 ), 1.5 );
		Defense = max( Defense * ( 1 - ( fAggroPanalty * 0.01f ) ), 0 );
	}

	float damage = 1.f;
	if( AddType == 1 )
	{
		// ( ���ݷ� - ���� ) * ( ( 1000 + ��ų���� + ���� ) / 1000 )
		damage = ( Attack - Defense ) * ( ( 1000.f + AddDamage + Strength ) / 1000.f );
	}
	else if( AddType == 2 )
	{
		// ( ���ݷ� - ���� ) * ( ( 1000 + ��ų���� + ������ݷ� ) / 1000 )
		damage = ( Attack - Defense ) * ( ( 1000.f + AddDamage + Weapon ) / 1000.f );
	}

	damage = ( damage * ( 1 +  ( RateAddValue / 100 ) ) ) + PlusAddValue;

	// ������� ������ �� ���� ��� ������ 1.5%�� ������ ����
	const float fAttackerLevel = pAttacker->GetLevel();
	const float fTargetLevel = pTarget->GetLevel();
	if( fAttackerLevel < fTargetLevel )
	{
		damage = ( damage < 1 ? 1 : damage );
		damage = damage * ( 1 + ( fAttackerLevel - fTargetLevel ) * 0.015f );
	}

	// ��
	if( 0 < Shield && Block > float(rand() % 100) )
	{
		pDamageInfo->bBlock	= TRUE;
		damage = ( damage * ( 0.6f - ( vitality / 4000 ) ) ) - Shield;
	}
	// 100221 ShinJS --- ���� ��� ũ��Ƽ�� ����.
	else if( (CriticalRate >= 100.f || CriticalRate >= ( ( rand() % 100 ) + 1 )) )
	{
		damage = ( damage * 1.5f ) * ( 1 + ( CriticalDamageRate / 100 ) ) + CriticalDamagePlus;

		// ũ��Ƽ���� ���
		pDamageInfo->bCritical = TRUE;
	}

	if( pTarget->GetObjectKind() == eObjectKind_Player && pAttacker->GetObjectKind() == eObjectKind_Player )
	{
		if(g_pServerSystem->GetMapNum() == GTMAPNUM)
			damage *= (this->GetGTDamageRatio() / 100);
	}

	// 080728 KTH -- ������ ��� �϶�
	if( SIEGEWARFAREMGR->Is_CastleMap() == FALSE &&
  		SIEGEWARFAREMGR->IsSiegeWarfareZone() &&
  		SIEGEWARFAREMGR->GetState() > eSiegeWarfare_State_Before )
	{
		damage *= (SIEGEWARFAREMGR->GetDecreaseDamageRatio() / 100 );
	}

	if( damage < 1 )
	{
		damage = 1;
	}

	pDamageInfo->RealDamage = (DWORD)damage;

	// 090204 LUJ, ī��Ʈ ������ �ִ� ��ų�� ������Ʈ�Ѵ�
	{
		float count = Attack;

		switch( AddType )
		{
		case 1:
			{
				count += AddDamage;
				break;
			}
		case 2:
			{
				count *= ( 1.0f + AddDamage / 100.0f );
				break;
			}
		}

		pAttacker->RemoveBuffCount( eBuffSkillCountType_PhysicalHitVolumn, int( count ) );
		pTarget->RemoveBuffCount( eBuffSkillCountType_PhysicalDamageVolumn, int( count ) );
	}
}

// 080912 LUJ, ���� ũ��Ƽ�� ���� ����(��ȹ: �۰���)
void CAttackManager::MagicAttack( CObject* pAttacker, CObject* pTarget, RESULTINFO* pDamageInfo, float Accuracy, float AddDamage, WORD AddType )
{
	if( !pAttacker || !pTarget )
		return;

	if( pTarget->GetAbnormalStatus()->IsGod )
	{
		return;
	}

	// �⺻ ��ġ ����
	float Attack = 1;
	float Defense = 1;
	float CriticalRate = 0;
	float CriticalDamagePlus = 0;
	float CriticalDamageRate = 0;
	float Intelligence = 1;
	float Vitality = 0;
	float OriginalIntelligence = 0;
	float RateAddValue = 0;
	float PlusAddValue = 0;
	float Weapon = 1;
	// 080912 LUJ, ũ��Ƽ�� ���� ��꿡 ����ϱ� ���� �߰�
	float wisdom				= 0;
	float castingProtectValue	= pAttacker->GetBuffStatus()->CastingProtect;
	float castingProtectRate	= pAttacker->GetRateBuffStatus()->CastingProtect + 1.0f;

	if( pAttacker->GetObjectKind() == eObjectKind_Player )
	{
		CPlayer* pPlayer = (CPlayer*)pAttacker;
		
		Attack = pPlayer->GetMagicAttack();
		Intelligence = float( pPlayer->GetIntelligence() );
		OriginalIntelligence = (float)pPlayer->GetRealIntelligence();

		CriticalRate = pPlayer->GetMagicCriticalRate();
		CriticalDamageRate = pPlayer->GetMagicCriticalDamageRate();
		CriticalDamagePlus = pPlayer->GetMagicCriticalDamagePlus();

		// 080912 LUJ, ũ��Ƽ�� ���� ��꿡 ����ϱ� ���� ����
		wisdom 				= 	float( pPlayer->GetWisdom() );
		castingProtectValue	+= 	pPlayer->GetPassiveStatus()->CastingProtect;
		castingProtectRate	+= 	pPlayer->GetRatePassiveStatus()->CastingProtect;

		Weapon = pPlayer->GetItemBaseStats().mMagicAttack.mPlus;
	}
	else if( pAttacker->GetObjectKind() & eObjectKind_Monster )
	{
		CMonster* pMonster = (CMonster*)pAttacker;
		const BASE_MONSTER_LIST& baseMonsterList = pMonster->GetSMonsterList();
		
		float min = baseMonsterList.AttackMagicalMin + pMonster->GetBuffStatus()->MagicAttack;
		float max = baseMonsterList.AttackMagicalMax + pMonster->GetBuffStatus()->MagicAttack;

		if( min < 0 ) min = 0;
		if( max < 0 ) max = 0;

		Attack = random( min, max );

		Weapon = float(baseMonsterList.Level * 2);
	}
	else if( pAttacker->GetObjectKind() == eObjectKind_Pet )
	{
		CPet* pPet = (CPet*)pAttacker;
		PlayerStat& pStat = pPet->GetStat();

		int iMax	=	(int)pPet->GetMagicAttackMax();
		int	iMin	=	(int)pPet->GetMagicAttackMin();

		float	fTempAttack	=	0.0f;

		if( iMax > iMin )
		{
			fTempAttack = float( random( iMin, iMax ) );
		}
		else
		{
			fTempAttack = float( iMin );
		}

		Attack	=	pPet->CalcMagicAttack( fTempAttack );

		Intelligence = pStat.mIntelligence.mPlus;
		
		ITEMBASE* pitembase = pPet->GetWearedItem( ePetEquipSlot_Weapon );

		if( pitembase )
		{
			ITEM_INFO* piteminfo = ITEMMGR->GetItemInfo( pitembase->wIconIdx );

			if( piteminfo )
			{
				Weapon = float(piteminfo->MagicAttack);
			}
		}

		Attack *= PETMGR->GetFriendlyPenalty( pPet );
		CriticalRate += pPet->GetPassiveStatus().MagicCriticalRate;

		Weapon	=	pPet->GetItemStat().mMagicAttack.mPlus;
	}
	else
	{
		ASSERT(0);
	}

	if( pTarget->GetObjectKind() == eObjectKind_Player )
	{
		CPlayer* pPlayer = (CPlayer*)pTarget;
		
		Defense = pPlayer->GetMagicDefense();
		Vitality = (float)pPlayer->GetVitality();

		if( pAttacker->GetObjectKind() == eObjectKind_Player )	//���� ������ ���
		{
			CPlayer* pAttackPlayer = (CPlayer*)pAttacker;
			if( pAttackPlayer->IsPKMode() )		//PK������ ����� ��������
				pAttackPlayer->SetPKStartTimeReset();

			if( pPlayer->IsPKMode() )			//PK������ ������� �¾�����
				pPlayer->SetPKStartTimeReset();
		}
	}
	// 090316 LUJ, Ż���� ���߽�ų �� ����. ����! ���� ���θ� ��Ʈ ����� �˻��Ѵ�.
	//			���� ������ �񱳹��� ��ġ�� ���, ���ͷ� üũ�Ǿ� ���ݹް� �ȴ�.
	else if( pTarget->GetObjectKind() == eObjectKind_Vehicle )
	{
		Accuracy = 0;
	}
	else if( pTarget->GetObjectKind() & eObjectKind_Monster )
	{
		CMonster* pMonster = (CMonster*)pTarget;
		const BASE_MONSTER_LIST& baseMonsterList = pMonster->GetSMonsterList();

		Defense = max(baseMonsterList.MagicalDefense + pMonster->GetBuffStatus()->MagicDefense, 0);
	}
	else if( pTarget->GetObjectKind() == eObjectKind_Pet )
	{
		CPet* pPet = (CPet*)pTarget;
		PlayerStat& pStat = pPet->GetStat();

		Vitality = pStat.mVitality.mPlus;
		Defense = pStat.mMagicDefense.mPlus;
		Defense *= PETMGR->GetFriendlyPenalty( pPet );
		if( pAttacker->GetObjectKind() == eObjectKind_Player )	//���� ������ ���
		{
			CPlayer* pAttackPlayer = (CPlayer*)pAttacker;
			if( pAttackPlayer->IsPKMode() )		//PK������ ����� ��������
				pAttackPlayer->SetPKStartTimeReset();
		}
	}
	else
	{
		ASSERT(0);
	}

	float damage = 1.f;
	if( AddType == 1 )
	{
		// ( ���ݷ� - ���� ) * ( ( 1000 + ��ų���� + ���� ) / 1000 )
		damage = ( Attack - Defense ) * ( ( 1000.f + AddDamage + Intelligence ) / 1000.f );
	}
	else if( AddType == 2 )
	{
		// ( ���ݷ� - ���� ) * ( ( 1000 + ��ų���� + ������ݷ� ) / 1000 )
		damage = ( Attack - Defense ) * ( ( 1000.f + AddDamage + Weapon ) / 1000.f );
	}

	damage = ( damage * ( 1 +  ( RateAddValue / 100 ) ) ) + PlusAddValue;

	// ������� ������ �� ���� ��� ������ 1.5%�� ������ ����
	const float fAttackerLevel = pAttacker->GetLevel();
	const float fTargetLevel = pTarget->GetLevel();
	if( fAttackerLevel < fTargetLevel )
	{
		damage = ( damage < 1 ? 1 : damage );
		damage = damage * ( 1 + ( fAttackerLevel - fTargetLevel ) * 0.015f );
	}

	// ũ��Ƽ���� ���
	if( CriticalRate >= 100.f || CriticalRate >= ( ( rand() % 100 ) + 1 ) )
	{
		damage = ( damage * 1.5f ) * ( 1 + ( CriticalDamageRate / 100 ) ) + CriticalDamagePlus;

		pDamageInfo->bCritical = TRUE;
	}

	if( pTarget->GetObjectKind() == eObjectKind_Player && pAttacker->GetObjectKind() == eObjectKind_Player )
	{
		if(g_pServerSystem->GetMapNum() == GTMAPNUM)
			damage *= (this->GetGTDamageRatio() / 100);
	}

	// 080728 KTH -- ������ ��� �϶�
	if( SIEGEWARFAREMGR->Is_CastleMap() == FALSE &&
  		SIEGEWARFAREMGR->IsSiegeWarfareZone() &&
  		SIEGEWARFAREMGR->GetState() > eSiegeWarfare_State_Before )
	{
		damage *= (SIEGEWARFAREMGR->GetDecreaseDamageRatio() / 100 );
	}

	if( damage < 1 )
	{
		damage = 1;
	}
	pDamageInfo->RealDamage = (DWORD)damage;

	// 090204 LUJ, ī��Ʈ ������ �ִ� ��ų�� ������Ʈ�Ѵ�
	{
		float count = Attack;

		switch( AddType )
		{
		case 1:
			{
				count += AddDamage;
				break;
			}
		case 2:
			{
				count *= ( 1.0f + AddDamage / 100.0f );
				break;
			}
		}

		// 090204 LUJ, ī��Ʈ ������ �ִ� ��ų�� ������Ʈ�Ѵ�
		pAttacker->RemoveBuffCount( eBuffSkillCountType_MagicalHitVolumn, int( count ) );
		pTarget->RemoveBuffCount( eBuffSkillCountType_MagicalDamageVolumn, int( count ) );
	}
}

void CAttackManager::SpecialAttack( CObject* pAttacker, CObject* pTarget, RESULTINFO* pDamageInfo, float Damage, WORD Type )
{
	if( !pAttacker || !pTarget )
		return;

	if( pTarget->GetAbnormalStatus()->IsGod )
	{
		return;
	}

	float damage = 0.f;
	float fTempDamage = 0.0f;

	if( Damage < 0 )
	{
		// 100226 ShinJS --- DOT ������ ����
		float fAttackStrength = 0.f;
		float fAttackIntelligense = 0.f;
		float fTargetVitality = 0.f;
		float fTargetWisdom = 0.f;
		float fAttackerLevel = (float)pAttacker->GetLevel();
		float fTargetLevel = (float)pTarget->GetLevel();

		switch( pAttacker->GetObjectKind() )
		{
		case eObjectKind_Player:
			{
				fAttackStrength = (float)((CPlayer*)pAttacker)->GetStrength();
				fAttackIntelligense = (float)((CPlayer*)pAttacker)->GetIntelligence();
			}
			break;
		case eObjectKind_Pet:
			{
				PlayerStat& pStat = ((CPet*)pTarget)->GetStat();
				fAttackStrength = (float)(pStat.mStrength.mPlus);
				fAttackIntelligense = (float)(pStat.mIntelligence.mPlus);
			}
			break;
		}

		switch( pTarget->GetObjectKind() )
		{
		case eObjectKind_Player:
			{
				fTargetVitality = (float)((CPlayer*)pTarget)->GetVitality();
				fTargetWisdom = (float)((CPlayer*)pTarget)->GetWisdom();
			}
			break;
		case eObjectKind_Pet:
			{
				PlayerStat& pStat = ((CPet*)pTarget)->GetStat();
				fTargetVitality = (float)(pStat.mVitality.mPlus);
				fTargetWisdom = (float)(pStat.mWisdom.mPlus);
			}
			break;
		}

		//BUFF DOT	= DOT_dmg * ( 1 + ( ( ������ �� + ������ ���� - ����� �ǰ� - ����� ���� ) / 3000 ) ) + ( ������ ���� - ����� ���� )									
		fTempDamage = ( -Damage * ( 1 + ( ( fAttackStrength + fAttackIntelligense - fTargetVitality - fTargetWisdom ) ) / 3000.f ) );
		
		if( fAttackerLevel <= fTargetLevel )
		{
			damage = fTempDamage + ( fAttackerLevel - fTargetLevel );
		}	
		else
		{
			damage = fTempDamage + 1;
		}

		// 090804 pdy �������� ����� ������ ���� ����
		if( SIEGEWARFAREMGR->Is_CastleMap() == FALSE &&
  			SIEGEWARFAREMGR->IsSiegeWarfareZone() &&
  			SIEGEWARFAREMGR->GetState() > eSiegeWarfare_State_Before )
  		{
			damage *= (SIEGEWARFAREMGR->GetDecreaseDamageRatio() / 100 );
  		}

		// 080115 KTH -- PVP Damage Ratio Setting
		if( pTarget->GetObjectKind() == eObjectKind_Player && pAttacker->GetObjectKind() == eObjectKind_Player )
		{
			if(g_pServerSystem->GetMapNum() == GTMAPNUM)
				damage = damage * (this->GetGTDamageRatio() / 100);
			else
				damage = damage * (this->GetPvpDamageRatio() / 100);

			CPlayer* pAttackPlayer = (CPlayer*)pAttacker;
			if( pAttackPlayer->IsPKMode() )			//PK������ ����� ��������
				pAttackPlayer->SetPKStartTimeReset();

			CPlayer* pTargetPlayer = (CPlayer*)pTarget;
			if( pTargetPlayer->IsPKMode() )			//PK������ ������� �¾�����
				pTargetPlayer->SetPKStartTimeReset();
		}

		if( damage < 1 )
			damage = 1;

		pDamageInfo->RealDamage = (DWORD)damage;

		// 100310 ShinJS --- �������� �Դ� ����� �����ǵ带 ������� ���
		if( pTarget->HasEventSkill( eStatusKind_DamageToManaDamage ) )
		{
			// eStatusKind_DamageToManaDamage �� ���� ó���� �Ҽ� �ֵ��� �Ѵ�.
			pTarget->Execute( CTakeDamageEvent( pAttacker, *pDamageInfo, eStatusKind_DamageToManaDamage ) );

			// Mana Damage
			pTarget->ManaDamage( pAttacker, pDamageInfo );
		}

		DWORD newLife = pTarget->Damage(pAttacker,pDamageInfo);

		if(newLife == 0)
		{
			// 080616 LUJ, ��� �� �̺�Ʈ�� ó���ϵ��� �Ѵ�
			// 080708 LUJ, ������/�����ڸ� ��� ���ڷ� �ѱ��
			pTarget->Execute( CDieEvent( pAttacker, pTarget ) );
			pAttacker->Execute( CKillEvent( pAttacker, pTarget ) );

			ATTACKMGR->sendDieMsg(pAttacker,pTarget);
			pTarget->Die(pAttacker);
		}
	}
	else
	{
		RecoverLife( pAttacker, pTarget, Damage, pDamageInfo );
	}
}

// 090204 LUJ, �ǰ� �� MP�� �սǵȴ�
void CAttackManager::BurnMana( CObject* offenseObject, CObject* defenseObject, const BUFF_SKILL_INFO* buffSkillInfo )
{
	if( ! offenseObject || ! defenseObject || ! buffSkillInfo )
	{
		return;
	}
	else if( defenseObject->GetAbnormalStatus()->IsGod )
	{
		return;
	}

	SKILL_INFO::Value damage = { 0 };

	// 090204 LUJ, ��ų�� ���� ���� ��ġ�� ���Ѵ�
	switch( buffSkillInfo->StatusDataType )
	{
	case BUFF_SKILL_INFO::StatusTypeAdd:
		{
			damage.mPlus += buffSkillInfo->StatusData;
			break;
		}
	case BUFF_SKILL_INFO::StatusTypePercent:
		{
			damage.mPlus += defenseObject->GetMaxMana() * buffSkillInfo->StatusData / 100.0f;
			break;
		}
	}

	// 090204 LUJ, MP ��ġ�� �����Ѵ�
	{
		const float manaDamage	= damage.mPlus * ( 1.0f + damage.mPercent );
		const float currentMana = float( defenseObject->GetMana() ) + manaDamage;

		defenseObject->SetMana( DWORD( max( 0, currentMana ) ) );
	}
}