#include "StdAfx.h"
#include "Food.h"

CFood::CFood(void)
{
}
CFood::CFood(ITEM*	tItem) :CItem(tItem)
{

}
CFood::~CFood(void)
{
	Release();
}
HRESULT CFood::Initialize(void)
{
	m_wstrObjKey = L"TestFood";
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);
	m_tItem.iCount = 0;
	m_tItem.eType = IT_FOOD;

	return S_OK;
}
void CFood::Progress(void)
{
	WorldMatrix();
}
void CFood::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"TestFood");
	
	D3DXMATRIX	matTrans2;

	TCHAR			szCount[MIN_STR];

	wsprintf(szCount, L"%d", m_tItem.iCount);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		szCount, 
		lstrlen(szCount), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CFood::Release(void)
{
}

void CFood::WorldMatrix(void)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x  , 
		m_tInfo.vPos.y  , 
		0.f);

	m_tInfo.matWorld = matTrans;
}
