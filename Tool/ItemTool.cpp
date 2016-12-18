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


// CItemTool �޽��� ó�����Դϴ�.
void CItemTool::CheckItemType(UINT ID) 
{
	
	UpdateData(TRUE);
	ItemTypeChecked();
	UpdateData(FALSE);

}
void CItemTool::ItemTypeChecked(void)
{
	switch(m_ItemType)
	{ ///���ҽ� ����Ʈ ����

	case 0: //����
		GetDlgItem(IDC_STATICOPTION)->SetWindowText(L"���ݷ�");
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"��");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"Ȱ");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"��ä");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"����");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"â");

		break; 
	case 1: //��
		GetDlgItem(IDC_STATICOPTION)->SetWindowText(L"����");
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"����");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"�尩");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"�밥");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"��ȭ");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"�㸮��");
		break; 
	case 2: //���Ĺ�
		GetDlgItem(IDC_STATICOPTION)->SetWindowText(L"ȸ����");
		GetDlgItem(IDC_RADIOITEMDETAIL1)->SetWindowText(L"��������");
		GetDlgItem(IDC_RADIOITEMDETAIL2)->SetWindowText(L"�ܹ���");
		GetDlgItem(IDC_RADIOITEMDETAIL3)->SetWindowText(L"�ֵ���");
		GetDlgItem(IDC_RADIOITEMDETAIL4)->SetWindowText(L"�ҹ�");
		GetDlgItem(IDC_RADIOITEMDETAIL5)->SetWindowText(L"������");
		break; 
	case 3://����ǰ
		GetDlgItem(IDC_STATICOPTION)->SetWindowText(L"����");
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
	
}
BOOL CItemTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	UpdateData(TRUE);
	ItemTypeChecked();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CItemTool::AddItem()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	for(map<CString, ITEM*>::iterator	iter = m_mapItemData.begin();
		iter != m_mapItemData.end(); ++iter)
	{
		WriteFile(hFile, iter->second, sizeof(ITEM), &dwByte, NULL);
	}
	CloseHandle(hFile);
	AfxMessageBox(L"Save Complete");
	// c:\Users\Administrator\Desktop\FrameKor02\ToolKor02\ // ���� ���
	// L"..\\Data";	// ��� ���
}

void CItemTool::LoadItemSet()
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
	m_ItemList.ResetContent();	// ����Ʈ�� ����� ��� �����ϴ� �Լ�

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
	case 0://����
		{
			(*_pItem).eType=IT_WEAPON;
			break;
		}
	case 1://��
		{
			switch(m_ItemDetail)
			{
			case 0://����
				{
					(*_pItem).eType=IT_ARMOR;
					break;
				}
			case 1://�尩
				{
					(*_pItem).eType=IT_GLOVE;
					break;
				}
			case 2://�밥
				{
					(*_pItem).eType=IT_HELMET;
					break;
				}
			case 3://��ȭ
				{
					(*_pItem).eType=IT_BOOTS;
					break;
				}
			case 4://�㸮��
				{
					(*_pItem).eType=IT_BELT;
					break;
				}
			}
			break;
		}
	case 2://����
		{
			(*_pItem).eType=IT_FOOD;
			break;
		}
	case 3://����ǰ
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	//�⺻�������ͽ�
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
