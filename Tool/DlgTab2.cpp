// DlgTab2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "DlgTab2.h"


// CDlgTab2 ��ȭ �����Դϴ�.

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


// CDlgTab2 �޽��� ó�����Դϴ�.

BOOL CDlgTab2::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	/*CString tpath = _T("../MFC-Team/Texture/Tile");
      
	//�˻� Ŭ����
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
			if (finder.IsArchived())
			{
					//������ �̸�
					CString _fileName =  finder.GetFileName();
	 
					// �������� �������� ����������� ����
					if( _fileName == _T(".") ||
						_fileName == _T("..")||
						_fileName == _T("Thumbs.db") ) continue;
	 
					fileName =  finder.GetFileTitle();
					m_ListBox2AddString(fileName);         
					//�о�� ���� �̸��� ����Ʈ�ڽ��� ����
			}
			// ���͸� �϶�
			//if (finder.IsDirectory())
			//{
					// �ʿ��ϸ� ���⼭ ó��
			//DirName = finder.GetFileName();
			//}
	}*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
