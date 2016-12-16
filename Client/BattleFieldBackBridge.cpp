#include "StdAfx.h"
#include "BattleFieldBackBridge.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "CrowdMgr.h"

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
	LoadTile(L"../Data/map.dat");

	return S_OK;
}

void	CBattleFieldBackBridge::Progress(INFO& rInfo)
{
	Drag();
}

void	CBattleFieldBackBridge::Render(void)
{
	D3DXMATRIX	matTrans;
	TCHAR		szBuf[MIN_STR] = L"";

	int RenderX = WINCX / TILECX + 1;
	int RenderY = WINCY / (TILECY / 2) + 1;

	int iCullX, iCullY;

	for(int i = 0; i < RenderY; ++i)
	{
		for(int j = 0; j < RenderX; ++j)
		{
			iCullX = int(-m_pObj->GetScroll().x) / TILECX;
			iCullY = int(-m_pObj->GetScroll().y) / (TILECY / 2);


			int	iIndex = (i + iCullY) * TILEX + (j + iCullX);

			if(iIndex < 0 || iIndex >= TILEX * TILEY)
				continue;

			const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", m_vecTile[iIndex]->byDrawID);

			D3DXMatrixTranslation(&matTrans, 
				m_vecTile[iIndex]->vPos.x + m_pObj->GetScroll().x,
				m_vecTile[iIndex]->vPos.y + m_pObj->GetScroll().y,
				0.f);


			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
			CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
				NULL, &D3DXVECTOR3(TILECX / 2.f, TILECY / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}

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


void	CBattleFieldBackBridge::Drag(void)
{
	D3DXVECTOR3	vMouse = ::GetMouse();

	if(CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON, 0))
	{
		m_rcDrag.right = long(vMouse.x);
		m_rcDrag.bottom = long(vMouse.y);

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

		m_vDrag[0] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.top);
		m_vDrag[1] = D3DXVECTOR2((float)m_rcDrag.right, (float)m_rcDrag.top);
		m_vDrag[2] = D3DXVECTOR2((float)m_rcDrag.right, (float)m_rcDrag.bottom);
		m_vDrag[3] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.bottom);
		m_vDrag[4] = D3DXVECTOR2((float)m_rcDrag.left, (float)m_rcDrag.top);
		
		list<CObj*>* pUnitList = CObjMgr::GetInstance()->GetObjList(OBJ_PLAYER);
		CCrowdMgr::GetInstance()->Release();

		for (list<CObj*>::iterator iter = pUnitList->begin(); iter != pUnitList->end(); ++iter)
		{
			if ((*iter)->GetInfo()->vPos.x + m_pObj->GetScroll().x > m_rcDrag.left &&
				(*iter)->GetInfo()->vPos.x + m_pObj->GetScroll().x < m_rcDrag.right &&
				(*iter)->GetInfo()->vPos.y + m_pObj->GetScroll().y > m_rcDrag.top &&
				(*iter)->GetInfo()->vPos.y + m_pObj->GetScroll().y < m_rcDrag.bottom)
			{
				(*iter)->SetSelect(true);
				CCrowdMgr::GetInstance()->GetSelectList()->push_back(*iter);
			}
		}
		m_iDragState = 0;
		ZeroMemory(&m_vDrag, sizeof(D3DXVECTOR2) * 5);

	}
	else if (CKeyMgr::GetInstance()->StayKeyDown(VK_LBUTTON) && m_iDragState == 0)
	{
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