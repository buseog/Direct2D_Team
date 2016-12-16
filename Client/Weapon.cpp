#include "StdAfx.h"
#include "Weapon.h"

#include "Bridge.h"
#include "KeyMgr.h"



CWeapon::CWeapon(void)
{
}

CWeapon::~CWeapon(void)
{
	Release();
}

HRESULT	CWeapon::Initialize(void)
{

	m_wstrObjKey = L"Weapon";
	
	//m_tInfo.vPos = D3DXVECTOR3(0.f,0.f,0.f);
	//m_tInfo.vDir = D3DXVECTOR3(1.f,0.f,0.f);
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);

	m_wstrObjKey = L"TestWeapon";
	//m_tItem.wstrName = L"¹«±â";
	//m_tItem.eType = IT_WEAPON;

	return S_OK;
}

void CWeapon::Progress(void)
{
		
	WorldMatrix();


}

void CWeapon::Render(void)
{
	
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"Weapon");
	

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CWeapon::Release(void)
{
	
	
}

void CWeapon::WorldMatrix(void)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x , 
		m_tInfo.vPos.y , 
		0.f);

	m_tInfo.matWorld = matTrans;
}
