#pragma once
#include "afxwin.h"
#include "MapTool.h"
#include "UnitTool.h"
#include "ItemTool.h"
#include "VillageTool.h"


// CMyForm �� ���Դϴ�.

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

private:
	CComboBox m_ToolComboList;

	CMapTool*	m_pMapTool;
	CUnitTool*	m_pUnitTool;
	CItemTool*	m_pItemTool;
	CVillageTool*	m_pVillageTool;


public:
	CMapTool*	GetMapTool(void);
	CUnitTool*	GetUnitTool(void);

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnToolComboBox();
	afx_msg void OnDestroy();
};


