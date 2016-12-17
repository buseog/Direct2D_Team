#include "StdAfx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr(void)
{
	ZeroMemory(m_bKeyDown, sizeof(MAX_PATH));
	ZeroMemory(m_bKeyUp, sizeof(MAX_PATH));
}

CKeyMgr::~CKeyMgr(void)
{
	
}

bool	CKeyMgr::StayKeyDown(int nKey)	// �� ������������
{
	if (GetAsyncKeyState(nKey) & 0x8000)	// �Լ��� ��� �ݺ��Ǹ鼭 Ű�� �ԷµȰ� Ȯ���ϰ� Ʈ�縦 ���c��
		return true;

	return false;	// if������ �ԷµȰ� �������� �ʾ������� ������ �ʾ���. �޽��� ��ȯ
}
bool	CKeyMgr::KeyDown(int nKey)	// �ѹ��� �� ��������
{
	if (GetAsyncKeyState(nKey) & 0x8000)	// Ű�� �Է���� Ȯ���ϰ�
	{
		if (m_bKeyDown[nKey] == false)	// �ٿ� �迭���� �Էµ� Ű���� �������� Ȯ��(������ ���ȴ���)
		{
			m_bKeyDown[nKey] = true;	//	������ �������� ������ Ʈ��� �ٲ���

			return true;				//	Ʈ��� ��ȯ
		}
	}
	else
	{
		m_bKeyDown[nKey] = false;		//	Ű�� �Էµ��� �ʾ����Ƿ� ���� ��ȯ
	}

	return false;						//	�׳� ���зΰ���
}
bool	CKeyMgr::KeyUp(int nKey, int iIndex)	// �����ٰ� �H����
{
	if (GetAsyncKeyState(nKey) & 0x8000)		// ���ȴ��� Ȯ��
	{
		m_bKeyUp[iIndex][nKey] = true;			//	�������� ���迭 �ش�Ű���� Ʈ��� �ٲ�
	}
	else if (m_bKeyUp[iIndex][nKey] == true)	//	�ٽ� �Լ��� ���ۉ����� �Էµ� Ű���� ������ �ʾҰ�, �ش� ���迭�� Ʈ����
	{
		m_bKeyUp[iIndex][nKey] = false;			//	�迭�� �޽��� �ʱ�ȭ�ϰ�

		return true;							//	Ʈ�縦 ��ȯ��
	}

	return false;								//	������
}
