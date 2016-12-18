#include "StdAfx.h"
#include "PortraitBridge.h"
#include "Ui.h"
#include "Portrait.h"
#include "UIObserver.h"

CPortraitBridge::CPortraitBridge(void)
{
}

CPortraitBridge::~CPortraitBridge(void)
{
}

HRESULT CPortraitBridge::Initialize(void)
{
	m_iIndex = -1;
	return S_OK;
}

void CPortraitBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	
}

void CPortraitBridge::Render(void)
{
	D3DXMATRIX matScale, matTrans, matWorld;

	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pUi->GetObjKey(), m_wstrStateKey, 0);

	if(pTexture == NULL)
		return;

	const UNITDATA*	pData = ((CUIObserver*)((CPortrait*)m_pUi)->GetObserver())->GetData();

	float fPercent = (float)pData->iHealthPoint / (float)pData->iMaxHelathPoint;

	if(pTexture == NULL)
		return;

	float fX = (float)pTexture->tImgInfo.Width;
	float fY = (float)pTexture->tImgInfo.Height;

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x - fX, m_pUi->GetInfo()->vPos.y - fY, 0.f); 

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexture = CTextureMgr::GetInstance()->GetTexture(L"HpBar");

	if(pTexture == NULL)
		return;

	
	fX = (float)pTexture->tImgInfo.Width;
	fY = (float)pTexture->tImgInfo.Height;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, fPercent, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x - 75.f, m_pUi->GetInfo()->vPos.y + 2.5f, 0.f); 

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(0.f, 0.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

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

void	CPortraitBridge::SetIndex(int iIndex)
{
	m_iIndex = iIndex;
}
int		CPortraitBridge::GetIndex(void)
{
	return m_iIndex;
}