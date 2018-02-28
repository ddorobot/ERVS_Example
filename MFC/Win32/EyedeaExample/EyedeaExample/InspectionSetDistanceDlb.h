#pragma once

#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"								//eyedea - draw lib.

// CInspectionSetDistanceDlb dialog

class CInspectionSetDistanceDlb : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectionSetDistanceDlb)

public:
	CInspectionSetDistanceDlb(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInspectionSetDistanceDlb();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INSPECTION_SET_DISTANCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	int m_select_id;
	afx_msg void OnBnClickedButtonDistanceTolGet();
	afx_msg void OnBnClickedButtonBaseDistanceGet();
	afx_msg void OnBnClickedButtonDistanceTypeGet();
	int m_radio_select_type;
	afx_msg void OnBnClickedButtonBaseDistanceSet();
	afx_msg void OnBnClickedButtonDistanceTypeSet();
	afx_msg void OnBnClickedButtonDistanceTolSet();
	afx_msg void OnBnClickedButtonDistanceCalc();
	afx_msg void OnBnClickedOk();
};
