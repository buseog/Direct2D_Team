#include "StdAfx.h"
#include "StoreBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "Item.h"
#include "ItemFactory.h"
#include "KeyMgr.h"
#include "Weapon.h"
#include "Armor.h"
#include "Glove.h"
#include "Helmet.h"
#include "Boots.h"
#include "Belt.h"
#include "Food.h"
#include "EmptyItem.h"
#include "Unit.h"
#include "UnitFactory.h"
#include "AllyUnit.h"
#include "EnemyUnit.h"
#include "EmptyUnit.h"

CStoreBridge::CStoreBridge(void)
: m_bSelect(false)
, m_bTooltip(false)
, m_bPick(false)
, m_bArmor(false)
, m_iSelectIndex(-1)
, m_iFood(-1)
{
}

CStoreBridge::~CStoreBridge(void)
{
	Release();
}


HRESULT CStoreBridge::Initialize(void)
{

	//m_wstrStateKey = L"Inventory";
	ITEM* pItem =new ITEM;
	//ZeroMemory(pItem);
	for(int i =0; i<20; ++i)
	{
		m_ItemSlot.push_back(CreateEmpty(m_tInfo.vPos));
	}
	::Safe_Delete(pItem);
	//
	//CItem*	pEquipWeapon = CItemFactory<CEmptyItem>::CreateItem(565.f,170.f);
	//m_EquipSlot.push_back(pEquipWeapon); // 무기슬롯 빈아이템으로 채우기
	//
	//CItem*	pEquipArmor = CItemFactory<CEmptyItem>::CreateItem(625.f, 170.f);
	//m_EquipSlot.push_back(pEquipArmor); // 방어구슬롯 빈아이템으로 채우기

	return S_OK;
}

void CStoreBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);

	AddItem(rInfo); // 인벤토리에 아이템 추가
	

	if (m_bSelect == false)
		SortItem(rInfo); // 인벤토리 아이템 칸에 맞게 들어가는 정렬

	for (int i = 0; i < 20; ++i)
	{
		m_ItemSlot[i]->Progress();
	}
	
	
//	m_EquipSlot[IT_WEAPON]->Progress();
//	m_EquipSlot[IT_ARMOR]->Progress();
}	

void CStoreBridge::Render(void)
{
	
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);
	

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

	//for(vector<CItem*>::iterator iter = m_EquipSlot.begin();
	//		iter != m_EquipSlot.end(); ++iter)
	//	{
	//		(*iter)->Render();
	//	}
	//
	
}

void CStoreBridge::Release(void)
{
	for(vector<CItem*>::iterator iter = m_ItemSlot.begin();
			iter != m_ItemSlot.end(); ++iter)
		{
			::Safe_Delete(*iter);
			
		}

	//for(vector<CItem*>::iterator iter = m_EquipSlot.begin();
	//		iter != m_EquipSlot.end(); ++iter)
	//	{
	//		::Safe_Delete(*iter);
	//		
	//	}
	
	
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

void CStoreBridge::AddItem(INFO& rInfo)///수정 필요
{

	/*if(CKeyMgr::GetInstance()->KeyDown('P'))
	{	
		for(size_t i =0; i < 20; ++i)
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
		for(size_t i =0; i < 20; ++i)
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
		for(size_t i =0; i < 20; ++i)
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
					for(int j = 0; j < 20; ++j)
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
	*/
}

int CStoreBridge::Picking(void)
{
	POINT	Pt;
		Pt.x = (long)GetMouse().x;
		Pt.y = (long)GetMouse().y;

	if(CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON, 1) && m_iSelectIndex >= 0)
	{
		for(size_t j =0; j<20; ++j)
		{
			if(PtInRect(&m_ItemSlot[j]->GetRect(), Pt))
			{
				swap(m_ItemSlot[m_iSelectIndex],m_ItemSlot[j]);
			}			
		}

		m_bSelect = false;
		m_iSelectIndex = -1;

		return 1;
	}



	if(CKeyMgr::GetInstance()->StayKeyDown(VK_LBUTTON) && m_iSelectIndex >= 0 && m_bSelect)
	{
		m_ItemSlot[m_iSelectIndex]->SetPos(GetMouse());

		return 1;
		
	}	
			
	if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON) && !m_ItemSlot.empty() && m_bSelect == false)
	{
		for(size_t i =0 ; i < 10; ++i)
		{
			if(PtInRect(&m_ItemSlot[i]->GetRect(), Pt))
			{
				m_bSelect = true;
				m_iSelectIndex = i;

				return 1;
			}
		}
		
	}

	
	return -1;
}

CItem*	CStoreBridge::CreateWeapon(ITEM* _pItem,D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CWeapon>::CreateItem(_pItem,vPos);
	
	return pItem;
}

CItem*	CStoreBridge::CreateArmor(ITEM* _pItem,D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CArmor>::CreateItem(_pItem,vPos);
	
	return pItem;
}

CItem*	CStoreBridge::CreateGlove(ITEM* _pItem,D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CGlove>::CreateItem(_pItem,vPos);
	
	return pItem;
}

CItem*	CStoreBridge::CreateHelmet(ITEM* _pItem,D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CHelmet>::CreateItem(_pItem,vPos);
	
	return pItem;
}

CItem*	CStoreBridge::CreateBoots(ITEM* _pItem,D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CBoots>::CreateItem(_pItem,vPos);
	
	return pItem;
}

CItem*	CStoreBridge::CreateBelt(ITEM* _pItem,D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CBelt>::CreateItem(_pItem,vPos);
	
	return pItem;
}


CItem*	CStoreBridge::CreateFood(ITEM* _pItem,D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CFood>::CreateItem(_pItem,vPos);
	
	return pItem;
}

CItem*	CStoreBridge::CreateEmpty(D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CEmptyItem>::CreateItem(vPos);
	
	return pItem;
}

CUnit* CStoreBridge::CreateUnitAlly(UNITDATA* _pUnit,D3DXVECTOR3 vPos)
{
	CUnit*	pUnit = CUnitFactory<CAllyUnit>::CreateUnit(_pUnit,vPos);
	
	return pUnit;
}

CUnit* CStoreBridge::CreateUnitEnemy(UNITDATA* _pUnit,D3DXVECTOR3 vPos)
{
	CUnit*	pUnit = CUnitFactory<CEnemyUnit>::CreateUnit(_pUnit,vPos);
	
	return pUnit;
}

CUnit*	CStoreBridge::CreateEmptyUnit(D3DXVECTOR3 vPos)
{
	CUnit*	pUnit = CUnitFactory<CEmptyUnit>::CreateUnit(vPos);
	
	return pUnit;
}
void CStoreBridge::SortItem(INFO& rInfo)
{

	for(size_t i = 0; i < 4; ++i)
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
										   (rInfo.vPos.y - 50) + (i * 65));
		}
	}

}
//
//void CStoreBridge::SortUnit(INFO& rInfo)
//{
//
//	for(size_t i = 0; i < 4; ++i)
//	{
//		for(size_t j = 0; j< 5; ++j)
//		{	
//			size_t iIndex = i * 5 + j;
//			if(iIndex >= m_UnitSlot.size())
//			{
//				break;
//			}
//			if (iIndex == m_iSelectIndex)
//				break;
//		
//			m_UnitSlot[iIndex]->SetPos((rInfo.vPos.x - 130) + (j * 65),
//										   (rInfo.vPos.y - 50) + (i * 65));
//		}
//	}
//
//}

void CStoreBridge::LoadData(void)
{
}

void CStoreBridge::ShowTooltip(void)
{
}