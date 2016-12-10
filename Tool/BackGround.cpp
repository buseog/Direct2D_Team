#include "StdAfx.h"
#include "BackGround.h"
#include "TextureMgr.h"
#include "ToolView.h"

CBackGround::CBackGround(void)
: m_pDevice(CDevice::GetInstance())
, m_pMainView(NULL)
{
}

CBackGround::~CBackGround(void)
{
	Release();
}

HRESULT CBackGround::Initialize(void)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			TILE*	pTile = new TILE;

			float fX = float(j * TILECX) + ((i % 2) * (TILECX / 2.f));
			float fY = (float)i * (TILECY / 2.f);
			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize = D3DXVECTOR3((float)TILECX, (float)TILECY, 0.f);
			pTile->byDrawID = 0;
			pTile->byOption = 0;

			m_vecTile.push_back(pTile);
		}
	}



	return S_OK;
}

void CBackGround::Progress(void)
{

}

void CBackGround::Render(void)
{
	D3DXMATRIX	matTrans;
	TCHAR		szBuf[MIN_STR] = L"";

	int iCountY = WINCY / TILECY + 1;
	int iCountX = WINCX / TILECX + 1;

	for (int i = 0; i < iCountY; ++i)
	{
		for (int j = 0; j < iCountX; ++j)
		{
			int iCullX = (m_pMainView->GetScrollPos(0)) / TILECX;
			int iCullY = (m_pMainView->GetScrollPos(1)) / TILECY;

			int iIndex = (i + iCullY) * TILEX + (j + iCullX);

			if(iIndex < 0 || iIndex >= TILEX * TILEY)
				break;

			const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", m_vecTile[iIndex]->byDrawID);

			D3DXMatrixTranslation(&matTrans, 
				m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0),
				m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1),
				0.f);

			m_pDevice->GetSprite()->SetTransform(&matTrans);

			m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
				NULL, &D3DXVECTOR3(62.f, 32.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

			// ÆùÆ® 
			/*wsprintf(szBuf, L"%d", iIndex);
			m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(), 
				szBuf, lstrlen(szBuf), 
				NULL, NULL, 
				D3DCOLOR_ARGB(255, 255, 255, 255));*/

		}
	}
}	

void CBackGround::MiniRender(void)
{
	D3DXMATRIX	matTrans;

	for(int i = 0; i < TILEY; ++i)
	{
		for(int j = 0; j < TILEX; ++j)
		{
			int	iIndex = i * TILEX + j;

			const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", m_vecTile[iIndex]->byDrawID);

			D3DXMatrixTranslation(&matTrans, 
				m_vecTile[iIndex]->vPos.x,
				m_vecTile[iIndex]->vPos.y,
				0.f);

			m_pDevice->GetSprite()->SetTransform(&matTrans);
			m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
				NULL, &D3DXVECTOR3(62.f, 32.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}
}

void CBackGround::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();

	for_each(m_vecAction.begin(), m_vecAction.end(), DeleteObj());
	m_vecAction.clear();
}

void CBackGround::SetMainView(CToolView* pMainView)
{
	m_pMainView = pMainView;
}

void CBackGround::TileChange(const D3DXVECTOR3& vPos, const int& iDrawID, const int& iSize, const int& iOption, const float& fAngle, const float& fMirror)
{
	int iIndex = GetTileIndex(vPos);

	if (iIndex < 0)
		return;

	for (int i = 0; i < iSize; ++i)
	{
		for (int j = 0; j < iSize; ++j)
		{
			int iNum = iIndex + (i * TILEX) + j;

			if (iNum < 0 || iNum > TILEX * TILEY)
				break;

			m_vecTile[iNum]->byDrawID = iDrawID;
			m_vecTile[iNum]->byOption = iOption;
		}
	}
}
int CBackGround::GetTileIndex(const D3DXVECTOR3& vPos)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if (Picking(vPos, i))
			return i;
	}

	return false;
}

//bool CBackGround::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
//{
//	//y = ax + b
//	float fGradient = (TILECY / 2.f) / (TILECX / 2.f);
//
//	D3DXVECTOR3	vPoint[4] =
//	{
//		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILECY / 2.f, 0.f),
//		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX / 2.f, m_vecTile[iIndex]->vPos.y, 0.f),
//		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILECY / 2.f, 0.f),
//		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX / 2.f, m_vecTile[iIndex]->vPos.y, 0.f),
//	};
//
//	//b = y - ax;
//	float fB[4] = 
//	{
//		vPoint[0].y - fGradient * vPoint[0].x,
//		vPoint[1].y + fGradient * vPoint[1].x,
//		vPoint[2].y - fGradient * vPoint[2].x,
//		vPoint[3].y + fGradient * vPoint[3].x,
//
//	};
//	
//	//y - ax -b
//	if (vPos.y - fGradient * vPos.x - fB[0] > 0 &&
//		vPos.y + fGradient * vPos.x - fB[1] < 0 &&
//		vPos.y - fGradient * vPos.x - fB[2] < 0 &&
//		vPos.y + fGradient * vPos.x - fB[3] > 0)
//	{
//		return true;
//	}
//
//
//	return false;
//}

bool CBackGround::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
{
	D3DXVECTOR3	vPoint[4] =
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILECY / 2.f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX / 2.f, m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILECY / 2.f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX / 2.f, m_vecTile[iIndex]->vPos.y, 0.f),
	};

	D3DXVECTOR3 vDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	D3DXVECTOR3 vNormal[4] = 
	{
		D3DXVECTOR3(vDir[0].y, -vDir[0].x, 0.f),
		D3DXVECTOR3(vDir[1].y, -vDir[1].x, 0.f),
		D3DXVECTOR3(vDir[2].y, -vDir[2].x, 0.f),
		D3DXVECTOR3(vDir[3].y, -vDir[3].x, 0.f)
	};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	for (int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3	vTemp = vPos - vPoint[i];
		D3DXVec3Normalize(&vTemp, &vTemp);

		float fDot = D3DXVec3Dot(&vTemp, &vNormal[i]);

		if (fDot > 0.f)
			return false;
	}


	return true;
}

void CBackGround::ReturnAction(void)
{
	if (m_vecAction.size())
	{
		m_vecTile[m_vecAction.back()->iIndex]->byDrawID = m_vecAction.back()->iPrevdraw;
		m_vecTile[m_vecAction.back()->iIndex]->byOption = m_vecAction.back()->iPrevOption;

		vector<TILE_ACTION*>::iterator iter = --m_vecAction.end();
		::Safe_Delete(*iter);
		m_vecAction.pop_back();
	}
}