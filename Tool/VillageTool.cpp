// VillageTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "VillageTool.h"


// CVillageTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CVillageTool, CDialog)

CVillageTool::CVillageTool(CWnd* pParent /*=NULL*/)
	: CDialog(CVillageTool::IDD, pParent)
{

}

CVillageTool::~CVillageTool()
{
	
}

void CVillageTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_COMBO1, m_VillageBox);
}


BEGIN_MESSAGE_MAP(CVillageTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CVillageTool::OnCreateButton)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CVillageTool::OnStroeCombo)
END_MESSAGE_MAP()


// CVillageTool �޽��� ó�����Դϴ�.

void CVillageTool::OnCreateButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CVillageTool::OnStroeCombo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	int iIndex = m_VillageBox.GetCurSel();

	switch(iIndex)
	{

	case 0:
		m_strName = L"������";
		m_Image.Load(L"../Texture/Back/Town/Wstore/Town3.png");
		m_Picture.SetBitmap(m_Image);
		m_Image.Destroy();
		break;

	case 1:
		m_strName  = "���";
		m_Image.Load(L"../Texture/Back/Town/Clinic/Town0.png");
		m_Picture.SetBitmap(m_Image);
		m_Image.Destroy();
		break;

	case 2:
		m_strName = "�Ʒü�";
		m_Image.Load(L"../Texture/Back/Town/GBarrack/Town0.png");
		m_Picture.SetBitmap(m_Image);
		m_Image.Destroy();
		break;


	}	
	
	UpdateData(FALSE);
}

void CVillageTool::Release(void)
{


}