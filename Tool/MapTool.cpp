// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "MainFrm.h"
#include "TextureMgr.h"


// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(CMapTool::IDD, pParent)
	, m_iTileSize(1)
	, m_iTileOption(0)
	, m_iTileNumber(1)
	, m_iAngle(0)
	, m_fMirror(1)
{

}

CMapTool::~CMapTool()
{
	Release();
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_mapListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_COMBO1, m_OptionComboBox);
	DDX_Text(pDX, IDC_EDIT1, m_iTileSize);
	DDX_Control(pDX, IDC_SLIDER3, m_TileAngle);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_DROPFILES()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMapTool::OnTileOption)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnReturn)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnDelete)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTool::OnClear)
	ON_BN_CLICKED(IDC_BUTTON5, &CMapTool::OnMirroring)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CMapTool::OnTileAngle)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.

void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);

	CDialog::OnDropFiles(hDropInfo);

	int iFileCount = DragQueryFile(hDropInfo, -1, NULL, 0);

	TCHAR szFullPath[MAX_PATH] = L"";
	TCHAR szDirPath[MAX_PATH] = L"";


	for (int i = 0; i < iFileCount; ++i)
	{
		DragQueryFile(hDropInfo, i, (LPWSTR)szFullPath, MAX_PATH);

		CString strFileName;

		GetCurrentDirectory(sizeof(szDirPath), szDirPath);
		PathRelativePathTo(szDirPath, 
							szDirPath, 
							FILE_ATTRIBUTE_DIRECTORY, 
							szFullPath, 
							FILE_ATTRIBUTE_NORMAL);

		strFileName = PathFindFileName(szDirPath);
		PathRemoveExtension((LPWSTR)strFileName.operator LPCWSTR());

		map<CString, CImage*>::iterator iter = m_MapPngImage.find(strFileName);

		if (iter == m_MapPngImage.end())
		{
			CImage*		pPngImage = new CImage;
			pPngImage->Load(szDirPath);
			m_MapPngImage.insert(map<CString, CImage*>::value_type(strFileName, pPngImage));
			m_mapListBox.AddString(strFileName);
		}
	}

	UpdateData(FALSE);
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_OptionComboBox.AddString(L"0 - 이동불가");
	m_OptionComboBox.AddString(L"1 - 이동가능");

	m_OptionComboBox.SetCurSel(0);

	m_TileAngle.SetRange(0, 360);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMapTool::OnTileOption()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_iTileOption = m_OptionComboBox.GetCurSel();
}

void CMapTool::Release(void)
{
	for_each(m_MapPngImage.begin(), m_MapPngImage.end(), DeleteMap());
	m_MapPngImage.clear();
}
void CMapTool::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iSelect = m_mapListBox.GetCurSel();
	CString strSelectName;

	if (iSelect < 0)
		return;

	m_mapListBox.GetText(iSelect, strSelectName);

	map<CString, CImage*>::iterator	iter = m_MapPngImage.find(strSelectName);

	if (iter == m_MapPngImage.end())
		return;

	// 그림을 띄워줌
	//m_Picture.SetBitmap(*iter->second);

	int i = 0;

	for (i = 0; i < strSelectName.GetLength(); ++i)
	{
		if (isdigit(strSelectName[i]) != 0)
			break;
	}

	strSelectName.Delete(0, i);
	m_iTileNumber = _tstoi(strSelectName);

	DrawTile();
	UpdateData(FALSE);

}


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
void CMapTool::OnDelete()
{
	int iSelect = m_mapListBox.GetCurSel();
	CString strSelectName;

	if (iSelect < 0)
		return;

	m_mapListBox.GetText(iSelect, strSelectName);

	map<CString, CImage*>::iterator	iter = m_MapPngImage.find(strSelectName);

	if (iter == m_MapPngImage.end())
		return;

	Safe_Delete(iter->second);
	m_MapPngImage.erase(strSelectName);

	m_mapListBox.DeleteString(iSelect);


	UpdateData(FALSE);
}

void CMapTool::OnClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	for (map<CString, CImage*>::iterator iter = m_MapPngImage.begin(); iter != m_MapPngImage.end(); ++iter)
	{
		::Safe_Delete(iter->second);
	}
	m_MapPngImage.clear();
	m_mapListBox.ResetContent();
}

void CMapTool::OnReturn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetBackGround()->ReturnAction();
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->Invalidate(TRUE);

	((CMainFrame*)AfxGetMainWnd())->GetMiniView()->Invalidate(true);
}

int	CMapTool::GetTileSize(void)
{
	UpdateData(TRUE);
	UpdateData(FALSE);
	return m_iTileSize;
}

int	CMapTool::GetTileOption(void)
{
	return m_iTileOption;
}

int		CMapTool::GetTileNumber(void)
{
	return m_iTileNumber;
}

float	CMapTool::GetTileAngle(void)
{
	return m_iAngle;
}

float	CMapTool::GetTileMirror(void)
{
	return m_fMirror;
}

void CMapTool::OnMirroring()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	m_fMirror *= -1.f;
	DrawTile();

	UpdateData(FALSE);
}


void CMapTool::OnTileAngle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	UpdateData(TRUE);
	m_iAngle = m_TileAngle.GetPos();
	
	DrawTile();
	UpdateData(FALSE);
}

void CMapTool::DrawTile(void)
{
	UpdateData(TRUE);

	CDevice::GetInstance()->GetDevice()->Clear(0, NULL, 
	D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 
	D3DCOLOR_ARGB(255, 255, 255, 255), 1.f, 0);

	CDevice::GetInstance()->Render_Begin();

	int iSelect = m_mapListBox.GetCurSel();

	if (iSelect < 0)
		return;

	CString strSelectName;

	const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"SNOWTILE", L"SnowTile", iSelect);
	m_mapListBox.GetText(iSelect, strSelectName);

	map<CString, CImage*>::iterator	iter = m_MapPngImage.find(strSelectName);

	D3DXMATRIX	matScale, matRot, matTrans, matWorld;

	D3DXMatrixIdentity(&matWorld);

	float fX = (float)WINCX / (float)iter->second->GetWidth() * m_fMirror;
	float fY = (float)WINCY / (float)iter->second->GetHeight();

	D3DXMatrixScaling(&matScale, fX, fY, 0.f);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(m_iAngle));
	D3DXMatrixTranslation(&matTrans, 400, 300, 0);

	matWorld = matScale * matRot * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
				NULL, &D3DXVECTOR3((float)iter->second->GetWidth() / 2.f, (float)iter->second->GetHeight() / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	CDevice::GetInstance()->Render_End();

	RECT rc = {250, 20, 410, 140};
	CDevice::GetInstance()->GetDevice()->Present(NULL, &rc, m_hWnd, NULL);



	UpdateData(FALSE);
}

