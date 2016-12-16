#include "StdAfx.h"
#include "Armor.h"


CArmor::CArmor(void)
{
}

CArmor::~CArmor(void)
{
	
	Release();
}
HRESULT CArmor::Initialize(void)
{
	m_wstrObjKey = L"Armor";
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);
	
	m_wstrObjKey = L"TestArmor";

	return S_OK;
}
void CArmor::Progress(void)
{
	WorldMatrix();
	
}
void CArmor::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"Armor");
	

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CArmor::Release(void)
{
}

void CArmor::WorldMatrix(void)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x , 
		m_tInfo.vPos.y , 
		0.f);

	m_tInfo.matWorld = matTrans;
}
