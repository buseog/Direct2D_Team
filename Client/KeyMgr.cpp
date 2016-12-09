#include "StdAfx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr(void)
: m_dwKey(0)
, m_dwKeyPressed(0)
, m_dwKeyDown(0)
{
	ZeroMemory(m_dwKeyPresseds, sizeof(m_dwKeyPresseds));
}

CKeyMgr::~CKeyMgr(void)
{
}

void CKeyMgr::KeyCheck(void)
{
	m_dwKey = 0;

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwKey |= KEY_LBUTTON;

	if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwKey |= KEY_RBUTTON;

	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwKey |= KEY_ENTER;

	if(GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwKey |= KEY_SPACE;

	if(GetAsyncKeyState('1') & 0x8000)
		m_dwKey |= KEY_1;

	if(GetAsyncKeyState('2') & 0x8000)
		m_dwKey |= KEY_2;

	if(GetAsyncKeyState('3') & 0x8000)
		m_dwKey |= KEY_3;

	if(GetAsyncKeyState('4') & 0x8000)
		m_dwKey |= KEY_4;

}
						
bool CKeyMgr::KeyPressed(DWORD dwKey)
{		
	if(m_dwKey & dwKey)
	{
		m_dwKeyPressed |= dwKey;
		return false;
	}

	else if(m_dwKeyPressed & dwKey)
	{
		m_dwKeyPressed = m_dwKey;
		return true;
	}

	return false;
}

bool CKeyMgr::KeyPressed(DWORD dwKey, int iIndex)
{
	if(m_dwKey & dwKey)
	{
		m_dwKeyPresseds[iIndex] |= dwKey;
		return false;
	}

	else if(m_dwKeyPresseds[iIndex] & dwKey)
	{
		m_dwKeyPresseds[iIndex] = m_dwKey;
		return true;
	}

	return false;
}						
									
					
bool CKeyMgr::KeyDown(DWORD dwKey)
{
	if(KeyPressed(dwKey))
		m_dwKeyDown ^= dwKey;	//	0001
			
	if(!(m_dwKeyDown & dwKey))
	{		
		if(m_dwKey & dwKey)
		{					
			m_dwKeyDown |= dwKey;
			return true;
		}
	}

	return false;
}

bool CKeyMgr::KeyCombine(DWORD dwFirstKey, DWORD dwSecondKey)
{
	if(m_dwKey & dwFirstKey)
	{
		if(KeyDown(dwSecondKey))
			return true;
	}

	return false;
}
