#pragma once

#include "Bridge.h"
#include "Obj.h"

template <typename T, typename T2>
class CBridgeFactory
{
public:
	static CObj*	CreateBridge(const wstring& wstrState, float _fX = 0, float _fY = 0)
	{
		CObj*	pObj = new T;
		CBridge* pBridge = new T2;

		pObj->SetBridge(pBridge);
		pObj->Initialize();
		pObj->SetPos(_fX, _fY);

		pBridge->Initialize();
		pBridge->SetObj(pObj);
		pBridge->SetFrame(wstrState);
		

		return pObj;
	}

	static CObj*	CreateBridge(const wstring& wstrState, D3DXVECTOR3 vPos)
	{
		CObj*	pObj = new T;
		CBridge* pBridge = new T2;

		pObj->SetBridge(pBridge);
		pObj->Initialize();
		pObj->SetPos(vPos);

		pBridge->SetFrame(wstrState);
		pBridge->Initialize();
		pBridge->SetObj(pObj);

		return pObj;
	}

public:
	CBridgeFactory(void){}
	~CBridgeFactory(void){}
};