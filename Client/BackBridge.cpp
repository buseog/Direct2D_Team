#include "StdAfx.h"
#include "BackBridge.h"

CBackBridge::CBackBridge(void)
{
}

CBackBridge::~CBackBridge(void)
{
}


HRESULT	CBackBridge::Initialize(void)
{

	return S_OK;
}

void	CBackBridge::Progress(INFO& rInfo)
{

}

void	CBackBridge::Render(void)
{

}

void	CBackBridge::Release(void)
{

}

const vector<TILE2*>* CBackBridge::GetTile(void)
{
	return &m_vecTile;
}


void CBackBridge::LoadTile(const wstring& wstrPath)
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