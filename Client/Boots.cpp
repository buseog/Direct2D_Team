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
	m_wstrObjKey = L"TestBoots";
	return S_OK;
}
void CBoots::Progress(void)
{
	
}
void CBoots::Render(void)
{
}
void CBoots::Release(void)
{
}
