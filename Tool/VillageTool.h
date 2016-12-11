#pragma once
#include "afxwin.h"


// CVillageTool ��ȭ �����Դϴ�.

class CVillageTool : public CDialog
{
	DECLARE_DYNAMIC(CVillageTool)


public:
	void	Release(void);


public:
	CVillageTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVillageTool();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VILLAGETOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CImage		m_Image;		// PNG ���� �ҷ����� ���� �������
	CStatic		m_Picture;		// ������Ʈ�� ����
	CString		m_strName;		// �����̸� ������ �������
	CComboBox	m_VillageBox;	// �޺��ڽ� ����
	
	afx_msg void OnCreateButton();
	afx_msg void OnStroeCombo();
};
