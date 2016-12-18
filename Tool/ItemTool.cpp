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
, m_iOption(0)
, m_iPrice(0)
, m_iWeight(0)
//, m_iHeal(0)
{

}

CItemTool::~CItemTool()
{
	Release();
}

void CItemTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ItemName);
	DDX_Text(pDX, IDC_EDIT2, m_iOption);
	DDX_Text(pDX, IDC_EDIT3, m_iPrice);
	DDX_Text(pDX, IDC_EDIT4, m_iWeight);
	//DDX_Text(pDX, IDC_EDIT5, m_iHeal);

	DDX_Radio(pDX, IDC_RADIOITEMDETAIL1, (int&)m_ItemDetail);
	//DDX_Radio(pDX, IDC_RADIOITEMTYPE1, (int&)m_ItemType);
	DDX_Radio(pDX, IDC_RADIOITEMTYPE1,(int&)m_ItemType);

	DDX_Control(pDX, IDC_LIST1, m_ItemList);
}


BEGIN_MESSAGE_MAP(CItemTool, CDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIOITEMDETAIL1,IDC_RADIOITEMDETAIL5, CheckItemDetail)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIOITEMTYPE1,IDC_RADIOITEMTYPE4, CheckItemType)
	//ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIOITEMTYPE1, IDC_RADIOITEMTYPE4, CheckItemType)
	ON_BN_CLICKED(IDC_BUTTON1, &CItemTool::AddItem)
	ON_BN_CLICKED(IDC_BUTTON5, &CItemTool::DeleteItem)
	ON_BN_CLICKED(IDC_BUTTON10, &CItemTool::SaveItemSet)
	ON_BN_CLICKED(IDC_BUTTON11, &CItemTool::LoadItemSet)
	ON_LBN_SELCHANGE(IDC_LIST1, &CItemTool::OnSelChangeItemList)
END_MESSAGE_MAP()


// CItemTool 메시지 처리기입니다.
void CItemTool::CheckItemType(UINT ID) 
{
	
	UpdateData(TRUE);
	ItemTypeChecked();
	UpdateData(FALSE);

}
void CItemTool::ItemTypeChecked(void)
{
	switch(m_ItemType)
	{ ///리소스 리스트 갱신

	case 0: //무기
		GetDlgItem(IDC_STATICOPTION)->SetWindowText(L"공격력");
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"검");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"활");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"부채");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"염주");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"창");

		break; 
	case 1: //방어구
		GetDlgItem(IDC_STATICOPTION)->SetWindowText(L"방어력");
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"갑옷");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"장갑");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"대갈");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"장화");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"허리띠");
		break; 
	case 2: //음식물
		GetDlgItem(IDC_STATICOPTION)->SetWindowText(L"회복량");
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"돼지국밥");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"햄버거");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"핫도그");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"쌀밥");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"보리밥");
		break; 
	case 3://교역품
		GetDlgItem(IDC_STATICOPTION)->SetWindowText(L"없음");
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
	
}
BOOL CItemTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(TRUE);
	ItemTypeChecked();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CItemTool::AddItem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	ITEM* pItem = new ITEM;
	//ZeroMemory(&pItem);
	pItem->wstrName= m_ItemName.operator LPCWSTR();
	pItem->iOption=m_iOption;
	pItem->iPrice= m_iPrice;
	pItem->iWeight= m_iWeight;
	pItem->iCount=1;
	
	SetItemDetail(pItem);

	m_mapItemData.insert(make_pair(m_ItemName,pItem));
	m_ItemList.AddString(m_ItemName);
	UpdateData(FALSE);
	
}

void CItemTool::DeleteItem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString		strSelectName;
	int		iSelectName = m_ItemList.GetCurSel();
	if(iSelectName < 0)
		return;
	m_ItemList.GetText(iSelectName, strSelectName);

	map<CString, ITEM*>::iterator	iter = m_mapItemData.find(strSelectName);

	if(iter == m_mapItemData.end())
		return;

	Safe_Delete(iter->second);
	m_mapItemData.erase(strSelectName);

	m_ItemList.DeleteString(iSelectName);

	UpdateData(FALSE);
}

void CItemTool::SaveItemSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog		Dlg(FALSE,	// false - save, true - load
						L"dat", // 파일의 확장자명
						L"*.dat", // 최초에 띄워줄 파일 이름
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						L"*.dat", // 저장 시 밑에 띄워주는 파일 형식
						this);

	if(Dlg.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);	// vcproj 파일 위치를 얻어 옴
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath);	// 응용 프로그램의 현재 작업 디렉토리를 지정된 디렉토리로 바꿔주는 함수
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath);	// 파일 이름만 남기고 마지막 경로를 삭제
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	lstrcat(szDirPath, L"\\Data");
	//szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\Data"


	Dlg.m_ofn.lpstrInitialDir = szDirPath;	

	DWORD	dwByte = 0;

	HANDLE	hFile  = CreateFile(Dlg.GetPathName(), 
								GENERIC_WRITE, 
								0, 
								NULL, 
								CREATE_ALWAYS, 
								FILE_ATTRIBUTE_NORMAL, 
								NULL);

	for(map<CString, ITEM*>::iterator	iter = m_mapItemData.begin();
		iter != m_mapItemData.end(); ++iter)
	{
		WriteFile(hFile, iter->second, sizeof(ITEM), &dwByte, NULL);
	}
	CloseHandle(hFile);
	AfxMessageBox(L"Save Complete");
	// c:\Users\Administrator\Desktop\FrameKor02\ToolKor02\ // 절대 경로
	// L"..\\Data";	// 상대 경로
}

void CItemTool::LoadItemSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CFileDialog		Dlg(TRUE,	// false - save, true - load
		L"dat", // 파일의 확장자명
		L"*.dat", // 최초에 띄워줄 파일 이름
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"*.dat", // 저장 시 밑에 띄워주는 파일 형식
		this);

	if(Dlg.DoModal() == IDCANCEL)
		return;

	Release();
	m_ItemList.ResetContent();	// 리스트의 목록을 모두 삭제하는 함수

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);	// vcproj 파일 위치를 얻어 옴
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath);	// 응용 프로그램의 현재 작업 디렉토리를 지정된 디렉토리로 바꿔주는 함수
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath);	// 파일 이름만 남기고 마지막 경로를 삭제
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	lstrcat(szDirPath, L"\\Data");
	//szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\Data"


	Dlg.m_ofn.lpstrInitialDir = szDirPath;	

	DWORD	dwByte = 0;

	HANDLE	hFile  = CreateFile(Dlg.GetPathName(), 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		ITEM*			pItemData = new ITEM;
		//pUnitData->tDetail = new DETAILDATA;
		ReadFile(hFile, pItemData, sizeof(ITEM), &dwByte, NULL);

		if(dwByte == 0)
		{
			//::Safe_Delete(pUnitData->tDetail);
			::Safe_Delete(pItemData);
			break;
		}
		m_mapItemData.insert(map<CString, ITEM*>
			::value_type(pItemData->wstrName.c_str(), pItemData));

		m_ItemList.AddString(pItemData->wstrName.c_str());
	}

	CloseHandle(hFile);

	UpdateData(FALSE);
	AfxMessageBox(L"Load Complete");
}

void CItemTool::SetItemDetail(ITEM* _pItem)
{
	switch(m_ItemType)
	{
	case 0://무기
		{
			(*_pItem).eType=IT_WEAPON;
			break;
		}
	case 1://방어구
		{
			switch(m_ItemDetail)
			{
			case 0://갑옷
				{
					(*_pItem).eType=IT_ARMOR;
					break;
				}
			case 1://장갑
				{
					(*_pItem).eType=IT_GLOVE;
					break;
				}
			case 2://대갈
				{
					(*_pItem).eType=IT_HELMET;
					break;
				}
			case 3://장화
				{
					(*_pItem).eType=IT_BOOTS;
					break;
				}
			case 4://허리띠
				{
					(*_pItem).eType=IT_BELT;
					break;
				}
			}
			break;
		}
	case 2://음식
		{
			(*_pItem).eType=IT_FOOD;
			break;
		}
	case 3://교역품
		{
			(*_pItem).eType=IT_TRADE;
			break;

		}
	}
}
void CItemTool::Release(void)
{
	for_each(m_mapItemData.begin(), m_mapItemData.end(), DeleteMap());
	m_mapItemData.clear();
}
void CItemTool::OnSelChangeItemList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString		strSelectName;

	int		iSelectName = m_ItemList.GetCurSel();

	if(iSelectName < 0)
		return;

	m_ItemList.GetText(iSelectName, strSelectName);
	
	map<CString, ITEM*>::iterator	iter = m_mapItemData.find(strSelectName);

	if(iter == m_mapItemData.end())
		return;

	m_ItemName = iter->second->wstrName.c_str();
	//기본스테이터스
	m_iOption = iter->second->iOption;
	m_iPrice = iter->second->iPrice;
	m_iWeight = iter->second->iWeight;

	switch(iter->second->eType)
	{
	case IT_WEAPON:
		{
			m_ItemType=0;
			break;
		}
	case IT_ARMOR:
		{
			m_ItemType=1;
			m_ItemDetail=0;
			break;
		}
	case IT_GLOVE:
		{
			m_ItemType=1;
			m_ItemDetail=1;
			break;
		}
	case IT_HELMET:
		{
			m_ItemType=1;
			m_ItemDetail=2;
			break;
		}
	case IT_BOOTS:
		{
			m_ItemType=1;
			m_ItemDetail=3;
			break;
		}
	case IT_BELT:
		{
			m_ItemType=1;
			m_ItemDetail=4;
			break;
		}
	case IT_FOOD:
		{
			m_ItemType=2;
			break;
		}
	case IT_TRADE:
		{
			m_ItemType=3;
			break;
		}
	}
	ItemTypeChecked();


	UpdateData(FALSE);
}
