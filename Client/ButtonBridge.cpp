#include "StdAfx.h"
#include "ButtonBridge.h"
#include "Ui.h"
#include "KeyMgr.h"

CButtonBridge::CButtonBridge(void)
{
}

CButtonBridge::~CButtonBridge(void)
{
	Release();
}

HRESULT CButtonBridge::Initialize(void)
{
	return S_OK;
}

void CButtonBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	
	if(CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON))
	{
		
		
	}

}

void CButtonBridge::Render(void)
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

void CButtonBridge::Release(void)
{
	
}

void	CButtonBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

int	CButtonBridge::Picking(void)
{
	return m_iPriority;
}