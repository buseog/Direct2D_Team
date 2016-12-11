#include "StdAfx.h"
#include "Missile.h"

CMissile::CMissile(void)
{
}

CMissile::~CMissile(void)
{
}

HRESULT CMissile::Initialize(void)
{
	return S_OK;
}

void CMissile::Progress(void)
{

}

void CMissile::Render(void)
{

}

void CMissile::Release(void)
{
	::Safe_Delete(m_pBridge);
}