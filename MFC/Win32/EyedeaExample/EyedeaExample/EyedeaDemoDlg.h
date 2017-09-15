#pragma once


// CEyedeaDemoDlg dialog

class CEyedeaDemoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEyedeaDemoDlg)

public:
	CEyedeaDemoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEyedeaDemoDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEMO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
