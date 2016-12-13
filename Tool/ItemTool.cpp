// ItemTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ItemTool.h"


// CItemTool ��ȭ �����Դϴ�.

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


// CItemTool �޽��� ó�����Դϴ�.
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
	{ ///���ҽ� ����Ʈ ����

	case 0: //����
		
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"��");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"Ȱ");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"��ä");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"����");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"â");

		break; 
	case 1: //��
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"����");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"�尩");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"�밥");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"��ȭ");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"�㸮��");
		break; 
	case 2: //���Ĺ�
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"��������");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"�ܹ���");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"�ֵ���");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"�ҹ�");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"������");
		break; 
	case 3://����ǰ
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"�Ѱ�");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"���ݽѰ�");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"�����Ѱ�");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"���ݺ�Ѱ�");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"��Ѱ�");
		break;
	}
}
void CItemTool::CheckItemDetail(UINT ID)
{
	int i=0;
}