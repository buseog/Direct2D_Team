#include "StdAfx.h"
#include "SKillMgr.h"
#include "ObjFactory.h"
#include "Effect.h"
#include "StandEffectBridge.h"
#include "MoveEffectBridge.h"

CSKillMgr::CSKillMgr(void)
{
}

CSKillMgr::~CSKillMgr(void)
{
}

CObj*	CSKillMgr::Skill(D3DXVECTOR3 vPos, D3DXVECTOR3 vTarget, const wstring&	wstrName)
{
	if (wstrName == L"YiSunshin")
	{
		CObj* pEffect = CObjFactory<CEffect, CMoveEffectBridge>::CreateObj(L"MagicUp", vPos);
		pEffect->SetTargetPoint(vTarget);
		return pEffect;
	}


	return NULL;
}