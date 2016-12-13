#include "StdAfx.h"
#include "Food.h"

CFood::CFood(void)
{
}

CFood::~CFood(void)
{
	Release();
}
HRESULT CFood::Initialize(void)
{
	return S_OK;
}
int CFood::Progress(void)
{
	return 0;
}
void CFood::Render(void)
{
}
void CFood::Release(void)
{
}
