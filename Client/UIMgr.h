#pragma once

#include "BIgheader.h"


class CUi;
class CUIMgr
{
	DECLARE_SINGLETON(CUIMgr)

private:
	list<CUi*>		m_UiList[SC_END][UI_END];
	map<int, CUi*>		m_mapUiRender;
	SCENEID			m_eSceneID;

public:
	void		SetSceneID(SCENEID	dID);		// �ش��ϴ� ���� ���� ����Ʈ�� �۵���Ű���� �뵵
	void		AddUI(UIID	eUiID, CUi*	pUi);
	const		CUi*	GetUi(UIID _eUI);

	void		AddSorting(CUi*	pUi);
	void		MapClear(void);
	int			Picking(void);

public:
	HRESULT			Initialize(void);
	void			Progress(void);
	void			Render(void);
	void			Release();


public:
	CUIMgr(void);
	~CUIMgr(void);
};
