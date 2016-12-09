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

		switch (eTexType)
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
			ERR_MSG(wstrObjKey.c_str())
			return E_FAIL;
		}
		m_MapTexture.insert(map<wstring, CTexture*>::value_type(wstrObjKey, pTexture));
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
