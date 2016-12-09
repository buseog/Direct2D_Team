#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMapTool 대화 상자입니다.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

private:
	int m_iTileSize;
	int m_iTileOption;
	int	m_iTileNumber;
	int m_iAngle;
	float	m_fMirror;
	map<CString, CImage*>		m_MapPngImage;

	CComboBox	m_OptionComboBox;
	CListBox	m_mapListBox;
	CStatic		m_Picture;
	CSliderCtrl m_TileAngle;

public:
	void	Release(void);
	int		GetTileSize(void);
	int		GetTileOption(void);
	int		GetTileNumber(void);
	float	GetTileAngle(void);
	float	GetTileMirror(void);
	void	DrawTile(void);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAPTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	
	virtual BOOL OnInitDialog();
	afx_msg void OnTileOption();
	afx_msg void OnListBox();
	afx_msg void OnReturn();
	afx_msg void OnDelete();
	afx_msg void OnClear();
	afx_msg void OnMirroring();
	afx_msg void OnTileAngle(NMHDR *pNMHDR, LRESULT *pResult);
	
};
