#include "StdAfx.h"
#include "Start.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CStart::CStart(void)
{
}

CStart::~CStart(void)
{
}


unsigned int __stdcall CStart::ImgLoadThreadFunc(void* pArg)
{
	CStart*		pStart = (CStart*)pArg;

	EnterCriticalSection(&pStart->GetCrt());

	LeaveCriticalSection(&pStart->GetCrt());
	_endthreadex(0);

	return 0;
}

CRITICAL_SECTION CStart::GetCrt(void)
{
	return m_Crt;
}

HRESULT	CStart::Initialize(void)
{
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/GersangLogo.png", L"LOGO", TEX_SINGLE);

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/LoadingBar/UI%d.png", L"UI", TEX_MULTI, L"LoadingBar", 56);

	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ImgLoadThreadFunc, this, 0, NULL);

	return S_OK;
}

void	CStart::Progress(void)
{
	if(CKeyMgr::GetInstance()->KeyDown(VK_RETURN))
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);

		DeleteCriticalSection(&m_Crt);
		CSceneMgr::GetInstance()->SetScene(SC_BATTLEFIELD);
	}
}

void	CStart::Render(void)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"LOGO");

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, WINCX / 2.f, WINCY / 2.f, 0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void	CStart::Release(void)
{

}

void	CStart::LoadPNG(void)
{
}