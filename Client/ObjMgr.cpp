#include "StdAfx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "ObjFactory.h"
#include "Back.h"
#include "Player.h"
#include "PlayerBridge.h"
#include "UnitBridge.h"
#include "BattleFieldBackBridge.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	Release();
}

void CObjMgr::AddObject(OBJID eObjID, CObj* pObj)
{
	m_ObjList[m_eSceneID][eObjID].push_back(pObj);
}

HRESULT CObjMgr::Initialize(void)
{
	m_ObjList[m_eSceneID][OBJ_BACK].push_back(CObjFactory<CBack, CBattleFieldBackBridge>::CreateObj(L"Walk_1", 0, 0));

	m_ObjList[m_eSceneID][OBJ_PLAYER].push_back(CObjFactory<CPlayer, CPlayerBridge>::CreateObj(L"Player", 0, 0));
	//m_ObjList[m_eSceneID][OBJ_PLAYER].push_back(CObjFactory<CPlayer, CUnitBridge>::CreateObj(L"Walk_1", 300.f, 300.f));

	return S_OK;
}

void CObjMgr::Progress(void)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator	iter = m_ObjList[m_eSceneID][i].begin();
			iter != m_ObjList[m_eSceneID][i].end(); )
		{
			(*iter)->Progress();

			if ((*iter)->GetDestroy())
			{
				::Safe_Delete(*iter);
				iter = m_ObjList[m_eSceneID][i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Render(void)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator	iter = m_ObjList[m_eSceneID][i].begin();
			iter != m_ObjList[m_eSceneID][i].end(); ++iter)
		{
			(*iter)->Render();
		}
	}
}

void CObjMgr::Release()
{
	for (int id = 0; id < SC_END; ++id)
	{
		for(size_t i = 0; i < OBJ_END; ++i)
		{
			for(list<CObj*>::iterator	iter = m_ObjList[id][i].begin();
				iter != m_ObjList[id][i].end(); ++iter)
			{
				::Safe_Delete(*iter);
			}
			m_ObjList[id][i].clear();
		}
	}
}

const vector<TILE2*>* CObjMgr::GetTile(void)
{
	return ((CBack*)m_ObjList[m_eSceneID][OBJ_BACK].front())->GetTile();
}

const CObj* CObjMgr::GetObj(OBJID _eID)
{
	return m_ObjList[m_eSceneID][_eID].front();
}

list<CObj*>* CObjMgr::GetObjList(OBJID _eID)
{
	return &m_ObjList[m_eSceneID][_eID];
}
void CObjMgr::SetSceneID(SCENEID	eID)
{
	m_eSceneID = eID;
}