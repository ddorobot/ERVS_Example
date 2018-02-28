// InspectionSetDistanceDlb.cpp : implementation file
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "InspectionSetDistanceDlb.h"
#include "afxdialogex.h"


// CInspectionSetDistanceDlb dialog

IMPLEMENT_DYNAMIC(CInspectionSetDistanceDlb, CDialogEx)

CInspectionSetDistanceDlb::CInspectionSetDistanceDlb(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_INSPECTION_SET_DISTANCE, pParent)
	, m_select_id(0)
	, m_radio_select_type(0)
{

}

CInspectionSetDistanceDlb::~CInspectionSetDistanceDlb()
{
}

void CInspectionSetDistanceDlb::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_DISTANCE_TYPE1, m_radio_select_type);
}


BEGIN_MESSAGE_MAP(CInspectionSetDistanceDlb, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DISTANCE_TOL_GET, &CInspectionSetDistanceDlb::OnBnClickedButtonDistanceTolGet)
	ON_BN_CLICKED(IDC_BUTTON_BASE_DISTANCE_GET, &CInspectionSetDistanceDlb::OnBnClickedButtonBaseDistanceGet)
	ON_BN_CLICKED(IDC_BUTTON_DISTANCE_TYPE_GET, &CInspectionSetDistanceDlb::OnBnClickedButtonDistanceTypeGet)
	ON_BN_CLICKED(IDC_BUTTON_BASE_DISTANCE_SET, &CInspectionSetDistanceDlb::OnBnClickedButtonBaseDistanceSet)
	ON_BN_CLICKED(IDC_BUTTON_DISTANCE_TYPE_SET, &CInspectionSetDistanceDlb::OnBnClickedButtonDistanceTypeSet)
	ON_BN_CLICKED(IDC_BUTTON_DISTANCE_TOL_SET, &CInspectionSetDistanceDlb::OnBnClickedButtonDistanceTolSet)
	ON_BN_CLICKED(IDC_BUTTON_DISTANCE_CALC, &CInspectionSetDistanceDlb::OnBnClickedButtonDistanceCalc)
	ON_BN_CLICKED(IDOK, &CInspectionSetDistanceDlb::OnBnClickedOk)
END_MESSAGE_MAP()


// CInspectionSetDistanceDlb message handlers


BOOL CInspectionSetDistanceDlb::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_select_id = ERVS_DB_Get_Select_ID();

	OnBnClickedButtonDistanceCalc();
	OnBnClickedButtonBaseDistanceGet();
	OnBnClickedButtonDistanceTolGet();
	OnBnClickedButtonDistanceTypeGet();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CInspectionSetDistanceDlb::OnBnClickedButtonDistanceTolGet()
{
	// TODO: Add your control notification handler code here
	int tol_min_value = 0;
	int tol_max_value = 0;

	ERVS_GetObjectTwoLineDistanceTolerance(m_select_id, &tol_min_value, &tol_max_value);

	CString str;
	str.Format(_T("%d"), tol_min_value);
	GetDlgItem(IDC_EDIT_DISTANCE_TOL_MIN)->SetWindowText(str);

	str.Format(_T("%d"), tol_max_value);
	GetDlgItem(IDC_EDIT_DISTANCE_TOL_MAX)->SetWindowText(str);
}


void CInspectionSetDistanceDlb::OnBnClickedButtonBaseDistanceGet()
{
	// TODO: Add your control notification handler code here

	int base_dist = ERVS_GetObjectTwoLineBaseDistance(m_select_id);

	CString str;
	str.Format(_T("%d"), base_dist);
	GetDlgItem(IDC_EDIT_BASE_DISTANCE)->SetWindowText(str);

}


void CInspectionSetDistanceDlb::OnBnClickedButtonDistanceTypeGet()
{
	// TODO: Add your control notification handler code here
	int type = ERVS_GetObjectTwoLineDistanceType(m_select_id);

	if (type == DISTANCE_A_B)
	{
		m_radio_select_type = 0;
	}
	else if (type == DISTANCE_B_A)
	{
		m_radio_select_type = 1;
	}

	UpdateData(FALSE);
}


void CInspectionSetDistanceDlb::OnBnClickedButtonBaseDistanceSet()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_BASE_DISTANCE)->GetWindowText(str);
	int base_dist = _ttoi(str);

	ERVS_SetObjectTwoLineBaseDistance(m_select_id, base_dist);

	OnBnClickedButtonBaseDistanceGet();
}


void CInspectionSetDistanceDlb::OnBnClickedButtonDistanceTypeSet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int type = 0;
	if (m_radio_select_type == 0)
		type = DISTANCE_A_B;
	else if(m_radio_select_type == 1)
		type = DISTANCE_B_A;

	ERVS_SetObjectTwoLineDistanceType(m_select_id, type);

	OnBnClickedButtonDistanceTypeGet();
}


void CInspectionSetDistanceDlb::OnBnClickedButtonDistanceTolSet()
{
	// TODO: Add your control notification handler code here
	int tol_min_value = 0;
	int tol_max_value = 0;

	CString str;
	GetDlgItem(IDC_EDIT_DISTANCE_TOL_MIN)->GetWindowText(str);
	tol_min_value = _ttoi(str);

	GetDlgItem(IDC_EDIT_DISTANCE_TOL_MAX)->GetWindowText(str);
	tol_max_value = _ttoi(str);

	ERVS_SetObjectTwoLineDistanceTolerance(m_select_id, tol_min_value, tol_max_value);

	OnBnClickedButtonDistanceTolGet();
}


void CInspectionSetDistanceDlb::OnBnClickedButtonDistanceCalc()
{
	// TODO: Add your control notification handler code here
	float dist = ERVS_GetObjectTwoLineCalcDistance(m_select_id);

	CString str;
	str.Format(_T("%.3f"), dist);
	GetDlgItem(IDC_EDIT_CALC_DISTANCE)->SetWindowText(str);
}


void CInspectionSetDistanceDlb::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnBnClickedButtonBaseDistanceSet();
	OnBnClickedButtonDistanceTypeSet();
	OnBnClickedButtonDistanceTolSet();

	CDialogEx::OnOK();
}
