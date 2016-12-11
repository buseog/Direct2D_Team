#include "StdAfx.h"
#include "Player.h"
#include "Bridge.h"

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	m_wstrObjKey = L"PLAYER";
	return S_OK;
}

void CPlayer::Progress(void)
{
	m_pBridge->Progress(m_tInfo);
}

void CPlayer::Render(void)
{
	m_pBridge->Render();
}

void CPlayer::Release(void)
{
	::Safe_Delete(m_pBridge);
}