#include "StdAfx.h"
#include "ObjBridge.h"
#include "Obj.h"

CObjBridge::CObjBridge(void)
{
}

CObjBridge::CObjBridge(CObj*	pObj)
:CBridge(pObj)
{
}


CObjBridge::~CObjBridge(void)
{
}

HRESULT CObjBridge::Initialize(void)
{
	return S_OK;
}

void CObjBridge::Progress(void)
{
	
}

void CObjBridge::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey(), 
		m_wstrStateKey, (int)m_tFrame.fFrame);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CObjBridge::Release(void)
{
	
}

