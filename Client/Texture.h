#pragma once

#include "Bigheader.h"

class CTexture
{
protected:
	

public:
	virtual HRESULT		InsertTexture(const wstring& wstrFilePath, 
							const wstring& wstrStateKey = L"", 
							const int& iCnt = 0)PURE;

	virtual const TEXINFO* GetTexture(const wstring& wstrStateKey = L"", 
									  const int& iCnt = 0) PURE;

	virtual  void		Release(void)PURE;

public:
	CTexture(void);
	virtual ~CTexture(void);
};
