#include "StdAfx.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "AStar.h"
#include "EnemyBridge.h"

CEnemyBridge::CEnemyBridge(void)
: m_bArrive(false)
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
	Move(rInfo);
	Frame();
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

void	CEnemyBridge::Move(INFO& rInfo)
{
	
	m_vOriginPoint = D3DXVECTOR3(400.f, 300.f, 0.f); 
	m_vTargetPoint = D3DXVECTOR3(500.f, 200.f, 0.f);
	
	if(m_bArrive == false)
	{
		rInfo.vDir = m_vTargetPoint - rInfo.vPos;
		float	fDistance = D3DXVec3Length(&rInfo.vDir);
		D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

			if(fDistance > 10.f)
			{
				rInfo.vPos += rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();
				
				if(rInfo.vPos == m_vTargetPoint)
				{
					m_bArrive = true;
					
				}
			}			
	}

	else if(m_bArrive == true)
	{
		rInfo.vDir = m_vOriginPoint - rInfo.vPos;
		float fDistance = D3DXVec3Length(&rInfo.vDir);
		D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

			if(fDistance > 10.f)
			{
				rInfo.vPos += rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();
				
				if(rInfo.vPos == m_vOriginPoint)
						m_bArrive = false;
			}		
	}
	



}