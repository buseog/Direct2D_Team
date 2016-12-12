#pragma once


// CItemTool 대화 상자입니다.

class CItemTool : public CDialog
{
	DECLARE_DYNAMIC(CItemTool)

public:
	CItemTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CItemTool();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ITEMTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void CheckItemType(UINT ID);
	afx_msg void CheckItemDetail(UINT ID);
private:
	void ItemTypeChecked(void);
private:
	UINT m_ItemType;//라디오버튼
	UINT m_ItemDetail;
private:
	CString m_ItemName;
	int m_iATK;
	int m_iDef;
	int m_iWeight;
	int m_iHeal;
};
