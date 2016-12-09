#pragma once

#include "Bigheader.h"

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	DWORD		m_dwKey;
	DWORD		m_dwKeyPressed;
	DWORD		m_dwKeyPresseds[3];

	DWORD		m_dwKeyDown;

public:
	void		KeyCheck(void);
	bool		KeyPressed(DWORD dwKey);
	bool		KeyPressed(DWORD dwKey, int iIndex);

	bool		KeyDown(DWORD dwKey);

	bool		KeyCombine(DWORD dwFirstKey, DWORD dwSecondKey);



private:
	CKeyMgr(void);
	~CKeyMgr(void);
};
