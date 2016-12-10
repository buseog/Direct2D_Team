#pragma once
#include "afxwin.h"


// CVillageTool 대화 상자입니다.

class CVillageTool : public CDialog
{
	DECLARE_DYNAMIC(CVillageTool)


public:
	void	Release(void);


public:
	CVillageTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVillageTool();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VILLAGETOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CImage		m_Image;		// PNG 파일 불러오기 위한 멤버변수
	CStatic		m_Picture;		// 픽쳐컨트롤 변수
	CString		m_strName;		// 상점이름 구분할 멤버변수
	CComboBox	m_VillageBox;	// 콤보박스 변수
	
	afx_msg void OnCreateButton();
	afx_msg void OnStroeCombo();
};
