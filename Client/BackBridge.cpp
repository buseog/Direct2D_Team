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
		TILE*			pTile = new TILE;
		TILE2*			pTile2 = new TILE2;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pTile);
			break;
		}

		pTile2->vPos = pTile->vPos;
		pTile2->vSize = pTile->vSize;
		pTile2->byDrawID = pTile->byDrawID;
		pTile2->byOption = pTile->byOption;

		m_vecTile.push_back(pTile2);
	}

	CloseHandle(hFile);

	
	for (int i = 0; i < m_iY; ++i)
	{
		for (int j = 0; j < m_iX; ++j)
		{
			int iIndex = i * m_iX + j;

			// 위
			if (i > 1)
				m_vecTile[iIndex]->Connectlist.push_back(iIndex - m_iX * 2);

			// 오른쪽위
			if (i > 0 && j <= m_iX - 1)
				m_vecTile[iIndex]->Connectlist.push_back(iIndex - m_iX + 1);

			// 오른쪽
			if (j < m_iX -2)
				m_vecTile[iIndex]->Connectlist.push_back(iIndex +1);

			// 오른쪽 아래
			if (i < TILEY - 1&& j <= m_iX - 1)
				m_vecTile[iIndex]->Connectlist.push_back(iIndex + m_iX);

			// 아래
			if (i < TILEY -2)
				m_vecTile[iIndex]->Connectlist.push_back(iIndex + m_iX * 2);

			// 왼쪽 아래
			if (i < TILEY - 1 && j >= 0)
				m_vecTile[iIndex]->Connectlist.push_back(iIndex + m_iX - 1);

			// 왼쪽
			if (j > 1)
				m_vecTile[iIndex]->Connectlist.push_back(iIndex - 1);

			// 왼쪽 위
			if (j >= 0 && i > 0)
				m_vecTile[iIndex]->Connectlist.push_back(iIndex - m_iX);
		}
	}
}

int	CBackBridge::Picking(void)
{
	return -1;
}

void	CBackBridge::LoadBack(const wstring&	wstrPath)
{
	
	HANDLE  hFile = CreateFile(wstrPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;

	while(1)
	{
		BACK2*			pBack = new BACK2;

		ReadFile(hFile, pBack, sizeof(BACK2), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pBack);
			break;
		}

		m_vecBack.push_back(pBack);
	}

	CloseHandle(hFile);
}

const D3DXVECTOR3* CBackBridge::GetSize(void)
{
	return &m_vSize;
}