#include "StdAfx.h"
#include "FieldBackBridge.h"

#include "ObjMgr.h"
#include "UiMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

#include "EnemyUnit.h"
#include "ObjFactory.h"
#include "Effect.h"
#include "StandEffectBridge.h"
#include "Player.h"
#include "TimeMgr.h"
#include "TimerEffectBridge.h"
#include "UIFactory.h"
#include "Portrait.h"
#include "PortraitBridge.h"
#include "Datasubject.h"
#include "UiObserver.h"

#include "Player.h"
#include "PlayerBridge.h"
#include "EnemyUnit.h"
#include "EnemyBridge.h"

#include "MainUi.h"
#include "MainUiBridge.h"
#include "Inventory.h"
#include "InvenBridge.h"
#include "Status.h"
#include "StatusBridge.h"
#include "BattleField.h"


CFieldBackBridge::CFieldBackBridge(void)
: m_bStage(false)
, m_fTime(-1.f)
, m_pPick(NULL)
{
	m_iX = 45;
	m_iY = 80;
	m_vSize = D3DXVECTOR3(2753.f, 1262.f, 0.f);
}

CFieldBackBridge::~CFieldBackBridge(void)
{
	Release();
}

HRESULT	CFieldBackBridge::Initialize(void)
{
	const CObj* m_pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_PLAYER);

	if (m_pPlayer == NULL)
	{
		LoadTile(L"../Data/FieldTile.dat");
		LoadBack(L"../Data/FieldObject.dat");

		InitPortrait();

		CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CObjFactory<CPlayer, CPlayerBridge>::CreateObj(L"Stand_1", 300.f, 300.f));
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"GoniSh", L"Walk_1", D3DXVECTOR3(500.f, 200.f, 0.f)));
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"DocuGawa", L"Walk_1", D3DXVECTOR3(200.f, 300.f, 0.f)));
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"BlueDragon", L"Walk_1", D3DXVECTOR3(600.f, 100.f, 0.f)));
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"HonGanji", L"Walk_1", D3DXVECTOR3(1200.f, 400.f, 0.f)));
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"KimYuSin", L"Walk_1", D3DXVECTOR3(1500.f, 700.f, 0.f)));
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"Waki", L"Walk_1", D3DXVECTOR3(900.f, 300.f, 0.f)));

		CUIMgr::GetInstance()->AddUI(UI_MAIN, CUIFactory<CMainUi,CMainUiBridge>::CreateUI(L"FieldMainUi",400.f,553.f));	
		CUIMgr::GetInstance()->AddUI(UI_INVEN, CUIFactory<CInventory,CInvenBridge>::CreateUI(L"Inventory", 580.f,250.f));
		CUIMgr::GetInstance()->AddUI(UI_STAT, CUIFactory<CStatus,CStatusBridge>::CreateUI(L"Status", 180.f, 250.f));

	}
	return S_OK;
}

void	CFieldBackBridge::Progress(INFO& rInfo)
{
	if(CKeyMgr::GetInstance()->KeyDown('5'))
	{
		const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_PLAYER);
		((CPlayer*)pPlayer)->SetDamage(50);
	}

	m_pObj->SetOriginScroll(m_pObj->GetScroll().x, m_pObj->GetScroll().y);
}

void	CFieldBackBridge::Render(void)
{
	D3DXMATRIX	matTrans;

	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);

	D3DXMatrixTranslation(&matTrans, 
		0 + m_pObj->GetScroll().x,
		0 + m_pObj->GetScroll().y,
		0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(TILECX / 2.f, TILECY / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	for (size_t i = 0; i < m_vecBack.size(); ++i)
	{ 
		pTexture = CTextureMgr::GetInstance()->GetTexture(L"Back", L"Object", m_vecBack[i]->iIndex);

		if (pTexture == NULL)
			return;

		D3DXMatrixTranslation(&matTrans, 
			m_vecBack[i]->vPos.x + m_pObj->GetScroll().x,
			m_vecBack[i]->vPos.y + m_pObj->GetScroll().y,
			0.f);

		float fX = pTexture->tImgInfo.Width / 2.f;
		float fY = pTexture->tImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
		CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
			NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	list<CObj*>* pvecUnit = CObjMgr::GetInstance()->GetObjList(SC_FIELD ,OBJ_UNIT);

	int iCount = 0;

	for (list<CObj*>::iterator iter = pvecUnit->begin(); iter != pvecUnit->end(); ++iter)
	{
		int iIndex = 10 + iCount;

		if (iIndex >= 20)
			break;

		m_vecPortrait[iCount]->GetBridge()->SetKey((*iter)->GetObjKey());
		CDataSubject::GetInstance()->AddData(iIndex,(*iter)->GetStat());
		((CUIObserver*)((CPortrait*)m_vecPortrait[iCount])->GetObserver())->SetIndex(iIndex);
		
		++iCount;
	}

	for (size_t i = 0; i < m_vecPortrait.size(); ++i)
	{
		m_vecPortrait[i]->Progress();
		m_vecPortrait[i]->Render();
	}

}

void	CFieldBackBridge::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();

	for_each(m_vecBack.begin(), m_vecBack.end(), DeleteObj());
	m_vecBack.clear();

	/*for_each(m_vecPortrait.begin(), m_vecPortrait.end(), DeleteObj());
	m_vecPortrait.clear();*/
	
}

int	CFieldBackBridge::Picking(void)
{
	if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON,5))
	{
		list<CObj*>* pMonster = CObjMgr::GetInstance()->GetObjList(SC_FIELD, OBJ_MONSTER);
		const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_PLAYER);
		
		POINT	Pt;
		Pt.x = (long)GetMouse().x - (long)m_pObj->GetScroll().x;
		Pt.y = (long)GetMouse().y - (long)m_pObj->GetScroll().y ;

		for (list<CObj*>::iterator iter = pMonster->begin(); iter != pMonster->end(); ++iter)
		{
			if(PtInRect(&(*iter)->GetRect(), Pt) &&
				(*iter)->GetInfo()->vPos.x > pPlayer->GetInfo()->vPos.x - 100 &&
				(*iter)->GetInfo()->vPos.x < pPlayer->GetInfo()->vPos.x + 100 &&
				(*iter)->GetInfo()->vPos.y > pPlayer->GetInfo()->vPos.y - 100 &&
				(*iter)->GetInfo()->vPos.y < pPlayer->GetInfo()->vPos.y + 100)
			{
				m_fTime = 4.f;
				CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, CObjFactory<CEffect, CTimerEffectBridge>::CreateObj(L"BattleWait", (*iter)->GetInfo()->vPos, m_fTime));
				CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, CObjFactory<CEffect, CTimerEffectBridge>::CreateObj(L"BattleWait", pPlayer->GetInfo()->vPos, m_fTime));
				
				(*iter)->SetOrder(OD_STAND);
				m_strMonsterKey=(*iter)->GetObjKey();
				((CPlayer*)pPlayer)->SetOrder(OD_STAND);
				m_bStage = true;
				m_pPick = *iter;

				return 1;	
			}

		}
	}	

	if (m_bStage)
	{
		BattleWait();		
	}

	if(m_bStage && m_fTime <= 0.f)		
	{
		list<CObj*>* pUnitList = CObjMgr::GetInstance()->GetObjList(SC_FIELD, OBJ_UNIT);

		CSceneMgr::GetInstance()->SetScene(SC_BATTLEFIELD);
		((CBattleField*)CSceneMgr::GetInstance()->GetScene(SC_BATTLEFIELD))->SetMonster(m_strMonsterKey);

		int iX = 0;
		int iY = 0;

		for (list<CObj*>::iterator iter = pUnitList->begin(); iter != pUnitList->end(); ++iter)
		{
			if (iX == 3)
			{
				iX = 0;
				++iY;
			}

			CObjMgr::GetInstance()->AddObject(OBJ_UNIT, (*iter));
			(*iter)->SetPos(D3DXVECTOR3(100 + (TILECX * iX), 100 + (TILECY * iY), 0.f));
			++iX;
		}
		m_bStage = false;
		m_pPick->SetDestroy(true);
		return 1;
	}

	return -1;
}

void	CFieldBackBridge::BattleWait(void)
{
	m_fTime -= CTimeMgr::GetInstance()->GetTime();
}



void	CFieldBackBridge::InitPortrait(void)
{
	float fCX = 72;
	float fCY = 26;

	int iCount = 0;

	float fYPos = 0;

	m_vecPortrait.reserve(10);

	for (int i = 0; i < 10; ++i)
	{
		fYPos = 100 + ((fCY + 15) * iCount);

		m_vecPortrait.push_back(CUIFactory<CPortrait, CPortraitBridge>::CreateUI(L"", fCX, fYPos));
		++iCount;
	}

}