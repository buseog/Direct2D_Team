#pragma once
#include "afxwin.h"


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
	void SetItemDetail(ITEM* _pItem);
	void Release(void);
private:
	UINT m_ItemType;//������ư
	UINT m_ItemDetail;
private:
	CString m_ItemName;
	int m_iOption;
	int m_iPrice;
	int m_iWeight;
	
	//list<ITEM*> m_ItemList;
	map<CString,ITEM*> m_mapItemData;
	//int m_iHeal;
public:
	virtual BOOL OnInitDialog();
private:
	CListBox m_ItemList;
public:
	afx_msg void AddItem();
	afx_msg void DeleteItem();
	afx_msg void SaveItemSet();
	afx_msg void LoadItemSet();
	afx_msg void OnSelChangeItemList();
};
