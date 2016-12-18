#include "StdAfx.h"
#include "UIObserver.h"
#include "DataSubject.h"

CUIObserver::CUIObserver(void)
:m_iIndex(-1)
{
	ZeroMemory(&m_tData, sizeof(UNITDATA));
}

CUIObserver::~CUIObserver(void)
{
}

void CUIObserver::Update(void)
{
	if (m_iIndex < 0)
		return;

	const UNITDATA* pData = CDataSubject::GetInstance()->GetData(m_iIndex);

	if(pData == NULL)
		return;

	m_tData = *pData;
}

const UNITDATA* CUIObserver::GetData(void)
{
	return &m_tData;
}

void	CUIObserver::SetIndex(int iIndex)
{
	m_iIndex = iIndex;
}