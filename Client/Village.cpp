#include "StdAfx.h"
#include "Village.h"
#include "ObjMgr.h"
#include "UiMgr.h"

CVillage::CVillage(void)
{
}

CVillage::~CVillage(void)
{
	Release();
}

HRESULT	CVillage::Initialize(void)
{

	return S_OK;
}

void	CVillage::Progress(void)
{
	CObjMgr::GetInstance()->Progress();
	CUIMgr::GetInstance()->Progress();
}

void	CVillage::Render(void)
{
	CObjMgr::GetInstance()->Render();
 	CUIMgr::GetInstance()->Render();
}

void	CVillage::Release(void)
{
	
}

void	CVillage::LoadPNG(void)
{

}