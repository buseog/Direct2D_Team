#include "StdAfx.h"
#include "AllyUnit.h"

CAllyUnit::CAllyUnit(void)
{
	m_fSpeed = 200.f;
	ZeroMemory(&m_tInfo, sizeof(INFO));
}
CAllyUnit::CAllyUnit(UNITDATA*	tUnit) :CUnit(tUnit)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tUnitData = *tUnit;
}
CAllyUnit::~CAllyUnit(void)
{
	Release();
}

HRESULT CAllyUnit::Initialize(void)
{
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);

	m_wstrObjKey = L"TestUnit";
	m_tUnitData.tDetail.UnitType = UNIT_ALLY;


	return S_OK;
}

void CAllyUnit::Progress(void)
{
	if(m_pBridge)
	{
		m_pBridge->Progress(m_tInfo);
	}

	/*if(m_wstrObjKey==L"TestUnit")
	{
		ScaleSync();
		return;
	}
	else
	{
		WorldMatrix();
		return;
	}*/
}

void CAllyUnit::Render(void)
{
	if(m_pBridge)
	{
		m_pBridge->Render();
	}

	//const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrObjKey);
	//
	//if(pTexture == NULL)
	//	return;

	//float fX = pTexture->tImgInfo.Width  / 2.f;
	//float fY = pTexture->tImgInfo.Height / 2.f;

	//CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	//CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
	//	NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CAllyUnit::Release(void)
{
	::Safe_Delete(m_pBridge);
}