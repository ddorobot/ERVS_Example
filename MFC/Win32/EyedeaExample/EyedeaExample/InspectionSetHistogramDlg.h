#pragma once

#include <boost/thread.hpp>														//eyedea - using thread on boost.
#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"								//eyedea - draw lib.
#include "opencv2/opencv.hpp"													//eyedea - opencv lib.
#include "../../../lib/cvvImage/CvvImage.h"										//eyedea - draw lib.


// CInspectionSetHistogramDlg dialog

class CInspectionSetHistogramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectionSetHistogramDlg)

public:
	CInspectionSetHistogramDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInspectionSetHistogramDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INSPECTION_SET_HISTOGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	float m_histogram_size;
	float *m_p_histogram;
	float *m_p_histogram_r;
	float *m_p_histogram_g;
	float *m_p_histogram_b;
	int m_select_id;

	cv::Mat m_result_histogram_image;
	cv::Mat m_result_histogram_r_image;
	cv::Mat m_result_histogram_g_image;
	cv::Mat m_result_histogram_b_image;
	afx_msg void OnBnClickedButtonHistoGet();
	afx_msg void OnBnClickedButtonHistoSet();
	afx_msg void OnBnClickedButtonHistoGet2();
	afx_msg void OnBnClickedButtonHistoSet2();
	afx_msg void OnBnClickedButtonHistoGet3();
	afx_msg void OnBnClickedButtonHistoSet3();
	afx_msg void OnBnClickedButtonHistoGet4();
	afx_msg void OnBnClickedButtonHistoSet4();
	afx_msg void OnBnClickedCheckHistoInspecGray();
	afx_msg void OnBnClickedCheckHistoInspecRed2();
	afx_msg void OnBnClickedCheckHistoInspecGreen2();
	afx_msg void OnBnClickedCheckHistoInspecBlue2();
	afx_msg void OnBnClickedButtonGetPixelCount();

	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunctionDraw();
	void DrawHistogram(int select_id);

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
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	int m_i_histogram_lbdwn_object;
	int m_i_histogmra_gray_min;
	int m_i_histogmra_gray_max;
	int m_i_histogmra_red_min;
	int m_i_histogmra_red_max;
	int m_i_histogmra_green_min;
	int m_i_histogmra_green_max;
	int m_i_histogmra_blue_min;
	int m_i_histogmra_blue_max;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedButtonHistogramTolGet();
	afx_msg void OnBnClickedButtonHistogramTolSet();
	afx_msg void OnBnClickedOk();
};
