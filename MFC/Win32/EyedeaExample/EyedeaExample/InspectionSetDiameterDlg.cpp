// InspectionSetDiameterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "InspectionSetDiameterDlg.h"
#include "afxdialogex.h"


// CInspectionSetDiameterDlg dialog

IMPLEMENT_DYNAMIC(CInspectionSetDiameterDlg, CDialogEx)

CInspectionSetDiameterDlg::CInspectionSetDiameterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_INSPECTION_SET_CIRCLE_DIAMETER, pParent)
	, m_select_id(0)
{

}

CInspectionSetDiameterDlg::~CInspectionSetDiameterDlg()
{
}

void CInspectionSetDiameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInspectionSetDiameterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DIAMETER_CALC, &CInspectionSetDiameterDlg::OnBnClickedButtonDiameterCalc)
	ON_BN_CLICKED(IDC_BUTTON_BASE_DIAMETER_GET, &CInspectionSetDiameterDlg::OnBnClickedButtonBaseDiameterGet)
	ON_BN_CLICKED(IDC_BUTTON_BASE_DIAMETER_SET, &CInspectionSetDiameterDlg::OnBnClickedButtonBaseDiameterSet)
	ON_BN_CLICKED(IDC_BUTTON_DIAMETER_TOL_GET, &CInspectionSetDiameterDlg::OnBnClickedButtonDiameterTolGet)
	ON_BN_CLICKED(IDC_BUTTON_DIAMETER_TOL_SET, &CInspectionSetDiameterDlg::OnBnClickedButtonDiameterTolSet)
	ON_BN_CLICKED(IDOK, &CInspectionSetDiameterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInspectionSetDiameterDlg message handlers


BOOL CInspectionSetDiameterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_select_id = ERVS_DB_Get_Select_ID();

	OnBnClickedButtonBaseDiameterGet();
	OnBnClickedButtonDiameterTolGet();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CInspectionSetDiameterDlg::OnBnClickedButtonDiameterCalc()
{
	// TODO: Add your control notification handler code here
	float diameter = ERVS_GetObjectCircleCalcDiameter(m_select_id);

	CString str;
	str.Format(_T("%.3f"), diameter);
	GetDlgItem(IDC_EDIT_CALC_DIAMETER)->SetWindowText(str);
}


void CInspectionSetDiameterDlg::OnBnClickedButtonBaseDiameterGet()
{
	// TODO: Add your control notification handler code here
	int base_diameter = ERVS_GetObjectCircleBaseDiameter(m_select_id);

	CString str;
	str.Format(_T("%d"), base_diameter);
	GetDlgItem(IDC_EDIT_BASE_DIAMETER)->SetWindowText(str);
}


void CInspectionSetDiameterDlg::OnBnClickedButtonBaseDiameterSet()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_BASE_DIAMETER)->GetWindowText(str);
	int base_diameter = _ttoi(str);

	ERVS_SetObjectCircleBaseDiameter(m_select_id, base_diameter);

	OnBnClickedButtonBaseDiameterGet();
}


void CInspectionSetDiameterDlg::OnBnClickedButtonDiameterTolGet()
{
	// TODO: Add your control notification handler code here
	int tol_min_value = 0;
	int tol_max_value = 0;

	ERVS_GetObjectCircleDiameterTolerance(m_select_id, &tol_min_value, &tol_max_value);

	CString str;
	str.Format(_T("%d"), tol_min_value);
	GetDlgItem(IDC_EDIT_DIAMETER_TOL_MIN)->SetWindowText(str);

	str.Format(_T("%d"), tol_max_value);
	GetDlgItem(IDC_EDIT_DIAMETER_TOL_MAX)->SetWindowText(str);
}


void CInspectionSetDiameterDlg::OnBnClickedButtonDiameterTolSet()
{
	// TODO: Add your control notification handler code here

	int tol_min_value = 0;
	int tol_max_value = 0;

	CString str;
	GetDlgItem(IDC_EDIT_DIAMETER_TOL_MIN)->GetWindowText(str);
	tol_min_value = _ttoi(str);

	GetDlgItem(IDC_EDIT_DIAMETER_TOL_MAX)->GetWindowText(str);
	tol_max_value = _ttoi(str);

	ERVS_SetObjectCircleDiameterTolerance(m_select_id, tol_min_value, tol_max_value);

	OnBnClickedButtonDiameterTolGet();
}


void CInspectionSetDiameterDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	OnBnClickedButtonBaseDiameterSet();
	OnBnClickedButtonDiameterTolSet();

	CDialogEx::OnOK();
}
