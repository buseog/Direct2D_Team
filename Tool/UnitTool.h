#pragma once
#include "afxwin.h"


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
private:
	
	CStatic m_Picture;// ��Ʈ���̹���
	CImage* pPngImage;


private:
	void Release(void);

public:
	virtual BOOL OnInitDialog();
private: //Container
	map<CString, UNITDATA*>		m_MapUnitData;
private: ///basestatus
	CString m_strName;
	int m_iStr;
	int m_iDex;
	int m_iVital;
	int m_iInt;
	
private:
	
	int m_iLevel;
	int m_iAttack;
	int m_iDeffence;
	int m_iHealthPoint;
	int m_iExperience;
	int m_iBonusPoint;
	int m_iWeight;
	float m_fAttackSpeed;
	float m_fMoveSpeed;
	float m_fRange;
	///test
	list<CString> keylist;
	list<CString> addrlist;
	map<CString,CString> mapTest;

private://üũ�ڽ�
	CButton m_Caravan;
	CButton m_RapidAttack;
	CButton m_RapidMoveSpeed;
	CButton m_HardSkin;
	CButton m_BadassDMG;
	CButton m_Tank;

private:
	UINT m_UnitType;//������ư
private:
	CListBox m_UnitList;//���ָ���Ʈ
	CListBox m_PortraitList;//�ʻ�ȭ����Ʈ

	

private://���Ŀ����Լ�
	void CalcWeight(void);
	void CalcAttack(void);
	void CalcDeffence(void);
	void CalcHealthPoint(void);
	void CalcAttackSpeed(void);
	void CalcMoveSpeed(void);
private:
	void SetRadioAction(void);
	void test(CString _Path);

public:
	afx_msg void OnEnChangeSTR();
	afx_msg void OnEnChangeDEX();
	afx_msg void OnEnChangeVITAL();
	afx_msg void OnEnChangeINT();
	afx_msg void OnEnChangeLEVEL();

	afx_msg void OnBnClickedCheckCaravan();


public:
	afx_msg void OnBnClickedCheckBadassDMG();
	afx_msg void OnBnClickedCheckTank();
	afx_msg void OnBnClickedCheckRapidAttack();
	afx_msg void OnBnClickedCheckRapidMoveSpeed();
	afx_msg void OnBnClickedCheckHardSkin();
	afx_msg void RadioCtrl(UINT ID);
	

public:
	afx_msg void AddUnit();
	afx_msg void DeleteUnit();

public:
	afx_msg void OnLbnSelchangeAddedUnitList();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButton5();

};
