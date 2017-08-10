#pragma once


// CEyedeaCameraConfigTabDlg ��ȭ �����Դϴ�.

class CEyedeaCameraConfigTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEyedeaCameraConfigTabDlg)

public:
	CEyedeaCameraConfigTabDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEyedeaCameraConfigTabDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CAMERA_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
};
