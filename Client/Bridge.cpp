#include "StdAfx.h"
#include "Bridge.h"
#include "TextureMgr.h"
#include "Obj.h"
#include "Ui.h"

CBridge::CBridge(void)
: m_pObj(NULL)
, m_pUi(NULL)
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
		m_tFrame.fFrame = 0;
}