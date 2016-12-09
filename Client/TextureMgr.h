#pragma once

#include "Bigheader.h"

class CTexture;
class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)
private:
	map<wstring, CTexture*>		m_MapTexture;

public:
	HRESULT		InsertTexture(const wstring& wstrFilePath,		// ������ �ִ� ���
								const wstring& wstrObjKey,		// Ű ��
								TEXTYPE eTexType,
								const wstring& wstrStateKey = L"", // ��Ƽ�ؽ����� ���
								const int& iCnt = 0);				// ��Ƽ�ؽ����� ���

	void		Release(void);

	const TEXINFO*	GetTexture(const wstring& wstrObjKey, 
								const wstring& wstrStateKey = L"", 
								const int& iCnt = 0);

	HRESULT		ReadImgPath(const wstring& wstrImgPath);
	size_t		GetImgCount(const wstring& wstrObjKey, 
							const wstring& wstrStateKey = L"");


private:
	CTextureMgr(void);
	~CTextureMgr(void);
};
