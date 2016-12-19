#include "StdAfx.h"
#include "InvenBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "Item.h"
#include "ItemFactory.h"
#include "KeyMgr.h"
#include "Weapon.h"
#include "Armor.h"
#include "Belt.h"
#include "Glove.h"
#include "Food.h"
#include "EmptyItem.h"
#include "Player.h"
#include "ObjMgr.h"

CInvenBridge::CInvenBridge(void)
: m_bSelect(false)
, m_bDrag(false)
, m_bWeapon(false)
, m_bArmor(false)
, m_bBelt(false)
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
	m_EquipSlot.push_back(pEquipWeapon); // ���⽽�� ����������� ä���
	
	CItem*	pEquipArmor = CItemFactory<CEmptyItem>::CreateItem(625.f, 170.f);
	m_EquipSlot.push_back(pEquipArmor); // ������ ����������� ä���
	
	CItem*	pEquipGlove = CItemFactory<CEmptyItem>::CreateItem(685.f, 110.f);
	m_EquipSlot.push_back(pEquipGlove);  //�尩���� ����������� ���߱�
	

	return S_OK;
}

void CInvenBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);

	AddItem(rInfo); // �κ��丮�� ������ �߰�
	

	if (m_bSelect == false)
		SortItem(rInfo); // �κ��丮 ������ ĭ�� �°� ���� ����

	for (int i = 0; i < 10; ++i)
	{
		m_ItemSlot[i]->Progress();
	}
	
	
	m_EquipSlot[IT_WEAPON]->Progress();
	m_EquipSlot[IT_ARMOR]->Progress();
	m_EquipSlot[IT_GLOVE]->Progress();
}	

void CInvenBridge::Render(void)
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

	if(CKeyMgr::GetInstance()->KeyDown('P')) // �������
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

	if(CKeyMgr::GetInstance()->KeyDown('O')) // ���ʻ���
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

	
	if(CKeyMgr::GetInstance()->KeyDown('Y')) //�尩 ����
	{
		for(size_t i =0; i < 10; ++i)
		{
			if(m_ItemSlot[i]->GetObjKey() == L"Empty")
			{
				CItem*	pTemp = m_ItemSlot[i]; 

				m_ItemSlot[i] = CreateGlove(rInfo.vPos);
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

int CInvenBridge::Picking(void)
{
	POINT	Pt;
		Pt.x = (long)GetMouse().x;
		Pt.y = (long)GetMouse().y;

		const CObj*	pPlayer = CObjMgr::GetInstance()->GetObjList(SC_FIELD, OBJ_PLAYER)->front();

	if(CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON, 1) && m_iSelectIndex >= 0)
	{
		for(size_t j =0; j<10; ++j)
		{
			if(PtInRect(&m_ItemSlot[j]->GetRect(), Pt))
			{
				swap(m_ItemSlot[m_iSelectIndex],m_ItemSlot[j]);
			}			
		}

	
		// ���� ����
		if(PtInRect(&m_EquipSlot[IT_WEAPON]->GetRect(), Pt) &&
					 m_ItemSlot[m_iSelectIndex]->GetItemInfo()->eType == IT_WEAPON )
		{
			swap(m_ItemSlot[m_iSelectIndex], m_EquipSlot[IT_WEAPON]);
			((CPlayer*)pPlayer)->SetPlusAttack(m_EquipSlot[IT_WEAPON]->GetItemInfo()->iOption);		
			
		}
		
		// �� ����
		if(PtInRect(&m_EquipSlot[IT_ARMOR]->GetRect(), Pt) &&
					 m_ItemSlot[m_iSelectIndex]->GetItemInfo()->eType == IT_ARMOR )
		{
			swap(m_ItemSlot[m_iSelectIndex], m_EquipSlot[IT_ARMOR]);
			((CPlayer*)pPlayer)->SetPlusDefence(m_EquipSlot[IT_ARMOR]->GetItemInfo()->iOption);		
		
		}

		
		// �尩 ����
		if(PtInRect(&m_EquipSlot[IT_GLOVE]->GetRect(), Pt) &&
					 m_ItemSlot[m_iSelectIndex]->GetItemInfo()->eType == IT_GLOVE )
		{
			swap(m_ItemSlot[m_iSelectIndex], m_EquipSlot[IT_GLOVE]);
			((CPlayer*)pPlayer)->SetPlusHP(m_EquipSlot[IT_GLOVE]->GetItemInfo()->iOption);		
			;
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

	// �����ϴ� �κ�
	if(CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON, 1))
	{
		if(PtInRect(&m_EquipSlot[IT_WEAPON]->GetRect(), Pt))
		{
			for(int i = 0; i < 10; ++i)
			{
				if(m_ItemSlot[i]->GetItemInfo()->eType == IT_EMPTY)
				{
					((CPlayer*)pPlayer)->SetMinusAttack(m_EquipSlot[IT_WEAPON]->GetItemInfo()->iOption);	
					swap(m_ItemSlot[i], m_EquipSlot[IT_WEAPON]);
				
					return 1;
				}
			}
		}	
		if(PtInRect(&m_EquipSlot[IT_ARMOR]->GetRect(), Pt))
		{
			for(int i = 0; i < 10; ++i)
			{
				if(m_ItemSlot[i]->GetItemInfo()->eType == IT_EMPTY)
				{
					((CPlayer*)pPlayer)->SetMinusDefence(m_EquipSlot[IT_ARMOR]->GetItemInfo()->iOption);	
					swap(m_ItemSlot[i], m_EquipSlot[IT_ARMOR]);
			
					return 1;
				}
			}
		}		
		
		if(PtInRect(&m_EquipSlot[IT_GLOVE]->GetRect(), Pt))
		{
			for(int i = 0; i < 10; ++i)
			{
				if(m_ItemSlot[i]->GetItemInfo()->eType == IT_EMPTY)
				{
					((CPlayer*)pPlayer)->SetMinusHP(m_EquipSlot[IT_GLOVE]->GetItemInfo()->iOption);	
					swap(m_ItemSlot[i], m_EquipSlot[IT_GLOVE]);
				
					return 1;
				}
			}
		}		

		// ���� �Ա�
		for(int j = 0; j < 10; ++j)
		{
			if(PtInRect(&m_ItemSlot[j]->GetRect(), Pt))
			{
				m_iSelectIndex = j;

				if(m_ItemSlot[m_iSelectIndex]->GetItemInfo()->eType == IT_FOOD)
				{
					if(((CPlayer*)pPlayer)->GetHP() >= ((CPlayer*)pPlayer)->GetMaxHP())
					{
						return 1;
					}

					((CPlayer*)pPlayer)->SetRecoveryHP(m_ItemSlot[m_iSelectIndex]->GetItemInfo()->iOption);		
					m_ItemSlot[m_iSelectIndex]->SetFoodMinus(1);
					return 1;
				}
			}
		}

	}
	
	return -1;
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

CItem*	CInvenBridge::CreateGlove(D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CGlove>::CreateItem(vPos);
	
	return pItem;
}

CItem*	CInvenBridge::CreateBelt(D3DXVECTOR3 vPos)
{
	CItem*	pItem = CItemFactory<CBelt>::CreateItem(vPos);
	
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
	m_EquipSlot[IT_GLOVE]->SetPos(685.f , 110.f);
}


bool CInvenBridge::EquipWeapon(void)
{
	return m_bWeapon;
}

bool CInvenBridge::EquipArmor(void)
{
	return m_bArmor;

}

vector<CItem*>* CInvenBridge::GetItemSlot(void)
{
	return &m_ItemSlot;
}