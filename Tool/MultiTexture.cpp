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
			szPath,					// ���
			pTexInfo->tImgInfo.Width,				// �̹��� ����
			pTexInfo->tImgInfo.Height,			// �̹��� ����
			pTexInfo->tImgInfo.MipLevels,			// �̹��� Ȯ����ҽ� ����(mfc���� �Ⱦ�)
			0,										// �̹����� �д� ���(default 0)
			pTexInfo->tImgInfo.Format,			// �̹��� ���� ����
			D3DPOOL_MANAGED,						// ���� �д� �̹������� � �޸𸮿� �������� ����
			D3DX_DEFAULT,							// �׵θ� ǥ���� ��� �� ���ΰ�
			D3DX_DEFAULT,							// Ȯ��, ��ҽ� ��� �� ���ΰ�	
			D3DCOLOR_ARGB(255,212,192,212),									// ������ �̹��� ����
			&pTexInfo->tImgInfo,					// �̹��� ���� ������ ��
			NULL,									// �ȷ�Ʈ ó�� ���
			&pTexInfo->pTexture)))				// �̹����� ��� ������ ��
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
