#include "StdAfx.h"
#include "FieldBackBridge.h"
#include "EnemyUnit.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ObjFactory.h"
#include "Effect.h"
#include "StandEffectBridge.h"
#include "Player.h"
#include "TimeMgr.h"
#include "TimerEffectBridge.h"

CFieldBackBridge::CFieldBackBridge(void)
: m_bStage(false)
, m_fTime(-1.f)
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
	LoadTile(L"../Data/FieldTile2.dat");
	LoadBack(L"../Data/1.dat");

	return S_OK;
}

void	CFieldBackBridge::Progress(INFO& rInfo)
{
	if(CKeyMgr::GetInstance()->KeyDown('5'))
	{
		const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_PLAYER);
		((CPlayer*)pPlayer)->SetDamage(50);
	}
		
	if (m_bStage)
	{
		BattleWait();		
	}

	if(m_fTime <= 0)
		m_bStage = false;
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

	//for (size_t i = 0; i < m_vecTile.size(); ++i)
	//{ 
	//	pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", m_vecTile[i]->byOption);

	//	D3DXMatrixTranslation(&matTrans, 
	//		m_vecTile[i]->vPos.x + m_pObj->GetScroll().x,
	//		m_vecTile[i]->vPos.y + m_pObj->GetScroll().y,
	//		0.f);

	//	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	//	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
	//		NULL, &D3DXVECTOR3(TILECX / 2.f, TILECY / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//}


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


}

void	CFieldBackBridge::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();

	for_each(m_vecBack.begin(), m_vecBack.end(), DeleteObj());
	m_vecBack.clear();
	
}

int	CFieldBackBridge::Picking(void)
{
	if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON,5))
	{
		const CObj*	pMonster = CObjMgr::GetInstance()->GetObj(OBJ_MONSTER);
		
		POINT	Pt;
		Pt.x = (long)GetMouse().x - (long)m_pObj->GetScroll().x;
		Pt.y = (long)GetMouse().y - (long)m_pObj->GetScroll().y ;

		if(PtInRect(&((CEnemyUnit*)pMonster)->GetRect(),Pt))
		{
			
			CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, CObjFactory<CEffect, CTimerEffectBridge>::CreateObj(L"BattleWait", pMonster->GetInfo()->vPos, m_fTime));
			m_fTime = 3.f;
			((CEnemyUnit*)pMonster)->SetOrder(OD_STAND);
			m_bStage = true;

			if(!m_bStage)		
				CSceneMgr::GetInstance()->SetScene(SC_BATTLEFIELD);
		

			return 1;	
		}
	}
	


	
	return -1;
}

void	CFieldBackBridge::BattleWait(void)
{
	if(m_fTime > 0)
		m_fTime -= CTimeMgr::GetInstance()->GetTime();
	
	
}