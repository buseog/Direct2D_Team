#include "StdAfx.h"
#include "Weapon.h"

#include "Bridge.h"
#include "KeyMgr.h"



CWeapon::CWeapon(void)
{
}

CWeapon::CWeapon(ITEM*	tItem) :CItem(tItem)
{

}


CWeapon::~CWeapon(void)
{
	Release();
}

HRESULT	CWeapon::Initialize(void)
{

	//m_wstrObjKey = L"Weapon";
	

	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);

	m_wstrObjKey = L"TestWeapon";
	//m_tItem.wstrName = L"¹«±â";
	m_tItem.iOption = 100;
	m_tItem.eType = IT_WEAPON;

	return S_OK;
}

void CWeapon::Progress(void)
{
		
	WorldMatrix();


}

void CWeapon::Release(void)
{
	
	
}
