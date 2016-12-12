// ItemTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ItemTool.h"


// CItemTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CItemTool, CDialog)

CItemTool::CItemTool(CWnd* pParent /*=NULL*/)
: CDialog(CItemTool::IDD, pParent),m_ItemType(0),m_ItemDetail(0)
{

}

CItemTool::~CItemTool()
{
}

void CItemTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Radio(pDX, IDC_RADIOITEMDETAIL1, (int&)m_ItemDetail);
	//DDX_Radio(pDX, IDC_RADIOITEMTYPE1, (int&)m_ItemType);
	DDX_Radio(pDX, IDC_RADIOITEMTYPE1,(int&)m_ItemType);
}


BEGIN_MESSAGE_MAP(CItemTool, CDialog)
	
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIOITEMDETAIL1,IDC_RADIOITEMDETAIL5, SelItemDetail)
	//ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIOITEMTYPE1,IDC_RADIOITEMTYPE4, SelItemType)

	ON_CONTROL_RANGE(BN_CLICKED,IDC_RADIOITEMTYPE1,IDC_RADIOITEMTYPE4,SelItemType)
END_MESSAGE_MAP()


// CItemTool �޽��� ó�����Դϴ�.
void CItemTool::SelItemType(UINT ID) 
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
		
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"a");

		break; 
	case 1: //��
		
		break; 
	case 2: //���Ĺ�
		
		break; 
	case 3://����ǰ
		break;
	}
}
void CItemTool::SelItemDetail(UINT ID)
{
	int i=0;
}