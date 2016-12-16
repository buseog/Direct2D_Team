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
	m_wstrObjKey = L"Player";

	m_tUnitData.wstrName = L"쥬신아카데미";
	m_tUnitData.tDetail.iLevel = 2;
	m_tUnitData.iAttack = 10;
	m_tUnitData.iDeffence = 5;
	m_tUnitData.iHealthPoint = 100;
	m_tUnitData.tDetail.iExperience = 0;
	m_tUnitData.tDetail.iBonusPoint = 5;
	m_tUnitData.tDetail.iWeight = 0;
	m_tUnitData.tDetail.iStr = 10;
	m_tUnitData.tDetail.iDex = 10;
	m_tUnitData.tDetail.iVital = 10;
	m_tUnitData.tDetail.iInt = 10;

	
	return S_OK;
}

void CPlayer::Progress(void)
{
	m_pBridge->Progress(m_tInfo);

	// 만약 플레이어의 레벨이 1이라면 보너스 스텟은 0
	if(m_tUnitData.tDetail.iLevel == 1) 
	{
		m_tUnitData.tDetail.iBonusPoint = 0; 
	}

}


void CPlayer::Render(void)
{
	m_pBridge->Render();
}

void CPlayer::Release(void)
{
	::Safe_Delete(m_pBridge);
}
