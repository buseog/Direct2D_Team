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
}


BEGIN_MESSAGE_MAP(CVillageTool, CDialog)
END_MESSAGE_MAP()


// CVillageTool 메시지 처리기입니다.
