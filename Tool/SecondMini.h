#pragma once


// CSecondMini ���Դϴ�.

class CSecondMini : public CView
{
	DECLARE_DYNCREATE(CSecondMini)

protected:
	CSecondMini();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CSecondMini();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


