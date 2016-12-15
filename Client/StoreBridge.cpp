#include "StdAfx.h"
#include "StoreBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Glove.h"
#include "Helmet.h"
#include "Boots.h"
#include "Belt.h"
#include "Food.h"

CStoreBridge::CStoreBridge(void)
:m_bState(FALSE),m_bToolTip(FALSE)
{
}

CStoreBridge::~CStoreBridge(void)
{
	Release();

}


HRESULT CStoreBridge::Initialize(void)
{

	m_wstrStateKey = L"Store";
	AddItem(IT_BELT);
	AddItem(IT_ARMOR);
	AddItem(IT_WEAPON);
	AddItem(IT_FOOD);
	AddItem(IT_BOOTS);
	AddItem(IT_HELMET);
	AddItem(IT_FOOD);
	AddItem(IT_BOOTS);
	AddItem(IT_HELMET);
	AddItem(IT_FOOD);
	AddItem(IT_BOOTS);
	AddItem(IT_HELMET);
	AddItem(IT_HELMET);
	AddItem(IT_HELMET);
	AddItem(IT_HELMET);
	AddItem(IT_HELMET);
	AddItem(IT_HELMET);


	//DeleteContainedOverItem();

	return S_OK;
}

void CStoreBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);

	int iIndexX=0;
	int iIndexY=0;
	for(vector<CItem*>::size_type i=0;i<m_vecItem.size();i++)
	{
		pItemTexture = CTextureMgr::GetInstance()->GetTexture(m_vecItem[i]->GetItemKey());

		float fIconX = (float)(CTextureMgr::GetInstance()->GetTexture(m_vecItem[i]->GetItemKey())->tImgInfo.Width);
		float fIconY = (float)(CTextureMgr::GetInstance()->GetTexture(m_vecItem[i]->GetItemKey())->tImgInfo.Height);
		//m_vecItem[i]

		float fx = m_pUi->GetInfo()->vPos.x;
		float fy = m_pUi->GetInfo()->vPos.y;
		float fX = fx-fx/2-fx/4+8;
		float fY = fy-fy/4+12;

		m_vecItem[i]->SetPos(D3DXVECTOR3(fX+(iIndexX*(fIconX+4)),fY+(iIndexY*(fIconY+5)),0.f));
		/*m_vecItem[i]->SetPos(D3DXVECTOR3(pItemTexture->tImgInfo.Width  / 2.f +((fIconX*2+8)-(iIndexX*fIconX+(iIndexX*4))),
		pItemTexture->tImgInfo.Height / 2.f + (fIconY-9)-((fIconY+5)*iIndexY),
		0));*/
		//float fXtmp = pItemTexture->tImgInfo.Width  / 2.f +((fIconX*2+8)-(iIndexX*fIconX+(iIndexX*4)));
		//float fYtmp = pItemTexture->tImgInfo.Height / 2.f + (fIconY-9)-((fIconY+5)*iIndexY);
		//CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);

		//&D3DXVECTOR3(fXtmp, fYtmp, 0.f) ,

		iIndexX++;
		if(iIndexX%5==0)
		{
			iIndexY++;
			iIndexX=0;
		}
	}
	Picking();


}

void CStoreBridge::Render(void)
{

	//	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pUi->GetObjKey());
	pTexture = CTextureMgr::GetInstance()->GetTexture(m_pUi->GetObjKey());
	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	for(vector<CItem*>::size_type i=0;i<m_vecItem.size();i++)
	{
		D3DXMATRIX matTrans;
		pItemTexture = CTextureMgr::GetInstance()->GetTexture(m_vecItem[i]->GetItemKey());
		D3DXMatrixTranslation(&matTrans,m_vecItem[i]->GetItemInfo()->vPos.x,m_vecItem[i]->GetItemInfo()->vPos.y,0.f);
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
		CDevice::GetInstance()->GetSprite()->Draw(pItemTexture->pTexture, 
			NULL, &D3DXVECTOR3(pItemTexture->tImgInfo.Width / 2.f, pItemTexture->tImgInfo.Height / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(m_bToolTip==TRUE)
	{
		ShowToolTip();
	}

	///testcode
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 600.f, 200.f, 0.f);
	TCHAR m_szTooltip[MIN_STR];
	wsprintf(m_szTooltip,L"Tooltip : %d ,index : %d" ,(int)m_bToolTip,m_iToolTipIndex);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szTooltip, 
		lstrlen(m_szTooltip), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 0));

}

void CStoreBridge::Picking(void)
{
	if(m_bState==FALSE)
		return;
	D3DXVECTOR3 vecMousepos = ::GetMouse();
	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	if(vecMousepos.x <= m_pUi->GetInfo()->vPos.x+fX &&
		vecMousepos.x >= m_pUi->GetInfo()->vPos.x-fX &&
		vecMousepos.y <= m_pUi->GetInfo()->vPos.y+fY &&
		vecMousepos.y >= m_pUi->GetInfo()->vPos.y-fY)
	{
		for(vector<CItem*>::size_type i=0;i<m_vecItem.size();i++)
		{
			float fIconX = (float)(CTextureMgr::GetInstance()->GetTexture(m_vecItem[i]->GetItemKey())->tImgInfo.Width)/2.f;
			float fIconY = (float)(CTextureMgr::GetInstance()->GetTexture(m_vecItem[i]->GetItemKey())->tImgInfo.Height)/2.f;
			float fItemX =m_vecItem[i]->GetItemInfo()->vPos.x;
			float fItemY =m_vecItem[i]->GetItemInfo()->vPos.y;
			if(vecMousepos.x >= fItemX-fIconX &&//오른쪽
				vecMousepos.x <= fItemX+fIconX && //왼쪽
				vecMousepos.y >= fItemY-fIconY &&//위
				vecMousepos.y <= fItemY+fIconY //아래
				) //오른쪽)
			{
				//showtooltip
				m_bToolTip=TRUE;
				m_iToolTipIndex=i;
				return;
			}
			else
			{
				m_bToolTip=FALSE;
			}

		}
	}
	//::GetMouse();
}
void CStoreBridge::ShowToolTip(/*int _iIndex,*/)
{

	D3DXVECTOR3 vecMousepos = ::GetMouse();
	D3DXMATRIX matTrans;
	pToolTipTexture = CTextureMgr::GetInstance()->GetTexture(L"ToolTip");
	float ToolTipPosX = vecMousepos.x+pToolTipTexture->tImgInfo.Width/2.f;
	float ToolTipPosY = vecMousepos.y+pToolTipTexture->tImgInfo.Height / 2.f;
	D3DXMatrixTranslation(&matTrans,ToolTipPosX,ToolTipPosY,vecMousepos.z);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pToolTipTexture->pTexture, 
		NULL,&D3DXVECTOR3(pToolTipTexture->tImgInfo.Width/2.f,pToolTipTexture->tImgInfo.Height / 2.f,0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));



	//초상화
	pItemTexture = CTextureMgr::GetInstance()->GetTexture(m_vecItem[m_iToolTipIndex]->GetItemKey());
	D3DXMatrixTranslation(&matTrans,ToolTipPosX-100,ToolTipPosY-50,0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pItemTexture->pTexture, 
		NULL, &D3DXVECTOR3(pItemTexture->tImgInfo.Width / 2.f, pItemTexture->tImgInfo.Height / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//툴팁 출력
	D3DXMatrixTranslation(&matTrans, ToolTipPosX, ToolTipPosY-80, 0.f);
	TCHAR m_szTooltip[MIN_STR] = L"";
	


	switch(m_vecItem[m_iToolTipIndex]->GetItemInfo()->eType)
	{
	case IT_WEAPON:
		{
			wsprintf(m_szTooltip, L"이름 : %s \n공격력 : %d\n무게 : %d \n가격 : %d 냥" ,m_vecItem[m_iToolTipIndex]->GetItemInfo()->wstrName.c_str(),
				m_vecItem[m_iToolTipIndex]->GetItemInfo()->iOption,
				m_vecItem[m_iToolTipIndex]->GetItemInfo()->iWeight,
				m_vecItem[m_iToolTipIndex]->GetItemInfo()->iPrice);
			break;
		}
	case IT_GLOVE:
	case IT_HELMET:
	case IT_BOOTS:
	case IT_BELT:
	case IT_ARMOR:
		{
			wsprintf(m_szTooltip, L"이름 : %s \n방어력 : %d\n무게 : %d \n가격 : %d 냥" ,m_vecItem[m_iToolTipIndex]->GetItemInfo()->wstrName.c_str(),
				m_vecItem[m_iToolTipIndex]->GetItemInfo()->iOption,
				m_vecItem[m_iToolTipIndex]->GetItemInfo()->iWeight,
				m_vecItem[m_iToolTipIndex]->GetItemInfo()->iPrice);
			break;
		}
	case IT_FOOD:
		{
			wsprintf(m_szTooltip, L"이름 : %s \n회복량: %d" ,m_vecItem[m_iToolTipIndex]->GetItemInfo()->wstrName.c_str(), m_vecItem[m_iToolTipIndex]->GetItemInfo()->iOption);
			break;
		}
	case IT_TRADE:
		{
			break;
		}
	}
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szTooltip, 
		lstrlen(m_szTooltip), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 0));






}
void CStoreBridge::Release(void)
{
	for(vector<CItem*>::size_type i=0;i<m_vecItem.size();i++)
	{
		::Safe_Delete(m_vecItem[i]);
	}

}

void	CStoreBridge::WorldMatrix(INFO& rInfo)
{

	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

void	CStoreBridge::AddItem(ITEMID _itemid)
{
	CItem* pItemTest;
	switch(_itemid)
	{
	case IT_WEAPON:
		{
			pItemTest = new CWeapon;
			((CWeapon*)pItemTest)->Initialize();
			((CWeapon*)pItemTest)->SetItemProperty(L"무기이름",IT_WEAPON,10,1000,30);
			break;
		}
	case IT_ARMOR:
		{
			pItemTest = new CArmor;
			((CArmor*)pItemTest)->Initialize();
			((CArmor*)pItemTest)->SetItemProperty(L"가슴이름",IT_ARMOR,10,1000,30);
			break;
		}
	case IT_GLOVE:
		{
			pItemTest = new CGlove;
			((CGlove*)pItemTest)->Initialize();
			((CGlove*)pItemTest)->SetItemProperty(L"손가락이름",IT_GLOVE,10,1000,30);
			break;
		}
	case IT_HELMET:
		{
			pItemTest = new CHelmet;
			((CHelmet*)pItemTest)->Initialize();
			((CHelmet*)pItemTest)->SetItemProperty(L"하이바이름",IT_HELMET,10,1000,30);
			break;
		}
	case IT_BOOTS:
		{
			pItemTest = new CBoots;
			((CBoots*)pItemTest)->Initialize();
			((CBoots*)pItemTest)->SetItemProperty(L"발가락이름",IT_BOOTS,10,1000,30);
			break;
		}
	case IT_BELT:
		{
			pItemTest = new CBelt;
			((CBelt*)pItemTest)->Initialize();
			((CBelt*)pItemTest)->SetItemProperty(L"허리이름",IT_BELT,10,1000,30);
			break;
		}
	case IT_FOOD:
		{
			pItemTest = new CFood;
			((CFood*)pItemTest)->Initialize();
			((CFood*)pItemTest)->SetItemProperty(L"음식이름",IT_FOOD,10,1000,30);
			break;
		}
	}
	m_vecItem.push_back(pItemTest);

}


void CStoreBridge::DeleteContainedOverItem(void)
{
	if(m_vecItem.size()>20)
	{
		for(vector<CItem*>::size_type i=15;i<m_vecItem.size();i++)
		{
			::Safe_Delete(m_vecItem[i]);
		}
	}
}
void CStoreBridge::SetState(void)
{
	if(m_bState==FALSE)
	{
		m_bState=TRUE;
	}
	else if(m_bState==TRUE)
	{
		m_bState=FALSE;
	}
}