#pragma once

#include "Bigheader.h"

class CScene;
class CSceneMgr
{
private:
	DECLARE_SINGLETON(CSceneMgr)

private:
	CScene*		m_pScene;
	CScene*		m_arScene[SC_END];
	wstring		wstrMouse;		//	마우스 텍스쳐 바꾸기 위한 변수
	FRAME		m_tFrame;		//	마우스 텍스쳐 스프라이트 돌리기 위한 변수

public:
	void	SetMouse(const wstring& wstrMouseKey);	//	여러곳에서 마우스 텍스쳐를 바꾸기 위해 필요한 함수. 싱글톤으로 여기저기서 불러다가 쓸 수 있음.
	const wstring	GetMouse(void);
	const CScene* GetScene(SCENEID _SceneId);

public:
	void	SetScene(SCENEID _eScene);
	void	Progress(void);
	void	Render(void);
	void	Release(void);

private:
	CSceneMgr(void);
	~CSceneMgr(void);
};
