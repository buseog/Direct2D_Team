#include "StdAfx.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "AStar.h"
#include "EnemyBridge.h"


CEnemyBridge::CEnemyBridge(void)
{
}

CEnemyBridge::~CEnemyBridge(void)
{
	Release();
}

HRESULT	CEnemyBridge::Initialize(void)
{
	
	m_wstrStateKey = L"Walk_1";
	
	return S_OK;
}

void	CEnemyBridge::Progress(INFO& rInfo)
{

	WorldMatrix(rInfo);
	Frame();
	

	switch (m_pObj->GetOrder())
	{
		case OD_STAND:
			Stop(rInfo);
			break;

		case OD_PATROL:
			Patrol(rInfo);
			break;
	}
	
	
}

void	CEnemyBridge::Render(void)
{

	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey(), 
	m_wstrStateKey, (int)m_tFrame.fFrame);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CEnemyBridge::Release(void)
{

}

void CEnemyBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matScale, matTrans;

	// 캐릭터 좌우 스케일링 계산
	if (rInfo.vDir.x < 0)
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	}
	else
	{
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
	}

	// 캐릭터 y각도에 따라서 각도 전환
	if (rInfo.vDir.y >= 0.75f)
		m_wstrStateKey = L"Walk_5";

	else if (rInfo.vDir.y >= 0.25f)
		m_wstrStateKey = L"Walk_1";

	else if (rInfo.vDir.y >= -0.25f)
		m_wstrStateKey = L"Walk_2";

	else if (rInfo.vDir.y >= -0.75f)
		m_wstrStateKey = L"Walk_3";

	else
		m_wstrStateKey = L"Walk_4";



	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x + m_pObj->GetScroll().x, 
		rInfo.vPos.y + m_pObj->GetScroll().y, 
		0.f);

	rInfo.matWorld = matScale * matTrans;
}

void	CEnemyBridge::Patrol(INFO& rInfo)
{
	

	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	
	float	fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	// 캐릭터 y각도에 따라서 각도 전환
	if (rInfo.vDir.y >= 0.75f)
		m_wstrStateKey = L"Walk_5";

	else if (rInfo.vDir.y >= 0.25f)
		m_wstrStateKey = L"Walk_1";

	else if (rInfo.vDir.y >= -0.25f)
		m_wstrStateKey = L"Walk_2";

	else if (rInfo.vDir.y >= -0.75f)
		m_wstrStateKey = L"Walk_3";

	else
		m_wstrStateKey = L"Walk_4";

	if(fDistance > 10.f)
	{
		rInfo.vPos += rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();
	}
	else
	{
		D3DXVECTOR3 vSwap = m_pObj->GetTargetPoint();
		m_pObj->SetTargetPoint(m_pObj->GetOriginPos());
		m_pObj->SetOriginPos(vSwap);
	}
}

void CEnemyBridge::Stop(INFO &rInfo)
{
		// 캐릭터 y각도에 따라서 각도 전환
	if (rInfo.vDir.y >= 0.75f)
		m_wstrStateKey = L"Stand_5";

	else if (rInfo.vDir.y >= 0.25f)
		m_wstrStateKey = L"Stand_1";

	else if (rInfo.vDir.y >= -0.25f)
		m_wstrStateKey = L"Stand_2";

	else if (rInfo.vDir.y >= -0.75f)
		m_wstrStateKey = L"Stand_3";

	else
		m_wstrStateKey = L"Stand_4";

}