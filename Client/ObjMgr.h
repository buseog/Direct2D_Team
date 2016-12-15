#pragma once

#include "Bigheader.h"

class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

private:
	list<CObj*>		m_ObjList[SC_END][OBJ_END];
	SCENEID			m_eSceneID;

public:
	void		AddObject(OBJID eObjID, CObj* pObj);
	void		SetSceneID(SCENEID	dID);		// �ش��ϴ� ���� ���� ����Ʈ�� �۵���Ű���� �뵵

	const		vector<TILE2*>*		GetTile(void);
	const		CObj*				GetObj(OBJID _eID);
	list<CObj*>*	GetObjList(OBJID _eID);

public:
	HRESULT			Initialize(void);
	void			Progress(void);
	void			Render(void);
	void			Release();

private:
	CObjMgr(void);
	~CObjMgr(void);
};
