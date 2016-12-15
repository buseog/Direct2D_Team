
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

#include "ToolView.h"
#include "MiniView.h"
#include "MyForm.h"
#include "SecondForm.h"
#include "SecondMini.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:
	CSplitterWnd			m_MainSplitter;
	CSplitterWnd			m_SecondSplitter;
	CSplitterWnd			m_ThirdSplitter; // ���� �߰�

// �۾��Դϴ�.
private:
	CToolView*				m_pMainView;
	CMiniView*				m_pMiniView;
	CMyForm*				m_pMyForm;
	CSecondForm*			m_pSecondForm; // ���� �߰�
	CSecondMini*			m_pSecondMini; // ���� �߰�

public:
	CToolView*		GetMainView(void);
	CMiniView*		GetMiniView(void);
	CMyForm*		GetForm(void);
	CSecondForm*	GetSecondForm(void); // ���� �߰�
	CSecondMini*	GetSecondMini(void); // ���� �߰�

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


