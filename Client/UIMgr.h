#pragma once

#include "BIgheader.h"

class CUi;
class CUIMgr
{
	DECLARE_SINGLETON(CUIMgr)

private:
	list<CUi*>		m_UiList[UI_END];

public:
	void	AddUI(UIID	eUiID, CUi*	pUi);
	const	CUi*	GetUi(UIID _eUI);
	

public:
	HRESULT			Initialize(void);
	void			Progress(void);
	void			Render(void);
	void			Release();


public:
	CUIMgr(void);
	~CUIMgr(void);
};
