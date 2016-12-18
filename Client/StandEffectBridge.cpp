#include "StdAfx.h"
#include "StandEffectBridge.h"

CStandEffectBridge::CStandEffectBridge(void)
{
}

CStandEffectBridge::~CStandEffectBridge(void)
{
}

HRESULT CStandEffectBridge::Initialize(void)
{

	return S_OK;
}

void CStandEffectBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	Frame();
}

void CStandEffectBridge::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey(), 
		m_wstrStateKey, (int)m_tFrame.fFrame);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->Render_End();
	CDevice::GetInstance()->Render_Begin();

	CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	CDevice::GetInstance()->Render_End();
	CDevice::GetInstance()->Render_Begin();
}

void CStandEffectBridge::Release(void)
{
	
}

void CStandEffectBridge::WorldMatrix(INFO& rInfo)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x + m_pObj->GetScroll().x, 
		rInfo.vPos.y + m_pObj->GetScroll().y + 30, 
		0.f);

	rInfo.matWorld = matTrans;
}

void	CStandEffectBridge::Frame(void)
{
	m_tFrame.fFrame += m_tFrame.fCount * CTimeMgr::GetInstance()->GetTime() * 1.5f;

	if(m_tFrame.fFrame > m_tFrame.fMax)
		m_pObj->SetDestroy(true);
}