#include "StdAfx.h"
#include "PlayerBridge.h"
#include "Obj.h"
#include "AStar.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"

CPlayerBridge::CPlayerBridge(void)
{
	Release();
}
	
CPlayerBridge::~CPlayerBridge(void)
{
}

HRESULT CPlayerBridge::Initialize(void)
{
	//m_wstrStateKey = L"Walk_1";
	Frame();

	return S_OK;
}

void CPlayerBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
}

void CPlayerBridge::Render(void)
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

void CPlayerBridge::Release(void)
{
	
}

void	CPlayerBridge::WorldMatrix(INFO& rInfo)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x + m_pObj->GetScroll().x, 
		rInfo.vPos.y + m_pObj->GetScroll().y, 
		0.f);

	rInfo.matWorld = matTrans;
}

void	CPlayerBridge::SetAstar(D3DXVECTOR3 vMouse)
{
	m_vecBestList.clear();
	CAStar::GetInstance()->StartPos(m_pObj->GetInfo()->vPos, vMouse, &m_vecBestList);
}

void	CPlayerBridge::KeyInput(INFO& rInfo)
{
	if (CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON))
	{
		D3DXVECTOR3 vMouse = ::GetMouse();
		vMouse += m_pObj->GetScroll();
		SetAstar(vMouse);

	}
}