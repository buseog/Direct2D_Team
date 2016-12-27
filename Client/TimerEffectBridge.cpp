#include "StdAfx.h"
#include "TimerEffectBridge.h"
#include "Effect.h"
#include "TimeMgr.h"

CTimerEffectBridge::CTimerEffectBridge(void)
{
}

CTimerEffectBridge::~CTimerEffectBridge(void)
{
}

HRESULT CTimerEffectBridge::Initialize(void)
{

	return S_OK;
}

void CTimerEffectBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);

	EffectTime();
}

void CTimerEffectBridge::Render(void)
{	
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey(), 
		m_wstrStateKey, (int)m_tFrame.fFrame);

	if(pTexture == NULL)
		return;

	float fX = (float)pTexture->tImgInfo.Width / 2.f;
	float fY = (float)pTexture->tImgInfo.Height;

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

void CTimerEffectBridge::Release(void)
{

}

void CTimerEffectBridge::WorldMatrix(INFO& rInfo)
{

	D3DXMATRIX	matTrans;
	if (m_wstrStateKey == L"Victory")
	{
		D3DXMatrixTranslation(&matTrans, 
			rInfo.vPos.x, 
			rInfo.vPos.y, 
			0.f);
	}
	else
	{
		D3DXMatrixTranslation(&matTrans, 
			rInfo.vPos.x + m_pObj->GetScroll().x, 
			rInfo.vPos.y + m_pObj->GetScroll().y + 20.f, 
			0.f);
	}

	rInfo.matWorld = matTrans;

}


void CTimerEffectBridge::EffectTime(void)
{
	if(m_fTime <= 0)
		m_pObj->SetDestroy(true);
	
	m_fTime -= CTimeMgr::GetInstance()->GetTime();

	m_tFrame.fFrame += m_tFrame.fCount * CTimeMgr::GetInstance()->GetTime();

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		if (m_wstrStateKey == L"Victory")
			return;

		m_tFrame.fFrame = 0;
	}


	return;
	
	
}