#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
: m_pBridge(NULL)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	
}
CItem::CItem(ITEM*	tItem)
: m_pBridge(NULL)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

	m_tItem = *tItem;
}

CItem::~CItem(void)
{
}


const wstring CItem::GetObjKey(void)
{
	return m_wstrObjKey;
}

CBridge* CItem::GetBridge(void)
{
	return m_pBridge;
}

void CItem::SetPos(const D3DXVECTOR3& vPos)
{
	m_tInfo.vPos = vPos;
}

void CItem::SetPos(float fX, float fY)
{
	m_tInfo.vPos.x = fX;
	m_tInfo.vPos.y = fY;
	m_tInfo.vPos.z = 0.f;
}

RECT CItem::GetRect(void)
{
	RECT rc = {
				(int)m_tInfo.vPos.x - (int)(m_tInfo.vSize.x / 2.f),
				(int)m_tInfo.vPos.y - (int)(m_tInfo.vSize.y / 2.f),
				(int)m_tInfo.vPos.x + (int)(m_tInfo.vSize.x / 2.f),
				(int)m_tInfo.vPos.y + (int)(m_tInfo.vSize.y / 2.f),

			};
	
	return rc;
}

ITEM* CItem::GetItemInfo(void)
{
	return &m_tItem;
}

void CItem::SetItemProperty(wstring _Name, ITEMID _eType,int _iOption,int _iPrice, int _iWeight)
{
	m_tItem.wstrName = _Name;
	m_tItem.eType = _eType;
	m_tItem.iOption = _iOption;
	m_tItem.iPrice = _iPrice;
	m_tItem.iWeight = _iWeight;
}

INFO*	CItem::GetInfo(void)
{
	return &m_tInfo;

}

void	CItem::SetFoodPlus(int iCount)
{
	m_tItem.iCount += iCount;
}

void	CItem::SetFoodZero(void)
{
	m_tItem.iCount = 0;
}


HRESULT	CItem::Initialize(void)
{

	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);


	return S_OK;
}

void CItem::Progress(void)
{
		
	WorldMatrix();


}

void CItem::Render(void)
{
	
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrObjKey);
	

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CItem::Release(void)
{
	
	
}

void CItem::WorldMatrix(void)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x , 
		m_tInfo.vPos.y , 
		0.f);

	m_tInfo.matWorld = matTrans;
}
