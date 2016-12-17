#include "StdAfx.h"
#include "BattleFieldBackBridge.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "CrowdMgr.h"
#include "SceneMgr.h"

CBattleFieldBackBridge::CBattleFieldBackBridge(void)
: m_iDragState(0)
{
}

CBattleFieldBackBridge::~CBattleFieldBackBridge(void)
{
	Release();
}

HRESULT	CBattleFieldBackBridge::Initialize(void)
{
	//LoadTile(L"../Data/map.dat");

	return S_OK;
}

void	CBattleFieldBackBridge::Progress(INFO& rInfo)
{
	Picking();
}

void	CBattleFieldBackBridge::Render(void)
{
	D3DXMATRIX	matTrans;

	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);

	D3DXMatrixTranslation(&matTrans, 
		0 + m_pObj->GetScroll().x,
		0 + m_pObj->GetScroll().y,
		0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(TILECX / 2.f, TILECY / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	// �巡�װ��� 1�̸� ȭ���� �׸�������.
	if (m_iDragState == 1)
	{
		CDevice::GetInstance()->Render_End();
		CDevice::GetInstance()->Render_Begin();

		CDevice::GetInstance()->GetLine()->Begin();
		CDevice::GetInstance()->GetLine()->Draw(m_vDrag, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
		CDevice::GetInstance()->GetLine()->End();

		CDevice::GetInstance()->Render_End();
		CDevice::GetInstance()->Render_Begin();
	}
}

void	CBattleFieldBackBridge::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();
}

void	CBattleFieldBackBridge::Picking(void)
{
	// ��Ʋ�ʵ� �Ʊ� ���� ����Ʈ�� �޾ƿ�
	list<CObj*>*	plistUnit = CObjMgr::GetInstance()->GetObjList(OBJ_PLAYER);
	list<CObj*>*	plistMonster = CObjMgr::GetInstance()->GetObjList(OBJ_MONSTER);
	POINT pt;
	pt.x = (long)::GetMouse().x - (long)m_pObj->GetScroll().x;
	pt.y = (long)::GetMouse().y - (long)m_pObj->GetScroll().y;

	/////////////////////// ���� ��ŷ
	if (m_iDragState == 4)
	{
		for (list<CObj*>::iterator iter = plistMonster->begin(); iter != plistMonster->end(); ++iter)
		{
			// ���콺�� �浹����� üũ
			if (PtInRect(&(*iter)->GetRect(), pt))
			{
				break;
			}
		}
		// �浹�� �ȳ����� ���콺�� �⺻���� �ٲ���
		CSceneMgr::GetInstance()->SetMouse(L"Hand_Stand");
		m_iDragState = 0;
	}

	if (m_iDragState == 0)
	{
		// ����Ʈ�� ��ȸ
		for (list<CObj*>::iterator iter = plistMonster->begin(); iter != plistMonster->end(); ++iter)
		{
			// ���콺�� �浹����� üũ
			if (PtInRect(&(*iter)->GetRect(), pt))
			{
				m_iDragState = 4;
				// �浹�� ��ٸ� ���콺�� �����ڵ�� �ٲ���
				CSceneMgr::GetInstance()->SetMouse(L"Sword_Stand");

				// �浹�Ȼ��¿��� ���ʹ�ư�� ������
				if (CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON))
				{
					CSceneMgr::GetInstance()->SetMouse(L"Sword_Click");
					return;
				}
			}
		}
	}

	/////////////////////////////////////////////// �Ʊ����� ��ŷ
	if (m_iDragState == 3)
	{
		for (list<CObj*>::iterator iter = plistUnit->begin(); iter != plistUnit->end(); ++iter)
		{
			// ���콺�� �浹����� üũ
			if (PtInRect(&(*iter)->GetRect(), pt))
			{
				break;
			}
		}
		// �浹�� �ȳ����� ���콺�� �⺻���� �ٲ���
		CSceneMgr::GetInstance()->SetMouse(L"Hand_Stand");
		m_iDragState = 0;
	}

	if (m_iDragState == 0)
	{
		// ����Ʈ�� ��ȸ
		for (list<CObj*>::iterator iter = plistUnit->begin(); iter != plistUnit->end(); ++iter)
		{
			// ���콺�� �浹����� üũ
			if (PtInRect(&(*iter)->GetRect(), pt))
			{
				m_iDragState = 3;
				// �浹�� ��ٸ� ���콺�� �����ڵ�� �ٲ���
				CSceneMgr::GetInstance()->SetMouse(L"Hand_Unit");
				// �浹�Ȼ��¿��� ���ʹ�ư�� ������
				if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
				{
					CSceneMgr::GetInstance()->SetMouse(L"Hand_Click");
					// ���߸Ŵ����� ����Ʈ�� ����ش�
					CCrowdMgr::GetInstance()->Release();
					// ���� ��ŷ�� �Ʊ� ������ ���߸Ŵ����� ���ø���Ʈ�� �ִ´�
					CCrowdMgr::GetInstance()->AddSelectList(*iter);
					// �巡�װ� �ߺ����� �Է¹޴°� �������� �ٷ� ����
					return;
				}
			}
		}
	}

	///////////////////////////////////// �巡�ױ�� �Ʊ����ּ���
	D3DXVECTOR3	vMouse = ::GetMouse();

	// ��ư�� ������, �ߺ��Ǵ� �Լ������� ���� �ε����� ���ó�� ������.
	if(CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON, 0) && m_iDragState == 1)
	{
		// �巡�׵Ǵ� �簢���� �׷��ֱ� ���� ����ü. ���������� ����Ʈ �������� ����
		m_rcDrag.right = long(vMouse.x);
		m_rcDrag.bottom = long(vMouse.y);

		// �巡�׸� �������� �ݴ�� ������ ����ó��
		if (m_rcDrag.left > m_rcDrag.right)
		{
			long TempX = m_rcDrag.left;
			m_rcDrag.left = m_rcDrag.right;
			m_rcDrag.right = TempX;
		}
		if (m_rcDrag.top > m_rcDrag.bottom)
		{
			long TempY = m_rcDrag.top;
			m_rcDrag.top = m_rcDrag.bottom;
			m_rcDrag.bottom = TempY;
		}

		// �簢���� �׷��ִ� 5���� ��
		m_vDrag[0] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.top);
		m_vDrag[1] = D3DXVECTOR2((float)m_rcDrag.right, (float)m_rcDrag.top);
		m_vDrag[2] = D3DXVECTOR2((float)m_rcDrag.right, (float)m_rcDrag.bottom);
		m_vDrag[3] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.bottom);
		m_vDrag[4] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.top);
		
		// ��Ʋ�ʵ� �Ʊ� ���ָ���Ʈ�� ���´�
		list<CObj*>* pUnitList = CObjMgr::GetInstance()->GetObjList(OBJ_PLAYER);
		// ���ָ���Ʈ�� ����ش�
		CCrowdMgr::GetInstance()->Release();

		// ����Ʈ�� ��ȸ�Ѵ�
		for (list<CObj*>::iterator iter = pUnitList->begin(); iter != pUnitList->end(); ++iter)
		{
			// �簢�� ������� �ִ� ������ ��󳻱����� ���ǹ�
			if ((*iter)->GetInfo()->vPos.x + m_pObj->GetScroll().x > m_rcDrag.left &&
				(*iter)->GetInfo()->vPos.x + m_pObj->GetScroll().x < m_rcDrag.right &&
				(*iter)->GetInfo()->vPos.y + m_pObj->GetScroll().y > m_rcDrag.top &&
				(*iter)->GetInfo()->vPos.y + m_pObj->GetScroll().y < m_rcDrag.bottom)
			{
				// ���ǿ� �����ϴ� ������ ���ø���Ʈ�� �߰���
				CCrowdMgr::GetInstance()->AddSelectList(*iter);
			}
		}
		// �巡�� �̺�Ʈ�� �������� 0���� �ʱ�ȭ��Ŵ, �巡�� ��Ʈ�� ��������
		m_iDragState = 0;
		ZeroMemory(&m_vDrag, sizeof(D3DXVECTOR2) * 5);

	}
	// ���� Ű�Է��� ������
	else if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON) && m_iDragState == 0)
	{
		// �巡�׸� �����ϸ鼭 �׸��� ������
		m_iDragState = 1;

		m_rcDrag.left = long(vMouse.x);
		m_rcDrag.top = long(vMouse.y);
	}
	else if (m_iDragState == 1)
	{
		m_rcDrag.right = long(vMouse.x);
		m_rcDrag.bottom = long(vMouse.y);

		m_vDrag[0] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.top);
		m_vDrag[1] = D3DXVECTOR2((float)m_rcDrag.right, (float)m_rcDrag.top);
		m_vDrag[2] = D3DXVECTOR2((float)m_rcDrag.right, (float)m_rcDrag.bottom);
		m_vDrag[3] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.bottom);
		m_vDrag[4] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.top);
	}
}