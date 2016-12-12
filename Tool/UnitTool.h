#pragma once
#include "afxwin.h"


// CUnitTool 대화 상자입니다.







class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_UNITTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	
	CStatic m_Picture;// 비트맵이미지
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

private://체크박스
	CButton m_Caravan;
	CButton m_RapidAttack;
	CButton m_RapidMoveSpeed;
	CButton m_HardSkin;
	CButton m_BadassDMG;
	CButton m_Tank;

private:
	UINT m_UnitType;//라디오버튼
private:
	CListBox m_UnitList;//유닛리스트
	CListBox m_PortraitList;//초상화리스트

	

private://수식연산함수
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
