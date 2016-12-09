// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"


// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitTool::IDD, pParent)
	, m_strName(_T(""))
	, m_fHp(0)
	, m_fAttack(0)
	, m_fAttackSpeed(0)
	, m_fSpeed(0)
	, m_iGold(0)
{
	
}

CUnitTool::~CUnitTool()
{
	Release();
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE1, m_Picture);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_fHp);
	DDX_Text(pDX, IDC_EDIT3, m_fAttack);
	DDX_Text(pDX, IDC_EDIT4, m_fAttackSpeed);
	DDX_Text(pDX, IDC_EDIT5, m_fSpeed);
	DDX_Text(pDX, IDC_EDIT6, m_iGold);
	DDX_Control(pDX, IDC_RADIO1, m_Class[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Class[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Class[2]);
	DDX_Control(pDX, IDC_RADIO4, m_Option[0]);
	DDX_Control(pDX, IDC_RADIO5, m_Option[1]);
	DDX_Control(pDX, IDC_LIST2, m_UnitListBox);
	DDX_Control(pDX, IDC_COMBO1, m_StageComboBox);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnPictureList)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_RADIO1, &CUnitTool::OnClassButton)
	ON_LBN_SELCHANGE(IDC_LIST2, &CUnitTool::OnListBox)
	ON_BN_CLICKED(1007, &CUnitTool::OnAddUnit)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnDeleteData)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnSaveData)
	ON_BN_CLICKED(1006, &CUnitTool::OnLoadData)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CUnitTool::OnStageComboBox)
END_MESSAGE_MAP()

void CUnitTool::Release(void)
{
	for_each(m_MapUnitData.begin(), m_MapUnitData.end(), DeleteMap());
	m_MapUnitData.clear();

	for(map<CString, CImage*>::iterator	iter = m_MapPngImage.begin();
		iter != m_MapPngImage.end(); ++iter)
	{
		iter->second->Destroy();
		Safe_Delete(iter->second);
	}
	m_MapPngImage.clear();
}


// CUnitTool 메시지 처리기입니다.


void CUnitTool::OnPictureList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString			strSelectName;

	int iSelectName = m_ListBox.GetCurSel();

	if(iSelectName < 0)
		return;

	m_ListBox.GetText(iSelectName, strSelectName);

	map<CString, CImage*>::iterator iter = m_MapPngImage.find(strSelectName);

	if(iter == m_MapPngImage.end())
		return;

	m_Picture.SetBitmap(*iter->second);

	int i = 0;

	for( i = 0; i < strSelectName.GetLength(); ++i)
	{
		if(isdigit(strSelectName[i]) != 0)
		{
			break;
		}
	}
	strSelectName.Delete(0, i);
	m_iDrawID = _tstoi(strSelectName);

	UpdateData(FALSE);
}

void CUnitTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(TRUE);

	CDialog::OnDropFiles(hDropInfo);

	int		iFileNumber = DragQueryFile(hDropInfo, -1, NULL, 0);

	TCHAR	szFullPath[MAX_PATH] = L"";

	for(int i = 0; i < iFileNumber; ++i)
	{
		DragQueryFile(hDropInfo, i, (LPWSTR)szFullPath, MAX_PATH);

		wstring wstrRelativePath = m_FileInfo.ConvertRelativePath(szFullPath);

		CString		strImageName;		
		
		strImageName = PathFindFileName(wstrRelativePath.c_str());
		PathRemoveExtension((LPWSTR)strImageName.operator LPCWSTR());

		map<CString, CImage*>::iterator iter = m_MapPngImage.find(strImageName);

		if(iter == m_MapPngImage.end())
		{
			CImage*		pPngImage = new CImage;
			pPngImage->Load(wstrRelativePath.c_str());
			m_MapPngImage.insert(map<CString, CImage*>::value_type(strImageName, pPngImage));
			m_ListBox.AddString(strImageName);
		}
	}

	UpdateData(FALSE);
}


void CUnitTool::OnClassButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CUnitTool::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString		strSelectName;

	int		iSelectName = m_UnitListBox.GetCurSel();

	if(iSelectName < 0)
		return;

	m_UnitListBox.GetText(iSelectName, strSelectName);
	
	map<CString, UNITDATA*>::iterator	iter = m_MapUnitData.find(strSelectName);

	if(iter == m_MapUnitData.end())
		return;

	m_strName		= iter->second->wstrName.c_str();            
	m_fHp			= iter->second->fHp;
	m_fAttack		= iter->second->fAttack;
	m_fAttackSpeed	= iter->second->fAttackSpeed;
	m_fSpeed		= iter->second->fSpeed;
	m_iGold			= iter->second->iGold;

	strSelectName = iter->second->wstrImage.c_str();

	map<CString, CImage*>::iterator iter2 = m_MapPngImage.find(strSelectName);

	if(iter2 == m_MapPngImage.end())
		return;

	m_Picture.SetBitmap(*iter2->second);


	for(int i = 0; i < 2; ++i)
	{
		m_Option[i].SetCheck(FALSE);
	}
	m_Option[iter->second->byOption].SetCheck(TRUE);

	

	UpdateData(FALSE);
}

void CUnitTool::OnAddUnit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString		strSelectName;

	int iSelectName = m_ListBox.GetCurSel();

	if(iSelectName < 0)
		return;

	m_ListBox.GetText(iSelectName, strSelectName);

	UNITDATA*		pUnitData = new UNITDATA;

	pUnitData->wstrName			= m_strName;
	pUnitData->fHp				= m_fHp;
	pUnitData->fAttack			= m_fAttack;
	pUnitData->fAttackSpeed		= m_fAttackSpeed;
	pUnitData->fSpeed			= m_fSpeed;
	pUnitData->iGold			= m_iGold;
	pUnitData->wstrImage		= strSelectName;

	for(int i = 0; i < 2; ++i)
	{
		if(m_Option[i].GetCheck())
		{
			pUnitData->byOption = i;
			break;
		}
	}

	m_UnitListBox.AddString(m_strName);
	m_MapUnitData.insert(make_pair(m_strName, pUnitData));

	UpdateData(FALSE);
}

void CUnitTool::OnDeleteData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString		strSelectName;

	int		iSelectName = m_UnitListBox.GetCurSel();

	if(iSelectName < 0)
		return;
	m_UnitListBox.GetText(iSelectName, strSelectName);

	map<CString, UNITDATA*>::iterator	iter = m_MapUnitData.find(strSelectName);

	if(iter == m_MapUnitData.end())
		return;

	Safe_Delete(iter->second);
	m_MapUnitData.erase(strSelectName);

	m_UnitListBox.DeleteString(iSelectName);

	UpdateData(FALSE);
}

void CUnitTool::OnSaveData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
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

	for(map<CString, UNITDATA*>::iterator	iter = m_MapUnitData.begin();
		iter != m_MapUnitData.end(); ++iter)
	{
		WriteFile(hFile, iter->second, sizeof(UNITDATA), &dwByte, NULL);
		int a = 0;
	}
	CloseHandle(hFile);

	// c:\Users\Administrator\Desktop\FrameKor02\ToolKor02\ // 절대 경로
	// L"..\\Data";	// 상대 경로.
}

void CUnitTool::OnLoadData()
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

	//Release();
	m_UnitListBox.ResetContent();	// 리스트의 목록을 모두 삭제하는 함수

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
		UNITDATA*			pUnitData = new UNITDATA;
		ReadFile(hFile, pUnitData, sizeof(UNITDATA), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pUnitData);
			break;
		}
		m_MapUnitData.insert(map<CString, UNITDATA*>
			::value_type(pUnitData->wstrName.c_str(), pUnitData));

		m_UnitListBox.AddString(pUnitData->wstrName.c_str());
	}

	CloseHandle(hFile);

	UpdateData(FALSE);
}

void CUnitTool::OnStageComboBox()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	switch(m_StageComboBox.GetCurSel())
	{
	case 0:
		m_iStage = 1;
		break;

	case 1:
		m_iStage = 2;
		break;

	case 2:
		m_iStage = 3;
		break;
	}
}

BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_StageComboBox.AddString(L"Stage1");
	m_StageComboBox.AddString(L"Stage2");
	m_StageComboBox.AddString(L"Stage3");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
