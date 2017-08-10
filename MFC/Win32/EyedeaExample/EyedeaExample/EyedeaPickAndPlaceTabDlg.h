#pragma once

#include <boost/thread.hpp>														//eyedea - using thread on boost.
#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"								//eyedea - draw lib.
#include "opencv2/opencv.hpp"													//eyedea - opencv lib.

// CEyedeaPickAndPlaceTabDlg dialog

class CEyedeaPickAndPlaceTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEyedeaPickAndPlaceTabDlg)

public:
	CEyedeaPickAndPlaceTabDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEyedeaPickAndPlaceTabDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PICK_AND_PLACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPapSetMasterObject();

	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunctionDraw();
	bool m_b_draw_pause;
	virtual BOOL OnInitDialog();
};
