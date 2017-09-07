// EyedeaVisionConfigTabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "EyedeaVisionConfigTabDlg.h"
#include "afxdialogex.h"


// CEyedeaVisionConfigTabDlg dialog

IMPLEMENT_DYNAMIC(CEyedeaVisionConfigTabDlg, CDialogEx)

CEyedeaVisionConfigTabDlg::CEyedeaVisionConfigTabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VISION_CONFIG, pParent) 
{

}

CEyedeaVisionConfigTabDlg::~CEyedeaVisionConfigTabDlg()
{
}

void CEyedeaVisionConfigTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO_ENV_OBJECT_TYPE, m_combo_object_type_for_env);
}


BEGIN_MESSAGE_MAP(CEyedeaVisionConfigTabDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VISION_CONFIG_GET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonVisionConfigGet)
	ON_BN_CLICKED(IDC_BUTTON_VISION_CONFIG_SET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonVisionConfigSet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_SEARCH_AREA_GET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionSearchAreaGet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_SEARCH_AREA_SET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionSearchAreaSet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_MASTER_AREA_GET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionMasterAreaGet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_MASTER_AREA_SET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionMasterAreaSet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_GET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectGet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_SET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectSet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_FEATURE_GET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectFeatureGet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_FEATURE_SET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectFeatureSet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_OUTLINE_GET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectOutlineGet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_OUTLINE_SET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectOutlineSet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_RECT_GET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectRectGet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_RECT_SET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectRectSet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_CENTER_GET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectCenterGet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_CENTER_SET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectCenterSet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_ANGLE_GET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectAngleGet)
	//ON_BN_CLICKED(IDC_BUTTON_ENV_OPTION_OBJECT_ANGLE_SET, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectAngleSet)
	ON_BN_CLICKED(IDC_BUTTON_VISION_CONFIG_GET2, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonVisionConfigGet2)
	ON_BN_CLICKED(IDC_BUTTON_VISION_CONFIG_SET2, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonVisionConfigSet2)
	//ON_BN_CLICKED(IDC_BUTTON_CONFIG_FILE_SAVE, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonConfigFileSave)
	//ON_BN_CLICKED(IDC_BUTTON_CONFIG_FILE_LOAD, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonConfigFileLoad)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_VISION_CONFIG_GLOBAL, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonCheckVisionConfigGlobal)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_VISION_CONFIG_LOCAL, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonCheckVisionConfigLocal)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_VISION_CONFIG_GLOBAL, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonApplyVisionConfigGlobal)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_VISION_CONFIG_LOCAL, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonApplyVisionConfigLocal)
	ON_BN_CLICKED(IDC_BUTTON_BG_LEARNING_START, &CEyedeaVisionConfigTabDlg::OnBnClickedButtonBgLearningStart)
END_MESSAGE_MAP()


// CEyedeaVisionConfigTabDlg message handlers


void CEyedeaVisionConfigTabDlg::OnBnClickedButtonVisionConfigGet()
{
	// TODO: Add your control notification handler code here
	float blur = ERVS_GetVisionConfigOption(VISION_CONFIG_BLUR);
	float denoising = ERVS_GetVisionConfigOption(VISION_CONFIG_DENOISING);
	float edge_low_thre = ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_LOW_THRESHOLD);
	float edge_max_thre = ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_MAX_LOW_THRESHOLD);
	float edge_ratio = ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_RATIO);
	float edge_kernel_size = ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_KERNEL_SIZE);
	float morph_size = ERVS_GetVisionConfigOption(VISION_CONFIG_MORPH_SIZE);
	float size_filter = ERVS_GetVisionConfigOption(VISION_CONFIG_SIZE_FILTER);
	float padding = ERVS_GetVisionConfigOption(VISION_CONFIG_BASE_RECT_PADDING);
	float dilation_size = ERVS_GetVisionConfigOption(VISION_CONFIG_DILATION_SIZE);
	float search_value_center = ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_CENTER);
	float search_value_roi = ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_USER_ROI);
	float search_value_search = ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALIE_AREA);
	float search_value_master = ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_OBJECT);
	float circle_detect_inlier_rate = ERVS_GetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_INLIER_RATE);
	float circle_detect_max_iteration = ERVS_GetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_MAX_ITERATION);
	float min_angle = ERVS_GetVisionConfigOption(VISION_CONFIG_L_MIN_ANGLE);
	float max_angle = ERVS_GetVisionConfigOption(VISION_CONFIG_L_MAX_ANGLE);
	float use_candidate_roi = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI);
	float candidate_roi_thre = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI_THRESHOLD);
	float use_candidate_search = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA);
	float candidate_search_thre = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA_THRESHOLD);
	float use_candidate_master = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT);
	float candidate_search_master = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT_THRESHOLD);
	float use_convexhull = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CONVEXHULL);
	float use_bg_sub = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_BGSUB);

	CString str;
	str.Format(_T("%.2f"), blur);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_1)->SetWindowText(str);
	str.Format(_T("%.2f"), denoising);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_2)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_low_thre);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_3)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_max_thre);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_4)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_ratio);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_5)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_kernel_size);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_6)->SetWindowText(str);
	str.Format(_T("%.2f"), morph_size);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_7)->SetWindowText(str);
	str.Format(_T("%.2f"), size_filter);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_8)->SetWindowText(str);
	str.Format(_T("%.2f"), padding);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_9)->SetWindowText(str);
	str.Format(_T("%.2f"), dilation_size);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_10)->SetWindowText(str);

	if (use_convexhull == 0)
	{
		CheckDlgButton(IDC_CHECK__VISION_CONFIG_USE_CONVEXHULL, FALSE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK__VISION_CONFIG_USE_CONVEXHULL, TRUE);
	}

	if (use_bg_sub == 0)
	{
		CheckDlgButton(IDC_CHECK__VISION_CONFIG_USE_BGSUB, FALSE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK__VISION_CONFIG_USE_BGSUB, TRUE);
	}
}


void CEyedeaVisionConfigTabDlg::OnBnClickedButtonVisionConfigSet()
{
	// TODO: Add your control notification handler code here
	float blur = 0.0; // ERVS_GetVisionConfigOption(VISION_CONFIG_BLUR);
	float denoising = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_DENOISING);
	float edge_low_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_LOW_THRESHOLD);
	float edge_max_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_MAX_LOW_THRESHOLD);
	float edge_ratio = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_RATIO);
	float edge_kernel_size = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_KERNEL_SIZE);
	float morph_size = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_MORPH_SIZE);
	float size_filter = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SIZE_FILTER);
	float padding = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_BASE_RECT_PADDING);
	float dilation_size = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_DILATION_SIZE);
	float matching_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_MATCHING_THRESHOLD);
	float search_value_center = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_CENTER);
	float search_value_roi = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_USER_ROI);
	float search_value_search = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALIE_AREA);
	float search_value_master = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_OBJECT);
	float circle_detect_inlier_rate = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_INLIER_RATE);
	float circle_detect_max_iteration = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_MAX_ITERATION);
	float min_angle = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_L_MIN_ANGLE);
	float max_angle = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_L_MAX_ANGLE);
	float scene_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SCENE_THRESHOLD);
	float use_candidate_roi = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI);
	float candidate_roi_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI_THRESHOLD);
	float use_candidate_search = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA);
	float candidate_search_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA_THRESHOLD);
	float use_candidate_master = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT);
	float candidate_search_master = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT_THRESHOLD);
	float use_convexhull = 0.0; 
	float use_bgsub = 0.0;

	CString str;
	GetDlgItem(IDC_EDIT_VISION_CONFIG_1)->GetWindowText(str);
	blur = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_2)->GetWindowText(str);
	denoising = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_3)->GetWindowText(str);
	edge_low_thre = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_4)->GetWindowText(str);
	edge_max_thre = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_5)->GetWindowText(str);
	edge_ratio = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_6)->GetWindowText(str);
	edge_kernel_size = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_7)->GetWindowText(str);
	morph_size = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_8)->GetWindowText(str);
	size_filter = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_9)->GetWindowText(str);
	padding = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_10)->GetWindowText(str);
	dilation_size = _ttof(str);

	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK__VISION_CONFIG_USE_CONVEXHULL);
	if (bCheck)
	{
		use_convexhull = 1.0;
	}
	else
	{
		use_convexhull = 0.0;
	}

	bCheck = IsDlgButtonChecked(IDC_CHECK__VISION_CONFIG_USE_BGSUB);
	if (bCheck)
	{
		use_bgsub = 1.0;
	}
	else
	{
		use_bgsub = 0.0;
	}

	//set
	ERVS_SetVisionConfigOption(VISION_CONFIG_BLUR, blur);
	ERVS_SetVisionConfigOption(VISION_CONFIG_DENOISING, denoising);
	ERVS_SetVisionConfigOption(VISION_CONFIG_EDGE_LOW_THRESHOLD, edge_low_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_EDGE_MAX_LOW_THRESHOLD, edge_max_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_EDGE_RATIO, edge_ratio);
	ERVS_SetVisionConfigOption(VISION_CONFIG_EDGE_KERNEL_SIZE, edge_kernel_size);
	ERVS_SetVisionConfigOption(VISION_CONFIG_MORPH_SIZE, morph_size);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SIZE_FILTER, size_filter);
	ERVS_SetVisionConfigOption(VISION_CONFIG_BASE_RECT_PADDING, padding);
	ERVS_SetVisionConfigOption(VISION_CONFIG_DILATION_SIZE, dilation_size);
	ERVS_SetVisionConfigOption(VISION_CONFIG_MATCHING_THRESHOLD, matching_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_CENTER, search_value_center);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_USER_ROI, search_value_roi);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SEARCH_VALIE_AREA, search_value_search);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_OBJECT, search_value_master);
	ERVS_SetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_INLIER_RATE, circle_detect_inlier_rate);
	ERVS_SetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_MAX_ITERATION, circle_detect_max_iteration);
	ERVS_SetVisionConfigOption(VISION_CONFIG_L_MIN_ANGLE, min_angle);
	ERVS_SetVisionConfigOption(VISION_CONFIG_L_MAX_ANGLE, max_angle);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SCENE_THRESHOLD, scene_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI, use_candidate_roi);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI_THRESHOLD, candidate_roi_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA, use_candidate_search);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA_THRESHOLD, candidate_search_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT, use_candidate_master);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT_THRESHOLD, candidate_search_master);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CONVEXHULL, use_convexhull);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_BGSUB, use_bgsub);

	OnBnClickedButtonVisionConfigGet();
}


BOOL CEyedeaVisionConfigTabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString str;
	/*
	str.Format(_T("-"));
	GetDlgItem(IDC_EDIT_VISION_CONFIG_1)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_2)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_3)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_4)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_5)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_6)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_7)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_8)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_9)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_10)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_11)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_27)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_28)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_29)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_30)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_31)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_32)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_33)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_34)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_35)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_36)->SetWindowText(str);
	
	GetDlgItem(IDC_EDIT_VISION_CONFIG_EDGE_MATCHING_MARGIN)->SetWindowText(str);
	*/

	//start Thread
	//eyedea - start of thread
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CEyedeaVisionConfigTabDlg::ThreadFunctionDraw, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEyedeaVisionConfigTabDlg::ThreadFunctionDraw()
{
	m_b_draw_pause = false;

	CRect rect_display_global;													//display rect
	GetDlgItem(IDC_STATIC_IMAGE_CHECK_GLOBAL)->GetClientRect(&rect_display_global);			//get rect information on window
	CClientDC dc_display_global(GetDlgItem(IDC_STATIC_IMAGE_CHECK_GLOBAL));					//device context for display mfc control

	CRect rect_display_local;													//display rect
	GetDlgItem(IDC_STATIC_IMAGE_CHECK_LOCAL)->GetClientRect(&rect_display_local);			//get rect information on window
	CClientDC dc_display_local(GetDlgItem(IDC_STATIC_IMAGE_CHECK_LOCAL));					//device context for display mfc control

	CvvImage vImage;		//display class for display on MFC control

	if (m_check_image.empty())
	{
		m_check_image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
	}

	if (m_check_image2.empty())
	{
		m_check_image2 = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
	}

	while (m_run_thread)
	{
		if (m_b_draw_pause)
		{
			boost::this_thread::sleep(boost::posix_time::millisec(1));
			continue;
		}

		//int len = 921600;
		//ERVS_GetImage(GET_IMAGE_CALIBRATION_FEATURE, 0, (char**)&m_check_image.data, &len);

		vImage.CopyOf(&IplImage(m_check_image), 1);							//mat to vimage
		vImage.DrawToHDC(dc_display_global .m_hDC, &rect_display_global);				//draw on display_rect

		vImage.CopyOf(&IplImage(m_check_image2), 1);							//mat to vimage
		vImage.DrawToHDC(dc_display_local.m_hDC, &rect_display_local);				//draw on display_rect
	};
}

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionSearchAreaGet()
{
	// TODO: Add your control notification handler code here

	int red = 0, green = 0, blue = 0;
	ERVS_GetSearchAreaColor(&red, &green, &blue);

	CString strColor;
	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_COLOR_BLUE)->SetWindowText(strColor);

	int width = ERVS_GetSearchAreaWidth();

	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionSearchAreaSet()
{
	// TODO: Add your control notification handler code here
	CString strColor;
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_COLOR_RED)->GetWindowText(strColor);
	int red = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_COLOR_GREEN)->GetWindowText(strColor);
	int green = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_COLOR_BLUE)->GetWindowText(strColor);
	int blue = _ttoi(strColor);

	ERVS_SetSearchAreaColor(red, green, blue);

	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_WIDTH)->GetWindowText(strColor);
	int width = _ttoi(strColor);

	ERVS_SetSearchAreaWidth(width);

	//cross check
	ERVS_GetSearchAreaColor(&red, &green, &blue);
	width = ERVS_GetSearchAreaWidth();

	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_COLOR_BLUE)->SetWindowText(strColor);
	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_SEARCH_AREA_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionMasterAreaGet()
{
	// TODO: Add your control notification handler code here
	int red = 0, green = 0, blue = 0;
	ERVS_GetMasterAreaColor(&red, &green, &blue);

	CString strColor;
	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_COLOR_BLUE)->SetWindowText(strColor);

	int width = ERVS_GetMasterAreaWidth();

	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionMasterAreaSet()
{
	// TODO: Add your control notification handler code here
	CString strColor;
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_COLOR_RED)->GetWindowText(strColor);
	int red = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_COLOR_GREEN)->GetWindowText(strColor);
	int green = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_COLOR_BLUE)->GetWindowText(strColor);
	int blue = _ttoi(strColor);

	ERVS_SetMasterAreaColor(red, green, blue);

	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_WIDTH)->GetWindowText(strColor);
	int width = _ttoi(strColor);

	ERVS_SetMasterAreaWidth(width);

	//cross check
	ERVS_GetMasterAreaColor(&red, &green, &blue);
	width = ERVS_GetMasterAreaWidth();

	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_COLOR_BLUE)->SetWindowText(strColor);
	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_MASTER_AREA_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectGet()
{
	// TODO: Add your control notification handler code here
	int object = m_combo_object_type_for_env.GetCurSel();		//Set Master Image

	int red = 0, green = 0, blue = 0;
	ERVS_GetObjectColor(object, &red, &green, &blue);

	CString strColor;
	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_COLOR_BLUE)->SetWindowText(strColor);

	int width = ERVS_GetObjectWidth(object);

	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectSet()
{
	// TODO: Add your control notification handler code here
	int object = m_combo_object_type_for_env.GetCurSel();		//Set Master Image

	CString strColor;
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_COLOR_RED)->GetWindowText(strColor);
	int red = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_COLOR_GREEN)->GetWindowText(strColor);
	int green = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_COLOR_BLUE)->GetWindowText(strColor);
	int blue = _ttoi(strColor);

	ERVS_SetObjectColor(object, red, green, blue);

	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_WIDTH)->GetWindowText(strColor);
	int width = _ttoi(strColor);

	ERVS_SetObjectWidth(object, width);

	//cross check
	ERVS_GetObjectColor(object, &red, &green, &blue);
	width = ERVS_GetObjectWidth(object);

	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_COLOR_BLUE)->SetWindowText(strColor);
	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectFeatureGet()
{
	// TODO: Add your control notification handler code here
	int use_feature = ERVS_GetObjectFeatureUse();
	if (use_feature)
	{
		CheckDlgButton(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_FEATUER, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_FEATUER, FALSE);
	}

	int red = 0, green = 0, blue = 0;
	ERVS_GetObjectFeatureColor(&red, &green, &blue);

	CString strColor;
	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_FEATUER_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_FEATURE_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_FEATURE_COLOR_BLUE)->SetWindowText(strColor);

	int width = ERVS_GetObjectFeatureWidth();

	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_FEATURE_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectFeatureSet()
{
	// TODO: Add your control notification handler code here
	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_FEATUER);
	if (bCheck)
	{
		ERVS_SetObjectFeatureUse(1);
	}
	else
	{
		ERVS_SetObjectFeatureUse(0);
	}

	CString strColor;
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_FEATUER_COLOR_RED)->GetWindowText(strColor);
	int red = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_FEATURE_COLOR_GREEN)->GetWindowText(strColor);
	int green = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_FEATURE_COLOR_BLUE)->GetWindowText(strColor);
	int blue = _ttoi(strColor);

	ERVS_SetObjectFeatureColor(red, green, blue);

	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_FEATURE_WIDTH)->GetWindowText(strColor);
	int width = _ttoi(strColor);

	ERVS_SetObjectFeatureWidth(width);

	OnBnClickedButtonEnvOptionObjectFeatureGet();
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectOutlineGet()
{
	// TODO: Add your control notification handler code here
	int use_outline = ERVS_GetObjectOutlineUse();
	if (use_outline)
	{
		CheckDlgButton(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_OUTLINE, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_OUTLINE, FALSE);
	}

	int red = 0, green = 0, blue = 0;
	ERVS_GetObjectOutlineColor(&red, &green, &blue);

	CString strColor;
	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_OUTLINE_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_OUTLINE_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_OUTLINE_COLOR_BLUE)->SetWindowText(strColor);

	int width = ERVS_GetObjectOutlineWidth();

	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_OUTLINE_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectOutlineSet()
{
	// TODO: Add your control notification handler code here
	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_OUTLINE);
	if (bCheck)
	{
		ERVS_SetObjectOutlineUse(1);
	}
	else
	{
		ERVS_SetObjectOutlineUse(0);
	}

	CString strColor;
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_OUTLINE_COLOR_RED)->GetWindowText(strColor);
	int red = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_OUTLINE_COLOR_GREEN)->GetWindowText(strColor);
	int green = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_OUTLINE_COLOR_BLUE)->GetWindowText(strColor);
	int blue = _ttoi(strColor);

	ERVS_SetObjectOutlineColor(red, green, blue);

	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_OUTLINE_WIDTH)->GetWindowText(strColor);
	int width = _ttoi(strColor);

	ERVS_SetObjectOutlineWidth(width);

	OnBnClickedButtonEnvOptionObjectOutlineGet();
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectRectGet()
{
	// TODO: Add your control notification handler code here
	int use_rect = ERVS_GetObjectRectUse();
	if (use_rect)
	{
		CheckDlgButton(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_RECT, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_RECT, FALSE);
	}

	int red = 0, green = 0, blue = 0;
	ERVS_GetObjectRectColor(&red, &green, &blue);

	CString strColor;
	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_RECT_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_RECT_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_RECT_COLOR_BLUE)->SetWindowText(strColor);

	int width = ERVS_GetObjectRectWidth();

	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_RECT_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectRectSet()
{
	// TODO: Add your control notification handler code here
	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_RECT);
	if (bCheck)
	{
		ERVS_SetObjectRectUse(1);
	}
	else
	{
		ERVS_SetObjectRectUse(0);
	}

	CString strColor;
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_RECT_COLOR_RED)->GetWindowText(strColor);
	int red = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_RECT_COLOR_GREEN)->GetWindowText(strColor);
	int green = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_RECT_COLOR_BLUE)->GetWindowText(strColor);
	int blue = _ttoi(strColor);

	ERVS_SetObjectRectColor(red, green, blue);

	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_RECT_WIDTH)->GetWindowText(strColor);
	int width = _ttoi(strColor);

	ERVS_SetObjectRectWidth(width);

	OnBnClickedButtonEnvOptionObjectRectGet();
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectCenterGet()
{
	// TODO: Add your control notification handler code here
	int use_center = ERVS_GetObjectCenterUse();
	if (use_center)
	{
		CheckDlgButton(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_CENTER, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_CENTER, FALSE);
	}

	int red = 0, green = 0, blue = 0;
	ERVS_GetObjectCenterColor(&red, &green, &blue);

	CString strColor;
	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_CENTER_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_CENTER_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_CENTER_COLOR_BLUE)->SetWindowText(strColor);

	int width = ERVS_GetObjectCenterWidth();

	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_CENTER_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectCenterSet()
{
	// TODO: Add your control notification handler code here
	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_CENTER);
	if (bCheck)
	{
		ERVS_SetObjectCenterUse(1);
	}
	else
	{
		ERVS_SetObjectCenterUse(0);
	}

	CString strColor;
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_CENTER_COLOR_RED)->GetWindowText(strColor);
	int red = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_CENTER_COLOR_GREEN)->GetWindowText(strColor);
	int green = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_CENTER_COLOR_BLUE)->GetWindowText(strColor);
	int blue = _ttoi(strColor);

	ERVS_SetObjectCenterColor(red, green, blue);

	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_CENTER_WIDTH)->GetWindowText(strColor);
	int width = _ttoi(strColor);

	ERVS_SetObjectCenterWidth(width);

	OnBnClickedButtonEnvOptionObjectCenterGet();
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectAngleGet()
{
	// TODO: Add your control notification handler code here
	int use_angle = ERVS_GetObjectAngleUse();
	if (use_angle)
	{
		CheckDlgButton(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_ANGLE, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_ANGLE, FALSE);
	}

	int red = 0, green = 0, blue = 0;
	ERVS_GetObjectAngleColor(&red, &green, &blue);

	CString strColor;
	strColor.Format(_T("%d"), red);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_ANGLE_COLOR_RED)->SetWindowText(strColor);
	strColor.Format(_T("%d"), green);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_ANGLE_COLOR_GREEN)->SetWindowText(strColor);
	strColor.Format(_T("%d"), blue);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_ANGLE_COLOR_BLUE)->SetWindowText(strColor);

	int width = ERVS_GetObjectAngleWidth();

	strColor.Format(_T("%d"), width);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_ANGLE_WIDTH)->SetWindowText(strColor);
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonEnvOptionObjectAngleSet()
{
	// TODO: Add your control notification handler code here
	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_OBJECT_DRAW_OPTION_WITH_ANGLE);
	if (bCheck)
	{
		ERVS_SetObjectAngleUse(1);
	}
	else
	{
		ERVS_SetObjectAngleUse(0);
	}

	CString strColor;
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_ANGLE_COLOR_RED)->GetWindowText(strColor);
	int red = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_ANGLE_COLOR_GREEN)->GetWindowText(strColor);
	int green = _ttoi(strColor);
	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_ANGLE_COLOR_BLUE)->GetWindowText(strColor);
	int blue = _ttoi(strColor);

	ERVS_SetObjectAngleColor(red, green, blue);

	GetDlgItem(IDC_EDIT_ENV_OPTION_OBJECT_ANGLE_WIDTH)->GetWindowText(strColor);
	int width = _ttoi(strColor);

	ERVS_SetObjectAngleWidth(width);

	OnBnClickedButtonEnvOptionObjectAngleGet();
}
#endif

void CEyedeaVisionConfigTabDlg::OnBnClickedButtonVisionConfigGet2()
{
	// TODO: Add your control notification handler code here
	float image_morph_size = ERVS_GetVisionConfigOption(VISION_CONFIG_IMAGE_MORPH_SIZE);

	float blur = ERVS_GetVisionConfigOption(VISION_CONFIG_BLUR2);
	float denoising = ERVS_GetVisionConfigOption(VISION_CONFIG_DENOISING2);
	float edge_low_thre = ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_LOW_THRESHOLD2);
	float edge_max_thre = ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_MAX_LOW_THRESHOLD2);
	float edge_ratio = ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_RATIO2);
	float edge_kernel_size = ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_KERNEL_SIZE2);
	float morph_size = ERVS_GetVisionConfigOption(VISION_CONFIG_MORPH_SIZE2);
	float size_filter = ERVS_GetVisionConfigOption(VISION_CONFIG_SIZE_FILTER2);
	float padding = ERVS_GetVisionConfigOption(VISION_CONFIG_BASE_RECT_PADDING2);
	float dilation_size = ERVS_GetVisionConfigOption(VISION_CONFIG_DILATION_SIZE2);
	float matching_thre = ERVS_GetVisionConfigOption(VISION_CONFIG_MATCHING_THRESHOLD2);
	float search_value_center = ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_CENTER2);
	float search_value_roi = ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_USER_ROI2);
	float search_value_search = ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALIE_AREA2);
	float search_value_master = ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_OBJECT2);
	float circle_detect_inlier_rate = ERVS_GetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_INLIER_RATE2);
	float circle_detect_max_iteration = ERVS_GetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_MAX_ITERATION2);
	//float min_angle = ERVS_GetVisionConfigOption(VISION_CONFIG_L_MIN_ANGLE2);
	//float max_angle = ERVS_GetVisionConfigOption(VISION_CONFIG_L_MAX_ANGLE2);
	float scene_thre = ERVS_GetVisionConfigOption(VISION_CONFIG_SCENE_THRESHOLD2);
	float use_candidate_roi = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI2);
	float candidate_roi_thre = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI_THRESHOLD2);
	float use_candidate_search = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA2);
	float candidate_search_thre = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA_THRESHOLD2);
	float use_candidate_master = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT2);
	float candidate_search_master = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT_THRESHOLD2);
	float edge_margin = ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_MATCHING_MARGIN);
	float masking_option = ERVS_GetVisionConfigOption(VISION_CONFIG_FIND_OBJECT_MASKING_OPTION);
	float masking_option_find_object_threshold = ERVS_GetVisionConfigOption(VISION_CONFIG_FIND_OBJECT_MASKING_OPTION_THRESHOLD);

	CString str;
	str.Format(_T("%.2f"), image_morph_size);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_IMAGE_MORPH)->SetWindowText(str);

	str.Format(_T("%.2f"), blur);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_27)->SetWindowText(str);
	str.Format(_T("%.2f"), denoising);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_28)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_low_thre);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_29)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_max_thre);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_30)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_ratio);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_31)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_kernel_size);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_32)->SetWindowText(str);
	str.Format(_T("%.2f"), morph_size);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_33)->SetWindowText(str);
	str.Format(_T("%.2f"), size_filter);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_34)->SetWindowText(str);
	str.Format(_T("%.2f"), padding);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_35)->SetWindowText(str);
	str.Format(_T("%.2f"), dilation_size);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_36)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_margin);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_EDGE_MATCHING_MARGIN)->SetWindowText(str);
	str.Format(_T("%.2f"), masking_option_find_object_threshold);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_FIND_OBJECT_THRESHOLD)->SetWindowText(str);

	
	if (masking_option == 0)
	{
		CheckDlgButton(IDC_CHECK_FIND_OBJECT_MASKING_OPTION, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_FIND_OBJECT_MASKING_OPTION, FALSE);
	}
}


void CEyedeaVisionConfigTabDlg::OnBnClickedButtonVisionConfigSet2()
{
	// TODO: Add your control notification handler code here
	float image_morph_size = 0.0; // ERVS_GetVisionConfigOption(VISION_CONFIG_BLUR);
	float blur = 0.0; // ERVS_GetVisionConfigOption(VISION_CONFIG_BLUR);
	float denoising = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_DENOISING);
	float edge_low_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_LOW_THRESHOLD);
	float edge_max_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_MAX_LOW_THRESHOLD);
	float edge_ratio = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_RATIO);
	float edge_kernel_size = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_KERNEL_SIZE);
	float morph_size = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_MORPH_SIZE);
	float size_filter = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SIZE_FILTER);
	float padding = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_BASE_RECT_PADDING);
	float dilation_size = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_DILATION_SIZE);
	float matching_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_MATCHING_THRESHOLD);
	float search_value_center = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_CENTER);
	float search_value_roi = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_USER_ROI);
	float search_value_search = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALIE_AREA);
	float search_value_master = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_OBJECT);
	float circle_detect_inlier_rate = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_INLIER_RATE);
	float circle_detect_max_iteration = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_MAX_ITERATION);
	//float min_angle = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_L_MIN_ANGLE);
	//float max_angle = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_L_MAX_ANGLE);
	float scene_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_SCENE_THRESHOLD);
	float use_candidate_roi = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI);
	float candidate_roi_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI_THRESHOLD);
	float use_candidate_search = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA);
	float candidate_search_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA_THRESHOLD);
	float use_candidate_master = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT);
	float candidate_search_master = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT_THRESHOLD);
	float edge_margin = 0.0; 
	float masking_option = 0.0;
	float masking_option_find_threshold = 0.0;

	CString str;
	GetDlgItem(IDC_EDIT_VISION_CONFIG_IMAGE_MORPH)->GetWindowText(str);
	image_morph_size = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_27)->GetWindowText(str);
	blur = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_28)->GetWindowText(str);
	denoising = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_29)->GetWindowText(str);
	edge_low_thre = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_30)->GetWindowText(str);
	edge_max_thre = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_31)->GetWindowText(str);
	edge_ratio = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_32)->GetWindowText(str);
	edge_kernel_size = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_33)->GetWindowText(str);
	morph_size = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_34)->GetWindowText(str);
	size_filter = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_35)->GetWindowText(str);
	padding = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_36)->GetWindowText(str);
	dilation_size = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_EDGE_MATCHING_MARGIN)->GetWindowText(str);
	edge_margin = _ttof(str);
	GetDlgItem(IDC_EDIT_VISION_CONFIG_FIND_OBJECT_THRESHOLD)->GetWindowText(str);
	masking_option_find_threshold = _ttof(str);

	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_FIND_OBJECT_MASKING_OPTION);
	if (bCheck)
	{
		masking_option = 0.0;
	}
	else
	{
		masking_option = 1.0;
	}

	//set
	ERVS_SetVisionConfigOption(VISION_CONFIG_IMAGE_MORPH_SIZE, image_morph_size);
	ERVS_SetVisionConfigOption(VISION_CONFIG_BLUR2, blur);
	ERVS_SetVisionConfigOption(VISION_CONFIG_DENOISING2, denoising);
	ERVS_SetVisionConfigOption(VISION_CONFIG_EDGE_LOW_THRESHOLD2, edge_low_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_EDGE_MAX_LOW_THRESHOLD2, edge_max_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_EDGE_RATIO2, edge_ratio);
	ERVS_SetVisionConfigOption(VISION_CONFIG_EDGE_KERNEL_SIZE2, edge_kernel_size);
	ERVS_SetVisionConfigOption(VISION_CONFIG_MORPH_SIZE2, morph_size);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SIZE_FILTER2, size_filter);
	ERVS_SetVisionConfigOption(VISION_CONFIG_BASE_RECT_PADDING2, padding);
	ERVS_SetVisionConfigOption(VISION_CONFIG_DILATION_SIZE2, dilation_size);
	ERVS_SetVisionConfigOption(VISION_CONFIG_MATCHING_THRESHOLD2, matching_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_CENTER2, search_value_center);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_USER_ROI2, search_value_roi);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SEARCH_VALIE_AREA2, search_value_search);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SEARCH_VALUE_OBJECT2, search_value_master);
	ERVS_SetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_INLIER_RATE2, circle_detect_inlier_rate);
	ERVS_SetVisionConfigOption(VISION_CONFIG_CIRCLE_DETECTION_MAX_ITERATION2, circle_detect_max_iteration);
	//ERVS_SetVisionConfigOption(VISION_CONFIG_L_MIN_ANGLE2, min_angle);
	//ERVS_SetVisionConfigOption(VISION_CONFIG_L_MAX_ANGLE2, max_angle);
	ERVS_SetVisionConfigOption(VISION_CONFIG_SCENE_THRESHOLD2, scene_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI2, use_candidate_roi);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_UROI_THRESHOLD2, candidate_roi_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA2, use_candidate_search);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_AREA_THRESHOLD2, candidate_search_thre);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT2, use_candidate_master);
	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_CANDIDATE_TM_OBJECT_THRESHOLD2, candidate_search_master);
	ERVS_SetVisionConfigOption(VISION_CONFIG_EDGE_MATCHING_MARGIN, edge_margin);
	ERVS_SetVisionConfigOption(VISION_CONFIG_FIND_OBJECT_MASKING_OPTION, masking_option);
	ERVS_SetVisionConfigOption(VISION_CONFIG_FIND_OBJECT_MASKING_OPTION_THRESHOLD, masking_option_find_threshold);
	
	//check
	OnBnClickedButtonVisionConfigGet2();
}

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonConfigFileSave()
{
	// TODO: Add your control notification handler code here
	ERVS_VisionConfigFileSave();
}
#endif

#if 0
void CEyedeaVisionConfigTabDlg::OnBnClickedButtonConfigFileLoad()
{
	// TODO: Add your control notification handler code here
	ERVS_VisionConfigFileLoad();

	//check
	OnBnClickedButtonVisionConfigGet();
	OnBnClickedButtonVisionConfigGet2();
}
#endif

void CEyedeaVisionConfigTabDlg::OnBnClickedButtonCheckVisionConfigGlobal()
{
	// TODO: Add your control notification handler code here
	int len = 921600;		//640*480*3;
	ERVS_GetImage(GET_IMAGE_WITH_INFO, WITH_DRAW_OPTION_FEATURE, (char**)&m_check_image.data, &len);
}


void CEyedeaVisionConfigTabDlg::OnBnClickedButtonCheckVisionConfigLocal()
{
	// TODO: Add your control notification handler code here
	int len = 921600;		//640*480*3;
	ERVS_GetImage(GET_IMAGE_LOCAL, WITH_DRAW_OPTION_FEATURE, (char**)&m_check_image2.data, &len);
}


void CEyedeaVisionConfigTabDlg::OnBnClickedButtonApplyVisionConfigGlobal()
{
	// TODO: Add your control notification handler code here
	ERVS_ApplyAndMakeBaseGlobalInfo();
}


void CEyedeaVisionConfigTabDlg::OnBnClickedButtonApplyVisionConfigLocal()
{
	// TODO: Add your control notification handler code here
	ERVS_ApplyAndMakeBaseLocalInfo();
}


void CEyedeaVisionConfigTabDlg::RoadAllFromERVS()
{
	OnBnClickedButtonVisionConfigGet();
	//OnBnClickedButtonCheckVisionConfigGlobal();
	OnBnClickedButtonVisionConfigGet2();
	//OnBnClickedButtonCheckVisionConfigLocal();
}


void CEyedeaVisionConfigTabDlg::OnBnClickedButtonBgLearningStart()
{
	// TODO: Add your control notification handler code here
	ERVS_BackgroundLearning();
}


BOOL CEyedeaVisionConfigTabDlg::PreTranslateMessage(MSG* pMsg)
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
