// PathFind.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "PathFind.h"
#include "FileInfo.h"


// CPathFind ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPathFind, CDialog)

CPathFind::CPathFind(CWnd* pParent /*=NULL*/)
	: CDialog(CPathFind::IDD, pParent)
{

}

CPathFind::~CPathFind()
{
}

void CPathFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(CPathFind, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CPathFind::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON1, &CPathFind::OnSaveButton)
	ON_BN_CLICKED(IDC_BUTTON5, &CPathFind::OnLoadButton)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON10, &CPathFind::OnClear)
END_MESSAGE_MAP()


// CPathFind �޽��� ó�����Դϴ�.

void CPathFind::OnListBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CPathFind::OnSaveButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	wofstream		SaveFile;

	SaveFile.open(L"../Data/Path.txt", ios::out);

	int		iCount = 0;

	for(list<IMGPATH*>::iterator	iter = m_PathInfoList.begin();
		iter != m_PathInfoList.end(); ++iter)
	{
		++iCount;

		SaveFile << (*iter)->wstrObjKey.c_str() << L"|";
		SaveFile << (*iter)->wstrStateKey.c_str() << L"|";
		SaveFile << (*iter)->iCount << L"|";

		if(iCount == m_PathInfoList.size())
			SaveFile << (*iter)->wstrPath.c_str() << flush;

		else
			SaveFile << (*iter)->wstrPath.c_str() << endl;
	}

	SaveFile.close();		// ��� ������� �ʾƵ� �ȴ�.

	WinExec("notepad.exe ../Data/Path.txt", SW_SHOW);
}

void CPathFind::OnLoadButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	wifstream		LoadFile;
	LoadFile.open("../Data/Path.txt", ios::in);

	TCHAR		szObjKey[MIN_STR]	= L"";
	TCHAR		szStateKey[MIN_STR] = L"";
	TCHAR		szCount[MIN_STR]	= L"";
	TCHAR		szImgPath[MAX_PATH] = L"";

	wstring		wstrCombine = L"";
	m_ListBox.ResetContent();

	while(!LoadFile.eof())
	{
		LoadFile.getline(szObjKey, MIN_STR, '|');
		LoadFile.getline(szStateKey, MIN_STR, '|');
		LoadFile.getline(szCount, MIN_STR, '|');
		LoadFile.getline(szImgPath, MAX_PATH);

		wstrCombine = wstring(szObjKey) + L"|" + wstring(szStateKey) + L"|";
		wstrCombine += szCount;
		wstrCombine += L"|" + wstring(szImgPath);

		m_ListBox.AddString(wstrCombine.c_str());
	}

	UpdateData(FALSE);
}

void CPathFind::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(TRUE);

	int		iFileNumber = DragQueryFile(hDropInfo, -1, NULL, 0);
	// 1���� : ��ӵ� ���� ������ �����ϴ� ����ü
	// 2���� : ������ �ε����� ����, -1(0xffffffff)�� �����ϸ� �� �Լ��� ��ȯ������ ���� ������ ��ȯ
	// 3���� : ����� ���ϸ��� �ݳ��ϴ� ���ۿ��� �����͸� ����
	// 4���� : ������ ���� ������

	TCHAR	szFullPath[MAX_PATH] = L"";

	for(int i = 0; i < iFileNumber; ++i)
	{
		DragQueryFile(hDropInfo, i, (LPWSTR)szFullPath, MAX_PATH);

		CFileInfo		FileInfo;

		FileInfo.DirInfoExtraction(szFullPath, m_PathInfoList);

		wstring	wstrCombine = L"";
		TCHAR	szBuf[MIN_STR] = L"";

		for(list<IMGPATH*>::iterator	iter = m_PathInfoList.begin();
			iter != m_PathInfoList.end(); ++iter)
		{
			_itow_s((*iter)->iCount, szBuf, 10); // iter�� ����� ���ڸ� 10������ �ٲ㼭 szBuf�� ����

			wstrCombine = (*iter)->wstrObjKey + L"|" + (*iter)->wstrStateKey + L"|";
			wstrCombine += szBuf;
			wstrCombine += L"|" + (*iter)->wstrPath;

			m_ListBox.AddString(wstrCombine.c_str());
		}
	}

	UpdateData(FALSE);
}

void CPathFind::OnClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_ListBox.ResetContent();
}
