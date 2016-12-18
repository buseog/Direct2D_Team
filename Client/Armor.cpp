#include "StdAfx.h"
#include "Armor.h"


CArmor::CArmor(void)
{
}
CArmor::CArmor(ITEM*	tItem) :CItem(tItem)
{

}

CArmor::~CArmor(void)
{
	
	Release();
}
HRESULT CArmor::Initialize(void)
{
	//m_wstrObjKey = L"Armor";
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);
	
	m_wstrObjKey = L"TestArmor";
	m_tItem.eType = IT_ARMOR;

	return S_OK;
}
void CArmor::Progress(void)
{
	WorldMatrix();
	
}

void CArmor::Release(void)
{
}
