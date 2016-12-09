#pragma once


// CVillageTool 대화 상자입니다.

class CVillageTool : public CDialog
{
	DECLARE_DYNAMIC(CVillageTool)

public:
	CVillageTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVillageTool();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VILLAGETOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
