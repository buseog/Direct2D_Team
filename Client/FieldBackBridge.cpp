#include "StdAfx.h"
#include "FieldBackBridge.h"
#include "EnemyUnit.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ObjFactory.h"
#include "Effect.h"
#include "StandEffectBridge.h"

CFieldBackBridge::CFieldBackBridge(void)
: m_bStage(false)
, m_dwTime(CTimeMgr::GetInstance()->GetTime())
{
}

CFieldBackBridge::~CFieldBackBridge(void)
{
	Release();
}

HRESULT	CFieldBackBridge::Initialize(void)
{

	return S_OK;
}

void	CFieldBackBridge::Progress(INFO& rInfo)
{

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


}

void	CFieldBackBridge::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();
}

int	CFieldBackBridge::Picking(void)
{
	if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON,5))
	{
		m_bStage = true;
		if(m_bStage)
		{
			const CObj*	pMonster = CObjMgr::GetInstance()->GetObj(OBJ_MONSTER);

			POINT	Pt;
			Pt.x = (long)GetMouse().x + ((CEnemyUnit*)pMonster)->GetScroll().x ;
			Pt.y = (long)GetMouse().y + ((CEnemyUnit*)pMonster)->GetScroll().y ;
			
				
			
			if(PtInRect(&((CEnemyUnit*)pMonster)->GetRect(),Pt))
			{
				CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"BattleWait", pMonster->GetInfo()->vPos));
				((CEnemyUnit*)pMonster)->SetSpeed(0.f);
				CSceneMgr::GetInstance()->SetScene(SC_BATTLEFIELD);
				return 1;	
		
			}
		}
	}
	return -1;
}

