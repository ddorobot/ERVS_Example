#pragma once

#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"

// CInspectionSetDiameterDlg dialog

class CInspectionSetDiameterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectionSetDiameterDlg)

public:
	CInspectionSetDiameterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInspectionSetDiameterDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INSPECTION_SET_CIRCLE_DIAMETER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_select_id;
	afx_msg void OnBnClickedButtonDiameterCalc();
	afx_msg void OnBnClickedButtonBaseDiameterGet();
	afx_msg void OnBnClickedButtonBaseDiameterSet();
	afx_msg void OnBnClickedButtonDiameterTolGet();
	afx_msg void OnBnClickedButtonDiameterTolSet();
	afx_msg void OnBnClickedOk();
};
