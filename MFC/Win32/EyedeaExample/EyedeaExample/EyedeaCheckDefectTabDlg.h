#pragma once

#include <boost/thread.hpp>														//eyedea - using thread on boost.
#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"								//eyedea - draw lib.
#include "opencv2/opencv.hpp"													//eyedea - opencv lib.

#include "afxwin.h"
#include "afxcmn.h"

// CEyedeaCheckDefectTabDlg dialog

class CEyedeaCheckDefectTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEyedeaCheckDefectTabDlg)

public:
	CEyedeaCheckDefectTabDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEyedeaCheckDefectTabDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OBEJCT_DETECT_AND_CHECK_DEFECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedButtonSetBase();
	//afx_msg void OnBnClickedCheckUsePca();
	virtual BOOL OnInitDialog();
	//afx_msg void OnBnClickedCheckOptionFixSearchArea();
	//afx_msg void OnBnClickedButtonSelectSearchArea();
	//afx_msg void OnBnClickedButtonVisionConfigFindSearchAreaGet();
	//afx_msg void OnBnClickedButtonVisionConfigFindSearchAreaSet();
	//afx_msg void OnBnClickedButtonSelectMasterArea();
	//afx_msg void OnBnClickedButtonVisionConfigFindIterationGet();
	//afx_msg void OnBnClickedButtonVisionConfigFindIterationSet();
	//CComboBox m_combo_object_type;
	//afx_msg void OnBnClickedButtonAddObject();
	//afx_msg void OnBnClickedButtonVisionConfigFindCenterGet();
	//afx_msg void OnBnClickedButtonVisionConfigFindCenterSet();
	//afx_msg void OnBnClickedButtonFind();
	int m_i_checkdefect_ret;
	//afx_msg void OnBnClickedCheckUseFindWithCheckdefect();
	
	cv::Mat m_mat_icon;
	cv::Mat m_mat_pass, m_mat_fail, m_mat_warning;
	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunctionDraw();
	bool m_b_draw_pause;
	//afx_msg void OnBnClickedButtonVisionConfigFindObjectGet();
	//afx_msg void OnBnClickedButtonVisionConfigFindObjectSet();
	//afx_msg void OnBnClickedButtonSelectBase();
	//afx_msg void OnBnClickedCheckFindMultiObjects();
	//afx_msg void OnBnClickedButtonFindObjectFilterSizeGet();
	//afx_msg void OnBnClickedButtonFindObjectFilterPaddingGet();
	//afx_msg void OnBnClickedButtonFindObjectFilterSizeSet();
	//afx_msg void OnBnClickedButtonFindObjectFilterPaddingSet();
	CListCtrl m_list_find_objects;
	//afx_msg void OnBnClickedButtonFindGetInfo();
	//afx_msg void OnBnClickedButtonFindObjectLocalPaddingGet();
	//afx_msg void OnBnClickedButtonFindObjectLocalPaddingSet();

	cv::Mat m_found_image_object;
	//afx_msg void OnBnClickedButtonFindGetPose();
	void DrawFindObectList(void);
	CImageList m_ImgList;
	void RoadAllFromERVS();
	//afx_msg void OnBnClickedButtonFindObjectClassifierThreGet();
	afx_msg void OnBnClickedButtonFindGetInfo2();
	//afx_msg void OnBnClickedButtonCheckCameraCalibok();
	//afx_msg void OnBnClickedCheckDependencySearcharea();

protected:
	CBitmap* IplImageToCBitmap(IplImage* img);
public:
	CComboBox m_combo_dependency_list;
	void ManageList();
	//afx_msg void OnBnClickedButtonDepIdCheck();
	//afx_msg void OnBnClickedCheckFixedArea();
	//afx_msg void OnBnClickedButtonSelectCircle();
	CButton m_btn_select_base_object;
	CRichEditCtrl m_editMain;

	void MyTextOut(LPCTSTR strText, COLORREF TextColor);
	//afx_msg void OnBnClickedButtonFindObjectDetectionLevelGet();
	//afx_msg void OnBnClickedButtonFindObjectDetectionLevelSet();
	afx_msg void OnBnClickedCheckUseCalibrationImage();
	afx_msg void OnBnClickedCheckHistogram();

	cv::Mat m_result_image;
	cv::Mat m_result_histogram_image;
	cv::Mat m_result_histogram_r_image;
	cv::Mat m_result_histogram_g_image;
	cv::Mat m_result_histogram_b_image;

	//CListBox m_list_result_index;
	//afx_msg void OnLbnDblclkListResult();
	CTreeCtrl m_tree_result;
	afx_msg void OnNMDblclkTreeResult(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnBnClickedCheckOneOfSubs();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonGeoAngle();
	afx_msg void OnBnClickedButtonGeoResultClear();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	float m_histogram_size;
	float *m_p_histogram;
	float *m_p_histogram_r;
	float *m_p_histogram_g;
	float *m_p_histogram_b;

	int m_i_histogram_lbdwn_object ;
	int m_i_histogmra_gray_min;
	int m_i_histogmra_gray_max;
	int m_i_histogmra_red_min;
	int m_i_histogmra_red_max;
	int m_i_histogmra_green_min;
	int m_i_histogmra_green_max;
	int m_i_histogmra_blue_min;
	int m_i_histogmra_blue_max;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	float m_f_histogram_w_scale_v;
	float m_f_histogram_w_scale_r;
	float m_f_histogram_w_scale_g;
	float m_f_histogram_w_scale_b;
	float m_f_histogram_size_v_on_ui;
	float m_f_histogram_size_r_on_ui;
	float m_f_histogram_size_g_on_ui;
	float m_f_histogram_size_b_on_ui;
	float m_f_start_x_v_on_ui;
	float m_f_start_x_r_on_ui;
	float m_f_start_x_g_on_ui;
	float m_f_start_x_b_on_ui;

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void DrawHistogram(void);

	int m_select_id;

	boost::mutex mutex;
	afx_msg void OnBnClickedButtonHistoGet();
	afx_msg void OnBnClickedButtonHistoGet2();
	afx_msg void OnBnClickedButtonHistoGet3();
	afx_msg void OnBnClickedButtonHistoGet4();
	afx_msg void OnBnClickedButtonHistoSet();
	afx_msg void OnBnClickedButtonHistoSet2();
	afx_msg void OnBnClickedButtonHistoSet3();
	afx_msg void OnBnClickedButtonHistoSet4();
};
