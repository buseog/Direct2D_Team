#pragma once
#include "afxwin.h"
#include "UnitTool.h"
#include "ItemTool.h"
#include "VillageTool.h"

#include "DlgTab1.h"
#include "DlgTab2.h"
#include "DlgTab3.h"
#include "afxcmn.h"
#include "PathFind.h"


// CMyForm 폼 뷰입니다.
class CMainFrm;
class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyForm();

public:
	enum { IDD = IDD_MYFORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public: // 탭 관련 변수
	CTabCtrl	m_TabCtrl;
	CDlgTab1	m_DlgTab1;
	CDlgTab2	m_DlgTab2;
	CDlgTab3	m_DlgTab3;
	CUnitTool	m_UnitTool;
	CItemTool	m_ItemTool;

public:
	CItemTool* GetItemTool(void);

public:
	virtual void OnInitialUpdate();


public: // 타일 개수 변경
	CBackGround*	m_pBack;
	float m_TileY;
	float m_TileX;
	afx_msg void OnClickButton();

public:	// 패스 파인더 임시
	afx_msg void OnPathFind();
	CPathFind	m_PathFind;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

public: // 유닛 
	afx_msg void OnUnitTool();

};


