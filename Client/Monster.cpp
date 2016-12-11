#include "StdAfx.h"
#include "Monster.h"

CMonster::CMonster(void)
{
}

CMonster::~CMonster(void)
{
}

HRESULT CMonster::Initialize(void)
{
	return S_OK;
}

void CMonster::Progress(void)
{

}

void CMonster::Render(void)
{

}

void CMonster::Release(void)
{
	//::Safe_Delete(m_pBridge);
}