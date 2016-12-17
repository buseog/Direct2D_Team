#pragma once

#include "Bigheader.h"

class CTexture;
class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)
private:
	map<wstring, CTexture*>		m_MapTexture;
	wstring						m_wstrString;
	int							m_iCounting;

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

	HRESULT		ReadImgPath(const wstring& wstrImgPath);
	size_t		GetImgCount(const wstring& wstrObjKey, 
							const wstring& wstrStateKey = L"");


	void		SetString(wstring _wstrBuf);						//	로딩 완료후 폰트 출력하기위한함수
	const wstring&	GetString(void);								//	세팅된 폰트를 불러오기위함

	int			GetCounting(void);									//	로딩을 퍼센티지로 나누기위해 몇개 로딩됬는지 확인해야함
private:
	CTextureMgr(void);
	~CTextureMgr(void);
};
