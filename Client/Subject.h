#pragma once

#include "Bigheader.h"

class CObserver;
class CSubject
{
protected:
	list<CObserver*>			m_ObserverList;

public:
	virtual void Subscribe(CObserver* pObserver);			// 관찰자 등록 함수
	virtual void UnSubscribe(CObserver* pObserver);			// 관찰자 등록 해제 함수
	virtual void Notify(int iFlag, void* pData = NULL);		// 관찰자들에게 데이터 갱신을 통보하는 함수
	virtual void Release(void);

public:
	CSubject(void);
	virtual ~CSubject(void);
};
