#include "StdAfx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "Start.h"
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

	CObjMgr::GetInstance()->SetSceneID(_eScene);
	if(FAILED(CObjMgr::GetInstance()->Initialize()))
	{
		ERR_MSG(L"ObjMgr Init Failed");
		return;
	}

	CUIMgr::GetInstance()->SetSceneID(_eScene);
	if(FAILED(CUIMgr::GetInstance()->Initialize()))
	{
		ERR_MSG(L"UIMgr Init Failed");
		return;
	}
}

void CSceneMgr::Progress(void)
{
	m_pScene->Progress();

	
	m_tFrame.fFrame += m_tFrame.fCount * CTimeMgr::GetInstance()->GetTime();

	if(m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0;

}

void CSceneMgr::Render(void)
{
	m_pScene->Render();

	const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"Mouse",  wstrMouse, (const int)m_tFrame.fFrame);

	if (pTexture == NULL)
		return;
		
	D3DXMATRIX matTrans;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	D3DXVECTOR3	vMouse = ::GetMouse();

	D3DXMatrixTranslation(&matTrans, vMouse.x, vMouse.y, 0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CSceneMgr::Release(void)
{
	if(m_pScene)
		::Safe_Delete(m_pScene);
}

void CSceneMgr::SetMouse(const wstring& wstrMouseKey)
{
	wstrMouse = wstrMouseKey;

	m_tFrame.fFrame = 0.f;
	m_tFrame.fCount = (float)CTextureMgr::GetInstance()->GetImgCount(L"Mouse", wstrMouseKey); 
	m_tFrame.fMax = m_tFrame.fCount;
}