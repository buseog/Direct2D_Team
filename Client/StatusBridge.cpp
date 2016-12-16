#include "StdAfx.h"
#include "StatusBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "Obj.h"
#include "ObjMgr.h"

CStatusBridge::CStatusBridge(void)
{
}

CStatusBridge::~CStatusBridge(void)
{
		Release();

}


HRESULT CStatusBridge::Initialize(void)
{
	m_wstrStateKey = L"Status";

	return S_OK;
}

void CStatusBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
}

void CStatusBridge::Render(void)
{
	
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pUi->GetObjKey());

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMATRIX		matScale, matTrans, matWorld;

	TCHAR			m_szPrint[MIN_STR];


	const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_PLAYER);

	// 레벨
	wsprintf(m_szPrint, L"레벨 %d", pPlayer->GetPlayerStat()->tDetail.iLevel);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 8.f, m_pUi->GetInfo()->vPos.y - 42.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 공격력
	wsprintf(m_szPrint, L"공격력		%d", pPlayer->GetPlayerStat()->iAttack);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 2.f, m_pUi->GetInfo()->vPos.y - 21.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));
	
	// 방어력
	wsprintf(m_szPrint, L"방어력              %d", pPlayer->GetPlayerStat()->iDeffence);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 2.f, m_pUi->GetInfo()->vPos.y - 1.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 체력
	wsprintf(m_szPrint, L"%체력                %d", pPlayer->GetPlayerStat()->iHealthPoint);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 8.f, m_pUi->GetInfo()->vPos.y + 27.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 경험치
	wsprintf(m_szPrint, L"경험치              %d", pPlayer->GetPlayerStat()->tDetail.iExperience);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 2.f, m_pUi->GetInfo()->vPos.y + 48.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 포인트
	wsprintf(m_szPrint, L"포인트              %d", pPlayer->GetPlayerStat()->tDetail.iBonusPoint);

	D3DXMatrixScaling(&matScale, 1.2f, 1.2f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 5.f, m_pUi->GetInfo()->vPos.y + 125.f, 0.f);
	
	matWorld = matScale * matTrans;
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));


	// 무게
	wsprintf(m_szPrint, L"%d", pPlayer->GetPlayerStat()->tDetail.iExperience);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 2.f, m_pUi->GetInfo()->vPos.y + 130.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));




}

void CStatusBridge::Release(void)
{
	
}

void	CStatusBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matTrans;


	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x , 
		rInfo.vPos.y, 
		0.f);

	rInfo.matWorld = matTrans;

}


int	CStatusBridge::Picking(void)
{
	return m_iPriority;
}