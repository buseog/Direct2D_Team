// DlgTab2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "DlgTab2.h"


// CDlgTab2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgTab2, CDialog)

CDlgTab2::CDlgTab2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTab2::IDD, pParent)
	, m_ListBox2(0)
{

}

CDlgTab2::~CDlgTab2()
{
}

void CDlgTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTab2, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgTab2 메시지 처리기입니다.

BOOL CDlgTab2::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;
   GetClientRect(rect);
   pDC->FillSolidRect( rect, RGB(255,255,255) );

   return TRUE;
}

void CDlgTab2::ListBoxAddItem(void)
{

}

BOOL CDlgTab2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	/*CString tpath = _T("../MFC-Team/Texture/Tile");
      
	//검색 클래스
	CFileFind finder;
	      
	//CFileFind는 파일, 디렉터리가 존재하면 TRUE 를 반환함
	BOOL bWorking = finder.FindFile(tpath); //
	      
	CString fileName;
	CString DirName;
	      
	while (bWorking)
	{
			//다음 파일 / 폴더 가 존재하면다면 TRUE 반환
			bWorking = finder.FindNextFile();
			//파일 일때
			if (finder.IsArchived())
			{
					//파일의 이름
					CString _fileName =  finder.GetFileName();
	 
					// 현재폴더 상위폴더 썸네일파일은 제외
					if( _fileName == _T(".") ||
						_fileName == _T("..")||
						_fileName == _T("Thumbs.db") ) continue;
	 
					fileName =  finder.GetFileTitle();
					m_ListBox2AddString(fileName);         
					//읽어온 파일 이름을 리스트박스에 넣음
			}
			// 디렉터리 일때
			//if (finder.IsDirectory())
			//{
					// 필요하면 여기서 처리
			//DirName = finder.GetFileName();
			//}
	}*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
