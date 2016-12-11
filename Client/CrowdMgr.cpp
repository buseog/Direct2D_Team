#include "StdAfx.h"
#include "CrowdMgr.h"

IMPLEMENT_SINGLETON(CCrowdMgr)

CCrowdMgr::CCrowdMgr(void)
{
}

CCrowdMgr::~CCrowdMgr(void)
{
	Release();
}

void CCrowdMgr::Release(void)
{
	m_vecSelectUnit.clear();
}

vector<CObj*>*	CCrowdMgr::GetSelectList(void)
{
	return &m_vecSelectUnit;
}