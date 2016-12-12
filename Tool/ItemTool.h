#pragma once


// CItemTool ��ȭ �����Դϴ�.

class CItemTool : public CDialog
{
	DECLARE_DYNAMIC(CItemTool)

public:
	CItemTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CItemTool();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ITEMTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void CheckItemType(UINT ID);
	afx_msg void CheckItemDetail(UINT ID);
private:
	void ItemTypeChecked(void);
private:
	UINT m_ItemType;//������ư
	UINT m_ItemDetail;
private:
	CString m_ItemName;
	int m_iATK;
	int m_iDef;
	int m_iWeight;
	int m_iHeal;
};
