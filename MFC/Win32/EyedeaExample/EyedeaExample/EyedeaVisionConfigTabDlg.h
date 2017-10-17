#pragma once

#include <boost/thread.hpp>														//eyedea - using thread on boost.
#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"								//eyedea - draw lib.
#include "opencv2/opencv.hpp"													//eyedea - opencv lib.
#include "../../../lib/cvvImage/CvvImage.h"										//eyedea - draw lib.

#include "afxwin.h"

// CEyedeaVisionConfigTabDlg dialog

class CEyedeaVisionConfigTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEyedeaVisionConfigTabDlg)

public:
	CEyedeaVisionConfigTabDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEyedeaVisionConfigTabDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VISION_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedButtonVisionConfigGet();
	//afx_msg void OnBnClickedButtonVisionConfigSet();
	virtual BOOL OnInitDialog();
	//CComboBox m_combo_object_type_for_env;
	//afx_msg void OnBnClickedButtonEnvOptionSearchAreaGet();
	//afx_msg void OnBnClickedButtonEnvOptionSearchAreaSet();
	//afx_msg void OnBnClickedButtonEnvOptionMasterAreaGet();
	//fx_msg void OnBnClickedButtonEnvOptionMasterAreaSet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectGet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectSet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectFeatureGet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectFeatureSet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectOutlineGet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectOutlineSet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectRectGet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectRectSet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectCenterGet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectCenterSet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectAngleGet();
	//afx_msg void OnBnClickedButtonEnvOptionObjectAngleSet();
	afx_msg void OnBnClickedButtonVisionConfigGet2();
	afx_msg void OnBnClickedButtonVisionConfigSet2();
	//afx_msg void OnBnClickedButtonConfigFileSave();
	//afx_msg void OnBnClickedButtonConfigFileLoad();
	//afx_msg void OnBnClickedButtonCheckVisionConfigGlobal();
	bool m_b_draw_pause;

private:
	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunctionDraw();

	cv::Mat m_check_image;
	cv::Mat m_check_image2;
public:
	//afx_msg void OnBnClickedButtonCheckVisionConfigLocal();
	//afx_msg void OnBnClickedButtonApplyVisionConfigGlobal();
	//afx_msg void OnBnClickedButtonApplyVisionConfigLocal();
	void RoadAllFromERVS();
	afx_msg void OnBnClickedButtonBgLearningStart();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCheckUseCalibrationImage();
	afx_msg void OnBnClickedButtonDepIdCheck();
	afx_msg void OnBnClickedCheckOneOfSubs();
	afx_msg void OnBnClickedCheckDependencySearcharea();
	afx_msg void OnBnClickedButtonSetBase();
	afx_msg void OnBnClickedButtonSetZoomImage();
	afx_msg void OnBnClickedButtonResetZoomImage();
	afx_msg void OnBnClickedCheckFixedArea();
	afx_msg void OnBnClickedButtonSelectBase();
	afx_msg void OnBnClickedButtonSelectCircle();
	//afx_msg void OnBnClickedButtonFindObjectDetectionLevelGet();
	//afx_msg void OnBnClickedButtonFindObjectDetectionLevelSet();
	afx_msg void OnBnClickedButtonCheckCameraCalibok();
	CComboBox m_combo_get_image_option_base;
	void DrawBoxForUserArea(cv::Mat draw);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	int m_command;						//eyedea - user command
	bool m_b_mouse_ldown_on_drawwindow;
	cv::Point m_pt_mouse;
	cv::Rect m_user_select_roi;
	cv::Rect m_user_rect;
	bool m_b_mouse_move_pattern;

	//afx_msg void OnBnClickedButtonSetZoomImage();
	//afx_msg void OnBnClickedButtonResetZoomImage();

	float m_select_rate_x;
	float m_select_rate_y;
	float m_select_rate_w;
	float m_select_rate_h;
	afx_msg void OnBnClickedButtonSelectLine();
	afx_msg void OnBnClickedButtonSetMaskArea();
	afx_msg void OnBnClickedButtonUndoMaskArea2();
	afx_msg void OnBnClickedButtonDelMaskArea();
	afx_msg void OnBnClickedButtonGetHistogram();

	float m_histogram_size;
	float *m_p_histogram;
	float *m_p_histogram_r;
	float *m_p_histogram_g;
	float *m_p_histogram_b;

	cv::Mat m_result_histogram_image;
	cv::Mat m_result_histogram_r_image;
	cv::Mat m_result_histogram_g_image;
	cv::Mat m_result_histogram_b_image;

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

	void DrawHistogram(int select_id);

	int m_i_histogram_lbdwn_object;
	int m_i_histogmra_gray_min;
	int m_i_histogmra_gray_max;
	int m_i_histogmra_red_min;
	int m_i_histogmra_red_max;
	int m_i_histogmra_green_min;
	int m_i_histogmra_green_max;
	int m_i_histogmra_blue_min;
	int m_i_histogmra_blue_max;
	int m_select_id;
	afx_msg void OnBnClickedButtonHistoGet();
	afx_msg void OnBnClickedButtonHistoGet2();
	afx_msg void OnBnClickedButtonHistoGet3();
	afx_msg void OnBnClickedButtonHistoGet4();
	afx_msg void OnBnClickedButtonHistoSet();
	afx_msg void OnBnClickedButtonHistoSet2();
	afx_msg void OnBnClickedButtonHistoSet3();
	afx_msg void OnBnClickedButtonHistoSet4();
	afx_msg void OnBnClickedCheckHistoInspecGray();
	afx_msg void OnBnClickedCheckHistoInspecRed2();
	afx_msg void OnBnClickedCheckHistoInspecGreen2();
	afx_msg void OnBnClickedCheckHistoInspecBlue2();
};
