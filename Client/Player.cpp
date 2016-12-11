#include "StdAfx.h"
#include "Player.h"

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	return S_OK;
}

void CPlayer::Progress(void)
{

}

void CPlayer::Render(void)
{

}

void CPlayer::Release(void)
{
	::Safe_Delete(m_pBridge);
}