#include "StdAfx.h"
#include "VillageBackBridge.h"
#include "Obj.h"

CVillageBackBridge::CVillageBackBridge(void)
{
	m_vSize = D3DXVECTOR3(800.f, 600.f, 0.f);
}

CVillageBackBridge::~CVillageBackBridge(void)
{
}


HRESULT	CVillageBackBridge::Initialize(void)
{

	return S_OK;
}

void	CVillageBackBridge::Progress(INFO& rInfo)
{

}

void	CVillageBackBridge::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);

	if(pTexture == NULL)
		return;
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void	CVillageBackBridge::Release(void)
{

}
