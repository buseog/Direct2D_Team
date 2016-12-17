#pragma once

#include "Bigheader.h"

class CObserver;
class CSubject
{
protected:
	list<CObserver*>			m_ObserverList;

public:
	virtual void Subscribe(CObserver* pObserver);			// ������ ��� �Լ�
	virtual void UnSubscribe(CObserver* pObserver);			// ������ ��� ���� �Լ�
	virtual void Notify(int iFlag, void* pData = NULL);		// �����ڵ鿡�� ������ ������ �뺸�ϴ� �Լ�
	virtual void Release(void);

public:
	CSubject(void);
	virtual ~CSubject(void);
};
