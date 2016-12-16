#include "StdAfx.h"
#include "MainGame.h"
#include "Device.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "AStar.h"
#include "CrowdMgr.h"

CMainGame::CMainGame(void)
: m_pDevice(CDevice::GetInstance())
, m_pSceneMgr(CSceneMgr::GetInstance())
, m_fTime(0.f)
, m_iCount(0)
,m_fMouseX(0)
,m_fMouseY(0)
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * MIN_STR);
	ZeroMemory(m_szMOUSEPOS, sizeof(TCHAR) * MIN_STR);
}

CMainGame::~CMainGame(void)
{
	Release();
}


HRESULT CMainGame::Initialize(void)
{
	if(FAILED(m_pDevice->InitDevice()))
	{
		ERR_MSG(L"Client Device Create Failed")
		return E_FAIL;
	}

	/*if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Hand_Stand/UI%d", L"UI", TEX_MULTI, L"Hand_Stand", 15)))
	{
		ERR_MSG(L"Mouse 멀티 텍스쳐 생성 실패")
		return E_FAIL;
	}	
	*/
	CTimeMgr::GetInstance()->InitTime();
	m_pSceneMgr->SetScene(SC_START);
	
	m_tFrame.fFrame = 0.f;
	m_tFrame.fCount = 15.f; 
	m_tFrame.fMax = m_tFrame.fCount;

	return S_OK;
}

void CMainGame::Progress(void)
{
	CTimeMgr::GetInstance()->SetTime();

	if (m_pSceneMgr)
		m_pSceneMgr->Progress();
	D3DXMatrixTranslation(&m_matTrans, 600.f, 50.f, 0.f);

	
}

void CMainGame::Render(void)
{
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 600.f, 100.f, 0.f);
	++m_iCount;

	m_fTime += CTimeMgr::GetInstance()->GetTime();
	m_fMouseX = ::GetMouse().x;
	m_fMouseY = ::GetMouse().y;
	wsprintf(m_szMOUSEPOS,L"MouseX : %d  MouseY : %d" ,(int)m_fMouseX,(int)m_fMouseY);
	if(m_fTime > 1.f)
	{
		m_fTime = 0.f;
		wsprintf(m_szFPS, L"FPS : %d", m_iCount);
		m_iCount = 0;
	}

	m_pDevice->GetDevice()->Clear(0, NULL, 
		D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	
	m_pDevice->Render_Begin();

	if (m_pSceneMgr)
		m_pSceneMgr->Render();

	m_pDevice->GetSprite()->SetTransform(&m_matTrans);

	m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(), 
		m_szFPS, 
		lstrlen(m_szFPS), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 0));
	m_pDevice->GetSprite()->SetTransform(&matTrans);
	m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(), 
		m_szMOUSEPOS, 
		lstrlen(m_szMOUSEPOS), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 0));


	//const TEXINFO* pTexture = CTextureMgr::GetInstance()->GetTexture(L"UI",  L"Hand_Stand", m_tFrame.fFrame);

	//D3DXMatrixTranslation(&matTrans, ::GetMouse().x, ::GetMouse().y, 0.f);
	//CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	//CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
	//	NULL, &D3DXVECTOR3(pTexture->tImgInfo.Width / 2.f, pTexture->tImgInfo.Height / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//m_tFrame.fFrame += m_tFrame.fCount * CTimeMgr::GetInstance()->GetTime();

	//if(m_tFrame.fFrame > m_tFrame.fMax)
	//	m_tFrame.fFrame = 0;


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
	CUIMgr::GetInstance()->DestroyInstance();
	m_pSceneMgr->DestroyInstance();
	m_pDevice->DestroyInstance();
}


