#include "StdAfx.h"
#include "Start.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CStart::CStart(void)
:m_iMaxLoad(82)
{
}

CStart::~CStart(void)
{
}


unsigned int __stdcall CStart::ImgLoadThreadFunc(void* pArg)
{
	CStart*		pStart = (CStart*)pArg;

	EnterCriticalSection(&pStart->GetCrt());

	CTextureMgr::GetInstance()->ReadImgPath(L"../Data/PlayerPath.txt");	// 21

	CTextureMgr::GetInstance()->ReadImgPath(L"../Data/EffectPath.txt");	// 27

	CTextureMgr::GetInstance()->ReadImgPath(L"../Data/MousePath.txt");	// 18

	CTextureMgr::GetInstance()->ReadImgPath(L"../Data/PortraitPath.txt");	// 24

//	CTextureMgr::GetInstance()->ReadImgPath(L"../Data/EnemyUnitPath.txt");	// 24


	CTextureMgr::GetInstance()->SetString(L"Press Enter");

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
		if (CTextureMgr::GetInstance()->GetCounting() < m_iMaxLoad)
			return;

		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);

		DeleteCriticalSection(&m_Crt);
		CSceneMgr::GetInstance()->SetScene(SC_FILED);
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

	float fPercent = (float)CTextureMgr::GetInstance()->GetCounting() / (float)m_iMaxLoad * 100.f;
	int	iLoading = int(fPercent / 1.8f);

	for (int i = 0; i < iLoading; ++i)
	{
		const TEXINFO*		pLoading = CTextureMgr::GetInstance()->GetTexture(L"UI", L"LoadingBar", i);
		
		fX = pLoading->tImgInfo.Width / 2.f;
		fY = pLoading->tImgInfo.Height / 2.f;
		
		D3DXMatrixTranslation(&matTrans, 
			230 + (float)pLoading->tImgInfo.Width * i,
			550, 0);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
		CDevice::GetInstance()->GetSprite()->Draw(pLoading->pTexture, 
			NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	D3DXMatrixTranslation(&matTrans, 350.f, 500.f, 0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetLoadingFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		CTextureMgr::GetInstance()->GetString().c_str(),
		CTextureMgr::GetInstance()->GetString().length(),
		NULL, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void	CStart::Release(void)
{

}

void	CStart::LoadPNG(void)
{
}