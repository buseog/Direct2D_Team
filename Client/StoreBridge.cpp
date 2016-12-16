#include "StdAfx.h"
#include "StoreBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Glove.h"
#include "Helmet.h"
#include "Boots.h"
#include "Belt.h"
#include "Food.h"

CStoreBridge::CStoreBridge(void)
:m_bState(FALSE),m_bToolTip(FALSE)
{
}

CStoreBridge::~CStoreBridge(void)
{
	Release();

}


HRESULT CStoreBridge::Initialize(void)
{
	
	return S_OK;
}

void CStoreBridge::Progress(INFO& rInfo)
{



}

void CStoreBridge::Render(void)
{

	

}

int CStoreBridge::Picking(void)
{

	return m_iPriority;
}
void CStoreBridge::ShowToolTip(/*int _iIndex,*/)
{




}
void CStoreBridge::Release(void)
{



}

void	CStoreBridge::WorldMatrix(INFO& rInfo)
{

	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}

void	CStoreBridge::AddItem(ITEMID _itemid,int _iIndex)
{

}


void CStoreBridge::DeleteContainedOverItem(void)
{

}
void CStoreBridge::SetState(void)
{
	
}
void CStoreBridge::LoadData(void)
{
	
}