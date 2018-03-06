#pragma once

#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"


// CInspectionSetAngleDlg dialog

class CInspectionSetAngleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectionSetAngleDlg)

public:
	CInspectionSetAngleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInspectionSetAngleDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INSPECTION_SET_ANGLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_select_id;
	afx_msg void OnBnClickedButtonAngleCalc();
	afx_msg void OnBnClickedButtonBaseAngleGet();
	afx_msg void OnBnClickedButtonBaseAngleSet();
	afx_msg void OnBnClickedButtonAngleTolGet();
	afx_msg void OnBnClickedButtonAngleTolSet();
	afx_msg void OnBnClickedOk();
};
