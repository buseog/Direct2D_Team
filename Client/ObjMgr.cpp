#include "StdAfx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "ObjFactory.h"
#include "BridgeFactory.h"
#include "Back.h"
#include "Player.h"
#include "UnitBridge.h"

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
	m_ObjList[eObjID].push_back(pObj);
}

HRESULT CObjMgr::Initialize(void)
{
	m_ObjList[OBJ_BACK].push_back(CObjFactory<CBack>::CreateObj(0, 0));
//	m_ObjList[OBJ_PLAYER].push_back(CBridgeFactory<CPlayer, CUnitBridge>::CreateBridge(L"Player"));
	return S_OK;
}

void CObjMgr::Progress(void)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator	iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Progress();
		}
	}
}

void CObjMgr::Render(void)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator	iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Render();
		}
	}
}

void CObjMgr::Release()
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator	iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); ++iter)
		{
			::Safe_Delete(*iter);
		}
		m_ObjList[i].clear();
	}
}

const vector<TILE2*>* CObjMgr::GetTile(void)
{
	return NULL;//((CBack*)m_ObjList[OBJ_BACK].front())->GetTile();
}

const CObj* CObjMgr::GetObj(OBJID _eID)
{
	return m_ObjList[_eID].front();
}
