// ItemTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ItemTool.h"


// CItemTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CItemTool, CDialog)

CItemTool::CItemTool(CWnd* pParent /*=NULL*/)
	: CDialog(CItemTool::IDD, pParent)
{

}

CItemTool::~CItemTool()
{
}

void CItemTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CItemTool, CDialog)
END_MESSAGE_MAP()


// CItemTool �޽��� ó�����Դϴ�.
