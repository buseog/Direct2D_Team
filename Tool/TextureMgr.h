#pragma once
#include "BigHeader.h"

class CTexture;
class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

private:
	map<wstring, CTexture*>		m_MapTexture;

public:
	HRESULT		InsertTexture(const wstring& wstrFilePath,		// 파일이 있는 경로
								const wstring& wstrObjKey,		// 키 값
								TEXTYPE eTexType,
								const wstring& wstrStateKey = L"", // 멀티텍스쳐인 경우
								const int& iCnt = 0);				// 멀티텍스쳐인 경우

	void		Release(void);

	const TEXINFO*	GetTexture(const wstring& wstrObjKey, 
								const wstring& wstrStateKey = L"", 
								const int& iCnt = 0);

public:
	CTextureMgr(void);
	~CTextureMgr(void);
};
