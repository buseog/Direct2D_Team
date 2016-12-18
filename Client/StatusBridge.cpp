#include "StdAfx.h"
#include "StatusBridge.h"
#include "UIMgr.h"
#include "Ui.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "UIFactory.h"
#include "MyButton.h"
#include "Ui.h"
#include "ButtonBridge.h"
#include "KeyMgr.h"
#include "Player.h"

CStatusBridge::CStatusBridge(void)

{
}

CStatusBridge::~CStatusBridge(void)
{
	Release();
}

HRESULT CStatusBridge::Initialize(void)
{
	// 버튼 객체 생성

	m_vecButton.push_back(CUIFactory<CMyButton, CButtonBridge>::CreateUI(L"Button",
		m_pUi->GetInfo()->vPos.x - 22.f, m_pUi->GetInfo()->vPos.y - 37.f, 0));	
	
	m_vecButton.push_back(CUIFactory<CMyButton, CButtonBridge>::CreateUI(L"Button",
		m_pUi->GetInfo()->vPos.x - 22.f, m_pUi->GetInfo()->vPos.y + 33.f, 1));
	
	
	m_vecButton.push_back(CUIFactory<CMyButton, CButtonBridge>::CreateUI(L"Button",
		m_pUi->GetInfo()->vPos.x - 22.f, m_pUi->GetInfo()->vPos.y + 81.f, 2));

	
	m_vecButton.push_back(CUIFactory<CMyButton, CButtonBridge>::CreateUI(L"Button",
		m_pUi->GetInfo()->vPos.x - 22.f, m_pUi->GetInfo()->vPos.y + 107.f, 3));

	for (size_t i = 0; i < m_vecButton.size(); ++i)
		m_vecButton[i]->SetSize(D3DXVECTOR3(16.f, 15.f, 0.f));

	return S_OK;
} 

void CStatusBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);

}

void CStatusBridge::Render(void)
{
	
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_wstrStateKey);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width  / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pUi->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMATRIX		matScale, matTrans, matWorld;

	TCHAR			m_szPrint[MIN_STR];

///////////////////////////////////////////스텟 데이터 출력 ///////////////////////////////////////////////////////

	const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_PLAYER);

	// 아이디
	wsprintf(m_szPrint, L"%s", pPlayer->GetStat()->wstrName.c_str());

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x -120.f, m_pUi->GetInfo()->vPos.y - 172.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 레벨
	wsprintf(m_szPrint, L"Lv. %d", pPlayer->GetStat()->tDetail.iLevel);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 22.f, m_pUi->GetInfo()->vPos.y - 172.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 경험치
	wsprintf(m_szPrint, L"%d / 100", pPlayer->GetStat()->tDetail.iExperience);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 32.f, m_pUi->GetInfo()->vPos.y - 150.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 전투력
	int iBattle = (pPlayer->GetStat()->iLAttack + pPlayer->GetStat()->iSAttack + 
		pPlayer->GetStat()->tDetail.iDex + pPlayer->GetStat()->tDetail.iInt) / 3 *
		pPlayer->GetStat()->iHealthPoint / 20;
	wsprintf(m_szPrint, L"%d", iBattle);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 32.f, m_pUi->GetInfo()->vPos.y - 75.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 공격력
	wsprintf(m_szPrint, L"%d", pPlayer->GetStat()->iAttack);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 90.f, m_pUi->GetInfo()->vPos.y - 42.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));
	
	// 방어력
	wsprintf(m_szPrint, L"%d", pPlayer->GetStat()->iDeffence);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 90.f, m_pUi->GetInfo()->vPos.y - 21.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));
	
	// 무게
	wsprintf(m_szPrint, L"%d", pPlayer->GetStat()->tDetail.iExperience);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 90.f, m_pUi->GetInfo()->vPos.y, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 체력
	wsprintf(m_szPrint, L"%d", pPlayer->GetStat()->iHealthPoint);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 90.f, m_pUi->GetInfo()->vPos.y + 75.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 포인트
	wsprintf(m_szPrint, L"%d", pPlayer->GetStat()->tDetail.iBonusPoint);

	D3DXMatrixScaling(&matScale, 1.2f, 1.2f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x + 95.f, m_pUi->GetInfo()->vPos.y + 128.f, 0.f);
	
	matWorld = matScale * matTrans;
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 0, 255, 0));

	
	// 힘
	wsprintf(m_szPrint, L"%d", pPlayer->GetStat()->tDetail.iStr);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x - 60.f, m_pUi->GetInfo()->vPos.y - 42.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));


	// 민첩성
	wsprintf(m_szPrint, L"%d", pPlayer->GetStat()->tDetail.iDex);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x - 60.f, m_pUi->GetInfo()->vPos.y + 27.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	
	// 생명력
	wsprintf(m_szPrint, L"%d", pPlayer->GetStat()->tDetail.iVital);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x - 60.f, m_pUi->GetInfo()->vPos.y + 75.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 지력
	wsprintf(m_szPrint, L"%d", pPlayer->GetStat()->tDetail.iInt);

	D3DXMatrixTranslation(&matTrans, m_pUi->GetInfo()->vPos.x - 60.f, m_pUi->GetInfo()->vPos.y + 102.f, 0.f);
	
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetUIFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
		m_szPrint, 
		lstrlen(m_szPrint), 
		NULL, NULL, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 만약 보너스 포인트가 0보다 크다면
	if(pPlayer->GetStat()->tDetail.iBonusPoint > 0)
	{
		for (size_t i = 0; i < m_vecButton.size(); ++i)
		{
			const TEXINFO* pStrButtonTexture = CTextureMgr::GetInstance()->GetTexture(m_vecButton[i]->GetObjKey());

			if(pStrButtonTexture == NULL)
			return;

			D3DXMatrixTranslation(&matTrans, m_vecButton[i]->GetInfo()->vPos.x, 
				m_vecButton[i]->GetInfo()->vPos.y, 0.f);

			float fX = pStrButtonTexture->tImgInfo.Width  / 2.f;
			float fY = pStrButtonTexture->tImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
			CDevice::GetInstance()->GetSprite()->Draw(pStrButtonTexture->pTexture, 
				NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

}

void CStatusBridge::Release(void)
{
	for_each(m_vecButton.begin(), m_vecButton.end(), DeleteObj());
	m_vecButton.clear();
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
	const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_PLAYER);

	POINT	Pt;
		Pt.x = (long)GetMouse().x;
		Pt.y = (long)GetMouse().y;

	if(CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON, 1))
	{
		for(size_t i = 0; i < m_vecButton.size(); ++i)
		{
			if(PtInRect(&m_vecButton[i]->GetRect(), Pt))
			{
				int iIndex = m_vecButton[i]->GetIndexKey();

				if(pPlayer->GetStat()->tDetail.iBonusPoint > 0)
				{
					switch(iIndex)
					{
						case 0:
							((CPlayer*)pPlayer)->SetStat(iIndex);
							break;

						case 1:
							((CPlayer*)pPlayer)->SetStat(iIndex);
							break;

						case 2:
							((CPlayer*)pPlayer)->SetStat(iIndex);
							break;

						case 3:
							((CPlayer*)pPlayer)->SetStat(iIndex);
							break;
					}

					return 1;
				}
			}
		}
	}

	return -1;
}

vector<CUi*>* CStatusBridge::GetButton(void)
{
	return &m_vecButton;
}