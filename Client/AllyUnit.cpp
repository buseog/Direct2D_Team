#include "StdAfx.h"
#include "AllyUnit.h"

CAllyUnit::CAllyUnit(void)
{
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

	m_tUnitData.wstrName = L"�̼���";
	m_tUnitData.tDetail.iLevel = 2;
	m_tUnitData.iAttack = 10;
	m_tUnitData.iDeffence = 5;
	m_tUnitData.iHealthPoint = 100;
	m_tUnitData.iMaxHelathPoint = 100;
	m_tUnitData.tDetail.iExperience = 0;
	m_tUnitData.tDetail.iBonusPoint = 5;
	m_tUnitData.tDetail.iWeight = 0;
	m_tUnitData.tDetail.iStr = 10;
	m_tUnitData.tDetail.iDex = 10;
	m_tUnitData.tDetail.iVital = 10;
	m_tUnitData.tDetail.iInt = 10;
	m_tUnitData.iLAttack = 100;
	m_tUnitData.iSAttack = 150;
	m_tUnitData.tDetail.UnitType = UNIT_ALLY;

	m_fSpeed = 200.f;

	return S_OK;
}

void CAllyUnit::Progress(void)
{
	if(m_pBridge)
	{
		m_pBridge->Progress(m_tInfo);
	}

	//if(m_wstrObjKey==L"TestUnit")
	//{
	//	ScaleSync();
	//	return;
	//}
	//else
	//{
	//	WorldMatrix();
	//	return;
	//}
}

void CAllyUnit::Render(void)
{
	if(m_pBridge)
	{
		m_pBridge->Render();
	}

	/*const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrObjKey);
	
	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));*/

}

void CAllyUnit::Release(void)
{
	::Safe_Delete(m_pBridge);
}