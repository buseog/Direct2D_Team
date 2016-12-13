#include "StdAfx.h"
#include "MultiTexture.h"

CMultiTexture::CMultiTexture(void)
{
}

CMultiTexture::~CMultiTexture(void)
{
	Release();
}

HRESULT CMultiTexture::InsertTexture(const wstring& wstrFilePath, 
									  const wstring& wstrStateKey, 
									  const int& iCnt)
{
	TCHAR szPath[MAX_PATH] = L"";
	vector<TEXINFO*>	vecTexture;

	for (int i = 0; i < iCnt; ++i)
	{
		wsprintf(szPath, wstrFilePath.c_str(), i);

		TEXINFO*	pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		if (FAILED(D3DXGetImageInfoFromFile(szPath, &pTexInfo->tImgInfo)))
		{
			ERR_MSG(wstrFilePath.c_str())
			return E_FAIL;
		}

		if (FAILED(D3DXCreateTextureFromFileEx(
			CDevice::GetInstance()->GetDevice(),	
			szPath,					// 경로
			pTexInfo->tImgInfo.Width,				// 이미지 가로
			pTexInfo->tImgInfo.Height,			// 이미지 세로
			pTexInfo->tImgInfo.MipLevels,			// 이미지 확대축소시 비율(mfc에선 안씀)
			0,										// 이미지를 읽는 방식(default 0)
			pTexInfo->tImgInfo.Format,			// 이미지 포맷 형태
			D3DPOOL_MANAGED,						// 현재 읽는 이미지들을 어떤 메모리에 보관할지 결정
			D3DX_DEFAULT,							// 테두리 표현을 어떻게 할 것인가
			D3DX_DEFAULT,							// 확대, 축소시 어떻게 할 것인가	
			D3DCOLOR_ARGB(255,212,192,212),									// 제거할 이미지 색상
			&pTexInfo->tImgInfo,					// 이미지 정보 저장할 곳
			NULL,									// 팔레트 처리 방식
			&pTexInfo->pTexture)))				// 이미지를 어디에 보관할 곳
		{
			ERR_MSG(L"Multi Texture Image Load Failed")
			return E_FAIL;
		}

		vecTexture.push_back(pTexInfo);
	}

	m_MapMultiTexture.insert(map<wstring, vector<TEXINFO*>>::value_type(wstrStateKey, vecTexture));


	return S_OK;
}

const TEXINFO* CMultiTexture::GetTexture(const wstring& wstrStateKey, 
										  const int& iCnt)
{
	map<wstring, vector<TEXINFO*>>::iterator iter = m_MapMultiTexture.find(wstrStateKey);

	if(iter == m_MapMultiTexture.end())
		return NULL;

	return iter->second[iCnt];
}

void CMultiTexture::Release(void)
{
	for (map<wstring, vector<TEXINFO*>>::iterator iter = m_MapMultiTexture.begin();
		iter != m_MapMultiTexture.end(); ++iter)
	{
		for_each (iter->second.begin(), iter->second.end(), DeleteObj());
		iter->second.clear();
	}
	m_MapMultiTexture.clear();
}
