// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "FileInfo.h"
#include "MainFrm.h"
// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
: CDialog(CUnitTool::IDD, pParent)
, m_strName(_T(""))
, m_iStr(0)
, m_iDex(0)
, m_iVital(0)
, m_iInt(0)
, m_iLevel(1)
, m_iAttack(0)
, m_iDeffence(0)
, m_iHealthPoint(0)
, m_iExperience(0)
, m_iBonusPoint(0)
, m_iWeight(0)
, m_fAttackSpeed(0)
, m_fMoveSpeed(0)
, m_UnitType(0) 
, m_fRange(0)
{

}

CUnitTool::~CUnitTool()
{
	Release();
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE1, m_Picture);
	DDX_Text(pDX, IDC_UNITEDIT1, m_strName);
	DDX_Text(pDX, IDC_UNITEDIT2, m_iStr);
	DDX_Text(pDX, IDC_UNITEDIT3, m_iDex);
	DDX_Text(pDX, IDC_UNITEDIT4, m_iVital);
	DDX_Text(pDX, IDC_UNITEDIT5, m_iInt);

	DDX_Text(pDX, IDC_UNITEDIT6, m_iLevel);
	DDX_Text(pDX, IDC_UNITEDIT7, m_iAttack);
	DDX_Text(pDX, IDC_UNITEDIT8, m_iDeffence);
	DDX_Text(pDX, IDC_UNITEDIT9, m_iHealthPoint);
	DDX_Text(pDX, IDC_UNITEDIT10, m_iExperience);
	DDX_Text(pDX, IDC_UNITEDIT11, m_iBonusPoint);
	DDX_Text(pDX, IDC_UNITEDIT12, m_iWeight);
	DDX_Control(pDX, IDC_UNITCHECK1, m_Caravan);
	DDX_Control(pDX, IDC_UNITCHECK2, m_BadassDMG);
	DDX_Control(pDX, IDC_UNITCHECK3, m_Tank);
	DDX_Control(pDX, IDC_UNITCHECK4, m_RapidAttack);
	DDX_Control(pDX, IDC_UNITCHECK5, m_RapidMoveSpeed);
	DDX_Control(pDX, IDC_UNITCHECK6, m_HardSkin);
	DDX_Text(pDX, IDC_UNITEDIT13, m_fAttackSpeed);
	DDX_Text(pDX, IDC_UNITEDIT14, m_fMoveSpeed);
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_UnitType);
	DDX_Control(pDX, IDC_LIST1, m_PortraitList);
	DDX_Control(pDX, IDC_LIST2, m_UnitList);
	DDX_Text(pDX, IDC_UNITEDIT15, m_fRange);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_EN_CHANGE(IDC_UNITEDIT2, &CUnitTool::OnEnChangeSTR)
	ON_EN_CHANGE(IDC_UNITEDIT3, &CUnitTool::OnEnChangeDEX)
	ON_EN_CHANGE(IDC_UNITEDIT4, &CUnitTool::OnEnChangeVITAL)
	ON_EN_CHANGE(IDC_UNITEDIT5, &CUnitTool::OnEnChangeINT)
	ON_EN_CHANGE(IDC_UNITEDIT6, &CUnitTool::OnEnChangeLEVEL)
	ON_BN_CLICKED(IDC_UNITCHECK1, &CUnitTool::OnBnClickedCheckCaravan)
	ON_BN_CLICKED(IDC_UNITCHECK2, &CUnitTool::OnBnClickedCheckBadassDMG)
	ON_BN_CLICKED(IDC_UNITCHECK3, &CUnitTool::OnBnClickedCheckTank)
	ON_BN_CLICKED(IDC_UNITCHECK4, &CUnitTool::OnBnClickedCheckRapidAttack)
	ON_BN_CLICKED(IDC_UNITCHECK5, &CUnitTool::OnBnClickedCheckRapidMoveSpeed)
	ON_BN_CLICKED(IDC_UNITCHECK6, &CUnitTool::OnBnClickedCheckHardSkin)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::AddUnit)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::DeleteUnit)
	ON_LBN_SELCHANGE(IDC_LIST2, &CUnitTool::OnLbnSelchangeAddedUnitList)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnBnClickedButtonLoad)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1,IDC_RADIO3, RadioCtrl)
	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CUnitTool::OnBnClickedButtonShowItemTool)
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.

BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	MoveWindow(0,0,1024,768);
	UpdateData(TRUE);

	//CFileInfo FileInfo;
	//CString tPath = L"../Texture/TOOL/UNITTOOL/UI21.png";

	////FileInfo.ConvertRelativePath(tPath.operator LPCWSTR());
	//pPngImage = new CImage;
	//pPngImage->Load(tPath);
	//wstring tmp =FileInfo.ConvertRelativePath(tPath.operator LPCWSTR()).c_str();
	//m_Picture.SetBitmap(*pPngImage);

	m_iStr		=m_iLevel*1;
	m_iDex		=m_iLevel*1;
	m_iVital	=m_iLevel*1;
	m_iInt		=m_iLevel*1;
	CalcAttack();
	CalcDeffence();
	CalcHealthPoint();
	CalcWeight();
	
	

	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CUnitTool::Release(void)
{
//	::Safe_Delete(pPngImage);
	for_each(m_MapUnitData.begin(), m_MapUnitData.end(), DeleteMap());
	m_MapUnitData.clear();
}
void CUnitTool::OnEnChangeSTR()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CalcAttack();
	CalcWeight();
	UpdateData(FALSE);
}

void CUnitTool::OnEnChangeDEX()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CalcAttack();
	CalcDeffence();
	UpdateData(FALSE);
}

void CUnitTool::OnEnChangeVITAL()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CalcHealthPoint();
	UpdateData(FALSE);
}

void CUnitTool::OnEnChangeINT()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CalcAttack();
	UpdateData(FALSE);
}

void CUnitTool::OnEnChangeLEVEL()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_iStr=m_iLevel*2;
	m_iDex=m_iLevel*2;
	m_iVital=m_iLevel*2;
	m_iInt=m_iLevel*2;


	CalcAttack();
	CalcDeffence();
	CalcHealthPoint();
	CalcWeight();
	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedCheckCaravan()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CalcWeight();
	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedCheckBadassDMG()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CalcAttack();
	UpdateData(FALSE);
}

void CUnitTool::OnBnClickedCheckTank()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CalcHealthPoint();
	UpdateData(FALSE);
}

void CUnitTool::OnBnClickedCheckRapidAttack()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CUnitTool::OnBnClickedCheckRapidMoveSpeed()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CUnitTool::OnBnClickedCheckHardSkin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CalcDeffence();
	UpdateData(FALSE);
}


void CUnitTool::CalcWeight(void)
{
	if(m_Caravan.GetCheck())
	{
		m_iWeight = m_iStr*20;
	}
	else
	{
		m_iWeight = m_iStr*10;
	}
}

void CUnitTool::CalcAttack(void)
{

	if(m_BadassDMG.GetCheck())
	{
		m_iAttack = ((m_iStr*2)+(m_iInt*2)+(m_iDex*1))*2;
	}
	else
	{
		m_iAttack = (m_iStr*2)+(m_iInt*2)+(m_iDex*1);
	}
}
void CUnitTool::CalcDeffence(void)
{

	if(m_HardSkin.GetCheck())
	{
		m_iDeffence= ((m_iDex*2)+(m_iStr*1))*2;
	}
	else
	{
		m_iDeffence= (m_iDex*2)+(m_iStr*1);
	}
}
void CUnitTool::CalcHealthPoint(void)
{

	if(m_Tank.GetCheck())
	{
		m_iHealthPoint = ((m_iVital*10)+(m_iLevel*5))*2;
	}
	else
	{
		m_iHealthPoint = (m_iVital*10)+(m_iLevel*5);
	}
}
void CUnitTool::CalcAttackSpeed(void)
{
}
void CUnitTool::CalcMoveSpeed(void)
{
}
void CUnitTool::RadioCtrl(UINT ID) 
{

	UpdateData(TRUE);
	SetRadioAction();
	UpdateData(FALSE);

}
void CUnitTool::AddUnit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	UNITDATA*		pUnitData = new UNITDATA;
//	pUnitData->tDetail= new DETAILDATA;
	pUnitData->wstrName = m_strName.operator LPCWSTR();
	pUnitData->tDetail.iStr = m_iStr;
	pUnitData->tDetail.iDex = m_iDex;
	pUnitData->tDetail.iVital = m_iVital;
	pUnitData->tDetail.iInt = m_iInt;
	pUnitData->tDetail.iLevel = m_iLevel;
	pUnitData->iAttack = m_iAttack;
	pUnitData->iDeffence = m_iDeffence;
	pUnitData->iHealthPoint = m_iHealthPoint;
	pUnitData->tDetail.iExperience = m_iExperience;
	pUnitData->tDetail.iBonusPoint = m_iBonusPoint;
	pUnitData->tDetail.iWeight = m_iWeight;
	pUnitData->fAttackSpeed = m_fAttackSpeed;
	pUnitData->fMoveSpeed = m_fMoveSpeed;
	pUnitData->fRange = m_fRange;

	pUnitData->tDetail.bCaravan = m_Caravan.GetCheck();;
	pUnitData->tDetail.bRapidAttack = m_RapidAttack.GetCheck();
	pUnitData->tDetail.bRapidMoveSpeed = m_RapidMoveSpeed.GetCheck();
	pUnitData->tDetail.bHardSkin = m_HardSkin.GetCheck();
	pUnitData->tDetail.bBadassDMG = m_BadassDMG.GetCheck();
	pUnitData->tDetail.bTank = m_Tank.GetCheck();

	pUnitData->tDetail.UnitType = m_UnitType;
	
	m_UnitList.AddString(pUnitData->wstrName.c_str());
	m_MapUnitData.insert(make_pair(m_strName,pUnitData));

	UpdateData(FALSE);
}
void CUnitTool::DeleteUnit()
{
	UpdateData(TRUE);

	CString		strSelectName;
	int		iSelectName = m_UnitList.GetCurSel();
	if(iSelectName < 0)
		return;
	m_UnitList.GetText(iSelectName, strSelectName);

	map<CString, UNITDATA*>::iterator	iter = m_MapUnitData.find(strSelectName);

	if(iter == m_MapUnitData.end())
		return;

	Safe_Delete(iter->second);
	m_MapUnitData.erase(strSelectName);

	m_UnitList.DeleteString(iSelectName);

	UpdateData(FALSE);
}

void CUnitTool::OnLbnSelchangeAddedUnitList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//m_UnitList.GetCurSel();

	UpdateData(TRUE);

	CString		strSelectName;

	int		iSelectName = m_UnitList.GetCurSel();

	if(iSelectName < 0)
		return;

	m_UnitList.GetText(iSelectName, strSelectName);
	
	map<CString, UNITDATA*>::iterator	iter = m_MapUnitData.find(strSelectName);

	if(iter == m_MapUnitData.end())
		return;

	m_strName = iter->second->wstrName.c_str();
	//�⺻�������ͽ�
	m_iStr = iter->second->tDetail.iStr;
	m_iDex = iter->second->tDetail.iDex;
	m_iVital = iter->second->tDetail.iVital;
	m_iInt = iter->second->tDetail.iInt;
	/////�����������ͽ�
	m_iAttack = iter->second->iAttack;
	m_iHealthPoint     = iter->second->iHealthPoint;
	m_iDeffence	  = iter->second->iDeffence;
	m_iLevel = iter->second->tDetail.iLevel;
	m_iExperience = iter->second->tDetail.iExperience;
	m_iBonusPoint = iter->second->tDetail.iBonusPoint;
	m_iWeight = iter->second->tDetail.iWeight;
	m_fAttackSpeed = iter->second->fAttackSpeed;
	m_fMoveSpeed = iter->second->fMoveSpeed;
	m_fRange = iter->second->fRange;
	/////�Ӽ� üũ�ڽ�
	m_Caravan.SetCheck(iter->second->tDetail.bCaravan);
	m_RapidMoveSpeed.SetCheck(iter->second->tDetail.bRapidMoveSpeed);
	m_HardSkin.SetCheck(iter->second->tDetail.bHardSkin);
	m_BadassDMG.SetCheck(iter->second->tDetail.bBadassDMG);
	m_Tank.SetCheck(iter->second->tDetail.bTank);
	//����Ÿ�� �����ڽ�
	m_UnitType = iter->second->tDetail.UnitType;
	SetRadioAction();
	

	UpdateData(FALSE);
}
void CUnitTool::SetRadioAction(void)
{
	switch(m_UnitType)
	{ ///���ҽ� ����Ʈ ����

	case 0: 
		//	m_PortraitList.AddString(L"1");

		break; 
	case 1:
		//m_PortraitList.AddString(L"2");
		break; 
	case 2:
		//m_PortraitList.AddString(L"3");
		break; 
	}
}

void CUnitTool::OnBnClickedButtonSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog		Dlg(FALSE,	// false - save, true - load
						L"dat", // ������ Ȯ���ڸ�
						L"*.dat", // ���ʿ� ����� ���� �̸�
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						L"*.dat", // ���� �� �ؿ� ����ִ� ���� ����
						this);

	if(Dlg.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);	// vcproj ���� ��ġ�� ��� ��
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath);	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �ٲ��ִ� �Լ�
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath);	// ���� �̸��� ����� ������ ��θ� ����
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
	}
	CloseHandle(hFile);

	// c:\Users\Administrator\Desktop\FrameKor02\ToolKor02\ // ���� ���
	// L"..\\Data";	// ��� ���
}

void CUnitTool::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		UpdateData(TRUE);

	CFileDialog		Dlg(TRUE,	// false - save, true - load
		L"dat", // ������ Ȯ���ڸ�
		L"*.dat", // ���ʿ� ����� ���� �̸�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"*.dat", // ���� �� �ؿ� ����ִ� ���� ����
		this);

	if(Dlg.DoModal() == IDCANCEL)
		return;

	Release();
	m_UnitList.ResetContent();	// ����Ʈ�� ����� ��� �����ϴ� �Լ�

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);	// vcproj ���� ��ġ�� ��� ��
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath);	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �ٲ��ִ� �Լ�
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath);	// ���� �̸��� ����� ������ ��θ� ����
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
		//pUnitData->tDetail = new DETAILDATA;
		ReadFile(hFile, pUnitData, sizeof(UNITDATA), &dwByte, NULL);

		if(dwByte == 0)
		{
			//::Safe_Delete(pUnitData->tDetail);
			::Safe_Delete(pUnitData);
			break;
		}
		m_MapUnitData.insert(map<CString, UNITDATA*>
			::value_type(pUnitData->wstrName.c_str(), pUnitData));

		m_UnitList.AddString(pUnitData->wstrName.c_str());
	}

	CloseHandle(hFile);

	UpdateData(FALSE);
}
void CUnitTool::test(CString _Path)
{
	m_PortraitList.ResetContent();
	CString tpath=_Path+L"/*.*";// =L"../Texture/*.*";
	
	CFileFind finder;
	//CFileFind�� ����, ���͸��� �����ϸ� TRUE �� ��ȯ��
	BOOL bWorking = finder.FindFile(tpath); //

	CString fileName;
	CString DirName;

	while (bWorking)
	{
		//���� ���� / ���� �� �����ϸ�ٸ� TRUE ��ȯ
		bWorking = finder.FindNextFile();
		//���� �϶�
		if(finder.IsDirectory())
		{
			DirName = finder.GetFileName();
			if( DirName == _T(".") || 
				DirName == _T("..")|| 
				DirName == _T("Thumbs.db") ) continue;
			keylist.push_back(DirName);
			mapTest.insert(map<CString,CString>::value_type(DirName,finder.GetFilePath()));
			CString Path = _Path +L"/"+DirName;
			test(Path);
		}
		if (finder.IsArchived())
		{
			fileName = finder.GetFileName();
			
			if( fileName == _T(".") || 
				fileName == _T("..")|| 
				fileName == _T("Thumbs.db") ) continue;
			CString Path = finder.GetFilePath();
			addrlist.push_back(Path);

		}

	}

}
void CUnitTool::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	test(L"../Texture");
}

void CUnitTool::OnBnClickedButtonShowItemTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//((*CMainFrame)AfxGetMainWnd())->
	//((CMainFrame*)AfxGetMainWnd())->GetForm()->GetItemTool();
	if(((CMainFrame*)AfxGetMainWnd())->GetForm()->GetItemTool()->GetSafeHwnd() == NULL)
	{
		//m_pUnitTool = new CUnitTool;
		((CMainFrame*)AfxGetMainWnd())->GetForm()->GetItemTool()->Create(IDD_ITEMTOOL);
	}

	((CMainFrame*)AfxGetMainWnd())->GetForm()->GetItemTool()->ShowWindow(SW_SHOW);
}
