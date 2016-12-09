#include "StdAfx.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)

CDevice::CDevice(void)
:m_p3D(NULL)
,m_pDevice(NULL)
,m_pSprite(NULL)
,m_pFont(NULL)
{
}

CDevice::~CDevice(void)
{
	Release();
}

HRESULT CDevice::InitDevice(void)
{
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	//디바이스에 필요한 캡스
	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		AfxMessageBox(L"Caps Create Failed");
		return E_FAIL;
	}

	//디바이스에 필요한 vp
	DWORD	vp;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;	//그래픽카드

	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	//CPU

	//디바이스 객체 생성
	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(d3dpp);

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		AfxMessageBox(L"Device Create Failed");
		return E_FAIL;
	}

	//스프라이트 객체 생성
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		AfxMessageBox(L"Sprite Create Failed");
		return E_FAIL;
	}

	//폰트 객체 생성
	D3DXFONT_DESCW		tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo.Height = 20;
	tFontInfo.Width = 10;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"굴림");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		AfxMessageBox(L"Font Create Failed");
		return E_FAIL;
	}


	return S_OK;
}

void CDevice::Release(void)
{
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

void	CDevice::SetParameters(D3DPRESENT_PARAMETERS& d3dpp)
{
	d3dpp.BackBufferWidth	= WINCX;  // 백버퍼 가로 사이즈
	 d3dpp.BackBufferHeight	= WINCY; // 백버퍼 세로 사이즈
	 d3dpp.BackBufferFormat	= D3DFMT_A8R8G8B8;	
	 d3dpp.BackBufferCount	= 1;  // 백버퍼 개수

	 d3dpp.MultiSampleType	= D3DMULTISAMPLE_NONE;	// 멀티샘플링 사용 안함
	 d3dpp.MultiSampleQuality	= 0;					// 퀄리티 0

	 d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
	 d3dpp.hDeviceWindow	= g_hWnd;
	 d3dpp.Windowed			= TRUE;			// 전체화면 OR 창모드
	 d3dpp.EnableAutoDepthStencil	= TRUE;
	 d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;
	
	 d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;	// 전체 화면시 모니터 주사율 설정
	 d3dpp.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
}