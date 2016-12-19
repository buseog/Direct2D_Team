#include "StdAfx.h"
#include "Bridge.h"
#include "TextureMgr.h"
#include "Obj.h"
#include "Ui.h"

CBridge::CBridge(void)
: m_pObj(NULL)
, m_pUi(NULL)
, m_fTime(-1)
, m_wstrStateKey(L"")
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CBridge::CBridge(CObj* pObj)
: m_pObj(pObj)
, m_wstrStateKey(L"")
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CBridge::CBridge(CUi*	pUi)
:	m_pUi(pUi)
,   m_wstrStateKey(L"")
{

}

CBridge::~CBridge(void)
{
}
void CBridge::SetObj(CObj* pObj)
{
	m_pObj = pObj;
}

void CBridge::SetUI(CUi*	pUi)
{
	m_pUi  = pUi;
}

void CBridge::SetFrame(const wstring& wstrStateKey)
{
	m_wstrStateKey = wstrStateKey;
	m_tFrame.fFrame = 0.f;
	m_tFrame.fCount = (float)CTextureMgr::GetInstance()->GetImgCount(m_pObj->GetObjKey(), wstrStateKey);
	m_tFrame.fMax = m_tFrame.fCount;

}
void CBridge::SetKey(const wstring& wstrStateKey)
{
	m_wstrStateKey = wstrStateKey;
}

void	CBridge::Frame(void)
{
	m_tFrame.fFrame += m_tFrame.fCount * CTimeMgr::GetInstance()->GetTime();

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		if (m_pObj != NULL && m_pObj->GetOrder() == OD_DIE)
			m_pObj->SetDestroy(true);
		else
			m_tFrame.fFrame = 0;
	}
}

void	CBridge::SetObjSize(void)
{
	if (m_pObj->GetObjKey() != L"")
	{
		const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey(), m_wstrStateKey, 0);

		if (pTexture == NULL)
			return;

		float fX = pTexture->tImgInfo.Width / 5.f;
		float fY = pTexture->tImgInfo.Height / 5.f;

		m_pObj->SetSize(D3DXVECTOR3(fX, fY, 0.f));
	}
}

void	CBridge::SetUiSize(void)
{
	if (m_pUi->GetObjKey() == L"")
	{
		const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey, m_wstrStateKey, 0);

		if (pTexture == NULL)
			return;

		float fX = pTexture->tImgInfo.Width / 2.f;
		float fY = pTexture->tImgInfo.Height / 2.f;

		m_pUi->SetSize(D3DXVECTOR3(fX, fY, 0.f));

		return;
	}
	const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(m_pUi->GetObjKey(), m_wstrStateKey, 0);

		if (pTexture == NULL)
			return;

		float fX = pTexture->tImgInfo.Width / 2.f;
		float fY = pTexture->tImgInfo.Height / 2.f;

		m_pUi->SetSize(D3DXVECTOR3(fX, fY, 0.f));
}

int		CBridge::Picking(void)
{
	return -1;
}

const	wstring&	CBridge::GetStateKey(void)
{
	return m_wstrStateKey;
}

void CBridge::SetTime(float fTime)
{
	m_fTime = fTime;
}