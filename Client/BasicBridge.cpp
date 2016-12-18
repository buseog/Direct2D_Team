#include "StdAfx.h"
#include "BasicBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

CBasicBridge::CBasicBridge(void)
{
}

CBasicBridge::~CBasicBridge(void)
{
}

HRESULT	CBasicBridge::Initialize(void)
{
	m_iMapKey = 0;

	return S_OK;
}

void CBasicBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	m_iMapKey = 0;

}

void CBasicBridge::Render(void)
{
	const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"BASIC", L"Basic", m_iMapKey);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBasicBridge::Release(void)
{

}

void CBasicBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

void CBasicBridge::SetMapKey(int _iKey)
{
	m_iMapKey = _iKey;
}

int CBasicBridge::Picking(void)
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