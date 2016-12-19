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
#include "MyButton.h"
#include "ButtonBridge.h"
#include "UIFactory.h"
#include "StoreButton.h"
#include "UImgr.h"
#include "Inventory.h"
#include "InvenBridge.h"
//#include "Bridge.h"


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

	//AddItem(rInfo); // 인벤토리에 아이템 추가

	if (m_bSelect == false)
		SortItem(rInfo); // 인벤토리 아이템 칸에 맞게 들어가는 정렬

	for (int i = 0; i < 20; ++i)
	{
		m_ItemSlot[i]->Progress();
	}
	for(size_t i =0; i<m_vecButton.size(); ++i)
	{
		m_vecButton[i]->Progress();
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
	if(m_bTooltip)
	{
		ShowTooltip();
	}

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 600.f, 200.f, 0.f);
	TCHAR m_szTooltip[MIN_STR];
	wsprintf(m_szTooltip,L"Tooltip : %d ,index : %d\nSelect : %d , move : %d",(int)m_bTooltip,m_iIndex,(int)m_bPick,(int)m_bMove);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szTooltip, 
		lstrlen(m_szTooltip), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 0));

}

void CBasicStoreBridge::Release(void)
{
	for(vector<CItem*>::iterator iter = m_ItemSlot.begin();
		iter != m_ItemSlot.end(); ++iter)
	{
		::Safe_Delete(*iter);

	}
	for(vector<CUi*>::iterator iter = m_vecButton.begin();
		iter != m_vecButton.end(); ++iter)
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



	if(PtInRect(&m_pUi->GetRect(),Pt))
	{
		for(size_t j =0; j<20; ++j)
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
						BuyItem();
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

void CBasicStoreBridge::ShowTooltip(void)
{

	D3DXMATRIX matTrans;
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"ToolTip");
	float TPosX =0.f;
	float TPosY = 0.f;
	if(m_bPick)
	{
		TPosX = m_ItemSlot[m_iIndex]->GetInfo()->vPos.x;
		TPosY = m_ItemSlot[m_iIndex]->GetInfo()->vPos.y;
	}
	else
	{
		TPosX = 	::GetMouse().x;
		TPosY = 	::GetMouse().y;
	}

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

void CBasicStoreBridge::BuyItem(void)
{
	CUi* pUi = CUIMgr::GetInstance()->GetUi(SC_FILED,UI_INVEN);
	vector<CItem*>* pInven  =  ((CInvenBridge*)pUi->GetBridge())->GetItemSlot();
	for(size_t i =0; i < (*pInven).size(); ++i)
	{

		if((*pInven)[i]->GetObjKey()==L"Empty")
		{
			CItem*	pTemp = (*pInven)[i];

			ITEM*			pItemData = new ITEM;
			pItemData->eType = m_ItemSlot[m_iIndex]->GetItemInfo()->eType;
			pItemData->iCount = m_ItemSlot[m_iIndex]->GetItemInfo()->iCount;
			pItemData->iOption = m_ItemSlot[m_iIndex]->GetItemInfo()->iOption;
			pItemData->iPrice = m_ItemSlot[m_iIndex]->GetItemInfo()->iPrice;
			pItemData->iWeight = m_ItemSlot[m_iIndex]->GetItemInfo()->iWeight;
			pItemData->wstrName = m_ItemSlot[m_iIndex]->GetItemInfo()->wstrName;

			/*pItemData=*/
			//m_ItemSlot[m_iIndex]->GetItemInfo()->eType
			switch(m_ItemSlot[m_iIndex]->GetItemInfo()->eType)
			{
			case IT_WEAPON:
				{
					(*pInven)[i] = CreateWeapon(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
					break;
				}
			case IT_ARMOR:
				{
					(*pInven)[i] = CreateArmor(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
					break;
				}
			case IT_GLOVE:
				{
					(*pInven)[i] = CreateGlove(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
					break;
				}
			case IT_HELMET:
				{
					(*pInven)[i] = CreateHelmet(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
					break;
				}
			case IT_BOOTS:
				{
					(*pInven)[i] = CreateBoots(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
					break;
				}
			case IT_BELT:
				{
					(*pInven)[i] = CreateBelt(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
					break;
				}
			case IT_FOOD:
				{
					(*pInven)[i] = CreateFood(pItemData,D3DXVECTOR3(0.f,0.f,0.f));
					break;
				}

			}

			::Safe_Delete(pTemp);

			::Safe_Delete(pItemData);
			break;
		}
	}
}