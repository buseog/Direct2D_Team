#include "StdAfx.h"
#include "FieldBackBridge.h"

CFieldBackBridge::CFieldBackBridge(void)
{
	m_iX = 45;
	m_iY = 80;
	m_vSize = D3DXVECTOR3(2753.f, 1262.f, 0.f);
}

CFieldBackBridge::~CFieldBackBridge(void)
{
	Release();
}

HRESULT	CFieldBackBridge::Initialize(void)
{
	LoadTile(L"../Data/FieldTile2.dat");
	LoadBack(L"../Data/1.dat");

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

	//for (size_t i = 0; i < m_vecTile.size(); ++i)
	//{ 
	//	pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", m_vecTile[i]->byOption);

	//	D3DXMatrixTranslation(&matTrans, 
	//		m_vecTile[i]->vPos.x + m_pObj->GetScroll().x,
	//		m_vecTile[i]->vPos.y + m_pObj->GetScroll().y,
	//		0.f);

	//	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	//	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
	//		NULL, &D3DXVECTOR3(TILECX / 2.f, TILECY / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//}


	for (size_t i = 0; i < m_vecBack.size(); ++i)
	{ 
		pTexture = CTextureMgr::GetInstance()->GetTexture(L"Back", L"Object", m_vecBack[i]->iIndex);

		D3DXMatrixTranslation(&matTrans, 
			m_vecBack[i]->vPos.x + m_pObj->GetScroll().x,
			m_vecBack[i]->vPos.y + m_pObj->GetScroll().y,
			0.f);

		float fX = pTexture->tImgInfo.Width / 2.f;
		float fY = pTexture->tImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
		CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
			NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}


}

void	CFieldBackBridge::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();

	for_each(m_vecBack.begin(), m_vecBack.end(), DeleteObj());
	m_vecBack.clear();
	
}

int	CFieldBackBridge::Picking(void)
{
	return -1;
}
