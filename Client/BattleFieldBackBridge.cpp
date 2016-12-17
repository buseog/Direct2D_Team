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

}

void	CBattleFieldBackBridge::Render(void)
{
	D3DXMATRIX	matTrans;
	TCHAR		szBuf[MIN_STR] = L"";

	/*m_iTileRenderX = WINCX / TILECX + 1;
	m_iTileRenderY = WINCY / (TILECY / 2) + 1;

	int iCullX, iCullY;

	for(int i = 0; i < m_iTileRenderY; ++i)
	{
		for(int j = 0; j < m_iTileRenderX; ++j)
		{
			iCullX = int(-m_vScroll.x) / TILECX;
			iCullY = int((-m_vScroll.y) / (TILECY / 2));


			int	iIndex = (i + iCullY) * TILEX + (j + iCullX);

			if(iIndex < 0 || iIndex >= TILEX * TILEY)
				continue;

			const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", m_vecTile[iIndex]->byDrawID);

			D3DXMatrixTranslation(&matTrans, 
				m_vecTile[iIndex]->vPos.x + m_vScroll.x,
				m_vecTile[iIndex]->vPos.y + m_vScroll.y,
				0.f);


			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
			CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
				NULL, &D3DXVECTOR3(TILECX / 2.f, TILECY / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}*/

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

int	CBattleFieldBackBridge::Picking(void)
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
					CCrowdMgr::GetInstance()->Clear();
					// ���� ��ŷ�� �Ʊ� ������ ���߸Ŵ����� ���ø���Ʈ�� �ִ´�
					CCrowdMgr::GetInstance()->AddSelectList(*iter);
					// �巡�װ� �ߺ����� �Է¹޴°� �������� �ٷ� ����
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

		if ((m_rcDrag.right - m_rcDrag.left) < 20 ||
			(m_rcDrag.bottom - m_rcDrag.top) < 20)
		{
			m_iDragState = 0;
			ZeroMemory(&m_vDrag, sizeof(D3DXVECTOR2) * 5);
			return -1;
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
		CCrowdMgr::GetInstance()->Clear();

		// ����Ʈ�� ��ȸ�Ѵ�
		for (list<CObj*>::iterator iter = pUnitList->begin(); iter != pUnitList->end(); ++iter)
		{
			// �簢�� ������� �ִ� ������ ��󳻱����� ���ǹ�
			if ((*iter)->GetInfo()->vPos.x + m_pObj->GetScroll().x > m_rcDrag.left &&
				(*iter)->GetInfo()->vPos.x + m_pObj->GetScroll().x < m_rcDrag.right &&
				(*iter)->GetInfo()->vPos.y + m_pObj->GetScroll().y > m_rcDrag.top &&
				(*iter)->GetInfo()->vPos.y + m_pObj->GetScroll().y < m_rcDrag.bottom)
			{
				// 10���� �̻��� ���õǸ� ������
				if (CCrowdMgr::GetInstance()->GetSelectList() >= 10)
				{
					m_iDragState = 0;
					ZeroMemory(&m_vDrag, sizeof(D3DXVECTOR2) * 5);
				}
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

	return -1;
}

void CBattleFieldBackBridge::LoadTile(const wstring& wstrPath)
{
	HANDLE  hFile = CreateFile(wstrPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;

	while(1)
	{
		TILE2*			pTile = new TILE2;

		ReadFile(hFile, pTile, sizeof(TILE2), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pTile);
			break;
		}

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);

	if (m_vecTile.empty())
	{

		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				TILE2*	pTile = new TILE2;

				float fX = float(j * TILECX) + ((i % 2) * (TILECX / 2.f));
				float fY = (float)i * (TILECY / 2.f);
				pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
				pTile->vSize = D3DXVECTOR3((float)TILECX, (float)TILECY, 0.f);
				pTile->byDrawID = 0;
				pTile->byOption = 0;

				int iIndex = i * TILEX + j;

				// ��
				if (i > 1)
					pTile->Connectlist.push_back(iIndex - TILEX * 2);

				// ��������
				if (i > 0 && j <= TILEX - 1)
					pTile->Connectlist.push_back(iIndex - TILEX + 1);

				// ������
				if (j < TILEX -2)
					pTile->Connectlist.push_back(iIndex +1);

				// ������ �Ʒ�
				if (i < TILEY - 1&& j <= TILEX - 1)
					pTile->Connectlist.push_back(iIndex + TILEX);

				// �Ʒ�
				if (i < TILEY -2)
					pTile->Connectlist.push_back(iIndex + TILEX * 2);

				// ���� �Ʒ�
				if (i < TILEY - 1 && j >= 0)
					pTile->Connectlist.push_back(iIndex + TILEX - 1);

				// ����
				if (j > 1)
					pTile->Connectlist.push_back(iIndex - 1);

				// ���� ��
				if (j >= 0 && i > 0)
					pTile->Connectlist.push_back(iIndex - TILEX);

				m_vecTile.push_back(pTile);
			}
		}
	}
}