#include "StdAfx.h"
#include "InvenBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "Item.h"
#include "ItemFactory.h"
#include "KeyMgr.h"
#include "Weapon.h"
#include "Armor.h"
#include "EmptyItem.h"

CInvenBridge::CInvenBridge(void)
: m_bSelect(false)
, m_bDrag(false)
, m_iSelectIndex(-1)

{
}

CInvenBridge::~CInvenBridge(void)
{
		Release();
}


HRESULT CInvenBridge::Initialize(void)
{
	m_wstrStateKey = L"Inventory";


	for(int i =0; i<10; ++i)
	{
	
		m_ItemSlot.push_back(CreateEmpty(m_tInfo.vPos));
	
	}
	return S_OK;
}

void CInvenBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);

	AddItem(rInfo); // 인벤토리에 아이템 추가
	
	Picking(rInfo); // 드래그
	
	if (m_bSelect == false)
		SortItem(rInfo); // 인벤토리 아이템 칸에 맞게 들어가는 정렬

	for (int i = 0; i < 10; ++i)
	{
		m_ItemSlot[i]->Progress();
	}
	
}	

void CInvenBridge::Render(void)
{
	
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pUi->GetObjKey());
	

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	
	for(vector<CItem*>::iterator iter = m_ItemSlot.begin();
			iter != m_ItemSlot.end(); ++iter)
		{
			(*iter)->Render();
		}

	
		


	
}

void CInvenBridge::Release(void)
{
	for(vector<CItem*>::iterator iter = m_ItemSlot.begin();
			iter != m_ItemSlot.end(); ++iter)
		{
			::Safe_Delete(*iter);
			
		}
	
	
	
}

void	CInvenBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

void CInvenBridge::AddItem(INFO& rInfo)
{

	if(CKeyMgr::GetInstance()->KeyDown('P'))
	{	
		for(size_t i =0; i < 10; ++i)
		{
			if(m_ItemSlot[i]->GetObjKey() == L"Empty")
			{
				CItem*	pTemp = m_ItemSlot[i]; 

				m_ItemSlot[i] = CreateWeapon(rInfo.vPos);
				::Safe_Delete(pTemp);
				break;
			}
		}
	}

	if(CKeyMgr::GetInstance()->KeyDown('O'))
	{
		for(size_t i =0; i < 10; ++i)
		{
			if(m_ItemSlot[i]->GetObjKey() == L"Empty")
			{
				CItem*	pTemp = m_ItemSlot[i]; 

				m_ItemSlot[i] = CreateArmor(rInfo.vPos);
				::Safe_Delete(pTemp);
				break;
			}
		}
	}
	
}

int CInvenBridge::Picking(INFO& rInfo)
{
	POINT	Pt;
		Pt.x = (long)GetMouse().x;
		Pt.y = (long)GetMouse().y;

	if(CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON, 1))
	{
		for(size_t j =0; j<10; ++j)
		{
			if(PtInRect(&m_ItemSlot[j]->GetRect(), Pt))
			{
				swap(m_ItemSlot[m_iSelectIndex],m_ItemSlot[j]);
			}			
		}
		m_bSelect = false;
		m_iSelectIndex = -1;
	}

	if(CKeyMgr::GetInstance()->StayKeyDown(VK_LBUTTON) && m_iSelectIndex >= 0 && m_bSelect)
	{
		m_ItemSlot[m_iSelectIndex]->SetPos(GetMouse());
		
	}	
			
	if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON) && !m_ItemSlot.empty() && m_bSelect == false)
	{
		for(size_t i =0 ; i < 10; ++i)
		{
			if(PtInRect(&m_ItemSlot[i]->GetRect(), Pt))
			{
				m_bSelect = true;
				m_iSelectIndex = i;
			}
		}
	}
	return 2;
}

CItem*	CInvenBridge::CreateWeapon(D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CWeapon>::CreateItem(vPos);
	
	return pItem;
}

CItem*	CInvenBridge::CreateArmor(D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CArmor>::CreateItem(vPos);
	
	return pItem;
}

CItem*	CInvenBridge::CreateEmpty(D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CEmptyItem>::CreateItem(vPos);
	
	return pItem;
}


void CInvenBridge::SortItem(INFO& rInfo)
{

	for(size_t i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j< 5; ++j)
		{	
			size_t iIndex = i * 5 + j;
			if(iIndex >= m_ItemSlot.size())
			{
				break;
			}
			if (iIndex == m_iSelectIndex)
				break;
		
			m_ItemSlot[iIndex]->SetPos((rInfo.vPos.x - 130) + (j * 65),
										   (rInfo.vPos.y + 55) + (i * 65));
		}
	}
}

void CInvenBridge::SetItem(INFO& rInfo)
{

}

int	CInvenBridge::Picking(void)
{
	return m_iPriority;
}

