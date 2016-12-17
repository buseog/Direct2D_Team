#pragma once

#include "Bigheader.h"

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	bool	m_bKeyDown[MAX_KEYUP][MAX_KEY];
	bool	m_bKeyUp[MAX_KEYUP][MAX_KEY];

public:
	bool	StayKeyDown(int nKey);
	bool	KeyDown(int nKey, int iIndex = 0);
	bool	KeyUp(int nKey, int iIndex);

private:
	CKeyMgr(void);
	~CKeyMgr(void);
};
