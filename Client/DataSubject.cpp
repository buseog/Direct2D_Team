#include "StdAfx.h"
#include "DataSubject.h"

IMPLEMENT_SINGLETON(CDataSubject)

CDataSubject::CDataSubject(void)
{
}

CDataSubject::~CDataSubject(void)
{
	Release();
}
void CDataSubject::AddData(int iFlag, const UNITDATA* pData)
{
	if(pData)
	{
		map<int, const UNITDATA*>::iterator	iter = m_MapData.find(iFlag);

		m_MapData[iFlag] = pData;
		Notify();

		pData = NULL;
	}
}

void CDataSubject::RemoveData(int iFlag, const UNITDATA* pData)
{
	map<int, const UNITDATA*>::iterator	iter = m_MapData.find(iFlag);
	
	if(iter != m_MapData.end())
	{
		m_MapData.erase(iter);
	}

}

void CDataSubject::Release(void)
{
	m_MapData.clear();
}

const UNITDATA* CDataSubject::GetData(int iFlag)
{
	map<int, const UNITDATA*>::iterator iter = m_MapData.find(iFlag);

	if(iter == m_MapData.end())
		return NULL;

	return iter->second;
}
