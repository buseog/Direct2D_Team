#pragma once

#include "Bigheader.h"

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	bool	m_bKeyDown[MAX_PATH];
	bool	m_bKeyUp[MAX_PATH];

public:
	bool	StayKeyDown(int nKey);
	bool	KeyDown(int nKey);
	bool	KeyUp(int nKey);

private:
	CKeyMgr(void);
	~CKeyMgr(void);
};
