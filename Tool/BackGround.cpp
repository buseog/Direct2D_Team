#include "StdAfx.h"
#include "BackGround.h"
#include "TextureMgr.h"
#include "ToolView.h"
#include "KeyMgr.h"



CBackGround::CBackGround(void)
: m_pDevice(CDevice::GetInstance())
, m_pMainView(NULL)
, m_bTileCheck(false)
, m_iCountKey(0)
,m_iObjCountKey(0)
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
	m_fTransX = 1.f;
	m_fTransY = 1.f;

	return S_OK;
}

void CBackGround::Progress(void)
{

}

void CBackGround::Render(void)
{
	D3DXMATRIX	matTrans;
	TCHAR		szBuf[MIN_STR] = L"";

	const TEXINFO*	pBackTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Map", m_iCountKey);
	
	D3DXMatrixTranslation(&matTrans, 
				(float)pBackTexture->tImgInfo.Width - m_pMainView->GetScrollPos(0), (float)pBackTexture->tImgInfo.Height - m_pMainView->GetScrollPos(1), 0.f);
	
	m_pDevice->GetSprite()->SetTransform(&matTrans);
	m_pDevice->GetSprite()->Draw(pBackTexture->pTexture, 
				NULL, &D3DXVECTOR3((float)pBackTexture->tImgInfo.Width, (float)pBackTexture->tImgInfo.Height, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));


	ObjRender();

	if(m_bTileCheck)
	{
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				int	iIndex = i * TILEX + j;

				if(iIndex < 0 || iIndex >= TILEX * TILEY)
					break;

				const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", m_vecTile[iIndex]->byDrawID);


				D3DXMatrixTranslation(&matTrans, 
					m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0),
					m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1),
					0.f);

				m_pDevice->GetSprite()->SetTransform(&matTrans);
				m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
					NULL, &D3DXVECTOR3(32.f, 16.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

				// ÆùÆ®
			/*wsprintf(szBuf, L"%d", iIndex);
			m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(), 
				szBuf, lstrlen(szBuf), 
				NULL, NULL, 
				D3DCOLOR_ARGB(255, 255, 255, 255));*/
			}
		}
	}

}	

void CBackGround::MiniRender(void)
{
	D3DXMATRIX	matScale, matTrans, matWorld;

	const TEXINFO*	pBackTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Map", m_iCountKey);
	
	D3DXMatrixScaling(&matScale, 0.6f, 0.6f, 0.f);

	D3DXMatrixTranslation(&matTrans, 
				0.f, 0.f, 0.f);

	matWorld = matScale * matTrans;
	
	m_pDevice->GetSprite()->SetTransform(&matWorld);
	m_pDevice->GetSprite()->Draw(pBackTexture->pTexture, 
				NULL, NULL/*&D3DXVECTOR3(1892.f, 780.f, 0.f)*/, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
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

void CBackGround::TileChange(const D3DXVECTOR3& vPos, const int& iDrawID/*, const int& iSize, const int& iOption, const float& fAngle, const float& fMirror*/)
{
	int iIndex = GetTileIndex(vPos);

	if (iIndex < 0)
		return;

	m_vecTile[iIndex]->byDrawID = iDrawID;
	m_vecTile[iIndex]->byOption = 2;
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

void CBackGround::SetTile(float _fX, float _fY)
{
	TILEX = (int)_fX;
	TILEY = (int)_fY;
}

void CBackGround::SetTileCheck(bool _bTileCheck)
{
	m_bTileCheck = _bTileCheck;
}

bool CBackGround::GetTileCheck(void)
{
	return m_bTileCheck;
}

void CBackGround::SetCount(int _iCountKey)
{
	m_iCountKey = _iCountKey;
}

void CBackGround::SetObjCount(int _iBackCountKey)
{
	m_iBackCountKey = _iBackCountKey;
}

void CBackGround::SetObjszState(CString _szStateKey)
{
	m_szBackStateKey = _szStateKey;
}

void CBackGround::SetObjszObj(CString _szObjKey)
{
	m_szBackObjKey = _szObjKey;
}

void CBackGround::ObjPick(D3DXVECTOR3& vPos, int& iIndex, CString& szObj, CString& szState)
{
	BACK*	pBack = new BACK;

	pBack->vPos.x = ::GetMouse().x + m_pMainView->GetScrollPos(0);
	pBack->vPos.y = ::GetMouse().y + m_pMainView->GetScrollPos(1);
	pBack->iIndex = iIndex;
	pBack->szObj = szObj;
	pBack->szState = szState;

	m_vecBack.push_back(pBack);
}

void CBackGround::ObjRender(void)
{
	D3DXMATRIX	matScale, matTrans, matWorld;

	for (size_t i = 0; i < m_vecBack.size(); ++i)
	{

		const TEXINFO*	pObjTexture = CTextureMgr::GetInstance()->GetTexture(L"OBJECT", L"Object", m_vecBack[i]->iIndex);
		
		D3DXMatrixScaling(&matScale, m_fTransX, m_fTransY, 0.f);

		D3DXMatrixTranslation(&matTrans, m_vecBack[i]->vPos.x - m_pMainView->GetScrollPos(0), m_vecBack[i]->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
		
		matWorld = matScale * matTrans;

		m_pDevice->GetSprite()->SetTransform(&matWorld);
		m_pDevice->GetSprite()->Draw(pObjTexture->pTexture, 
			NULL, &D3DXVECTOR3(pObjTexture->tImgInfo.Width / 2.f, pObjTexture->tImgInfo.Height / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}


vector<TILE*>* CBackGround::GetTile(void)
{
	return &m_vecTile;
}

vector<BACK*>* CBackGround::GetObject(void)
{
	return &m_vecBack;
}

void CBackGround::SecondRender(void)
{
	D3DXMATRIX	matScale, matTrans, matWorld;

	const TEXINFO*	pObjTexture = CTextureMgr::GetInstance()->GetTexture(L"OBJECT", L"Object", (int)m_iObjCountKey);
		
	D3DXMatrixScaling(&matScale, 1.2f, 1.2f, 0.f);

	D3DXMatrixTranslation(&matTrans, 0.f, 0.f, 0.f);

	matWorld = matScale * matTrans;
		
	m_pDevice->GetSprite()->SetTransform(&matWorld);
	m_pDevice->GetSprite()->Draw(pObjTexture->pTexture, 
					NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

int CBackGround::GetObjCount(void)
{
	return m_iBackCountKey;
}

void CBackGround::SetTrans(float _TransX, float _TransY)
{
	m_fTransX = _TransX;
	m_fTransY = _TransY;
}


void CBackGround::SetObjectCount(int _iObjCountKey)
{
	m_iObjCountKey = (float)_iObjCountKey;
}

int	CBackGround::GetObjectCount(void)
{
	return (int)m_iObjCountKey;
}