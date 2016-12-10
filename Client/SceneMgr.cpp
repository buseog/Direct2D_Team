#include "StdAfx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ObjMgr.h"


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
	case SC_LOGO:
		
		break;

	case SC_STAGE:
		
		break;
	}

	if(FAILED(m_pScene->Initialize()))
	{
		ERR_MSG(L"Scene Init Failed");
		return;
	}

	if(FAILED(CObjMgr::GetInstance()->Initialize()))
	{
		ERR_MSG(L"ObjMgr Init Failed");
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
