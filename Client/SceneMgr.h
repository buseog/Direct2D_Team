#pragma once

#include "Bigheader.h"

class CScene;
class CSceneMgr
{
private:
	DECLARE_SINGLETON(CSceneMgr)

private:
	CScene*		m_pScene;

public:
	void	SetScene(SCENEID _eScene);
	void	Progress(void);
	void	Render(void);
	void	Release(void);

private:
	CSceneMgr(void);
	~CSceneMgr(void);
};
