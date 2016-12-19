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
	ZeroMemory(&m_arScene, sizeof(CScene) * SC_END);
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}
void CSceneMgr::SetScene(SCENEID _eScene)
{
	switch(_eScene)
	{
	case SC_START:
		if (m_arScene[SC_START] == NULL)
			m_pScene = new CStart;

		else
			m_pScene = m_arScene[SC_START];
		break;

	case SC_FIELD:
		if (m_arScene[SC_FIELD] == NULL)
			m_pScene = new CField;

		else
			m_pScene = m_arScene[SC_FIELD];
		break;
	
	case SC_VILLAGE:
		if (m_arScene[SC_VILLAGE] == NULL)
			m_pScene = new CVillage;

		else
			m_pScene = m_arScene[SC_VILLAGE];
		break;

	case SC_BATTLEFIELD:
		if (m_arScene[SC_BATTLEFIELD] == NULL)
			m_pScene = new CBattleField;

		else
			m_pScene = m_arScene[SC_BATTLEFIELD];
		break;
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

	if(FAILED(m_pScene->Initialize()))
	{
		ERR_MSG(L"Scene Init Failed");
		return;
	}
}

void CSceneMgr::Progress(void)
{
	m_pScene->Progress();

	
	m_tFrame.fFrame += m_tFrame.fCount * CTimeMgr::GetInstance()->GetTime() * 1.5f;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		wstrMouse = L"Hand_Stand";
		SetMouse(L"Hand_Stand");
	}

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
	for (int i = 0; i < SC_END; ++i)
	{
		::Safe_Delete(m_arScene[i]);
	}
	m_pScene = NULL;
}

void CSceneMgr::SetMouse(const wstring& wstrMouseKey)
{
	if (wstrMouse == L"Sword_Click" || wstrMouse == L"Hand_Click")
		return;

	wstrMouse = wstrMouseKey;

	m_tFrame.fFrame = 0.f;
	m_tFrame.fCount = (float)CTextureMgr::GetInstance()->GetImgCount(L"Mouse", wstrMouseKey); 
	m_tFrame.fMax = m_tFrame.fCount;
}

const wstring	CSceneMgr::GetMouse(void)
{
	return wstrMouse;
}