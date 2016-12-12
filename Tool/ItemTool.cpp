// ItemTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ItemTool.h"


// CItemTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CItemTool, CDialog)

CItemTool::CItemTool(CWnd* pParent /*=NULL*/)
: CDialog(CItemTool::IDD, pParent),m_ItemType(0),m_ItemDetail(0)
, m_ItemName(_T(""))
, m_iATK(0)
, m_iDef(0)
, m_iWeight(0)
, m_iHeal(0)
{

}

CItemTool::~CItemTool()
{
}

void CItemTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ItemName);
	DDX_Text(pDX, IDC_EDIT2, m_iATK);
	DDX_Text(pDX, IDC_EDIT3, m_iDef);
	DDX_Text(pDX, IDC_EDIT4, m_iWeight);
	DDX_Text(pDX, IDC_EDIT5, m_iHeal);

	DDX_Radio(pDX, IDC_RADIOITEMDETAIL1, (int&)m_ItemDetail);
	//DDX_Radio(pDX, IDC_RADIOITEMTYPE1, (int&)m_ItemType);
	DDX_Radio(pDX, IDC_RADIOITEMTYPE1,(int&)m_ItemType);
	
}


BEGIN_MESSAGE_MAP(CItemTool, CDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIOITEMDETAIL1,IDC_RADIOITEMDETAIL5, CheckItemDetail)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIOITEMTYPE1,IDC_RADIOITEMTYPE4, CheckItemType)
	//ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIOITEMTYPE1, IDC_RADIOITEMTYPE4, CheckItemType)
END_MESSAGE_MAP()


// CItemTool 메시지 처리기입니다.
void CItemTool::CheckItemType(UINT ID) 
{
	int i=0;
	UpdateData(TRUE);
	ItemTypeChecked();
	UpdateData(FALSE);

}
void CItemTool::ItemTypeChecked(void)
{
	switch(m_ItemType)
	{ ///리소스 리스트 갱신

	case 0: //무기
		
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"검");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"활");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"부채");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"염주");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"창");

		break; 
	case 1: //방어구
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"갑옷");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"장갑");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"대갈");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"장화");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"허리띠");
		break; 
	case 2: //음식물
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"돼지국밥");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"햄버거");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"핫도그");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"쌀밥");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"보리밥");
		break; 
	case 3://교역품
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"싼거");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"조금싼거");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"적당한거");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"조금비싼거");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"비싼거");
		break;
	}
}
void CItemTool::CheckItemDetail(UINT ID)
{
	int i=0;
}