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
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);		// ��ü���� �Ҵ� �Լ�(�����ν�)

	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if(FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		// AfxMessageBox();
		//MessageBox(g_hWnd, L"��ġ ���� ����", L"error", MB_OK);
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
		ERR_MSG(L"��ġ ���� ����");
		return E_FAIL;
	}

	// ��������Ʈ ��ü ����

	if(FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"��������Ʈ ��ġ ���� ����");
		return E_FAIL;
	}

	// ��Ʈ ��ü ����

	D3DXFONT_DESCW			tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo.Height = 10;
	tFontInfo.Width = 5;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"�ü�");

	if(FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		ERR_MSG(L"��Ʈ ��ü ���� ����");
		return E_FAIL;
	}

	// �ε���Ʈ ��ü ����

	D3DXFONT_DESCW			tFontInfo2;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo2.Height = 20;
	tFontInfo2.Width = 10;
	tFontInfo2.Weight = FW_HEAVY;
	tFontInfo2.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo2.FaceName, L"����");

	if(FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo2, &m_pLoadingFont)))
	{
		ERR_MSG(L"�ε���Ʈ ��ü ���� ����");
		return E_FAIL;
	}

	// ���ΰ�ü ����
	if(FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		ERR_MSG(L"���� ��ü ���� ����");
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
	
	// 1, 2���� : ��Ʈ �� ���� ���� ��, �� ���� ���� ����ŭ Ȯ��/����ϴ� �뵵
	// 1���� ���� ��Ʈ 2���� ū ��Ʈ�� ������ Ȯ��, �ݴ�� ������ ���
	// 3���� : ��� �����쿡 ���� ���ΰ�, �ڵ�
	// 4���� : �������� ���� ���� �����ϴ� ����(��Ʈ)
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
	 d3dpp.BackBufferWidth  = WINCX;  // ����� ���� ������
	 d3dpp.BackBufferHeight = WINCY; // ����� ���� ������
	 d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	
	 d3dpp.BackBufferCount  = 1;  // ����� ����

	 d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;	// ��Ƽ���ø� ��� ����
	 d3dpp.MultiSampleQuality = 0;					// ����Ƽ 0

	 d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	 d3dpp.hDeviceWindow = g_hWnd;
	 d3dpp.Windowed = TRUE;			// ��üȭ�� OR â���
	 d3dpp.EnableAutoDepthStencil = TRUE;
	 d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	
	 d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ��ü ȭ��� ����� �ֻ��� ����
	 d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}
