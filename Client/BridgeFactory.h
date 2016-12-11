#pragma once

#include "Bridge.h"

template <typename T>
class CBridgeFactory
{
public:
	template <typename T2>
	static CBridge*	CreateBridge(const wstring& wstrState, float _fX = 0, float _fY = 0)
	{
		CObj*	pObj = new T;
		CBridge* pBridge = new T2;

		pObj->SetBridge(pBirdge);
		pObj->Initialize();
		pEffect->SetPos(vPos);

		pBridge->SetFrame(wstrState);
		pBridge->Initialize();

		return pObj;
	}

	template <typename T2>
	static CBridge*	CreateBridge(const wstring& wstrState, D3DXVECTOR3 vPos)
	{
		CObj*	pObj = new T;
		CBridge* pBridge = new T2;

		pObj->SetBridge(pBirdge);
		pObj->Initialize();
		pEffect->SetPos(_fX, _fY);

		pBridge->SetFrame(wstrState);
		pBridge->Initialize();

		return pObj;
	}

public:
	CBridgeFactory(void){}
	~CBridgeFactory(void){}
};