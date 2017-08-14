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
	afx_msg void OnBnClickedButtonSetBase();
	//afx_msg void OnBnClickedCheckUsePca();
	CComboBox m_combo_get_image_option_base;
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
	afx_msg void OnBnClickedButtonSelectBase();
	//afx_msg void OnBnClickedCheckFindMultiObjects();
	afx_msg void OnBnClickedButtonFindObjectFilterSizeGet();
	afx_msg void OnBnClickedButtonFindObjectFilterPaddingGet();
	afx_msg void OnBnClickedButtonFindObjectFilterSizeSet();
	afx_msg void OnBnClickedButtonFindObjectFilterPaddingSet();
	CListCtrl m_list_find_objects;
	//afx_msg void OnBnClickedButtonFindGetInfo();
	afx_msg void OnBnClickedButtonFindObjectLocalPaddingGet();
	afx_msg void OnBnClickedButtonFindObjectLocalPaddingSet();

	cv::Mat m_found_image_object;
	//afx_msg void OnBnClickedButtonFindGetPose();
	void DrawFindObectList(void);
	CImageList m_ImgList;
	void RoadAllFromERVS();
	//afx_msg void OnBnClickedButtonFindObjectClassifierThreGet();
	afx_msg void OnBnClickedButtonFindGetInfo2();
	afx_msg void OnBnClickedButtonCheckCameraCalibok();
	afx_msg void OnBnClickedCheckDependencySearcharea();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	int m_command;						//eyedea - user command
	bool m_b_mouse_ldown_on_drawwindow;
	cv::Point m_pt_mouse;
	cv::Rect m_user_select_roi;
	cv::Rect m_user_rect;
	bool m_b_mouse_move_pattern;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	void DrawBoxForUserArea(cv::Mat draw);
	afx_msg void OnBnClickedButtonSetZoomImage();
	afx_msg void OnBnClickedButtonResetZoomImage();

	float m_select_rate_x;
	float m_select_rate_y;
	float m_select_rate_w;
	float m_select_rate_h;

protected:
	CBitmap* IplImageToCBitmap(IplImage* img);
public:
	CComboBox m_combo_dependency_list;
	void ManageList();
	afx_msg void OnBnClickedButtonDepIdCheck();
	afx_msg void OnBnClickedCheckFixedArea();
	afx_msg void OnBnClickedButtonSelectCircle();
	CButton m_btn_select_base_object;
	CRichEditCtrl m_editMain;

	void MyTextOut(LPCTSTR strText, COLORREF TextColor);
	afx_msg void OnBnClickedButtonFindObjectDetectionLevelGet();
	afx_msg void OnBnClickedButtonFindObjectDetectionLevelSet();
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
};
