#pragma once



// CSecondForm 폼 뷰입니다.

class CSecondForm : public CFormView
{
	DECLARE_DYNCREATE(CSecondForm)

protected:
	CSecondForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CSecondForm();

public:
	enum { IDD = IDD_SECONDFORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


public: //수치 출력 관련
	CString m_StateKey;
	CString m_ObjKey;

	void	SetKey(float _fObjKey, float _StateKey);
};


