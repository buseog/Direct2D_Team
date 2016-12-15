#include "StdAfx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "Start.h"
#include "MyMenu.h"
#include "Field.h"
#include "Village.h"
#include "BattleField.h"


IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr(void)
: m_pScene(NULL)
{
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}
void CSceneMgr::SetScene(SCENEID _eScene)
{
	if(m_pScene)
		::Safe_Delete(m_pScene);

	switch(_eScene)
	{
	case SC_START:
		m_pScene = new CStart;
		break;

	case SC_MENU:
		m_pScene = new CMyMenu;
		break;

	case SC_FILED:
		m_pScene = new CField;
		break;
	
	case SC_VILLAGE:
		m_pScene = new CVillage;
		break;

	case SC_BATTLEFIELD:
		m_pScene = new CBattleField;
		break;
	}

	if(FAILED(m_pScene->Initialize()))
	{
		ERR_MSG(L"Scene Init Failed");
		return;
	}

	CObjMgr::GetInstance()->SetSceneID(SC_BATTLEFIELD);
	if(FAILED(CObjMgr::GetInstance()->Initialize()))
	{
		ERR_MSG(L"ObjMgr Init Failed");
		return;
	}

	CUIMgr::GetInstance()->SetSceneID(SC_BATTLEFIELD);
	if(FAILED(CUIMgr::GetInstance()->Initialize()))
	{
		ERR_MSG(L"UIMgr Init Failed");
		return;
	}
}

void CSceneMgr::Progress(void)
{
	m_pScene->Progress();
}

void CSceneMgr::Render(void)
{
	m_pScene->Render();
}

void CSceneMgr::Release(void)
{
	if(m_pScene)
		::Safe_Delete(m_pScene);
}
