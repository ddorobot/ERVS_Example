// EyedeaCameraConfigTabDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "EyedeaCameraConfigTabDlg.h"
#include "afxdialogex.h"
#include "EyedeaExampleDlg.h"


// CEyedeaCameraConfigTabDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEyedeaCameraConfigTabDlg, CDialogEx)

CEyedeaCameraConfigTabDlg::CEyedeaCameraConfigTabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CAMERA_CONFIG, pParent)
{

}

CEyedeaCameraConfigTabDlg::~CEyedeaCameraConfigTabDlg()
{
}

BOOL CEyedeaCameraConfigTabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
//	m_Slider_Camera_Exposure.SetRange(0, 1<<19, TRUE);
//	m_Slider_Camera_Exposure.SetPos( (1<<19) /2);
	m_Slider_Camera_Exposure.SetRange(0, 1<<16, TRUE);
	m_Slider_Camera_Exposure.SetPos( (1<<16) /2);


	m_Slider_Camera_GAIN.SetRange(0, 1 << 9, TRUE);
	m_Slider_Camera_GAIN.SetPos((1 << 9) / 2);

	m_Slider_Camera_AE_Range_High.SetRange(0, 1 << 14, TRUE);
	m_Slider_Camera_AE_Range_High.SetPos((1 << 14) / 2);

	m_Slider_Camera_AE_Range_Low.SetRange(0, 1 << 14, TRUE);
	m_Slider_Camera_AE_Range_Low.SetPos((1 << 14) / 2);

	m_Slider_Camera_Exposure.EnableWindow(FALSE);
	m_Slider_Camera_GAIN.EnableWindow(FALSE);

	m_Slider_Camera_AE_Range_High.EnableWindow(TRUE);
	m_Slider_Camera_AE_Range_Low.EnableWindow(TRUE);

	m_Slider_Camera_LED_Brightness.SetRange(10, 1000, TRUE);
	m_Slider_Camera_LED_Brightness.SetPos((500) / 2);

	m_Slider_Camera_LED_Brightness_Timer.SetRange(10, 1000, TRUE);
	m_Slider_Camera_LED_Brightness_Timer.SetPos((500) / 2);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEyedeaCameraConfigTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_Exposure, m_Slider_Camera_Exposure);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_GAIN, m_Slider_Camera_GAIN);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_RANGE_HIGH, m_Slider_Camera_AE_Range_High);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_RANGE_LOW, m_Slider_Camera_AE_Range_Low);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_LED_BRIGHTNESS, m_Slider_Camera_LED_Brightness);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_LED_BRIGHTNESS_TIMER, m_Slider_Camera_LED_Brightness_Timer);		
}


BEGIN_MESSAGE_MAP(CEyedeaCameraConfigTabDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_OPTION_CAMERA_EXPOSURE, &CEyedeaCameraConfigTabDlg::OnBnClickedCheckOptionCameraExposure)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_TAKEPIC, &CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraTakepic)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_TIMER_LED, &CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraTimerLed)
END_MESSAGE_MAP()

void CEyedeaCameraConfigTabDlg::OnBnClickedCheckOptionCameraExposure()
{
	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_OPTION_CAMERA_EXPOSURE);

	if (bCheck)
	{
		m_Slider_Camera_Exposure.EnableWindow(TRUE);
		m_Slider_Camera_GAIN.EnableWindow(TRUE);

		m_Slider_Camera_AE_Range_High.EnableWindow(FALSE);
		m_Slider_Camera_AE_Range_Low.EnableWindow(FALSE);

		ERVS_SetCameraConfig(SET_CAMERA_MANUAL_EXPOSURE, 0, 0);
	}
	else
	{
		m_Slider_Camera_Exposure.EnableWindow(FALSE);
		m_Slider_Camera_GAIN.EnableWindow(FALSE);

		m_Slider_Camera_AE_Range_High.EnableWindow(TRUE);
		m_Slider_Camera_AE_Range_Low.EnableWindow(TRUE);
		ERVS_SetCameraConfig(SET_CAMERA_AUTO_EXPOSURE, 0, 0);
	}
}


void CEyedeaCameraConfigTabDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (pScrollBar == (CScrollBar *)&m_Slider_Camera_Exposure) {
		int value = m_Slider_Camera_Exposure.GetPos();
		CString str;
		str.Format(_T("%d"), value);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_EXPOSURE)->SetWindowText(str);
		ERVS_SetCameraConfig(SET_CAMERA_MANUAL_EXPOSURE_EXPOSURE, value, 0);
		//		printf("%d\n", value);
	}
	else if (pScrollBar == (CScrollBar *)&m_Slider_Camera_GAIN) {
		int value = m_Slider_Camera_GAIN.GetPos();
		CString str;
		str.Format(_T("%d"), value);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_GAIN)->SetWindowText(str);
		//		printf("%d\n", value);
		ERVS_SetCameraConfig(SET_CAMERA_MANUAL_EXPOSURE_GAIN, value, 0);
	}
	else if (pScrollBar == (CScrollBar *)&m_Slider_Camera_AE_Range_High) {
		int value = m_Slider_Camera_AE_Range_High.GetPos();
		CString str;
		str.Format(_T("%d"), value);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_RANGE_HIGH_LIMIT)->SetWindowText(str);
		//		printf("%d\n", value);
		ERVS_SetCameraConfig(SET_CAMERA_AUTO_EXPOSURE_RANGE_GO_OUT, value, 0);
	}
	else if (pScrollBar == (CScrollBar *)&m_Slider_Camera_AE_Range_Low) {
		int value = m_Slider_Camera_AE_Range_Low.GetPos();
		CString str;
		str.Format(_T("%d"), value);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_RANGE_LOW_LIMIT)->SetWindowText(str);
		//		printf("%d\n", value);
		ERVS_SetCameraConfig(SET_CAMERA_AUTO_EXPOSURE_RANGE_ENTER, value, 0);
	}
	else if (pScrollBar == (CScrollBar *)&m_Slider_Camera_LED_Brightness) {
		int value = m_Slider_Camera_LED_Brightness.GetPos();
		CString str;
		str.Format(_T("%d"), value);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_LED_BRIGHTNESS)->SetWindowText(str);
		//		printf("%d\n", value);
		ERVS_SetCameraConfig(SET_CAMERA_LED_BRIGHTNESS, value, 0);
	}
	else if( pScrollBar ==(CScrollBar *)&m_Slider_Camera_LED_Brightness_Timer) {
		int value = m_Slider_Camera_LED_Brightness_Timer.GetPos();
		CString str;	
		str.Format(_T("%d"), value);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_LED_BRIGHTNESS_TIMER)->SetWindowText(str);
		//		printf("%d\n", value);
	}
	else {
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraTakepic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ERVS_SetCameraConfig(SET_CAMERA_TAKE_PIC, 0, 0);
}


void CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraTimerLed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int value = m_Slider_Camera_LED_Brightness_Timer.GetPos();
	CString str;	
	GetDlgItem(IDC_EDIT_CAMERA_VAL_LED_ONTIME)->GetWindowText(str);
	int ms = (int)_ttof(str);
	ERVS_SetCameraConfig(SET_CAMERA_LED_TIMER_ON,value,ms);
}
