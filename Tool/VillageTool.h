#pragma once


// CVillageTool ��ȭ �����Դϴ�.

class CVillageTool : public CDialog
{
	DECLARE_DYNAMIC(CVillageTool)

public:
	CVillageTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVillageTool();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VILLAGETOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
