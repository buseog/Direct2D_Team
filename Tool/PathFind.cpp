// PathFind.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "PathFind.h"
#include "FileInfo.h"


// CPathFind 대화 상자입니다.

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


// CPathFind 메시지 처리기입니다.

void CPathFind::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CPathFind::OnSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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

	SaveFile.close();		// 사실 사용하지 않아도 된다.

	WinExec("notepad.exe ../Data/Path.txt", SW_SHOW);
}

void CPathFind::OnLoadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(TRUE);

	int		iFileNumber = DragQueryFile(hDropInfo, -1, NULL, 0);
	// 1인자 : 드롭된 파일 정보를 저장하는 구조체
	// 2인자 : 파일의 인덱스를 지정, -1(0xffffffff)을 지정하면 이 함수의 반환값으로 파일 개수를 반환
	// 3인자 : 취득한 파일명을 격납하는 버퍼에의 포인터를 지정
	// 4인자 : 지정한 버퍼 사이즈

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
			_itow_s((*iter)->iCount, szBuf, 10); // iter에 저장된 숫자를 10진수로 바꿔서 szBuf에 저장

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_ListBox.ResetContent();
}
