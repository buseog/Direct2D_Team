#include "StdAfx.h"
#include "BasicStoreBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "Item.h"
#include "ItemFactory.h"
#include "KeyMgr.h"
#include "Weapon.h"
#include "Armor.h"
#include "Food.h"
#include "EmptyItem.h"

CBasicStoreBridge::CBasicStoreBridge(void)
{
}

CBasicStoreBridge::~CBasicStoreBridge(void)
{
	Release();
}


HRESULT CBasicStoreBridge::Initialize(void)
{

	//m_wstrStateKey = L"Inventory";

	for(int i =0; i<20; ++i)
	{
		m_ItemSlot.push_back(CreateEmpty(m_tInfo.vPos));
	}
	LoadData();

	return S_OK;
}

void CBasicStoreBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);

	AddItem(rInfo); // 인벤토리에 아이템 추가
	

	if (m_bSelect == false)
		SortItem(rInfo); // 인벤토리 아이템 칸에 맞게 들어가는 정렬

	for (int i = 0; i < 20; ++i)
	{
		m_ItemSlot[i]->Progress();
	}
	
}	

void CBasicStoreBridge::Render(void)
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
	
}

void CBasicStoreBridge::Release(void)
{
	for(vector<CItem*>::iterator iter = m_ItemSlot.begin();
			iter != m_ItemSlot.end(); ++iter)
		{
			::Safe_Delete(*iter);
			
		}
}

void	CBasicStoreBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

void CBasicStoreBridge::AddItem(INFO& rInfo)///수정 필요 안씀!
{


}

int CBasicStoreBridge::Picking(void) ///툴팁기능 추가해야함
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



void CBasicStoreBridge::LoadData(void)
{
	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;

	hFile = CreateFile(L"../Data/TestItem2.dat",
	//hFile = CreateFile(L"../Data/DrugStore.dat",
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);


	while(true)
	{
		ITEM*			pItemData = new ITEM;
		ReadFile(hFile, pItemData, sizeof(ITEM), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pItemData);
			break;
		}


		for(size_t i =0; i < 20; ++i)
		{
			if(m_ItemSlot[i]->GetObjKey() == L"Empty")
			{
				CItem*	pTemp = m_ItemSlot[i]; 

				switch(pItemData->eType)
				{
				case IT_WEAPON:
					{
						m_ItemSlot[i] = CreateWeapon(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
						break;
					}
				case IT_ARMOR:
					{
						m_ItemSlot[i] = CreateArmor(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
						break;
					}
				case IT_GLOVE:
					{
						m_ItemSlot[i] = CreateGlove(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
						break;
					}
				case IT_HELMET:
					{
						m_ItemSlot[i] = CreateHelmet(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
						break;
					}
				case IT_BOOTS:
					{
						m_ItemSlot[i] = CreateBoots(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
						break;
					}
				case IT_BELT:
					{
						m_ItemSlot[i] = CreateBelt(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
						break;
					}
				case IT_FOOD:
					{
						m_ItemSlot[i] = CreateFood(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
						break;
					}
				}

				::Safe_Delete(pTemp);
				break;
			}
		}

		::Safe_Delete(pItemData);

	}

	CloseHandle(hFile);
}

