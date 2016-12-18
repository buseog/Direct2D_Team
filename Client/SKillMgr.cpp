#include "StdAfx.h"
#include "SKillMgr.h"
#include "ObjFactory.h"
#include "Effect.h"
#include "StandEffectBridge.h"
#include "MoveEffectBridge.h"
#include "ObjMgr.h"

CSKillMgr::CSKillMgr(void)
{
}

CSKillMgr::~CSKillMgr(void)
{
}

void	CSKillMgr::Skill(D3DXVECTOR3 vPos, D3DXVECTOR3 vTarget, const wstring&	wstrName)
{
	if (wstrName == L"YiSunshin")
	{
		ThunderField(vPos);		
	}
	
	if (wstrName == L"YuSeongryong")
	{
		BlackHole(vTarget);		
	}

	if (wstrName == L"Samyeong")
	{
		IceBomb(vTarget);
	}

	if (wstrName == L"BlueDragon")
	{
		Blizzard(vTarget);
	}
}

void	CSKillMgr::ThunderField(D3DXVECTOR3 vPos)
{
	float fAngle = 90.f;
	float fDistance = 100.f;

	for (int i = 0; i < 40; ++i)
	{
		D3DXVECTOR3 vPosition;
		vPosition.x = vPos.x + cosf(D3DXToRadian(fAngle)) * fDistance;
		vPosition.y = vPos.y - sinf(D3DXToRadian(fAngle)) * fDistance;


		CObj* pEffect = CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"Light", vPosition);
		CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pEffect);

		pEffect = CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"LightEff", vPosition);
		CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pEffect);

		fAngle += 30.f;
		fDistance += 10.f;
	}
}


void	CSKillMgr::BlackHole(D3DXVECTOR3	vTarget)
{
	CObj* pEffect = CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"MagicOval", vTarget);
		CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pEffect);

	pEffect = CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"MagicOvalEff", vTarget);
		CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pEffect);
	
}


void	CSKillMgr::IceBomb(D3DXVECTOR3	vTarget)
{
	CObj* pEffect = CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"IceArrowSmoke", vTarget);
		CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pEffect);

	pEffect = CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"FogofIce", vTarget);
		CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pEffect);
	
}

void	CSKillMgr::Blizzard(D3DXVECTOR3	vTarget)
{
	CObj* pEffect = CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"ThunderArea_Cloud", vTarget);
		CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pEffect);

	pEffect = CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"SnowStorm", vTarget);
		CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pEffect);
}