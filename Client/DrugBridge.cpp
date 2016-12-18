#include "StdAfx.h"
#include "DrugBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

CDrugBridge::CDrugBridge(void)
{
}

CDrugBridge::~CDrugBridge(void)
{
}

HRESULT	CDrugBridge::Initialize(void)
{
	m_iMapKey = 0;

	return S_OK;
}

void CDrugBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	m_iMapKey = 0;

}

void CDrugBridge::Render(void)
{
	const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"DRUG", L"Drug", m_iMapKey);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CDrugBridge::Release(void)
{

}

void CDrugBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

void CDrugBridge::SetMapKey(int _iKey)
{
	m_iMapKey = _iKey;
}

int CDrugBridge::Picking(void)
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