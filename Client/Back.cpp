#include "StdAfx.h"
#include "Back.h"
#include "TimeMgr.h"
#include "BridgeFactory.h"

CBack::CBack(void)
: m_iTileRenderX(0)
, m_iTileRenderY(0)
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

	return S_OK;
}

void CBack::Progress(void)
{
	MoveScroll();


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
				NULL, &D3DXVECTOR3(65.f, 34.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

			// ÆùÆ®
			wsprintf(szBuf, L"%d", iIndex);
			CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
				szBuf, lstrlen(szBuf), 
				NULL, NULL, 
				D3DCOLOR_ARGB(255, 255, 255, 255));


		}
	}
}

void CBack::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();
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
}

void	CBack::MoveScroll(void)
{
	D3DXVECTOR3		vMousePos = ::GetMouse();

	if(vMousePos.x < 20)
	{
		m_vScroll.x += m_fScrollSpeed * CTimeMgr::GetInstance()->GetTime();

		if (vMousePos.x < 0)
			vMousePos.x = 3;
	}

	if(WINCX - 20 < vMousePos.x)
	{
		m_vScroll.x -= m_fScrollSpeed * CTimeMgr::GetInstance()->GetTime();

		if (vMousePos.x > WINCX)
			vMousePos.x = WINCX - 3;
	}

	if(20 > vMousePos.y)
	{
		m_vScroll.y += m_fScrollSpeed * CTimeMgr::GetInstance()->GetTime();

		if (vMousePos.y < 0)
			vMousePos.y = 3;
	}

	if(WINCY - 20 < vMousePos.y)
	{
		m_vScroll.y -= m_fScrollSpeed * CTimeMgr::GetInstance()->GetTime();

		if (vMousePos.y > WINCY)
			vMousePos.y = WINCY - 3;
	}
}
