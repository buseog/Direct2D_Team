	#include "StdAfx.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)

CDevice::CDevice(void)
: m_p3D(NULL)
, m_pDevice(NULL)
, m_pSprite(NULL)
, m_pFont(NULL)
, m_pLoadingFont(NULL)
, m_pLine(NULL)
{
}

CDevice::~CDevice(void)
{
	Release();
}

HRESULT CDevice::InitDevice(void)
{
	//return E_FAIL;
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);		// 자체적인 할당 함수(버전인식)

	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if(FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		// AfxMessageBox();
		//MessageBox(g_hWnd, L"장치 생성 실패", L"error", MB_OK);
		return E_FAIL;
	}

	DWORD		vp;

	if(DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(d3dpp);

	if(FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
		g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		ERR_MSG(L"장치 생성 실패");
		return E_FAIL;
	}

	// 스프라이트 객체 생성

	if(FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"스프라이트 장치 생성 실패");
		return E_FAIL;
	}

	// 폰트 객체 생성

	D3DXFONT_DESCW			tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo.Height = 10;
	tFontInfo.Width = 5;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"궁서");

	if(FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		ERR_MSG(L"폰트 객체 생성 실패");
		return E_FAIL;
	}

	// 로딩폰트 객체 생성

	D3DXFONT_DESCW			tFontInfo2;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo2.Height = 20;
	tFontInfo2.Width = 10;
	tFontInfo2.Weight = FW_HEAVY;
	tFontInfo2.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo2.FaceName, L"굴림");

	if(FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo2, &m_pLoadingFont)))
	{
		ERR_MSG(L"로딩폰트 객체 생성 실패");
		return E_FAIL;
	}

	// 라인객체 생성
	if(FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		ERR_MSG(L"라인 객체 생성 실패");
		return E_FAIL;
	}
	
	return S_OK;
}

void CDevice::Release(void)
{
	m_pLine->Release();
	m_pLoadingFont->Release();
	m_pFont->Release();
	m_pSprite->Release();
	m_pDevice->Release();
	m_p3D->Release();
}

void CDevice::Render_Begin(void)
{
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::Render_End()
{

	m_pSprite->End();
	m_pDevice->EndScene();
	
	// 1, 2인자 : 렉트 두 개를 만든 뒤, 두 개의 비율 차만큼 확대/축소하는 용도
	// 1번에 작은 렉트 2번에 큰 렉트를 넣으면 확대, 반대로 넣으면 축소
	// 3인자 : 어느 윈도우에 넣을 것인가, 핸들
	// 4인자 : 보여주지 않을 곳을 설정하는 인자(렉트)
}

LPDIRECT3DDEVICE9 CDevice::GetDevice(void)
{
	return m_pDevice;
}

LPD3DXSPRITE CDevice::GetSprite(void)
{
	return m_pSprite;
}

LPD3DXFONT CDevice::GetFont(void)
{
	return m_pFont;
}

LPD3DXFONT CDevice::GetLoadingFont(void)
{	
	return m_pLoadingFont;
}

LPD3DXLINE CDevice::GetLine(void)
{
	return m_pLine;
}

void CDevice::SetParameters(D3DPRESENT_PARAMETERS& d3dpp)
{
	 d3dpp.BackBufferWidth  = WINCX;  // 백버퍼 가로 사이즈
	 d3dpp.BackBufferHeight = WINCY; // 백버퍼 세로 사이즈
	 d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	
	 d3dpp.BackBufferCount  = 1;  // 백버퍼 개수

	 d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;	// 멀티샘플링 사용 안함
	 d3dpp.MultiSampleQuality = 0;					// 퀄리티 0

	 d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	 d3dpp.hDeviceWindow = g_hWnd;
	 d3dpp.Windowed = TRUE;			// 전체화면 OR 창모드
	 d3dpp.EnableAutoDepthStencil = TRUE;
	 d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	
	 d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// 전체 화면시 모니터 주사율 설정
	 d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}
