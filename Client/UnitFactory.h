#pragma once

#include "Unit.h"

template <typename T>
class CUnitFactory
{
public:
	static CUnit*	CreateUnit(void)
	{
		CUnit*	pUnit = new T;
		pUnit->Initialize();
	
		return pUnit;
	}
	
	static CUnit* CreateUnit(float _fX, float _fY)
	{
		CUnit*		pUnit = new T;
		pUnit->Initialize();
		pUnit->SetPos(_fX, _fY);
	
		return pUnit;
	}



	static CUnit* CreateUnit(D3DXVECTOR3 vPos)	
	{
		CUnit*		pUnit = new T;
		pUnit->Initialize();
		pUnit->SetPos(vPos);
		return pUnit;
	}

	static CUnit* CreateUnit(UNITDATA*	_pUnit,D3DXVECTOR3 vPos)	
	{
		CUnit*		pUnit = new T(_pUnit);
		pUnit->Initialize();
		pUnit->SetPos(vPos);
		return pUnit;
	}


public:
	CUnitFactory(void){ }
	~CUnitFactory(void){ }
};
