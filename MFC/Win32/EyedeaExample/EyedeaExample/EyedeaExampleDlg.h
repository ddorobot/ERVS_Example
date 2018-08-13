
// EyedeaExampleDlg.h : header file
//

#pragma once

#include <boost/thread.hpp>														//eyedea - using thread on boost.
#include "../../../lib/cvvImage/CvvImage.h"										//eyedea - draw lib.
#include "opencv2/opencv.hpp"													//eyedea - opencv lib.
#include "../../../src/EyedeaSDK/CXX/EyedeaAPI.h"								//eyedea - draw lib.
#include "afxcmn.h"
#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"
#include "boost\system\error_code.hpp"

#include "afxwin.h"
#include "EyedeaVisionConfigTabDlg.h"
#include "EyedeaCheckDefectTabDlg.h"
#include "EyedeaCalibrationTabDlg.h"
#include "EyedeaCameraConfigTabDlg.h"

#include "use_opencv_static.h"

#if defined(WIN32) || defined(WIN16)
#ifndef _CONSOLE 
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

//eyedea - command list
enum UserCommand
{
	USER_COMMAND_NORMAL = 0,
	USER_COMMAND_LIVE_MODE,
	USER_COMMAND_SELECT_OBJECT,
	USER_COMMAND_SELECT_SEARCH_AREA,
	USER_COMMAND_SELECT_MASTER_AREA,
	USER_COMMAND_FIND_OBJECT,
	USER_COMMAND_DRAW_RESULT,
	USER_COMMAND_DRAW_RESULT_LOCAL,
	USER_COMMAND_DRAW_RESULT_GLOBAL,
	USER_COMMAND_SET_BASE,
	USER_COMMAND_SELECT_PAP_MASTER_OBJECT,
	USER_COMMAND_SELECT_BASE_OBJECT,
	USER_COMMAND_SET_ZOOM_IMAGE,
	USER_COMMAND_SELECT_OBJECT_CIRCLE,
	USER_COMMAND_SELECT_OBJECT_LINE,
	USER_COMMAND_SELECT_MASK_AREA
};

// CEyedeaExampleDlg dialog
class CEyedeaExampleDlg : public CDialogEx
{
// Construction
public:
	CEyedeaExampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EYEDEAEXAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	CIPAddressCtrl m_ip_addr;
	bool m_run_thread;
private:
	// eyedea - boost thread
	boost::thread m_thread;
public:
	void ThreadFunctionDraw();

private:
	cv::Mat m_display;
public:
	int m_command;						//eyedea - user command

	afx_msg void OnClose();
	//CComboBox m_combo_get_image_option;
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//bool m_b_mouse_ldown_on_drawwindow;
	//bool m_b_mouse_move_pattern;
	//cv::Point m_pt_mouse;
	//cv::Rect m_user_select_roi;
	//cv::Rect m_user_rect;
	//void DrawBoxForUserArea(cv::Mat draw);
	afx_msg void OnBnClickedButtonSetSampleImage();

	CTabCtrl m_tab_mode;
	CWnd* m_pwndShow;
	CEyedeaVisionConfigTabDlg m_tab_dlg_vision_config;
	CEyedeaCheckDefectTabDlg m_tab_dlg_check_defect;
	//CEyedeaPickAndPlaceTabDlg m_tab_dlg_pick_and_place;
	CEyedeaCalibrationTabDlg m_tab_dlg_calibration;
	CEyedeaCameraConfigTabDlg m_tab_dlg_camera_config;

	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_list_information;
	afx_msg void OnBnClickedButtonNewModel();
	afx_msg void OnNMDblclkListInformation(NMHDR *pNMHDR, LRESULT *pResult);
	void OnTcnSelchangeTabMy(int index);

	int m_select_list_number;
	CString m_select_list_string;
	afx_msg void OnBnClickedButtonGetVersion();
	void ManageDBListInfo(void);
	afx_msg void OnBnClickedButtonDelModel();
	afx_msg void OnBnClickedButtonListSave();
	afx_msg void OnBnClickedCheckLog();
	afx_msg void OnBnClickedButtonListLoad();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonCheckDbSaveList();
	afx_msg void OnBnClickedButtonListLoad2();
};
