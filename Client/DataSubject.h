#pragma once
#include "subject.h"

class CDataSubject :
	public CSubject
{
	DECLARE_SINGLETON(CDataSubject)

private:
	map<int, const UNITDATA*>		m_MapData;
	
public:
	void	AddData(int iFlag, const UNITDATA* pData);
	void	RemoveData(int iFlag, const UNITDATA* pData);
	virtual void	Release(void);
	const UNITDATA*	GetData(int iFlag);

public:
	CDataSubject(void);
	virtual ~CDataSubject(void);
};
