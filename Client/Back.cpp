#include "StdAfx.h"
#include "Back.h"
#include "TimeMgr.h"
#include "ObjFactory.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "CrowdMgr.h"
#include "Player.h"
#include "UnitBridge.h"

CBack::CBack(void)
: m_iTileRenderX(0)
, m_iTileRenderY(0)
, m_iDragState(0)
{
}

CBack::~CBack(void)
{
	Release();
}

HRESULT CBack::Initialize(void)
{
	LoadTile(L"../Data/map.dat");
	m_fScrollSpeed = 500.f;

	MouseLock();

	return S_OK;
}

void CBack::Progress(void)
{
	MoveScroll();
	Drag();

	if (CKeyMgr::GetInstance()->KeyDown('1'))
	{
		D3DXVECTOR3 vPos = ::GetMouse() - m_vScroll;
		CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CObjFactory<CPlayer, CUnitBridge>::CreateObj(L"Walk_1", vPos.x, vPos.y));
	}


}

void CBack::Render(void)
{
	D3DXMATRIX	matTrans;
	TCHAR		szBuf[MIN_STR] = L"";

	m_iTileRenderX = WINCX / TILECX + 1;
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

void CBack::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();

	::Safe_Delete(m_pBridge);
}

const vector<TILE2*>* CBack::GetTile(void)
{
	return &m_vecTile;
}

void CBack::LoadTile(const wstring& wstrPath)
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

				// 위
				if (i > 1)
					pTile->Connectlist.push_back(iIndex - TILEX * 2);

				// 오른쪽위
				if (i > 0 && j <= TILEX - 1)
					pTile->Connectlist.push_back(iIndex - TILEX + 1);

				// 오른쪽
				if (j < TILEX -2)
					pTile->Connectlist.push_back(iIndex +1);

				// 오른쪽 아래
				if (i < TILEY - 1&& j <= TILEX - 1)
					pTile->Connectlist.push_back(iIndex + TILEX);

				// 아래
				if (i < TILEY -2)
					pTile->Connectlist.push_back(iIndex + TILEX * 2);

				// 왼쪽 아래
				if (i < TILEY - 1 && j >= 0)
					pTile->Connectlist.push_back(iIndex + TILEX - 1);

				// 왼쪽
				if (j > 1)
					pTile->Connectlist.push_back(iIndex - 1);

				// 왼쪽 위
				if (j >= 0 && i > 0)
					pTile->Connectlist.push_back(iIndex - TILEX);

				m_vecTile.push_back(pTile);
			}
		}
	}
}

void	CBack::MoveScroll(void)
{
	D3DXVECTOR3		vMousePos = ::GetMouse();

	if(vMousePos.x < 20)
		m_vScroll.x += m_fScrollSpeed * CTimeMgr::GetInstance()->GetTime();

	if(WINCX - 20 < vMousePos.x)
		m_vScroll.x -= m_fScrollSpeed * CTimeMgr::GetInstance()->GetTime();

	if(20 > vMousePos.y)
		m_vScroll.y += m_fScrollSpeed * CTimeMgr::GetInstance()->GetTime();

	if(WINCY - 20 < vMousePos.y)
		m_vScroll.y -= m_fScrollSpeed * CTimeMgr::GetInstance()->GetTime();
}

void	CBack::MouseLock(void)
{
	RECT rc;
	GetWindowRect(g_hWnd, &rc);
	rc.left += 20;
	rc.top += 30;
	rc.right -= 20;
	rc.bottom -= 20;
	ClipCursor(&rc);
}

void	CBack::Drag(void)
{
	D3DXVECTOR3	vMouse = ::GetMouse();

	if(CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON))
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
			if ((*iter)->GetInfo()->vPos.x + m_vScroll.x > m_rcDrag.left &&
				(*iter)->GetInfo()->vPos.x + m_vScroll.x < m_rcDrag.right &&
				(*iter)->GetInfo()->vPos.y + m_vScroll.y > m_rcDrag.top &&
				(*iter)->GetInfo()->vPos.y + m_vScroll.y < m_rcDrag.bottom)
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