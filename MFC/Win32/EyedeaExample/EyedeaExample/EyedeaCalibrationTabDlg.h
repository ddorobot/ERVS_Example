#pragma once

#include <boost/thread.hpp>														//eyedea - using thread on boost.
#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"								//eyedea - draw lib.
#include "opencv2/opencv.hpp"													//eyedea - opencv lib.
#include "../../../lib/cvvImage/CvvImage.h"										//eyedea - draw lib.
#include "afxcmn.h"

#include "D:\vb_shared\EyedeaDemoForDRA\lib\boost_1_62_0\boost\thread\detail\thread.hpp"
#include "D:\vb_shared\EyedeaDemoForDRA\lib\boost_1_62_0\boost\property_tree\ptree.hpp"
#include "D:\vb_shared\EyedeaDemoForDRA\lib\boost_1_62_0\boost\property_tree\ini_parser.hpp"
#include "D:\vb_shared\EyedeaDemoForDRA\lib\boost_1_62_0\boost\filesystem\operations.hpp"
#include "D:\vb_shared\EyedeaDemoForDRA\lib\boost_1_62_0\boost\range\iterator_range.hpp"
#include "D:\vb_shared\EyedeaDemoForDRA\lib\boost_1_62_0\boost\system\error_code.hpp"

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
	void UpdateDataCalibrationRun(void);

protected:
	CBitmap* IplImageToCBitmap(IplImage* img);
public:
	afx_msg void OnBnClickedButtonGetCalibrationImage();
	cv::Mat m_calib_image;
	void Update();
	afx_msg void OnBnClickedButtonCalibrationCopy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonStandaloneCalibRun();
	afx_msg void OnBnClickedButtonstandaloneCalibGetFeaturePos();
	afx_msg void OnBnClickedButtonStandaloneCalibGetFeaturePos();
	afx_msg void OnBnClickedButtonStandaloneCalibSetMatrix();
	afx_msg void OnBnClickedButtonStandaloneCalibGetMatrix();
	afx_msg void OnBnClickedButtonStandaloneCalibCalcMatrix();
	afx_msg void OnBnClickedButtonStandaloneCalibInit();
	afx_msg void OnBnClickedButtonStandaloneCalibSetYDirection();
	afx_msg void OnBnClickedButtonStandaloneCalibSetYDirectionInv();
};
