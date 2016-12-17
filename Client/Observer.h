#pragma once

#include "Bigheader.h"

class CObserver
{
public:
	virtual void Update(int iFlag, void* pData)PURE;

public:
	CObserver(void);
	virtual ~CObserver(void);
};
