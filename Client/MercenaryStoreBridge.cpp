#include "StdAfx.h"
#include "MercenaryStoreBridge.h"
#include "UIMgr.h"
#include "Ui.h"

#include "KeyMgr.h"

#include "Unit.h"

CMercenaryStoreBridge::CMercenaryStoreBridge(void)
{
}

CMercenaryStoreBridge::~CMercenaryStoreBridge(void)
{
	Release();
}


HRESULT CMercenaryStoreBridge::Initialize(void)
{

	//m_wstrStateKey = L"Inventory";

	for(int i =0; i<20; ++i)
	{
		m_UnitSlot.push_back(CreateEmptyUnit(m_tInfo.vPos));
	}
	LoadData();

	return S_OK;
}

void CMercenaryStoreBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	

	if (m_bSelect == false)
		SortItem(rInfo); // 인벤토리 아이템 칸에 맞게 들어가는 정렬

	for (int i = 0; i < 20; ++i)
	{
		m_UnitSlot[i]->Progress();
	}
	
}	

void CMercenaryStoreBridge::Render(void)
{
	
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);
	

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	
	for(vector<CUnit*>::iterator iter = m_UnitSlot.begin();
			iter != m_UnitSlot.end(); ++iter)
		{
			/*(*iter)->Render();*/
			const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture((*iter)->GetObjKey());

			if(pTexture == NULL)
				return;

			float fX = pTexture->tImgInfo.Width  / 2.f;
			float fY = pTexture->tImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&(*iter)->GetInfo()->matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
				NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	
}

void CMercenaryStoreBridge::Release(void)
{
	for(vector<CUnit*>::iterator iter = m_UnitSlot.begin();
			iter != m_UnitSlot.end(); ++iter)
		{
			::Safe_Delete(*iter);
			
		}
}

void	CMercenaryStoreBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

void CMercenaryStoreBridge::AddItem(INFO& rInfo)///수정 필요 안씀!
{


}

int CMercenaryStoreBridge::Picking(void) ///툴팁기능 추가해야함
{
	//POINT	Pt;
	//Pt.x = (long)GetMouse().x;
	//Pt.y = (long)GetMouse().y;



	//if(PtInRect(&m_pUi->GetRect(),Pt))
	//{
	//	for(size_t j =0; j<20; ++j)
	//	{
	//		if(PtInRect(&m_ItemSlot[j]->GetRect(), Pt) && m_ItemSlot[j]->GetObjKey() != L"Empty")
	//		{
	//			m_bTooltip=true;
	//			if(!m_bPick)
	//				m_iIndex = j;
	//			if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON,4))
	//			{
	//				if(!m_bPick)//flase
	//					m_bPick=true;
	//				else
	//					m_bPick=false;
	//				break;
	//			}
	//			//m_bPick=false;
	//			break;
	//		}
	//		if(!m_bPick)
	//		{
	//			m_bTooltip=false;
	//		}
	//	}

	//}
	//if(m_bPick&&m_bTooltip)//툴팁 버튼 클릭
	//{
	//	for(size_t i =0; i<m_vecButton.size(); ++i)
	//	{
	//		if(PtInRect(&m_vecButton[i]->GetRect(), Pt)&&CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON,4))
	//		{
	//			switch(m_vecButton[i]->GetIndexKey())
	//			{
	//			case 0://구매버튼
	//				{

	//					BuyItem();

	//				break;
	//				}
	//			case 1://취소버튼
	//				{
	//					m_bPick=false;
	//				break;
	//				}
	//			}
	//		}
	//	}
	//}

	//
	//if(PtInRect(&m_pUi->GetRect(),Pt))
	//{
	//	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);
	//	float fX = (float)(pTexture->tImgInfo.Width/2);
	//	float fY = (float)(pTexture->tImgInfo.Height/2);
	//	if(m_pUi->GetInfo()->vPos.x+fX >= Pt.x &&
	//		m_pUi->GetInfo()->vPos.x-fX <= Pt.x &&
	//		m_pUi->GetInfo()->vPos.y -fY <=Pt.y &&
	//		m_pUi->GetInfo()->vPos.y -fY+40 >=Pt.y )
	//	{ 
	//		//float tmpx = Pt.x;
	//		//float tmpy = Pt.y;
	//		if(!m_bMove)
	//		{
	//			m_bMove=true;
	//		}
	//		else
	//		{
	//			m_bMove=false;
	//		}
	//		if(CKeyMgr::GetInstance()->StayKeyDown(VK_LBUTTON))
	//		{
	//			m_pUi->SetPos(D3DXVECTOR3((float)Pt.x/*+fX-20*/,(float)Pt.y+fY-20,0.f));
	//		}
	//		
	//	}
	//}
	//
	return -1;
}



void CMercenaryStoreBridge::LoadData(void)
{
	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;

	hFile = CreateFile(L"../Data/TestUnit.dat",
	//hFile = CreateFile(L"../Data/DrugStore.dat",
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);


	while(true)
	{
		UNITDATA*			pUnitData = new UNITDATA;
		ReadFile(hFile, pUnitData, sizeof(UNITDATA), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pUnitData);
			break;
		}


		for(size_t i =0; i < 20; ++i)
		{
			if(m_UnitSlot[i]->GetObjKey() == L"Empty")
			{
				CUnit*	pTemp = m_UnitSlot[i]; 

				switch(pUnitData->tDetail.UnitType)
				{
				case UNIT_PLAYER:
					{
						ERR_MSG(L"Bad UnitData!");
						break;
					}
				case UNIT_ALLY:
					{
						m_UnitSlot[i] = CreateUnitAlly(pUnitData,D3DXVECTOR3(0.f,0.f,0.f));
						break;
					}
				case UNIT_ENEMY:
					{
						m_UnitSlot[i] = CreateUnitEnemy(pUnitData,D3DXVECTOR3(0.f,0.f,0.f));
						break;
					}
				}

				::Safe_Delete(pTemp);
				break;
			}
		}

		::Safe_Delete(pUnitData);

	}

	CloseHandle(hFile);
}
void CMercenaryStoreBridge::SortItem(INFO& rInfo)
{

	for(size_t i = 0; i < 4; ++i)
	{
		for(size_t j = 0; j< 5; ++j)
		{	
			size_t iIndex = i * 5 + j;
			if(iIndex >= m_UnitSlot.size())
			{
				break;
			}
			if (iIndex == m_iSelectIndex)
				break;
		
			m_UnitSlot[iIndex]->SetPos((rInfo.vPos.x - 130) + (j * 65),
										   (rInfo.vPos.y - 50) + (i * 65));
		}
	}

}
void CMercenaryStoreBridge::ShowTooltip(void)
{
}
void CMercenaryStoreBridge::BuyItem(void)
{
}