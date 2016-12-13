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
		wstrFilePath.c_str(),					// ���
		m_pTexInfo->tImgInfo.Width,				// �̹��� ����
		m_pTexInfo->tImgInfo.Height,			// �̹��� ����
		m_pTexInfo->tImgInfo.MipLevels,			// �̹��� Ȯ����ҽ� ����(mfc���� �Ⱦ�)
		0,										// �̹����� �д� ���(default 0)
		m_pTexInfo->tImgInfo.Format,			// �̹��� ���� ����
		D3DPOOL_MANAGED,						// ���� �д� �̹������� � �޸𸮿� �������� ����
		D3DX_DEFAULT,							// �׵θ� ǥ���� ��� �� ���ΰ�
		D3DX_DEFAULT,							// Ȯ��, ��ҽ� ��� �� ���ΰ�	
		D3DCOLOR_ARGB(255,212,192,212),									// ������ �̹��� ����
		&m_pTexInfo->tImgInfo,					// �̹��� ���� ������ ��
		NULL,									// �ȷ�Ʈ ó�� ���
		&m_pTexInfo->pTexture)))				// �̹����� ��� ������ ��
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
