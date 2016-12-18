#include "StdAfx.h"
#include "Subject.h"
#include "Observer.h"

CSubject::CSubject(void)
{
}

CSubject::~CSubject(void)
{
	Release();
}
void CSubject::Subscribe(CObserver* pObserver)
{
	m_ObserverList.push_back(pObserver);
}

void CSubject::UnSubscribe(CObserver* pObserver)
{
	for(list<CObserver*>::iterator iter = m_ObserverList.begin();
		iter != m_ObserverList.end(); )
	{
		if((*iter) == pObserver)
		{
			iter = m_ObserverList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CSubject::Notify(void)
{
	for(list<CObserver*>::iterator iter = m_ObserverList.begin();
		iter != m_ObserverList.end(); ++iter)
	{
		(*iter)->Update();		
	}
}

void CSubject::Release(void)
{
	m_ObserverList.clear();
}