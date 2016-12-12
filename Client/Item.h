#pragma once

class CItem
{
public:
	CItem(void);
	virtual ~CItem(void);

public:
	virtual HRESULT Initialize(void)PURE;
	virtual int Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;
};
