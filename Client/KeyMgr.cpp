#include "StdAfx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr(void)
{
	ZeroMemory(m_bKeyDown, sizeof(MAX_PATH));
	ZeroMemory(m_bKeyUp, sizeof(MAX_PATH));
}

CKeyMgr::~CKeyMgr(void)
{
	
}

bool	CKeyMgr::StayKeyDown(int nKey)	// �� ������������
{
	if (GetAsyncKeyState(nKey) & 0x8000)
		return true;

	return false;
}
bool	CKeyMgr::KeyDown(int nKey)	// �ѹ��� �� ��������
{
	if (GetAsyncKeyState(nKey) & 0x8000)
	{
		if (m_bKeyDown[nKey] == false)
		{
			m_bKeyDown[nKey] = true;

			return true;
		}
	}
	else
	{
		m_bKeyDown[nKey] = false;
	}

	return false;
}
bool	CKeyMgr::KeyUp(int nKey)	// �����ٰ� �H����
{
	if (GetAsyncKeyState(nKey) & 0x8000)
	{
		m_bKeyUp[nKey] = true;
	}
	else if (m_bKeyUp[nKey] == true)
	{
		m_bKeyUp[nKey] = false;

		return true;
	}

	return false;
}
