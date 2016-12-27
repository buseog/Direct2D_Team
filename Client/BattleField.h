#pragma once
#include "scene.h"

class CBattleField :
	public CScene
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual void	LoadPNG(void);
	void SetMonster(wstring _MonsterKey);

public:
	CBattleField(void);
	~CBattleField(void);
};
