#pragma once
#include "afxwin.h"


// CEyedeaCameraConfigTabDlg 대화 상자입니다.

class CEyedeaCameraConfigTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEyedeaCameraConfigTabDlg)

public:
	CEyedeaCameraConfigTabDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEyedeaCameraConfigTabDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CAMERA_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CSliderCtrl m_Slider_Camera_Exposure;
	CSliderCtrl m_Slider_Camera_GAIN;
	CSliderCtrl m_Slider_Camera_AE_Range_High;
	CSliderCtrl m_Slider_Camera_AE_Range_Low;
	CSliderCtrl m_Slider_Camera_LED_Brightness;
	CSliderCtrl m_Slider_Camera_LED_Brightness_Timer;

	afx_msg void OnBnClickedCheckOptionCameraExposure();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButtonCameraTakepic();
	afx_msg void OnBnClickedButtonCameraTimerLed();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonCameraSetDefault();
	CButton m_CheckManualExposure;

	void SetCameraConfigUI();
	afx_msg void OnBnClickedButtonCameraSaveParam();
	afx_msg void OnBnClickedButtonCameraLoadParam();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonCameraSaveParamWithId();
	afx_msg void OnBnClickedButtonCameraLoadParamWithId();
};
