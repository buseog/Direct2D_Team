#pragma once

#include "Bigheader.h"

class CScene;
class CSceneMgr
{
private:
	DECLARE_SINGLETON(CSceneMgr)

private:
	CScene*		m_pScene;
	wstring		wstrMouse;		//	���콺 �ؽ��� �ٲٱ� ���� ����
	FRAME		m_tFrame;		//	���콺 �ؽ��� ��������Ʈ ������ ���� ����

public:
	void	SetMouse(const wstring& wstrMouseKey);	//	���������� ���콺 �ؽ��ĸ� �ٲٱ� ���� �ʿ��� �Լ�. �̱������� �������⼭ �ҷ��ٰ� �� �� ����.

public:
	void	SetScene(SCENEID _eScene);
	void	Progress(void);
	void	Render(void);
	void	Release(void);

private:
	CSceneMgr(void);
	~CSceneMgr(void);
};
