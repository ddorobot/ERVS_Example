// InspectionSetAngleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "InspectionSetAngleDlg.h"
#include "afxdialogex.h"


// CInspectionSetAngleDlg dialog

IMPLEMENT_DYNAMIC(CInspectionSetAngleDlg, CDialogEx)

CInspectionSetAngleDlg::CInspectionSetAngleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_INSPECTION_SET_ANGLE, pParent)
	, m_select_id(0)
{

}

CInspectionSetAngleDlg::~CInspectionSetAngleDlg()
{
}

void CInspectionSetAngleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInspectionSetAngleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ANGLE_CALC, &CInspectionSetAngleDlg::OnBnClickedButtonAngleCalc)
	ON_BN_CLICKED(IDC_BUTTON_BASE_ANGLE_GET, &CInspectionSetAngleDlg::OnBnClickedButtonBaseAngleGet)
	ON_BN_CLICKED(IDC_BUTTON_BASE_ANGLE_SET, &CInspectionSetAngleDlg::OnBnClickedButtonBaseAngleSet)
	ON_BN_CLICKED(IDC_BUTTON_ANGLE_TOL_GET, &CInspectionSetAngleDlg::OnBnClickedButtonAngleTolGet)
	ON_BN_CLICKED(IDC_BUTTON_ANGLE_TOL_SET, &CInspectionSetAngleDlg::OnBnClickedButtonAngleTolSet)
	ON_BN_CLICKED(IDOK, &CInspectionSetAngleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInspectionSetAngleDlg message handlers


BOOL CInspectionSetAngleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_select_id = ERVS_DB_Get_Select_ID();

	OnBnClickedButtonBaseAngleGet();
	OnBnClickedButtonAngleTolGet();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CInspectionSetAngleDlg::OnBnClickedButtonAngleCalc()
{
	// TODO: Add your control notification handler code here
	float angle = ERVS_GetObjectTwoLineCalcAngle(m_select_id);

	CString str;
	str.Format(_T("%.3f"), angle);
	GetDlgItem(IDC_EDIT_CALC_ANGLE)->SetWindowText(str);
}


void CInspectionSetAngleDlg::OnBnClickedButtonBaseAngleGet()
{
	// TODO: Add your control notification handler code here
	int base_angle = ERVS_GetObjectTwoLineBaseAngle(m_select_id);

	CString str;
	str.Format(_T("%d"), base_angle);
	GetDlgItem(IDC_EDIT_BASE_ANGLE)->SetWindowText(str);
}


void CInspectionSetAngleDlg::OnBnClickedButtonBaseAngleSet()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_BASE_ANGLE)->GetWindowText(str);
	int base_angle = _ttoi(str);

	ERVS_SetObjectTwoLineBaseAngle(m_select_id, base_angle);

	OnBnClickedButtonBaseAngleGet();
}


void CInspectionSetAngleDlg::OnBnClickedButtonAngleTolGet()
{
	// TODO: Add your control notification handler code here
	int tol_min_value = 0;
	int tol_max_value = 0;

	ERVS_GetObjectTwoLineAngleTolerance(m_select_id, &tol_min_value, &tol_max_value);

	CString str;
	str.Format(_T("%d"), tol_min_value);
	GetDlgItem(IDC_EDIT_ANGLE_TOL_MIN)->SetWindowText(str);

	str.Format(_T("%d"), tol_max_value);
	GetDlgItem(IDC_EDIT_ANGLE_TOL_MAX)->SetWindowText(str);
}


void CInspectionSetAngleDlg::OnBnClickedButtonAngleTolSet()
{
	// TODO: Add your control notification handler code here
	int tol_min_value = 0;
	int tol_max_value = 0;

	CString str;
	GetDlgItem(IDC_EDIT_ANGLE_TOL_MIN)->GetWindowText(str);
	tol_min_value = _ttoi(str);

	GetDlgItem(IDC_EDIT_ANGLE_TOL_MAX)->GetWindowText(str);
	tol_max_value = _ttoi(str);

	ERVS_SetObjectTwoLineAngleTolerance(m_select_id, tol_min_value, tol_max_value);

	OnBnClickedButtonAngleTolGet();
}


void CInspectionSetAngleDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnBnClickedButtonBaseAngleSet();
	OnBnClickedButtonAngleTolSet();

	CDialogEx::OnOK();
}
