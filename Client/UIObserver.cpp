#include "StdAfx.h"
#include "UIObserver.h"
#include "DataSubject.h"

CUIObserver::CUIObserver(void)
{
	ZeroMemory(&m_tData, sizeof(UNITDATA));
}

CUIObserver::~CUIObserver(void)
{
}

void CUIObserver::Update(int iFlag, void* pData)
{
	list<void*>*	pDataList = CDataSubject::GetInstance()->GetDataList(iFlag);

	if(pDataList == NULL)
		return;

	list<void*>::iterator	iter = find(pDataList->begin(), pDataList->end(), pData);

	m_tData = *((UNITDATA*)(*iter));
}

const UNITDATA* CUIObserver::GetData(void)
{
	return &m_tData;
}