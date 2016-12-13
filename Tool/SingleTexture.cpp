#include "StdAfx.h"
#include "SingleTexture.h"

CSingleTexture::CSingleTexture(void)
:m_pTexInfo(NULL)
{
}

CSingleTexture::~CSingleTexture(void)
{
	Release();
}

HRESULT CSingleTexture::InsertTexture(const wstring& wstrFilePath, 
									  const wstring& wstrStateKey, 
									  const int& iCnt)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_pTexInfo->tImgInfo)))
	{
		ERR_MSG(wstrFilePath.c_str())
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(
		CDevice::GetInstance()->GetDevice(),	
		wstrFilePath.c_str(),					// 경로
		m_pTexInfo->tImgInfo.Width,				// 이미지 가로
		m_pTexInfo->tImgInfo.Height,			// 이미지 세로
		m_pTexInfo->tImgInfo.MipLevels,			// 이미지 확대축소시 비율(mfc에선 안씀)
		0,										// 이미지를 읽는 방식(default 0)
		m_pTexInfo->tImgInfo.Format,			// 이미지 포맷 형태
		D3DPOOL_MANAGED,						// 현재 읽는 이미지들을 어떤 메모리에 보관할지 결정
		D3DX_DEFAULT,							// 테두리 표현을 어떻게 할 것인가
		D3DX_DEFAULT,							// 확대, 축소시 어떻게 할 것인가	
		D3DCOLOR_ARGB(255,212,192,212),									// 제거할 이미지 색상
		&m_pTexInfo->tImgInfo,					// 이미지 정보 저장할 곳
		NULL,									// 팔레트 처리 방식
		&m_pTexInfo->pTexture)))				// 이미지를 어디에 보관할 곳
	{
		ERR_MSG(L"Single Texture Load Failed")
		return E_FAIL;
	}



	return S_OK;
}

const TEXINFO* CSingleTexture::GetTexture(const wstring& wstrStateKey, 
										  const int& iCnt)
{
	return m_pTexInfo;
}

void CSingleTexture::Release(void)
{
	m_pTexInfo->pTexture->Release();
	::Safe_Delete(m_pTexInfo);
}
