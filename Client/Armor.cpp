#include "StdAfx.h"
#include "Armor.h"

CArmor::CArmor(void)
{
}

CArmor::~CArmor(void)
{
	Release();
}
HRESULT CArmor::Initialize(void)
{
	return S_OK;
}
int CArmor::Progress(void)
{
	return 0;
}
void CArmor::Render(void)
{
}
void CArmor::Release(void)
{
}