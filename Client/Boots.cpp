#include "StdAfx.h"
#include "Boots.h"

CBoots::CBoots(void)
{
}

CBoots::~CBoots(void)
{
	Release();
}
HRESULT CBoots::Initialize(void)
{
	return S_OK;
}
int CBoots::Progress(void)
{
	return 0;
}
void CBoots::Render(void)
{
}
void CBoots::Release(void)
{
}
