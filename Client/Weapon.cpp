#include "StdAfx.h"
#include "Weapon.h"

CWeapon::CWeapon(void)
{
}

CWeapon::~CWeapon(void)
{
	Release();
}
HRESULT CWeapon::Initialize(void)
{
	m_wstrObjKey = L"TestWeapon";
	//m_tItem.wstrName = L"¹«±â";
	//m_tItem.eType = IT_WEAPON;
	return S_OK;
}
int CWeapon::Progress(void)
{
	return 0;
}
void CWeapon::Render(void)
{
}
void CWeapon::Release(void)
{
}