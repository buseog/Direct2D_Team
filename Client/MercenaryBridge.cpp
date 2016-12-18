#include "StdAfx.h"
#include "MercenaryBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

CMercenaryBridge::CMercenaryBridge(void)
{
}

CMercenaryBridge::~CMercenaryBridge(void)
{
}

HRESULT	CMercenaryBridge::Initialize(void)
{
	m_iMapKey = 0;

	return S_OK;
}

void CMercenaryBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	m_iMapKey = 0;

}

void CMercenaryBridge::Render(void)
{
	const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MERCENARY", L"Mercenary", m_iMapKey);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMercenaryBridge::Release(void)
{

}

void CMercenaryBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

void CMercenaryBridge::SetMapKey(int _iKey)
{
	m_iMapKey = _iKey;
}

int CMercenaryBridge::Picking(void)
{
	POINT	Pt;
	Pt.x = (long)GetMouse().x;
	Pt.y = (long)GetMouse().y;

	if(PtInRect(&m_pUi->GetRect(), Pt))
	{
		SetMapKey(1);
		if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON, 7))
		{
			return 1;	

		}
	}


	return -1;
}