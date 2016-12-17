#include "StdAfx.h"
#include "InvenBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "Item.h"
#include "ItemFactory.h"
#include "KeyMgr.h"
#include "Weapon.h"
#include "Armor.h"
#include "Food.h"
#include "EmptyItem.h"

CInvenBridge::CInvenBridge(void)
: m_bSelect(false)
, m_bDrag(false)
, m_bWeapon(false)
, m_bArmor(false)
, m_iSelectIndex(-1)
, m_iFood(-1)
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
	
	CItem*	pEquipWeapon = CItemFactory<CEmptyItem>::CreateItem(565.f,170.f);
	m_EquipSlot.push_back(pEquipWeapon); // 무기슬롯 빈아이템으로 채우기
	
	CItem*	pEquipArmor = CItemFactory<CEmptyItem>::CreateItem(625.f, 170.f);
	m_EquipSlot.push_back(pEquipArmor); // 방어구슬롯 빈아이템으로 채우기

	return S_OK;
}

void CInvenBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);

	AddItem(rInfo); // 인벤토리에 아이템 추가
	
	Picking(rInfo); // 드래그 및 장착


	if (m_bSelect == false)
		SortItem(rInfo); // 인벤토리 아이템 칸에 맞게 들어가는 정렬

	for (int i = 0; i < 10; ++i)
	{
		m_ItemSlot[i]->Progress();
	}
	
	
	m_EquipSlot[IT_WEAPON]->Progress();
	m_EquipSlot[IT_ARMOR]->Progress();
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

	for(vector<CItem*>::iterator iter = m_EquipSlot.begin();
			iter != m_EquipSlot.end(); ++iter)
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

	for(vector<CItem*>::iterator iter = m_EquipSlot.begin();
			iter != m_EquipSlot.end(); ++iter)
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

	if(CKeyMgr::GetInstance()->KeyDown('U'))
	{
		for(size_t i =0; i < 10; ++i)
		{
			if(m_ItemSlot[i]->GetObjKey() == L"TestFood")
			{
				if(m_ItemSlot[i]->GetItemInfo()->iCount < 500)
				{
					m_ItemSlot[i]->SetFoodPlus(100);
					break;
				}

				else if(m_ItemSlot[i]->GetItemInfo()->iCount >= 500)
				{
					for(int j = 0; j < 10; ++j)
					{
						if(m_ItemSlot[j]->GetObjKey() == L"Empty")
						{
							CItem*	pTemp = m_ItemSlot[j]; 
							m_ItemSlot[j] = CreateFood(rInfo.vPos);
							m_ItemSlot[j]->SetFoodPlus(100);
							::Safe_Delete(pTemp);
							break;
						}
					break;
					}
				
				}
			}

			if(m_ItemSlot[i]->GetObjKey() == L"Empty")
			{
				CItem*	pTemp = m_ItemSlot[i]; 
				m_ItemSlot[i] = CreateFood(rInfo.vPos);
				m_ItemSlot[i]->SetFoodPlus(100);
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

	if(CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON, 1) && m_iSelectIndex >= 0)
	{
		for(size_t j =0; j<10; ++j)
		{
			if(PtInRect(&m_ItemSlot[j]->GetRect(), Pt))
			{
				swap(m_ItemSlot[m_iSelectIndex],m_ItemSlot[j]);
			}			
		}

		if(PtInRect(&m_EquipSlot[IT_WEAPON]->GetRect(), Pt) &&
					 m_ItemSlot[m_iSelectIndex]->GetItemInfo()->eType == IT_WEAPON )
		{
			swap(m_ItemSlot[m_iSelectIndex], m_EquipSlot[IT_WEAPON]);
			m_bWeapon = true;
		}
		
		if(PtInRect(&m_EquipSlot[IT_ARMOR]->GetRect(), Pt) &&
					 m_ItemSlot[m_iSelectIndex]->GetItemInfo()->eType == IT_ARMOR )
		{
			swap(m_ItemSlot[m_iSelectIndex], m_EquipSlot[IT_ARMOR]);
			m_bArmor = true;
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

	// 해제하는 부분
	if(CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON))
	{
		if(PtInRect(&m_EquipSlot[IT_WEAPON]->GetRect(), Pt))
		{
			for(int i = 0; i < 10; ++i)
			{
				if(m_ItemSlot[i]->GetItemInfo()->eType == IT_EMPTY)
				{
					swap(m_ItemSlot[i], m_EquipSlot[IT_WEAPON]);
					m_bWeapon = false;
					break;
				}
			}
		}	
		if(PtInRect(&m_EquipSlot[IT_ARMOR]->GetRect(), Pt))
		{
			for(int i = 0; i < 10; ++i)
			{
				if(m_ItemSlot[i]->GetItemInfo()->eType == IT_EMPTY)
				{
					swap(m_ItemSlot[i], m_EquipSlot[IT_ARMOR]);
					m_bArmor = false;
					break;
				}
			}
		}
		
		
	}
	
	return m_iPriority;
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

CItem*	CInvenBridge::CreateFood(D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CFood>::CreateItem(vPos);
	
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
	m_EquipSlot[IT_WEAPON]->SetPos(565.f, 170.f);
	m_EquipSlot[IT_ARMOR]->SetPos(625.f, 170.f);
}


int	CInvenBridge::Picking(void)
{
	return m_iPriority;
}

