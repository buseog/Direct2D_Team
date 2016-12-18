#pragma once
#include "subject.h"

class CDataSubject :
	public CSubject
{
	DECLARE_SINGLETON(CDataSubject)

private:
	map<int, list<void*>>		m_MapData;
	
public:
	void	AddData(int iFlag, void* pData);
	void	RemoveData(int iFlag, void* pData);
	void	Release(void);
	list<void*>*	GetDataList(int iFlag);

public:
	CDataSubject(void);
	virtual ~CDataSubject(void);
};
