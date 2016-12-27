#include "StdAfx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Back.h"
#include "CrowdMgr.h"

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
	return S_OK;
}

void CObjMgr::Progress(void)
{
	switch (m_eSceneID)
	{
	case SC_FIELD:
		for(size_t i = 0; i < OBJ_END; ++i)
		{
			if (i == OBJ_UNIT)
				continue;

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
		break;
	case SC_BATTLEFIELD:
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
		break;


	}
}

void CObjMgr::Render(void)
{
	switch (m_eSceneID)
	{
	case SC_FIELD:
		for(size_t i = 0; i < OBJ_END; ++i)
		{
			if (i == OBJ_UNIT)
				continue;

			for(list<CObj*>::iterator	iter = m_ObjList[m_eSceneID][i].begin();
				iter != m_ObjList[m_eSceneID][i].end(); ++iter)
			{
				(*iter)->Render();
			}
		}
		break;

	case SC_BATTLEFIELD:
		for(size_t i = 0; i < OBJ_END; ++i)
		{
			for(list<CObj*>::iterator	iter = m_ObjList[m_eSceneID][i].begin();
				iter != m_ObjList[m_eSceneID][i].end(); ++iter)
			{
				(*iter)->Render();
			}
		}
		break;

	case SC_VILLAGE:
		for(size_t i = 0; i < OBJ_END; ++i)
		{
			for(list<CObj*>::iterator	iter = m_ObjList[m_eSceneID][i].begin();
				iter != m_ObjList[m_eSceneID][i].end(); ++iter)
			{
				(*iter)->Render();
			}
		}
		break;

	case SC_INVILLAGE:
		for(size_t i = 0; i < OBJ_END; ++i)
		{
			for(list<CObj*>::iterator	iter = m_ObjList[m_eSceneID][i].begin();
				iter != m_ObjList[m_eSceneID][i].end(); ++iter)
			{
				(*iter)->Render();
			}
		}
		break;
	}
}

void CObjMgr::Release()
{
	for (int id = 0; id < SC_END; ++id)
	{
		for(int i = 0; i < OBJ_END; ++i)
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
	if (m_ObjList[m_eSceneID][_eID].empty())
		return NULL;
	else
		return m_ObjList[m_eSceneID][_eID].front();

	return NULL;
}

list<CObj*>* CObjMgr::GetObjList(SCENEID eSCID, OBJID _eID)
{
	return &m_ObjList[eSCID][_eID];
}
void CObjMgr::SetSceneID(SCENEID	eID)
{
	m_eSceneID = eID;
}


void CObjMgr::BattleFieldClear( void )
{
	for (int i = 0 ; i < OBJ_END; ++i)
	{
		m_ObjList[SC_BATTLEFIELD][i].clear();
	}
	
	
}

int	CObjMgr::Picking(void)
{
	int iResult = -1;
	
	if (m_eSceneID == SC_BATTLEFIELD)
		iResult = CCrowdMgr::GetInstance()->Progress();

	if (iResult > 0)
		return iResult;


	for(int i = 0; i < OBJ_END; ++i)
	{
		if (i == OBJ_EFFECT)
			continue;

		for(list<CObj*>::iterator	iter = m_ObjList[m_eSceneID][i].begin();
			iter != m_ObjList[m_eSceneID][i].end(); ++iter)
		{
			iResult = (*iter)->Picking();

			if (iResult > 0)
				return iResult;
		}
	}

	return iResult;
}