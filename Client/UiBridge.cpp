#include "StdAfx.h"
#include "UiBridge.h"
#include "Ui.h"


CUiBridge::CUiBridge(void)
: m_iPriority(0)
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
	
}

void CUiBridge::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey(), 
		m_wstrStateKey, (int)m_tFrame.fFrame);

	
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
	

}

int		CUiBridge::Picking(void)
{
	return -1;
}