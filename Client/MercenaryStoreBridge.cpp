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
			(*iter)->Render();
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
	/*POINT	Pt;
		Pt.x = (long)GetMouse().x;
		Pt.y = (long)GetMouse().y;

	if(CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON, 1) && m_iSelectIndex >= 0)
	{
		for(size_t j =0; j<20; ++j)
		{
			if(PtInRect(&m_UnitSlot[j]->GetRect(), Pt))
			{
				swap(m_UnitSlot[m_iSelectIndex],m_UnitSlot[j]); 
			}			
		}

		m_bSelect = false;
		m_iSelectIndex = -1;

		return 1;
	}



	if(CKeyMgr::GetInstance()->StayKeyDown(VK_LBUTTON) && m_iSelectIndex >= 0 && m_bSelect)
	{
		m_UnitSlot[m_iSelectIndex]->SetPos(GetMouse());

		return 1;
		
	}	
			
	if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON) && !m_ItemSlot.empty() && m_bSelect == false)
	{
		for(size_t i =0 ; i < 10; ++i)
		{
			if(PtInRect(&m_UnitSlot[i]->GetRect(), Pt))
			{
				m_bSelect = true;
				m_iSelectIndex = i;

				return 1;
			}
		}
		
	}*/

	
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