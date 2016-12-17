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

	// 드래그값이 1이면 화면을 그리시작함.
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
	// 배틀필드 아군 유닛 리스트를 받아옴
	list<CObj*>*	plistUnit = CObjMgr::GetInstance()->GetObjList(OBJ_PLAYER);
	list<CObj*>*	plistMonster = CObjMgr::GetInstance()->GetObjList(OBJ_MONSTER);
	POINT pt;
	pt.x = (long)::GetMouse().x - (long)m_pObj->GetScroll().x;
	pt.y = (long)::GetMouse().y - (long)m_pObj->GetScroll().y;

	/////////////////////// 몬스터 피킹
	if (m_iDragState == 4)
	{
		for (list<CObj*>::iterator iter = plistMonster->begin(); iter != plistMonster->end(); ++iter)
		{
			// 마우스랑 충돌됬는지 체크
			if (PtInRect(&(*iter)->GetRect(), pt))
			{
				break;
			}
		}
		// 충돌이 안났으면 마우스를 기본으로 바꿔줌
		CSceneMgr::GetInstance()->SetMouse(L"Hand_Stand");
		m_iDragState = 0;
	}

	if (m_iDragState == 0)
	{
		// 리스트를 순회
		for (list<CObj*>::iterator iter = plistMonster->begin(); iter != plistMonster->end(); ++iter)
		{
			// 마우스랑 충돌됬는지 체크
			if (PtInRect(&(*iter)->GetRect(), pt))
			{
				m_iDragState = 4;
				// 충돌이 됬다면 마우스를 유닛핸드로 바꿔줌
				CSceneMgr::GetInstance()->SetMouse(L"Sword_Stand");

				// 충돌된상태에서 왼쪽버튼을 누르면
				if (CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON))
				{
					CSceneMgr::GetInstance()->SetMouse(L"Sword_Click");
					return;
				}
			}
		}
	}

	/////////////////////////////////////////////// 아군유닛 피킹
	if (m_iDragState == 3)
	{
		for (list<CObj*>::iterator iter = plistUnit->begin(); iter != plistUnit->end(); ++iter)
		{
			// 마우스랑 충돌됬는지 체크
			if (PtInRect(&(*iter)->GetRect(), pt))
			{
				break;
			}
		}
		// 충돌이 안났으면 마우스를 기본으로 바꿔줌
		CSceneMgr::GetInstance()->SetMouse(L"Hand_Stand");
		m_iDragState = 0;
	}

	if (m_iDragState == 0)
	{
		// 리스트를 순회
		for (list<CObj*>::iterator iter = plistUnit->begin(); iter != plistUnit->end(); ++iter)
		{
			// 마우스랑 충돌됬는지 체크
			if (PtInRect(&(*iter)->GetRect(), pt))
			{
				m_iDragState = 3;
				// 충돌이 됬다면 마우스를 유닛핸드로 바꿔줌
				CSceneMgr::GetInstance()->SetMouse(L"Hand_Unit");
				// 충돌된상태에서 왼쪽버튼을 누르면
				if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
				{
					CSceneMgr::GetInstance()->SetMouse(L"Hand_Click");
					// 군중매니저의 리스트를 비워준다
					CCrowdMgr::GetInstance()->Release();
					// 현재 피킹된 아군 유닛을 군중매니저의 선택리스트로 넣는다
					CCrowdMgr::GetInstance()->AddSelectList(*iter);
					// 드래그가 중복으로 입력받는걸 막기위해 바로 리턴
					return;
				}
			}
		}
	}

	///////////////////////////////////// 드래그기능 아군유닛선택
	D3DXVECTOR3	vMouse = ::GetMouse();

	// 버튼이 뗐을떄, 중복되는 함수방지를 위해 인덱스로 사용처를 구분함.
	if(CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON, 0) && m_iDragState == 1)
	{
		// 드래그되는 사각형을 그려주기 위한 구조체. 끝나는점을 라이트 바텀으로 설정
		m_rcDrag.right = long(vMouse.x);
		m_rcDrag.bottom = long(vMouse.y);

		// 드래그를 시작점과 반대로 했을때 예외처리
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

		// 사각형을 그려주는 5개의 점
		m_vDrag[0] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.top);
		m_vDrag[1] = D3DXVECTOR2((float)m_rcDrag.right, (float)m_rcDrag.top);
		m_vDrag[2] = D3DXVECTOR2((float)m_rcDrag.right, (float)m_rcDrag.bottom);
		m_vDrag[3] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.bottom);
		m_vDrag[4] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.top);
		
		// 배틀필드 아군 유닛리스트를 얻어온다
		list<CObj*>* pUnitList = CObjMgr::GetInstance()->GetObjList(OBJ_PLAYER);
		// 유닛리스트를 비워준다
		CCrowdMgr::GetInstance()->Release();

		// 리스트를 순회한다
		for (list<CObj*>::iterator iter = pUnitList->begin(); iter != pUnitList->end(); ++iter)
		{
			// 사각형 사이즈내에 있는 유닛을 골라내기위한 조건문
			if ((*iter)->GetInfo()->vPos.x + m_pObj->GetScroll().x > m_rcDrag.left &&
				(*iter)->GetInfo()->vPos.x + m_pObj->GetScroll().x < m_rcDrag.right &&
				(*iter)->GetInfo()->vPos.y + m_pObj->GetScroll().y > m_rcDrag.top &&
				(*iter)->GetInfo()->vPos.y + m_pObj->GetScroll().y < m_rcDrag.bottom)
			{
				// 조건에 부합하는 유닛을 선택리스트에 추가함
				CCrowdMgr::GetInstance()->AddSelectList(*iter);
			}
		}
		// 드래그 이벤트가 끝났으니 0으로 초기화시킴, 드래그 렉트도 마찬가지
		m_iDragState = 0;
		ZeroMemory(&m_vDrag, sizeof(D3DXVECTOR2) * 5);

	}
	// 왼쪽 키입력이 됬을때
	else if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON) && m_iDragState == 0)
	{
		// 드래그를 시작하면서 그리기 시작함
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