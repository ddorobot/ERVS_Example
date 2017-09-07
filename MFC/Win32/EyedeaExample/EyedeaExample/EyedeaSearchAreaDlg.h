#pragma once

#include <boost/thread.hpp>														//eyedea - using thread on boost.
#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"								//eyedea - draw lib.
#include "opencv2/opencv.hpp"													//eyedea - opencv lib.
#include "../../../lib/cvvImage/CvvImage.h"										//eyedea - draw lib.

// CEyedeaSearchAreaDlg dialog

class CEyedeaSearchAreaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEyedeaSearchAreaDlg)

public:
	CEyedeaSearchAreaDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEyedeaSearchAreaDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH_AREA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSelectSearchArea();
	afx_msg void OnBnClickedButtonFindSearchArea();

public:
	void ThreadFunctionDraw();

	bool m_run_thread;
	bool m_b_draw_pause;
	boost::thread m_thread;
public:
	virtual BOOL OnInitDialog();

private:
	cv::Mat m_image_result;
public:
	afx_msg void OnBnClickedButtonSearchAreaConfigGet();
	afx_msg void OnBnClickedButtonSearchAreaConfigSet();
	afx_msg void OnBnClickedButtonSearchAreaConfigRemake();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
