#pragma once

#include "Obj.h"

template <typename T>
class CObjFactory
{
public:
	static CObj* CreateObj(void)
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* CreateObj(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fX, _fY);

		return pObj;
	}

	static CObj* CreateObj(D3DXVECTOR3 vPos)	
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos);

		return pObj;
	}

public:
	CObjFactory(void){	}
	~CObjFactory(void){	}
};
