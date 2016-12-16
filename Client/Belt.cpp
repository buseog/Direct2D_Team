#include "StdAfx.h"
#include "Belt.h"

CBelt::CBelt(void)
{
}

CBelt::~CBelt(void)
{
	Release();
}
HRESULT CBelt::Initialize(void)
{
	m_wstrObjKey = L"TestBelt";
	return S_OK;
}
void CBelt::Progress(void)
{
	
}
void CBelt::Render(void)
{
}
void CBelt::Release(void)
{
}
