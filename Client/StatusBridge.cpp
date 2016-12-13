#include "StdAfx.h"
#include "StatusBridge.h"
#include "UIMgr.h"
#include "Ui.h"

CStatusBridge::CStatusBridge(void)
{
}

CStatusBridge::~CStatusBridge(void)
{
		Release();

}


HRESULT CStatusBridge::Initialize(void)
{
	m_wstrStateKey = L"Status";

	return S_OK;
}

void CStatusBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
}

void CStatusBridge::Render(void)
{
	
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pUi->GetObjKey());

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CStatusBridge::Release(void)
{
	
}

void	CStatusBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}