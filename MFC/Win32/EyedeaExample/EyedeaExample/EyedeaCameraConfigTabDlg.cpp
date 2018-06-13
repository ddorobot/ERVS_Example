// EyedeaCameraConfigTabDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "EyedeaCameraConfigTabDlg.h"
#include "afxdialogex.h"
#include "EyedeaExampleDlg.h"


// CEyedeaCameraConfigTabDlg ��ȭ �����Դϴ�.

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
	m_Slider_Camera_Exposure.SetRange(0, 1 << 16, TRUE);
	m_Slider_Camera_Exposure.SetPos((1 << 16) / 2);


	m_Slider_Camera_GAIN.SetRange(0, 1 << 9, TRUE);
	m_Slider_Camera_GAIN.SetPos((1 << 9) / 2);
	
	m_Slider_Camera_Exposure.EnableWindow(FALSE);
	m_Slider_Camera_GAIN.EnableWindow(FALSE);
	
	m_Slider_Camera_LED_Brightness.SetRange(10, 1000, TRUE);
	m_Slider_Camera_LED_Brightness.SetPos((500) / 2);

	m_Slider_Camera_LED_Brightness_Timer.SetRange(10, 1000, TRUE);
	m_Slider_Camera_LED_Brightness_Timer.SetPos((500) / 2);

	m_Slider_Camera_Focus.SetRange(0, 386, TRUE);
	m_Slider_Camera_Focus.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEyedeaCameraConfigTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_Exposure, m_Slider_Camera_Exposure);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_GAIN, m_Slider_Camera_GAIN);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_LED_BRIGHTNESS, m_Slider_Camera_LED_Brightness);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_LED_BRIGHTNESS_TIMER, m_Slider_Camera_LED_Brightness_Timer);
	DDX_Control(pDX, IDC_CHECK_OPTION_CAMERA_EXPOSURE, m_CheckManualExposure);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_FOCUS_VAL, m_Slider_Camera_Focus);
}


BEGIN_MESSAGE_MAP(CEyedeaCameraConfigTabDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_OPTION_CAMERA_EXPOSURE, &CEyedeaCameraConfigTabDlg::OnBnClickedCheckOptionCameraExposure)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_TAKEPIC, &CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraTakepic)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_TIMER_LED, &CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraTimerLed)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_SET_DEFAULT, &CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraSetDefault)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_SAVE_PARAM, &CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraSaveParam)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_LOAD_PARAM, &CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraLoadParam)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_SAVE_PARAM_WITH_ID, &CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraSaveParamWithId)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_LOAD_PARAM_WITH_ID, &CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraLoadParamWithId)
	ON_BN_CLICKED(IDC_CHECK_OPTION_CAMERA_AUTOFOCUS, &CEyedeaCameraConfigTabDlg::OnBnClickedCheckOptionCameraAutofocus)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_FOCUS_GET_ENV, &CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraFocusGetEnv)
END_MESSAGE_MAP()

void CEyedeaCameraConfigTabDlg::OnBnClickedCheckOptionCameraExposure()
{
	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_OPTION_CAMERA_EXPOSURE);

	if (bCheck)
	{
		m_Slider_Camera_Exposure.EnableWindow(TRUE);
		m_Slider_Camera_GAIN.EnableWindow(TRUE);

		ERVS_SetCameraConfig(SET_CAMERA_MANUAL_EXPOSURE, 0, 0);
	}
	else
	{
		m_Slider_Camera_Exposure.EnableWindow(FALSE);
		m_Slider_Camera_GAIN.EnableWindow(FALSE);

		ERVS_SetCameraConfig(SET_CAMERA_AUTO_EXPOSURE, 0, 0);
	}
}


void CEyedeaCameraConfigTabDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	else if (pScrollBar == (CScrollBar *)&m_Slider_Camera_LED_Brightness) {
		int value = m_Slider_Camera_LED_Brightness.GetPos();
		CString str;
		str.Format(_T("%d"), value);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_LED_BRIGHTNESS)->SetWindowText(str);
		//		printf("%d\n", value);
		ERVS_SetCameraConfig(SET_CAMERA_LED_BRIGHTNESS, value, 0);
	}
	else if (pScrollBar == (CScrollBar *)&m_Slider_Camera_LED_Brightness_Timer) {
		int value = m_Slider_Camera_LED_Brightness_Timer.GetPos();
		CString str;
		str.Format(_T("%d"), value);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_LED_BRIGHTNESS_TIMER)->SetWindowText(str);
		//		printf("%d\n", value);
	}
	else if (pScrollBar == (CScrollBar *)&m_Slider_Camera_Focus) {

		BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_OPTION_CAMERA_AUTOFOCUS);
		if (bCheck == true)
		{
			((CButton*)GetDlgItem(IDC_CHECK_OPTION_CAMERA_AUTOFOCUS))->SetCheck(0);
		}

		int value = m_Slider_Camera_Focus.GetPos();
		CString str;
		str.Format(_T("%d"), value);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_FOCUSVAL)->SetWindowText(str);
		//		printf("%d\n", value);
		ERVS_SetCameraConfig(SET_CAMERA_FOCUS_VALUE, value, 0);
	}
	else {
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraTakepic()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ERVS_SetCameraConfig(SET_CAMERA_TAKE_PIC, 0, 0);
}


void CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraTimerLed()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int value = m_Slider_Camera_LED_Brightness_Timer.GetPos();
	CString str;
	GetDlgItem(IDC_EDIT_CAMERA_VAL_LED_ONTIME)->GetWindowText(str);
	int ms = (int)_ttof(str);
	ERVS_SetCameraConfig(SET_CAMERA_LED_TIMER_ON, value, ms);
}


BOOL CEyedeaCameraConfigTabDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;                // Do not process further
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CEyedeaCameraConfigTabDlg::SetCameraConfigUI()
{
	int aex_enter = -2;
	int aex_goout = -2;
	int isManualExposure = -2;
	int exposure = -2;
	int gain = -2;
	int ledbright = -2;

	int gain_max = -2;
	int exposure_max = -2;
	int gain_min = -2;
	int exposure_min = -2;

	ledbright = ERVS_GetCameraConfig(GET_CAMERA_LED_BRIGHTNESS);
	isManualExposure = ERVS_GetCameraConfig(GET_CAMERA_MANUAL_EXPOSURE);
	aex_goout = ERVS_GetCameraConfig(GET_CAMERA_AUTO_EXPOSURE_RANGE_GO_OUT);
	aex_enter = ERVS_GetCameraConfig(GET_CAMERA_AUTO_EXPOSURE_RANGE_ENTER);
	exposure = ERVS_GetCameraConfig(GET_CAMERA_MANUAL_EXPOSURE_EXPOSURE);
	gain = ERVS_GetCameraConfig(GET_CAMERA_MANUAL_EXPOSURE_GAIN);

	gain_max = ERVS_GetCameraConfig(GET_CAMERA_MANUAL_EXPOSURE_GAIN_MAX);
	exposure_max = ERVS_GetCameraConfig(GET_CAMERA_MANUAL_EXPOSURE_EXPOSURE_MAX);

	gain_min = ERVS_GetCameraConfig(GET_CAMERA_MANUAL_EXPOSURE_GAIN_MIN);
	exposure_min = ERVS_GetCameraConfig(GET_CAMERA_MANUAL_EXPOSURE_EXPOSURE_MIN);


	printf(" isManualExposure = 0x%x \n", isManualExposure);
	printf(" aex_goout = 0x%x \n", aex_goout);
	printf(" aex_enter = 0x%x \n", aex_enter);
	printf(" exposure = 0x%x \n", exposure);
	printf(" gain = 0x%x \n", gain);
	printf(" ledbright = 0x%x \n", ledbright);
	printf(" gain max = 0x%x \n", gain_max);
	printf(" exposure max = 0x%x \n", exposure_max);
	printf(" gain min = 0x%x \n", gain_min);
	printf(" exposure min = 0x%x \n", exposure_min);


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	if (exposure_min != -1 && exposure_max != -1)
	{
		m_Slider_Camera_Exposure.SetRange(exposure_min, exposure_max, TRUE);
		m_Slider_Camera_GAIN.SetRange(gain_min, gain_max, TRUE);
	}

	if (isManualExposure == 0) // 0 = auto
	{
		m_CheckManualExposure.SetCheck(false);
		OnBnClickedCheckOptionCameraExposure();
		//GetDlgItem(IDC_CHECK_OPTION_CAMERA_EXPOSURE)->SetCheck(1);
	}
	else
	{
		m_CheckManualExposure.SetCheck(true);
		OnBnClickedCheckOptionCameraExposure();
		m_Slider_Camera_Exposure.SetPos(exposure);

		CString str;
		str.Format(_T("%d"), exposure);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_EXPOSURE)->SetWindowText(str);

		m_Slider_Camera_GAIN.SetPos(gain);

		str.Format(_T("%d"), gain);
		GetDlgItem(IDC_EDIT_CAMERA_VAL_GAIN)->SetWindowText(str);

	}
	m_Slider_Camera_LED_Brightness.SetPos(ledbright);
	CString str;
	str.Format(_T("%d"), ledbright);
	GetDlgItem(IDC_EDIT_CAMERA_VAL_LED_BRIGHTNESS)->SetWindowText(str);

	OnBnClickedButtonCameraFocusGetEnv();
}

void CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraSetDefault()
{
	ERVS_SetCameraConfig_Default();
	SetCameraConfigUI();
}

void CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraSaveParam()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ERVS_SetCameraConfig_Save();
	//	SetCameraConfigUI();
}

void CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraLoadParam()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ERVS_SetCameraConfig_Load();
	SetCameraConfigUI();
}


void CEyedeaCameraConfigTabDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	SetCameraConfigUI();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraSaveParamWithId()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	GetDlgItem(IDC_EDIT_CAMERA_CONFIG_ID)->GetWindowText(str);
	int ConfigID = (int)_ttof(str);
	ERVS_SetCameraConfig_Save_With_ID(ConfigID);
}


void CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraLoadParamWithId()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	GetDlgItem(IDC_EDIT_CAMERA_CONFIG_ID)->GetWindowText(str);
	int ConfigID = (int)_ttof(str);
	ERVS_SetCameraConfig_Load_With_ID(ConfigID);
	SetCameraConfigUI();
}


void CEyedeaCameraConfigTabDlg::OnBnClickedCheckOptionCameraAutofocus()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_OPTION_CAMERA_AUTOFOCUS);

	if (bCheck == true)
	{
		ERVS_SetCameraConfig(SET_CAMERA_FOCUS_AUTO, 0, 0);
	}
}


void CEyedeaCameraConfigTabDlg::OnBnClickedButtonCameraFocusGetEnv()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int use_auto_focus = ERVS_GetCameraConfig(GET_CAMERA_FOCUS_AUTO);
	int camera_focus_value = ERVS_GetCameraConfig(GET_CAMERA_FOCUS_VALUE);

	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_OPTION_CAMERA_AUTOFOCUS);

	CString focus;
	if (use_auto_focus == 1)
	{
		focus = "USE AUTO FOCUS\r\n";
		if (bCheck == false)
		{
			((CButton*)GetDlgItem(IDC_CHECK_OPTION_CAMERA_AUTOFOCUS))->SetCheck(1);
		}
	}
	else
	{
		focus = "MANUAL FOCUS\r\n";
		if (bCheck == true)
		{
			((CButton*)GetDlgItem(IDC_CHECK_OPTION_CAMERA_AUTOFOCUS))->SetCheck(0);
		}
	}
	m_Slider_Camera_Focus.SetPos(camera_focus_value);

	CString str;
	str.Format(_T("FOCUS VAL:%d"), camera_focus_value);

	GetDlgItem(IDC_EDIT_CAMERA_FOCUS_ENV)->SetWindowText(focus+str);
}
