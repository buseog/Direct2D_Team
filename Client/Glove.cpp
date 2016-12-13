#include "StdAfx.h"
#include "Glove.h"

CGlove::CGlove(void)
{
}

CGlove::~CGlove(void)
{
	Release();
}
HRESULT CGlove::Initialize(void)
{
	return S_OK;
}
int CGlove::Progress(void)
{
	return 0;
}
void CGlove::Render(void)
{
}
void CGlove::Release(void)
{
}
