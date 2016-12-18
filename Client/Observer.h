#pragma once

#include "Bigheader.h"

class CObserver
{
public:
	virtual void Update(void)PURE;

public:
	CObserver(void);
	virtual ~CObserver(void);
};
