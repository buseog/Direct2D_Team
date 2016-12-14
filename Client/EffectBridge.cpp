#include "StdAfx.h"
#include "EffectBridge.h"

CEffectBridge::CEffectBridge(void)
{
}

CEffectBridge::~CEffectBridge(void)
{
}

HRESULT CEffectBridge::Initialize(void)
{
	return S_OK;
}

void CEffectBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	Frame();
}

void CEffectBridge::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey(), 
		m_wstrStateKey, (int)m_tFrame.fFrame);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CEffectBridge::Release(void)
{
	
}

void	CEffectBridge::WorldMatrix(INFO& rInfo)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x + m_pObj->GetScroll().x, 
		rInfo.vPos.y + m_pObj->GetScroll().y, 
		0.f);

	rInfo.matWorld = matTrans;
}