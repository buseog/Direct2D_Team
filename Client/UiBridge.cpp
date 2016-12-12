#include "StdAfx.h"
#include "UiBridge.h"
#include "Ui.h"
#include "UIMgr.h"

CUiBridge::CUiBridge(void)
{
}


CUiBridge::CUiBridge(CUi*	pUi)
:CBridge(pUi)
{
}

CUiBridge::~CUiBridge(void)
{
}

HRESULT CUiBridge::Initialize(void)
{
	return S_OK;
}

void CUiBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
}

void CUiBridge::Render(void)
{
	//const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey(), 
	//	m_wstrStateKey, (int)m_tFrame.fFrame);

	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pUi->GetObjKey());

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUiBridge::Release(void)
{
	
}

void	CUiBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}