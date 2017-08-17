#pragma once

#include <boost/thread.hpp>														//eyedea - using thread on boost.
#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"								//eyedea - draw lib.
#include "opencv2/opencv.hpp"													//eyedea - opencv lib.
#include "../../../lib/cvvImage/CvvImage.h"										//eyedea - draw lib.
#include "afxcmn.h"

// CEyedeaCalibrationTabDlg dialog

class CEyedeaCalibrationTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEyedeaCalibrationTabDlg)

public:
	CEyedeaCalibrationTabDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEyedeaCalibrationTabDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CALIBRATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunctionDraw();
	bool m_b_draw_pause;
	afx_msg void OnBnClickedButtonCalibrationGetListInfo();
	CListCtrl m_List_calibration;
	CImageList m_ImgList;
	afx_msg void OnBnClickedButtonCalibrationChessInfoGet();
	afx_msg void OnBnClickedButtonCalibrationChessInfoSet();
	afx_msg void OnBnClickedButtonCalibrationAddListInfo();
	afx_msg void OnBnClickedButtonCalibrationDelListInfo();
	afx_msg void OnBnClickedButtonCalibrationGetListInfo3();
	afx_msg void OnBnClickedButtonCalibrationRun();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonSaveCalibration();
	afx_msg void OnBnClickedButtonLoadCalibration();

protected:
	CBitmap* IplImageToCBitmap(IplImage* img);
public:
	afx_msg void OnBnClickedButtonGetCalibrationImage();

private:
	cv::Mat m_calib_image;
};
