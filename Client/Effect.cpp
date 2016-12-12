#include "StdAfx.h"
#include "Effect.h"

CEffect::CEffect(void)
{
}

CEffect::~CEffect(void)
{
}

HRESULT CEffect::Initialize(void)
{
	return S_OK;
}

void CEffect::Progress(void)
{

}

void CEffect::Render(void)
{

}

void CEffect::Release(void)
{
	//::Safe_Delete(m_pBridge);
}