#pragma once
#include "afxwin.h"
#include "FileInfo.h"

// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_UNITTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public: //value
	CString m_strName;
	float m_fHp;
	float m_fAttack;
	float m_fAttackSpeed;
	float m_fSpeed;
	int m_iGold;

public: // user
	CFileInfo					m_FileInfo;

	map<CString, CImage*>		m_MapPngImage;
	map<CString, UNITDATA*>     m_MapUnitData;

	int							m_iDrawID;
	int							m_iStage;

public:
	void	Release(void);
	
public: // control
	CListBox					m_UnitListBox;
	CListBox					m_ListBox;
	CStatic						m_Picture;
	CComboBox					m_StageComboBox;

	CButton						m_Option[2];
	CButton						m_Class[3];
public:

	afx_msg void OnPictureList();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	
	
	afx_msg void OnClassButton();
	afx_msg void OnListBox();
	afx_msg void OnAddUnit();
	
	afx_msg void OnDeleteData();
	afx_msg void OnSaveData();
	afx_msg void OnLoadData();
	afx_msg void OnStageComboBox();
	
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
};
