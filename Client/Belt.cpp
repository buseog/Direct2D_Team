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
int CBelt::Progress(void)
{
	return 0;
}
void CBelt::Render(void)
{
}
void CBelt::Release(void)
{
}
