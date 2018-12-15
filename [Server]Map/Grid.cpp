// Grid.cpp: implementation of the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Grid.h"
#include "PackedData.h"
#include "Network.h"
#include "CharMove.h"
#include "Object.h"
#include "Player.h"
// 080616 LUJ, ������ ���� �����ָ� Ÿ������ ���� �ʵ��� ó��
#include "Trap.h"

// 081027 LYW --- GridSystem : �� �Ŵ��� ȣ��.
#include "./PetManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrid::CGrid()
{
	m_CharacterHashTable.Initialize(10);
}

CGrid::~CGrid()
{
	m_CharacterHashTable.RemoveAll();
}

void CGrid::AddObject(CObject* pObject)
{
	CObject* pPreObject = m_CharacterHashTable.GetData(pObject->GetID());
	if(pPreObject)
	{
		char temp[256];
		sprintf(temp,"PreObj %d,  %s,   %d", pPreObject->GetID(),pPreObject->GetObjectName(),pPreObject);
		ASSERTMSG(0,temp);
		sprintf(temp,"NewObj %d,  %s,   %d", pObject->GetID(),pObject->GetObjectName(),pObject);
		ASSERTMSG(0,temp);
		return;
	}
	m_CharacterHashTable.Add(pObject,pObject->GetID());
}

void CGrid::RemoveObject(CObject* pObject)
{
	ASSERT(m_CharacterHashTable.GetData(pObject->GetID()) != NULL);
	m_CharacterHashTable.Remove(pObject->GetID());
}

void CGrid::AddNeighborGrid(CGrid* pGrid)
{
	m_NeighborGrid.AddTail(pGrid);
}

void CGrid::AddGridToPackedData(CPackedData* pPackedData)
{
	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	
	AddObjectToPacket(0,pPackedData);
	while( (pGrid = m_NeighborGrid.GetNextPos(pos)) != NULL)
	{
		pGrid->AddObjectToPacket(0,pPackedData);
	}
}

void CGrid::AddGridToPackedDataWithoutOne(DWORD dwID,CPackedData* pPackedData)
{
	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	
	AddObjectToPacket(dwID,pPackedData);
	while( (pGrid = m_NeighborGrid.GetNextPos(pos)) != NULL)
	{
		pGrid->AddObjectToPacket(dwID,pPackedData);
	}
}

void CGrid::AddObjectToPacket(DWORD ExceptID,CPackedData* pPackedData)
{
	m_CharacterHashTable.SetPositionHead();
	CObject* pObject;
	while( (pObject = (CObject*)m_CharacterHashTable.GetData() ) != NULL)
	{
		if(pObject->GetObjectKind() != eObjectKind_Player)
			continue;
		if(ExceptID == pObject->GetID())
			continue;
		
		pPackedData->AddObject(pObject);
		//pObject->SendMsg(pPackedData->GetMsg(),pPackedData->GetMsgLen());
	}
}

void CGrid::AddGridToPackedDataExceptLastGrid(DWORD ExceptID,CGrid* pLastGrid,CPackedData* pPackedData)
{
	if(pLastGrid == NULL)
	{
		AddGridToPackedDataWithoutOne(ExceptID,pPackedData);
		return;
	}
	
	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	
	if(!pLastGrid->IsNeighborGrid(this))
		AddObjectToPacket(ExceptID,pPackedData);
	
	while( (pGrid = m_NeighborGrid.GetNextPos(pos) ) != NULL)
	{
		if(!pLastGrid->IsNeighborGrid(pGrid))
			pGrid->AddObjectToPacket(ExceptID,pPackedData);
	}
}

BOOL CGrid::IsNeighborGrid(CGrid* pGrid)
{
	if(pGrid == this)
		return TRUE;
	
	CGrid* pNeighborGrid;
	POS pos = m_NeighborGrid.GetFirstPos();
	while( (pNeighborGrid = m_NeighborGrid.GetNextPos(pos) ) != NULL)
	{
		if(pNeighborGrid == pGrid)
			return TRUE;
	}
	return FALSE;
}

void CGrid::SendCurrentCharacterMsg(CObject* pNewObject)
{
	m_CharacterHashTable.SetPositionHead();
	
	while(CObject* const pObject = m_CharacterHashTable.GetData())
	{
		if(pNewObject->GetID() == pObject->GetID())
			continue;

		MSGBASE* message = 0;
		const DWORD messageLength = pObject->SetAddMsg(
			pNewObject->GetID(),
			FALSE,
			message);
		g_Network.Send2Server(
			pNewObject->GetAgentNum(),
			LPTSTR(message),
			messageLength);
	}	
}

void CGrid::SendCurrentObjectInfo(CObject* pNewObject,CGrid* pLastGrid)
{
	/////////////////////////////////////////////////////////////////////////
	// 06. 04. �׸��� ����
	// �� �Լ��� �߰��� ������Ʈ�� �Ҽӵ� �׸����� ������Ʈ����
	// �߰��� ������Ʈ���� ����� Agent�� �޼����� ������ �κ��ε�
	// �÷��̾� �̿��� ������Ʈ�� ����� Agent�� �����Ƿ� ���� �ʿ䰡 ����.
	if(pNewObject->GetObjectKind() != eObjectKind_Player)
		return;
	//////////////////////////////////////////////////////////////////////////

	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	
	if(pLastGrid == NULL)
	{
		SendCurrentCharacterMsg(pNewObject);
		while( (pGrid = m_NeighborGrid.GetNextPos(pos)) != NULL)
		{
			pGrid->SendCurrentCharacterMsg(pNewObject);
		}
	}
	else
	{
		if(!pLastGrid->IsNeighborGrid(this))
		{
			SendCurrentCharacterMsg(pNewObject);
		}
		while( (pGrid = m_NeighborGrid.GetNextPos(pos)) != NULL)
		{
			if(!pLastGrid->IsNeighborGrid(pGrid))
			{
				pGrid->SendCurrentCharacterMsg(pNewObject);
			}
		}
	}
}


void CGrid::SendRemoveCharacterMsg(CObject* pLeavedObject)
{
	m_CharacterHashTable.SetPositionHead();
	CObject* pObject;
	while( (pObject = (CObject*)m_CharacterHashTable.GetData()) != NULL)
	{
		if(pLeavedObject->GetID() == pObject->GetID())
			continue;

		MSGBASE* message = 0;
		const DWORD messageLength = pObject->SetRemoveMsg(
			pLeavedObject->GetID(),
			message);
		g_Network.Send2Server(
			pLeavedObject->GetAgentNum(),
			LPTSTR(message),
			messageLength);
	}	
}

void CGrid::SendRemoveObjectInfo(CObject* pLeavedObject,CGrid* pCurGrid)
{
	
	/////////////////////////////////////////////////////////////////////////
	// 06. 04. �׸��� ����
	// �� �Լ��� ������ ������Ʈ�� �Ҽӵ� �׸����� ������Ʈ����
	// ������ ������Ʈ���� ����� Agent�� �޼����� ������ �κ��ε�
	// �÷��̾� �̿��� ������Ʈ�� ����� Agent�� �����Ƿ� ���� �ʿ䰡 ����.
	if(pLeavedObject->GetObjectKind() != eObjectKind_Player )
		return;
	/////////////////////////////////////////////////////////////////////////

	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	
	if(pCurGrid == NULL)
	{
		SendRemoveCharacterMsg(pLeavedObject);
	//	SendRemoveItemMsg(pLeavedObject);
		while( (pGrid = m_NeighborGrid.GetNextPos(pos)) != NULL)
		{
			pGrid->SendRemoveCharacterMsg(pLeavedObject);
	//		pGrid->SendRemoveItemMsg(pLeavedObject);
		}
	}
	else
	{
		if(!pCurGrid->IsNeighborGrid(this))
		{
			SendRemoveCharacterMsg(pLeavedObject);
	//		SendRemoveItemMsg(pLeavedObject);
		}
		
		while( (pGrid = m_NeighborGrid.GetNextPos(pos)) != NULL)
		{
			if(!pCurGrid->IsNeighborGrid(pGrid))
			{
				pGrid->SendRemoveCharacterMsg(pLeavedObject);
	//			pGrid->SendRemoveItemMsg(pLeavedObject);
			}
		}
	}
}

void CGrid::FindPlayerInRange(CObject* pFinder,VECTOR3* pPos,float Range,float& MinRange,CObject** ppObject)
{
	MinRange = Range;
	*ppObject = NULL;
	float dist;
	
	m_CharacterHashTable.SetPositionHead();
	
	while(CObject* pObject = m_CharacterHashTable.GetData())
	{
		if(pObject->GetObjectKind() != eObjectKind_Player)
			continue;
		
		if(pObject->GetState() == eObjectState_Die || pObject->GetState() == eObjectState_Immortal)
			continue;

		/// ���������� ��� �н�(GM)
		if( !((CPlayer*)pObject)->IsVisible() )
			continue;
		
		dist = CalcDistanceXZ(pPos,CCharMove::GetPosition(pObject));
		if(dist < MinRange)
		{
			if(pFinder != pObject)
			{
				MinRange = dist;
				*ppObject = pObject;
			}
		}
	}
}

CObject* CGrid::FindPlayerInRange(CObject* pFinder,VECTOR3* pPos,float Range)
{
	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	CObject* pObject;
	CObject* pClosestObject;
	float dist;
	float mindist;
	
	FindPlayerInRange(pFinder,pPos,Range,mindist,&pClosestObject);
	while( (pGrid = m_NeighborGrid.GetNextPos(pos) ) != NULL)
	{
		pGrid->FindPlayerInRange(pFinder,pPos,Range,dist,&pObject);
		if(dist < mindist)
		{
			mindist = dist;
			pClosestObject = pObject;
		}
	}
	
	return pClosestObject;
}

void CGrid::FindFirstPlayerInRange(CObject* pFinder,VECTOR3* pPos,float Range,CObject** ppObject)
{
	*ppObject = NULL;
	float dist;
	
	m_CharacterHashTable.SetPositionHead();

	while(CObject* pObject = m_CharacterHashTable.GetData())
	{
		if( pFinder == pObject ) continue;

		if(pObject->GetObjectKind() != eObjectKind_Player)
			continue;
		
		if(pObject->GetState() == eObjectState_Die || pObject->GetState() == eObjectState_Immortal)
			continue;

		/// ���������� ��� �н�(GM)
		if( !((CPlayer*)pObject)->IsVisible() )
			continue;
		
		dist = CalcDistanceXZ(pPos,CCharMove::GetPosition(pObject));
		if(dist < Range)
		{
			*ppObject = pObject;
			return;
		}
	}
}

CObject* CGrid::FindFirstPlayerInRange(CObject* pFinder,VECTOR3* pPos,float Range)
{
	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	CObject* pObject;
	
	FindFirstPlayerInRange(pFinder,pPos,Range,&pObject);
	if(pObject)
		return pObject;

	while( (pGrid = m_NeighborGrid.GetNextPos(pos)) != NULL)
	{
		pGrid->FindFirstPlayerInRange(pFinder,pPos,Range,&pObject);
		if(pObject)
			return pObject;
	}
	
	return NULL;

}



void CGrid::FindMonsterInRange(CObject* pFinder,VECTOR3* pPos,float Range,float& MinRange,CObject** ppObject)
{
	MinRange = Range;
	*ppObject = NULL;
	float dist;
	
	m_CharacterHashTable.SetPositionHead();
	CObject* pObject;
	while( (pObject = (CObject*)m_CharacterHashTable.GetData()) != NULL)
	{
		if( pFinder == pObject ) continue;

		if(FALSE == (pObject->GetObjectKind() & eObjectKind_Monster))
			continue;
		
		if(pObject->GetState() == eObjectState_Die || pObject->GetState() == eObjectState_Immortal)
			continue;
		
		dist = CalcDistanceXZ(pPos,CCharMove::GetPosition(pObject));
		if(dist < MinRange)
		{
//			if(pFinder != pObject)
			{
				MinRange = dist;
				*ppObject = pObject;
			}
		}
	}
}

CObject* CGrid::FindMonsterInRange(CObject* pFinder,VECTOR3* pPos,float Range)
{
	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	CObject* pObject;
	CObject* pClosestObject;
	float dist;
	float mindist;
	
	FindMonsterInRange(pFinder,pPos,Range,mindist,&pClosestObject);
	while( (pGrid = m_NeighborGrid.GetNextPos(pos)) != NULL)
	{
		pGrid->FindMonsterInRange(pFinder,pPos,Range,dist,&pObject);
		if(dist < mindist)
		{
			mindist = dist;
			pClosestObject = pObject;
		}
	}
	
	return pClosestObject;
}

void CGrid::FindFirstMonsterInRange(CObject* pFinder,VECTOR3* pPos,float Range,CObject** ppObject)
{
	*ppObject = NULL;
	float dist;
	
	m_CharacterHashTable.SetPositionHead();
	CObject* pObject;
	while( (pObject = (CObject*)m_CharacterHashTable.GetData()) != NULL)
	{
		if( pFinder == pObject ) continue;

		if(FALSE == (pObject->GetObjectKind() & eObjectKind_Monster))
			continue;
		
		if(pObject->GetState() == eObjectState_Die || pObject->GetState() == eObjectState_Immortal)
			continue;
		
		dist = CalcDistanceXZ(pPos,CCharMove::GetPosition(pObject));
		if(dist < Range)
		{
//			if(pFinder != pObject)
			{
				*ppObject = pObject;
				return;
			}
		}
	}
}

CObject* CGrid::FindFirstMonsterInRange(CObject* pFinder,VECTOR3* pPos,float Range)
{
	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	CObject* pObject;
	
	FindFirstMonsterInRange(pFinder,pPos,Range,&pObject);
	if(pObject)
		return pObject;

	while( (pGrid = m_NeighborGrid.GetNextPos(pos) ) != NULL)
	{
		pGrid->FindFirstMonsterInRange(pFinder,pPos,Range,&pObject);
		if(pObject)
			return pObject;
	}
	
	return NULL;

}

WORD CGrid::FindMonsterGroupInRange(CObject* pFinder,VECTOR3* pPos, DWORD* pObjectList)
{
	WORD wFindNum = 0;

	m_CharacterHashTable.SetPositionHead();
	CObject* pObject;
	while( (pObject = (CObject*)m_CharacterHashTable.GetData()) != NULL)
	{
		if(wFindNum >= MAX_FIND_MONSTERNUM)
			break;

		if( pFinder == pObject ) continue;

		if(FALSE == (pObject->GetObjectKind() & eObjectKind_Monster))
			continue;

		if(pObject->GetGroupAlias() != pFinder->GetGroupAlias())
			continue;

		if(pObject->GetState() == eObjectState_Die || pObject->GetState() == eObjectState_Immortal)
			continue;

		pObjectList[wFindNum] = pObject->GetID();
		wFindNum++;
	}

	return wFindNum;
}

WORD CGrid::FindMonsterGroupInRange(DWORD* pFriendsList, CObject* pFinder,VECTOR3* pPos)
{
	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	WORD wStartEmptyNum = 0;
	DWORD objectList[MAX_FIND_MONSTERNUM] = {0,};
	WORD wFindNum = FindMonsterGroupInRange(pFinder, pPos, &objectList[0]);

	for(WORD i=0; i<wFindNum; ++i)
	{
		pFriendsList[wStartEmptyNum] = objectList[i];
		wStartEmptyNum++;
	}

	while( (pGrid = m_NeighborGrid.GetNextPos(pos) ) != NULL)
	{
		if(wStartEmptyNum >= MAX_FIND_MONSTERNUM)
			return wStartEmptyNum;

		ZeroMemory(objectList, sizeof(objectList));

		wFindNum = pGrid->FindMonsterGroupInRange(pFinder, pPos, &objectList[0]);

		for(WORD i=0; i<wFindNum; i++)
		{
			if(wStartEmptyNum >= MAX_FIND_MONSTERNUM)
				return wStartEmptyNum;

			pFriendsList[wStartEmptyNum] = objectList[i];
			wStartEmptyNum++;
		}
	}

	return wStartEmptyNum;
}

CObject* CGrid::FindPlayerRandom()
{
	POS pos = m_NeighborGrid.GetFirstPos();
	CGrid* pGrid;
	CObject* pObject[9];
	CObject* temp;
	WORD count = 0;

	/// �켱 �ڱ� �׸��� ������ �÷��̾ ������.
	FindPlayerRandom( &temp );
	if( temp )
	{
		pObject[count++] = temp;
	}

	/// �� �׸��忡�� �÷��̾ ���´�.
	while( ( pGrid = m_NeighborGrid.GetNextPos( pos ) ) != NULL)
	{
		temp = NULL;
		pGrid->FindPlayerRandom( &temp );
		if( temp )
		{
			pObject[count++] = temp;

			if(count == 9)
				break;
		}
	}
	
	/// ���õ� �÷��̾ 1�� �̻��϶�
	if(count > 0)
	{
		/// ������ �÷��̾ ������
		WORD select = WORD( rand() % count);

		return pObject[select];
	}

	/// ���õ� �÷��̾ ������ NULL ����
	return NULL;
}

void CGrid::FindPlayerRandom( CObject** ppObject )
{
	/// ��ü ��ü��
	DWORD num = m_CharacterHashTable.GetDataNum();
	
	/// ��ü���� 0�̸� NULL ����
	if(num == 0)
	{
		*ppObject = NULL;
		return;
	}

	/// Ž���� ������ ������
	DWORD muster = 0;
	if( num > 1 )
		muster = rand() % ( num - 1 );

	/// ī��Ʈ�� ����
	DWORD count = 0;

	m_CharacterHashTable.SetPositionHead();
	CObject* pObject = NULL;
	while( ( pObject = ( CObject* )m_CharacterHashTable.GetData() ) != NULL)
	{
		/// ī��Ʈ�� �������� ���� �������� �˻��Ѵ�.
		if( count < muster )
		{
			count++;
			continue;
		}

		/// �÷��̾ �ƴϸ� �н�
		if( pObject->GetObjectKind() != eObjectKind_Player )
			continue;

		/// ���� ����̳� ���� ���´� �н�
		if( pObject->GetState() == eObjectState_Die || pObject->GetState() == eObjectState_Immortal )
			continue;

		/// ���������� ��� �н�(GM)
		if( !((CPlayer*)pObject)->IsVisible() )
			continue;

		/// ���� �߰ߵ� �÷��̾ �����Ѵ�.
		*ppObject = pObject;
		return;
	}

	/// ���� �÷��̾ ��ã���� ���
	/// ó������ ���������� �ٽ� �˻��Ѵ�.
	m_CharacterHashTable.SetPositionHead();
	pObject = NULL;
	count = 0;
	while( (pObject = ( CObject* )m_CharacterHashTable.GetData()) != NULL)
	{
		/// �������� �Ǹ� �˻� �����Ѵ�
		if( count >= muster )
		{
			break;
		}
		
		/// ī��Ʈ ����
		count++;

		/// �÷��̾ �ƴϸ� �н�
		if( pObject->GetObjectKind() != eObjectKind_Player )
			continue;

		/// ���� ����̳� ���� ���´� �н�
		if( pObject->GetState() == eObjectState_Die || pObject->GetState() == eObjectState_Immortal )
			continue;

		/// ���� �߰ߵ� �÷��̾ �����Ѵ�.
		*ppObject = pObject;
		return;
	}

	/// �׷��� ��ã�Ҵٸ� NULL ����
	*ppObject = NULL;
	return;
}
//////////////////////////////////////////////////////////////////////////