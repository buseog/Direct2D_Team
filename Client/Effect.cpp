#include "StdAfx.h"
#include "Effect.h"
#include "Bridge.h"

CEffect::CEffect(void)
{
}

CEffect::~CEffect(void)
{
	Release();
}

HRESULT CEffect::Initialize(void)
{
	m_wstrObjKey = L"Effect";
	m_fSpeed = 300.f;
	return S_OK;
}

void CEffect::Progress(void)
{
	m_pBridge->Progress(m_tInfo);
}

void CEffect::Render(void)
{
	m_pBridge->Render();
}

void CEffect::Release(void)
{
	::Safe_Delete(m_pBridge);
}

const RECT	CEffect::GetRect(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrObjKey, m_pBridge->GetStateKey(), 0);

	float fX = pTexture->tImgInfo.Width;
	float fY = pTexture->tImgInfo.Height;

	RECT rc  = {
		m_tInfo.vPos.x - fX / 2.f,
		m_tInfo.vPos.y - fY / 2.f,
		m_tInfo.vPos.x + fX / 2.f,
		m_tInfo.vPos.y + fY / 2.f
	};

	return rc;
}