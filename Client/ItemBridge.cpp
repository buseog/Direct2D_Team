#include "StdAfx.h"
#include "ItemBridge.h"



CItemBridge::CItemBridge(void)
{
}


CItemBridge::CItemBridge(CUi*	pItem)
:CBridge(pItem)
{
}

CItemBridge::~CItemBridge(void)
{
}

HRESULT CItemBridge::Initialize(void)
{
	return S_OK;
}

void CItemBridge::Progress(INFO& rInfo)
{
	
}

void CItemBridge::Render(void)
{

}

void CItemBridge::Release(void)
{
	
}

void	CItemBridge::WorldMatrix(INFO& rInfo)
{
	

}