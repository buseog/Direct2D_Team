#pragma once



// CSecondForm �� ���Դϴ�.

class CSecondForm : public CFormView
{
	DECLARE_DYNCREATE(CSecondForm)

protected:
	CSecondForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()


public: //��ġ ��� ����
	CString m_StateKey;
	CString m_ObjKey;

	void	SetKey(float _fObjKey, float _StateKey);
};


