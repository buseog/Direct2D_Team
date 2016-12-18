#include "StdAfx.h"
#include "MercenaryDisplayBridge.h"
#include "UIMgr.h"
#include "Ui.h"

#include "KeyMgr.h"

#include "Unit.h"
#include "AllyUnit.h"
#include "EnemyUnit.h"
#include "EmptyUnit.h"
#include "UnitFactory.h"

#define MAX_UNIT 8

CMercenaryDisplayBridge::CMercenaryDisplayBridge(void)
{
}

CMercenaryDisplayBridge::~CMercenaryDisplayBridge(void)
{
	Release();
}


HRESULT CMercenaryDisplayBridge::Initialize(void)
{
	for(int i =0; i<MAX_UNIT; ++i)
	{
		m_UnitSlot.push_back(CreateEmptyUnit(m_tInfo.vPos));
	}
	LoadData();
	

	return S_OK;
}

void CMercenaryDisplayBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	

	//if (m_bSelect == false)
		SortItem(rInfo); // 인벤토리 아이템 칸에 맞게 들어가는 정렬

	for (int i = 0; i < MAX_UNIT; ++i)
	{
		m_UnitSlot[i]->Progress();
	}
	
}	

void CMercenaryDisplayBridge::Render(void)
{
	
	/*const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);
	

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));*/

	
	for(vector<CUnit*>::iterator iter = m_UnitSlot.begin();
			iter != m_UnitSlot.end(); ++iter)
		{
			(*iter)->Render();
		}
	
}

void CMercenaryDisplayBridge::Release(void)
{
	for(vector<CUnit*>::iterator iter = m_UnitSlot.begin();
			iter != m_UnitSlot.end(); ++iter)
		{
			::Safe_Delete(*iter);
			
		}
}

void	CMercenaryDisplayBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

void CMercenaryDisplayBridge::AddItem(INFO& rInfo)///수정 필요 안씀!
{


}

int CMercenaryDisplayBridge::Picking(void) ///툴팁기능 추가해야함
{
	
	return -1;
}



void CMercenaryDisplayBridge::LoadData(void)
{
	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;

	hFile = CreateFile(L"../Data/TestUnit.dat",
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


		for(size_t i =0; i < MAX_UNIT; ++i)
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
						m_UnitSlot[i]->SetObjKey(L"TestUnit2");
						break;
					}
				case UNIT_ENEMY:
					{
						m_UnitSlot[i] = CreateUnitEnemy(pUnitData,D3DXVECTOR3(0.f,0.f,0.f));
						m_UnitSlot[i]->SetObjKey(L"TestUnit2");
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
void CMercenaryDisplayBridge::SortItem(INFO& rInfo)
{

	
		for(size_t j = 0; j< MAX_UNIT; ++j)
		{	
			size_t iIndex = j;
			if(iIndex >= m_UnitSlot.size())
			{
				break;
			}
			if (iIndex == m_iSelectIndex)
				break;
		
			m_UnitSlot[iIndex]->SetPos((rInfo.vPos.x+40) ,
										   (rInfo.vPos.y - 150)+ (j * 30));
		}
	

}


CUnit* CMercenaryDisplayBridge::CreateUnitAlly(UNITDATA* _pUnit,D3DXVECTOR3 vPos)
{
	CUnit*	pUnit = CUnitFactory<CAllyUnit>::CreateUnit(_pUnit,vPos);
	
	return pUnit;
}

CUnit* CMercenaryDisplayBridge::CreateUnitEnemy(UNITDATA* _pUnit,D3DXVECTOR3 vPos)
{
	CUnit*	pUnit = CUnitFactory<CEnemyUnit>::CreateUnit(_pUnit,vPos);
	
	return pUnit;
}

CUnit*	CMercenaryDisplayBridge::CreateEmptyUnit(D3DXVECTOR3 vPos)
{
	CUnit*	pUnit = CUnitFactory<CEmptyUnit>::CreateUnit(vPos);
	
	return pUnit;
}