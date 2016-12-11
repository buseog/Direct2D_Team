// VillageTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "VillageTool.h"


// CVillageTool 대화 상자입니다.

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


// CVillageTool 메시지 처리기입니다.

void CVillageTool::OnCreateButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CVillageTool::OnStroeCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	int iIndex = m_VillageBox.GetCurSel();

	switch(iIndex)
	{

	case 0:
		m_strName = L"무기점";
		m_Image.Load(L"../Texture/Back/Town/Wstore/Town3.png");
		m_Picture.SetBitmap(m_Image);
		m_Image.Destroy();
		break;

	case 1:
		m_strName  = "약방";
		m_Image.Load(L"../Texture/Back/Town/Clinic/Town0.png");
		m_Picture.SetBitmap(m_Image);
		m_Image.Destroy();
		break;

	case 2:
		m_strName = "훈련소";
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