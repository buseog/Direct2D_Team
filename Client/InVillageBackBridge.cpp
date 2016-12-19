#include "StdAfx.h"
#include "InVillageBackBridge.h"
#include "Obj.h"

CInVillageBackBridge::CInVillageBackBridge(void)
{
	m_vSize = D3DXVECTOR3(800.f, 600.f, 0.f);
}

CInVillageBackBridge::~CInVillageBackBridge(void)
{
}

HRESULT	CInVillageBackBridge::Initialize(void)
{

	return S_OK;
}

void	CInVillageBackBridge::Progress(INFO& rInfo)
{

}

void	CInVillageBackBridge::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);

	if(pTexture == NULL)
		return;
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void	CInVillageBackBridge::Release(void)
{

}