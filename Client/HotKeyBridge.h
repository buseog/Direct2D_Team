#pragma once
#include "buttonbridge.h"

class CHotKeyBridge :
	public CButtonBridge
{
public:
	HRESULT	Initialize(void);
	void	Progress(INFO& rInfo);
	void	Render(void);
	void	Release(void);
	void	WorldMatrix(INFO& rInfo);

public:
	CHotKeyBridge(void);
	~CHotKeyBridge(void);
};
