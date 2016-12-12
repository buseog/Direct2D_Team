#include "StdAfx.h"
#include "MainGame.h"
#include "Device.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "AStar.h"
#include "CrowdMgr.h"

CMainGame::CMainGame(void)
: m_pDevice(CDevice::GetInstance())
, m_pSceneMgr(CSceneMgr::GetInstance())
{
}

CMainGame::~CMainGame(void)
{
	Release();
}


HRESULT CMainGame::Initialize(void)
{
	if(FAILED(m_pDevice->InitDevice()))
	{
		ERR_MSG(L"Client Device Create Failed");
		return E_FAIL;
	}

	CTimeMgr::GetInstance()->InitTime();
	m_pSceneMgr->SetScene(SC_BATTLEFIELD);

	return S_OK;
}

void CMainGame::Progress(void)
{
	CTimeMgr::GetInstance()->SetTime();

	if (m_pSceneMgr)
		m_pSceneMgr->Progress();
}

void CMainGame::Render(void)
{
	m_pDevice->GetDevice()->Clear(0, NULL, 
		D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	
	m_pDevice->Render_Begin();

	if (m_pSceneMgr)
		m_pSceneMgr->Render();

	m_pDevice->Render_End();
	m_pDevice->GetDevice()->Present(NULL, NULL, NULL, NULL);
}

void CMainGame::Release(void)
{
	CCrowdMgr::GetInstance()->DestroyInstance();
	CAStar::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	m_pSceneMgr->DestroyInstance();
	m_pDevice->DestroyInstance();
}


