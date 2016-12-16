#include "StdAfx.h"
#include "FieldBackBridge.h"

CFieldBackBridge::CFieldBackBridge(void)
{
}

CFieldBackBridge::~CFieldBackBridge(void)
{
	Release();
}

HRESULT	CFieldBackBridge::Initialize(void)
{

	return S_OK;
}

void	CFieldBackBridge::Progress(INFO& rInfo)
{

}

void	CFieldBackBridge::Render(void)
{
	D3DXMATRIX	matTrans;

	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);

	D3DXMatrixTranslation(&matTrans, 
		0 + m_pObj->GetScroll().x,
		0 + m_pObj->GetScroll().y,
		0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(TILECX / 2.f, TILECY / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));


}

void	CFieldBackBridge::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();
}

void	CFieldBackBridge::Picking(void)
{
	return;
}