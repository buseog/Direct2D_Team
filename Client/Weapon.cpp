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