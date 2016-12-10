#pragma once

#include "Bigheader.h"

class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

private:
	list<CObj*>		m_ObjList[OBJ_END];
	
public:
	void			AddObject(OBJID eObjID, CObj* pObj);
	HRESULT			Initialize(void);
	void			Progress(void);
	void			Render(void);
	void			Release();

	const vector<TILE2*>*		GetTile(void);
	const CObj* GetObj(OBJID _eID);

private:
	CObjMgr(void);
	~CObjMgr(void);
};
