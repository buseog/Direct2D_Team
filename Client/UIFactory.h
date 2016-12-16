#pragma once

#include "Ui.h"

template <typename T, typename T2>
class CUIFactory
{
public:
	static CUi*	CreateUI(const wstring& wstrState, float _fX, float _fY)
	{
		CUi*		pUI = new T;
		CBridge* pBridge = new T2;
		
		pUI->SetBridge(pBridge);
		pUI->Initialize();
		pUI->SetPos(_fX, _fY);

		pBridge->SetUI(pUI);
		pBridge->Initialize();
		pBridge->SetKey(wstrState);

		return pUI;	
	}
	
	//static CUi*	CreateUI(float _fX, float _fY)
	//{
	//	CUi*		pUI = new T;
	//	pUI->Initialize();

	//	return pUI;	
	//}

	//static CUi*	CreateUI(void)
	//{
	//	CUi*		pUI = new T;
	//	pUI->Initialize();

	//	return pUI;	
	//}

public:
	CUIFactory(void){ }
	~CUIFactory(void){ }
};
