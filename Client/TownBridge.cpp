#include "StdAfx.h"
#include "TownBridge.h"
#include "TownButton.h"
#include "UIMgr.h"
#include "Ui.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "TimeMgr.h"

CTownBridge::CTownBridge(void)
{
}

CTownBridge::~CTownBridge(void)
{
}

HRESULT	CTownBridge::Initialize(void)
{
	m_iMapKey = 0;

	return S_OK;
}

void CTownBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	m_iMapKey = 0;

}

void CTownBridge::Render(void)
{
	const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"BIGTOWN", L"BigTown", m_iMapKey);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f - m_pObj->GetScroll().x;
	float fY = pTexture->tImgInfo.Height / 2.f - m_pObj->GetScroll().y;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CTownBridge::Release(void)
{

}

void CTownBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

void CTownBridge::SetMapKey(int _iKey)
{
	m_iMapKey = _iKey;
}

int CTownBridge::Picking(void)
{
	POINT	Pt;
	Pt.x = (long)GetMouse().x - (long)m_pObj->GetScroll().x;
	Pt.y = (long)GetMouse().y - (long)m_pObj->GetScroll().y;

	if(PtInRect(&m_pUi->GetRect(), Pt))
	{
		SetMapKey(1);
		if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON, 6))
		{
			CSoundMgr::GetInstance()->SoundPlay(3, 0);
			CSceneMgr::GetInstance()->SetScene(SC_VILLAGE);
			return 1;	
		}
	}


	return -1;
}