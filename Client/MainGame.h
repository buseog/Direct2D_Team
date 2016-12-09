#pragma once
#include "Bigheader.h"

class CMainGame
{
public:
	HRESULT	Initialize(void);
	void	Progress(void);
	void	Render(void);
	void	Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};
