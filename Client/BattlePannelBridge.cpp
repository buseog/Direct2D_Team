#include "StdAfx.h"
#include "BattlePannelBridge.h"
#include "Ui.h"

CBattlePannelBridge::CBattlePannelBridge(void)
{
}

CBattlePannelBridge::~CBattlePannelBridge(void)
{
	Release();
}

HRESULT CBattlePannelBridge::Initialize(void)
{
	return S_OK;
}

void CBattlePannelBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	
}

void CBattlePannelBridge::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBattlePannelBridge::Release(void)
{
	
}

void	CBattlePannelBridge::WorldMatrix(INFO& rInfo)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;
}

int	CBattlePannelBridge::Picking(void)
{
	return m_iPriority;
}