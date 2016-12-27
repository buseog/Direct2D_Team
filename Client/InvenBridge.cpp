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
#include "MyButton.h"
#include "ButtonBridge.h"
#include "UIFactory.h"
#include "StoreButton.h"
#include "UImgr.h"
#include "Inventory.h"
#include "InvenBridge.h"

CInvenBridge::CInvenBridge(void)
: m_bSelect(false)
, m_bDrag(false)
, m_bWeapon(false)
, m_bArmor(false)
, m_bBelt(false)
, m_bPick(false)
, m_bMove(false)
, m_bTooltip(false)
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

	CItem*	pEquipGlove = CItemFactory<CEmptyItem>::CreateItem(685.f, 110.f);
	m_EquipSlot.push_back(pEquipGlove);  //장갑슬롯 빈아이템으로 애추기


	return S_OK;
}

void CInvenBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);

	AddItem(rInfo); // 인벤토리에 아이템 추가


	if (m_bSelect == false)
		SortItem(rInfo); // 인벤토리 아이템 칸에 맞게 들어가는 정렬

	for (int i = 0; i < 10; ++i)
	{
		m_ItemSlot[i]->Progress();
	}
	for(size_t i =0; i<m_vecButton.size(); ++i)
	{
		m_vecButton[i]->Progress();
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
	if(m_bTooltip&&!m_bDrag)
	{
		ShowTooltip();
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

		for(vector<CUi*>::iterator iter = m_vecButton.begin();
		iter != m_vecButton.end(); ++iter)
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

	if(CKeyMgr::GetInstance()->KeyDown('P')) // 무기생성
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

	if(CKeyMgr::GetInstance()->KeyDown('O')) // 갑옷생성
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


	if(CKeyMgr::GetInstance()->KeyDown('Y')) //장갑 생성
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


		// 무기 장착
		if(PtInRect(&m_EquipSlot[IT_WEAPON]->GetRect(), Pt) &&
			m_ItemSlot[m_iSelectIndex]->GetItemInfo()->eType == IT_WEAPON )
		{
			swap(m_ItemSlot[m_iSelectIndex], m_EquipSlot[IT_WEAPON]);
			((CPlayer*)pPlayer)->SetPlusAttack(m_EquipSlot[IT_WEAPON]->GetItemInfo()->iOption);		

		}

		// 방어구 장착
		if(PtInRect(&m_EquipSlot[IT_ARMOR]->GetRect(), Pt) &&
			m_ItemSlot[m_iSelectIndex]->GetItemInfo()->eType == IT_ARMOR )
		{
			swap(m_ItemSlot[m_iSelectIndex], m_EquipSlot[IT_ARMOR]);
			((CPlayer*)pPlayer)->SetPlusDefence(m_EquipSlot[IT_ARMOR]->GetItemInfo()->iOption);		

		}


		// 장갑 장착
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
		m_bDrag=true;
		m_ItemSlot[m_iSelectIndex]->SetPos(GetMouse());

		return 1;

	}
	else
	{
		m_bDrag=false;
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

	// 해제하는 부분
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

		// 물약 먹기
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



	//POINT	Pt;
	//Pt.x = (long)GetMouse().x;
	//Pt.y = (long)GetMouse().y;



	if(PtInRect(&m_pUi->GetRect(),Pt))
	{
		for(size_t j =0; j<10; ++j)
		{
			if(PtInRect(&m_ItemSlot[j]->GetRect(), Pt) && m_ItemSlot[j]->GetObjKey() != L"Empty")
			{
				m_bTooltip=true;
				if(!m_bPick)
					m_iIndex = j;
				if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON,4))
				{
					if(!m_bPick)//flase
						m_bPick=true;
					else
						m_bPick=false;
					break;
				}
				//m_bPick=false;
				break;
			}
			if(!m_bPick)
			{
				m_bTooltip=false;
			}
		}

	}
	if(m_bPick&&m_bTooltip)//툴팁 버튼 클릭
	{
		for(size_t i =0; i<m_vecButton.size(); ++i)
		{
			if(PtInRect(&m_vecButton[i]->GetRect(), Pt)&&CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON,4))
			{
				switch(m_vecButton[i]->GetIndexKey())
				{
				case 0://구매버튼
					{

						//BuyItem();

						break;
					}
				case 1://취소버튼
					{
						m_bPick=false;
						break;
					}
				}
			}
		}
	}


	if(PtInRect(&m_pUi->GetRect(),Pt))
	{
		const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);
		float fX = (float)(pTexture->tImgInfo.Width/2);
		float fY = (float)(pTexture->tImgInfo.Height/2);
		if(m_pUi->GetInfo()->vPos.x+fX >= Pt.x &&
			m_pUi->GetInfo()->vPos.x-fX <= Pt.x &&
			m_pUi->GetInfo()->vPos.y -fY <=Pt.y &&
			m_pUi->GetInfo()->vPos.y -fY+40 >=Pt.y )
		{ 
			//float tmpx = Pt.x;
			//float tmpy = Pt.y;
			if(!m_bMove)
			{
				m_bMove=true;
			}
			else
			{
				m_bMove=false;
			}
			if(CKeyMgr::GetInstance()->StayKeyDown(VK_LBUTTON))
			{
				m_pUi->SetPos(D3DXVECTOR3((float)Pt.x/*+fX-20*/,(float)Pt.y+fY-20,0.f));
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
void CInvenBridge::ShowTooltip()
{
	if(m_bDrag)
		return;
	D3DXMATRIX matTrans;
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"ToolTip");
	float TPosX =0.f;
	float TPosY = 0.f;
	/*if(m_bPick)
	{
		TPosX = m_ItemSlot[m_iIndex]->GetInfo()->vPos.x;
		TPosY = m_ItemSlot[m_iIndex]->GetInfo()->vPos.y;
	}
	else
	{*/
		TPosX = 	::GetMouse().x;
		TPosY = 	::GetMouse().y;
	/*}*/

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;
	D3DXMatrixTranslation(&matTrans,TPosX+fX,TPosY+fY,0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//툴팁배경


	if(m_vecButton.empty())
	{
		m_vecButton.push_back(CUIFactory<CStoreButton, CButtonBridge>::CreateUI(L"StoreButton",
			TPosX,TPosY, 0));	

		m_vecButton.push_back(CUIFactory<CStoreButton, CButtonBridge>::CreateUI(L"StoreButton",
			TPosX,TPosY, 1));
		for (size_t i = 0; i < m_vecButton.size(); ++i)
			m_vecButton[i]->SetSize(D3DXVECTOR3(90.f, 24.f, 0.f));
	}




	//아이템 초상화
	float PortraitPosX = TPosX+65; 
	float PortraitPosY = TPosY+85;
	pTexture = CTextureMgr::GetInstance()->GetTexture(m_ItemSlot[m_iIndex]->GetObjKey());
	D3DXMatrixTranslation(&matTrans,PortraitPosX,PortraitPosY,0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(pTexture->tImgInfo.Width / 2.f, pTexture->tImgInfo.Height / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//툴팁 내용 출력
	D3DXMatrixTranslation(&matTrans, PortraitPosX+100, PortraitPosY-30, 0.f);
	TCHAR m_szTooltip[MIN_STR] = L"";



	switch(m_ItemSlot[m_iIndex]->GetItemInfo()->eType)
	{
	case IT_WEAPON:
		{
			wsprintf(m_szTooltip, L"이름 : %s \n공격력 : %d\n무게 : %d \n가격 : %d 냥" ,
				m_ItemSlot[m_iIndex]->GetItemInfo()->wstrName.c_str(),
				m_ItemSlot[m_iIndex]->GetItemInfo()->iOption,
				m_ItemSlot[m_iIndex]->GetItemInfo()->iWeight,
				m_ItemSlot[m_iIndex]->GetItemInfo()->iPrice);
			break;
		}
	case IT_GLOVE:
	case IT_HELMET:
	case IT_BOOTS:
	case IT_BELT:
	case IT_ARMOR:
		{
			wsprintf(m_szTooltip, L"이름 : %s \n방어력 : %d\n무게 : %d \n가격 : %d 냥" ,
				m_ItemSlot[m_iIndex]->GetItemInfo()->wstrName.c_str(),
				m_ItemSlot[m_iIndex]->GetItemInfo()->iOption,
				m_ItemSlot[m_iIndex]->GetItemInfo()->iWeight,
				m_ItemSlot[m_iIndex]->GetItemInfo()->iPrice);
			break;
		}
	case IT_FOOD:
		{
			wsprintf(m_szTooltip, L"이름 : %s \n방어력 : %d\n무게 : %d \n가격 : %d 냥" ,
				m_ItemSlot[m_iIndex]->GetItemInfo()->wstrName.c_str(),
				m_ItemSlot[m_iIndex]->GetItemInfo()->iOption,
				m_ItemSlot[m_iIndex]->GetItemInfo()->iWeight,
				m_ItemSlot[m_iIndex]->GetItemInfo()->iPrice);
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

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i]->SetPos(D3DXVECTOR3(TPosX+115+(i*(m_vecButton[i]->GetInfo()->vSize.x+10)),TPosY+210,0.f));
		m_vecButton[i]->Render();
		D3DXMatrixTranslation(&matTrans,m_vecButton[i]->GetInfo()->vPos.x-10,m_vecButton[i]->GetInfo()->vPos.y-5,0.f);

		TCHAR m_szTooltip[MIN_STR] = L"";

		switch(m_vecButton[i]->GetIndexKey())
		{
		case 0:
			wsprintf(m_szTooltip, L"구 매");
			break;
		case 1:
			wsprintf(m_szTooltip, L"취 소");
			break;

		}
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
			m_szTooltip, 
			lstrlen(m_szTooltip), 
			NULL, NULL, 
			D3DCOLOR_ARGB(255, 255, 255, 0));

	}




}