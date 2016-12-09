#include "StdAfx.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTextureMgr)


CTextureMgr::CTextureMgr(void)
{
}

CTextureMgr::~CTextureMgr(void)
{
	Release();
}
HRESULT CTextureMgr::InsertTexture(const wstring& wstrFilePath, 
								   const wstring& wstrObjKey,
								   TEXTYPE eTexType, 
								   const wstring& wstrStateKey,
								   const int& iCnt)
{
	map<wstring, CTexture*>::iterator	iter = m_MapTexture.find(wstrObjKey);

	if(iter == m_MapTexture.end())
	{
		CTexture*		pTexture = NULL;

		switch(eTexType)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;

		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if(FAILED(pTexture->InsertTexture(wstrFilePath, wstrStateKey, iCnt)))
		{
			ERR_MSG(wstrObjKey.c_str());
			return E_FAIL;
		}
		m_MapTexture.insert(map<wstring, CTexture*>::value_type(wstrObjKey, pTexture));
	}
	else
	{
		if(TEX_MULTI == eTexType)
		{
			iter->second->InsertTexture(wstrFilePath, wstrStateKey, iCnt);
		}
	}

	return 0;
}

void CTextureMgr::Release(void)
{
	/*for(map<wstring, CTexture*>::iterator	iter = m_MapTexture.begin();
		iter != m_MapTexture.end(); ++iter)
	{
		::Safe_Delete(iter->second);
	}
	m_MapTexture.clear();*/

	for_each(m_MapTexture.begin(), m_MapTexture.end(), DeleteMap());
	m_MapTexture.clear();
}

const TEXINFO* CTextureMgr::GetTexture(const wstring& wstrObjKey, 
									   const wstring& wstrStateKey /*= L""*/, 
									   const int& iCnt /*= 0*/)
{
	map<wstring, CTexture*>::iterator	iter = m_MapTexture.find(wstrObjKey);

	if(iter == m_MapTexture.end())
		return NULL;

	return iter->second->GetTexture(wstrStateKey, iCnt);
}

HRESULT CTextureMgr::ReadImgPath(const wstring& wstrImgPath)
{
	wifstream		LoadFile;
	LoadFile.open("../Data/ImgPath.txt", ios::in);

	TCHAR		szObjKey[MIN_STR]	= L"";
	TCHAR		szStateKey[MIN_STR] = L"";
	TCHAR		szCount[MIN_STR]	= L"";
	TCHAR		szImgPath[MAX_PATH] = L"";

	wstring		wstrCombine = L"";

	while(!LoadFile.eof())
	{
		LoadFile.getline(szObjKey, MIN_STR, '|');
		LoadFile.getline(szStateKey, MIN_STR, '|');
		LoadFile.getline(szCount, MIN_STR, '|');
		LoadFile.getline(szImgPath, MAX_PATH);

		int iCount = _ttoi(szCount);

		if(FAILED(CTextureMgr::GetInstance()->InsertTexture(szImgPath, szObjKey, TEX_MULTI, szStateKey, iCount)))
		{
			ERR_MSG(L"Stage 멀티 텍스쳐 생성 실패");
			return E_FAIL;
		}
	}		

	LoadFile.close();

	return S_OK;
}

size_t CTextureMgr::GetImgCount(const wstring& wstrObjKey, 
								const wstring& wstrStateKey /*= L""*/)
{
	map<wstring, CTexture*>::iterator	iter = m_MapTexture.find(wstrObjKey);

	if(iter == m_MapTexture.end())
		return -1;

	return ((CMultiTexture*)iter->second)->GetImgCount(wstrStateKey);
}
