#include "StdAfx.h"
#include "PortraitBridge.h"
#include "Ui.h"

CPortraitBridge::CPortraitBridge(void)
{
}

CPortraitBridge::~CPortraitBridge(void)
{
}

HRESULT CPortraitBridge::Initialize(void)
{
	return S_OK;
}

void CPortraitBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	
}

void CPortraitBridge::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pUi->GetObjKey(), m_wstrStateKey, 0);

	if(pTexture == NULL)
		return;

	float fX = (float)pTexture->tImgInfo.Width;
	float fY = (float)pTexture->tImgInfo.Height;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexture = CTextureMgr::GetInstance()->GetTexture(L"HpBar");

	if(pTexture == NULL)
		return;

	D3DXMATRIX matTrans;

	fX = (float)pTexture->tImgInfo.Width;
	fY = (float)pTexture->tImgInfo.Height;

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x - 10.f, m_pUi->GetInfo()->vPos.y + 8.f, 0.f); 

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MpBar");

	if(pTexture == NULL)
		return;

	fX = (float)pTexture->tImgInfo.Width;
	fY = (float)pTexture->tImgInfo.Height;

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x - 10.f, m_pUi->GetInfo()->vPos.y + 10.f, 0.f); 

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CPortraitBridge::Release(void)
{
	
}

void CPortraitBridge::WorldMatrix(INFO& rInfo)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;
}