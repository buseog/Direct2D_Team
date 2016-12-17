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
void CDataSubject::AddData(int iFlag, void* pData)
{
	if(pData)
	{
		map<int, list<void*>>::iterator	iter = m_MapData.find(iFlag);

		if(iter == m_MapData.end())
		{
			m_MapData[iFlag] = list<void*>();
		}

		m_MapData[iFlag].push_back(pData);
		//Notify(iFlag, pData);
	}
}

void CDataSubject::RemoveData(int iFlag, void* pData)
{
	map<int, list<void*>>::iterator	iter = m_MapData.find(iFlag);
	
	if(iter != m_MapData.end())
	{
		list<void*>& rList = m_MapData[iFlag];

		for(list<void*>::iterator	Listiter = rList.begin();
			Listiter != rList.end(); )
		{
			if((*Listiter) == pData)
			{
				Listiter = rList.erase(Listiter);
			}
			else
			{
				++Listiter;
			}
		}
	}

}

void CDataSubject::Release(void)
{
	for(map<int, list<void*>>::iterator	iter = m_MapData.begin();
		iter != m_MapData.end(); ++iter)
	{
		iter->second.clear();
	}
	m_MapData.clear();
}

list<void*>* CDataSubject::GetDataList(int iFlag)
{
	map<int, list<void*>>::iterator		iter = m_MapData.find(iFlag);

	if(iter == m_MapData.end())
		return NULL;

	return &iter->second;
}
