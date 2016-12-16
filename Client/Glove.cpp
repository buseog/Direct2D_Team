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
	m_wstrObjKey = L"TestGlove";
	return S_OK;
}
void CGlove::Progress(void)
{
	
}
void CGlove::Render(void)
{
}
void CGlove::Release(void)
{
}
