// EyedeaSearchAreaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "EyedeaSearchAreaDlg.h"
#include "afxdialogex.h"
#include "EyedeaExampleDlg.h"

// CEyedeaSearchAreaDlg dialog

IMPLEMENT_DYNAMIC(CEyedeaSearchAreaDlg, CDialogEx)

CEyedeaSearchAreaDlg::CEyedeaSearchAreaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SEARCH_AREA, pParent)
{
	m_image_result = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
}

CEyedeaSearchAreaDlg::~CEyedeaSearchAreaDlg()
{
}

void CEyedeaSearchAreaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEyedeaSearchAreaDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_SEARCH_AREA, &CEyedeaSearchAreaDlg::OnBnClickedButtonSelectSearchArea)
	ON_BN_CLICKED(IDC_BUTTON_FIND_SEARCH_AREA, &CEyedeaSearchAreaDlg::OnBnClickedButtonFindSearchArea)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_AREA_CONFIG_GET, &CEyedeaSearchAreaDlg::OnBnClickedButtonSearchAreaConfigGet)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_AREA_CONFIG_SET, &CEyedeaSearchAreaDlg::OnBnClickedButtonSearchAreaConfigSet)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_AREA_CONFIG_REMAKE, &CEyedeaSearchAreaDlg::OnBnClickedButtonSearchAreaConfigRemake)
END_MESSAGE_MAP()


// CEyedeaSearchAreaDlg message handlers


void CEyedeaSearchAreaDlg::OnBnClickedButtonSelectSearchArea()
{
	// TODO: Add your control notification handler code here
	((CEyedeaExampleDlg *)GetParent())->m_command = USER_COMMAND_SELECT_SEARCH_AREA;

	//((CEyedeaExampleDlg *)GetParent())->m_combo_get_image_option.SetCurSel(1);		//Set Base Image
}


void CEyedeaSearchAreaDlg::OnBnClickedButtonFindSearchArea()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_SEARCH_AREA_FIND_LEVEL)->GetWindowText(str);
	int level = _ttoi(str);

	ERVS_FindSearchArea(level);

	BOOL bArrow = IsDlgButtonChecked(IDC_CHECK_SEARCH_AREA_RESULT_WITH_ARROW);
	BOOL bBox = IsDlgButtonChecked(IDC_CHECK_SEARCH_AREA_RESULT_WITH_BOX);
	BOOL bFeature = IsDlgButtonChecked(IDC_CHECK_SEARCH_AREA_RESULT_FEATURE);

	int option = 0;
	if (bArrow) option |= RESULT_DRAW_OPTION_SEARCH_ARROW;
	if (bBox) option |= RESULT_DRAW_OPTION_SEARCH_BOX;
	if (bFeature) option |= RESULT_DRAW_OPTION_SEARCH_FEAT;

	//Get Result
	int len = 921600;
	ERVS_GetImage(GET_IMAGE_SEARCH_AREA_FIND_RESULT, option, (char**)&m_image_result.data, &len);
}

void CEyedeaSearchAreaDlg::ThreadFunctionDraw()
{
	cv::Mat image_ori = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
	cv::Mat image_result = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display

	CRect rect_display_ori;													//display rect
	GetDlgItem(IDC_STATIC_IMAGE_SEARCH_AREA)->GetClientRect(&rect_display_ori);			//get rect information on window
	CClientDC dc_display_ori(GetDlgItem(IDC_STATIC_IMAGE_SEARCH_AREA));					//device context for display mfc control

	CRect rect_display_ori2;													
	GetDlgItem(IDC_STATIC_IMAGE_SEARCH_AREA2)->GetClientRect(&rect_display_ori2);
	CClientDC dc_display_ori2(GetDlgItem(IDC_STATIC_IMAGE_SEARCH_AREA2));		

	CvvImage vImage;		//display class for display on MFC control

	while (m_run_thread)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(1));

		if (m_b_draw_pause)
		{
			continue;
		}

		int len = 921600;
		ERVS_GetImage(GET_IMAGE_SEARCH_AREA_INFO, 0, (char**)&image_ori.data, &len);

		vImage.CopyOf(&IplImage(image_ori), 1);							//mat to vimage
		vImage.DrawToHDC(dc_display_ori.m_hDC, &rect_display_ori);				//draw on display_rect

		vImage.CopyOf(&IplImage(m_image_result), 1);							//mat to vimage
		vImage.DrawToHDC(dc_display_ori2.m_hDC, &rect_display_ori2);				//draw on display_rect
	};
}

BOOL CEyedeaSearchAreaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	CString str;
	str.Format(_T("-"));
	GetDlgItem(IDC_EDIT_SA_CONFIG_BLUR)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_DENOISE)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_THRE1)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_THRE2)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_RATIO)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_KERNEL_SIZE)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_MATCHING_MARGIN)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_RANGE_MIN)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_RANGE_MAX)->SetWindowText(str);

	str.Format(_T("5"));
	GetDlgItem(IDC_EDIT_SEARCH_AREA_FIND_LEVEL)->SetWindowText(str);
	
	CheckDlgButton(IDC_CHECK_SEARCH_AREA_RESULT_WITH_ARROW, TRUE);
	CheckDlgButton(IDC_CHECK_SEARCH_AREA_RESULT_WITH_BOX, TRUE);
	CheckDlgButton(IDC_CHECK_SEARCH_AREA_RESULT_FEATURE, FALSE);

	//start Thread
	//eyedea - start of thread
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CEyedeaSearchAreaDlg::ThreadFunctionDraw, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CEyedeaSearchAreaDlg::OnBnClickedButtonSearchAreaConfigGet()
{
	// TODO: Add your control notification handler code here
	float blur = ERVS_GetVisionConfigOption(SEARCHAREA_VISION_CONFIG_BLUR);
	float denoising = ERVS_GetVisionConfigOption(SEARCHAREA_VISION_CONFIG_DENOISING);
	float edge_low_thre = ERVS_GetVisionConfigOption(SEARCHAREA_VISION_CONFIG_EDGE_LOW_THRESHOLD);
	float edge_max_thre = ERVS_GetVisionConfigOption(SEARCHAREA_VISION_CONFIG_EDGE_MAX_LOW_THRESHOLD);
	float edge_ratio = ERVS_GetVisionConfigOption(SEARCHAREA_VISION_CONFIG_EDGE_RATIO);
	float edge_kernel_size = ERVS_GetVisionConfigOption(SEARCHAREA_VISION_CONFIG_EDGE_KERNEL_SIZE);
	float edge_margin = ERVS_GetVisionConfigOption(SEARCHAREA_VISION_CONFIG_EDGE_MATCHING_MARGIN);

	float range_min = ERVS_GetVisionConfigOption(SEARCHAREA_VISION_CONFIG_RANGE_MIN);
	float range_max = ERVS_GetVisionConfigOption(SEARCHAREA_VISION_CONFIG_RANGE_MAX);

	CString str;
	str.Format(_T("%.2f"), blur);
	GetDlgItem(IDC_EDIT_SA_CONFIG_BLUR)->SetWindowText(str);
	str.Format(_T("%.2f"), denoising);
	GetDlgItem(IDC_EDIT_SA_CONFIG_DENOISE)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_low_thre);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_THRE1)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_max_thre);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_THRE2)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_ratio);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_RATIO)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_kernel_size);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_KERNEL_SIZE)->SetWindowText(str);
	str.Format(_T("%.2f"), edge_margin);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_MATCHING_MARGIN)->SetWindowText(str);

	str.Format(_T("%.2f"), range_min);
	GetDlgItem(IDC_EDIT_SA_CONFIG_RANGE_MIN)->SetWindowText(str);

	str.Format(_T("%.2f"), range_max);
	GetDlgItem(IDC_EDIT_SA_CONFIG_RANGE_MAX)->SetWindowText(str);
}


void CEyedeaSearchAreaDlg::OnBnClickedButtonSearchAreaConfigSet()
{
	// TODO: Add your control notification handler code here
	float blur = 0.0; // ERVS_GetVisionConfigOption(VISION_CONFIG_BLUR);
	float denoising = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_DENOISING);
	float edge_low_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_LOW_THRESHOLD);
	float edge_max_thre = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_MAX_LOW_THRESHOLD);
	float edge_ratio = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_RATIO);
	float edge_kernel_size = 0.0; //ERVS_GetVisionConfigOption(VISION_CONFIG_EDGE_KERNEL_SIZE);
	float edge_margin = 0.0;
	float range_min = 0.0;
	float range_max = 0.0;

	CString str;
	GetDlgItem(IDC_EDIT_SA_CONFIG_BLUR)->GetWindowText(str);
	blur = _ttof(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_DENOISE)->GetWindowText(str);
	denoising = _ttof(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_THRE1)->GetWindowText(str);
	edge_low_thre = _ttof(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_THRE2)->GetWindowText(str);
	edge_max_thre = _ttof(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_RATIO)->GetWindowText(str);
	edge_ratio = _ttof(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_KERNEL_SIZE)->GetWindowText(str);
	edge_kernel_size = _ttof(str);
	GetDlgItem(IDC_EDIT_SA_CONFIG_EDGE_MATCHING_MARGIN)->GetWindowText(str);
	edge_margin = _ttof(str);

	GetDlgItem(IDC_EDIT_SA_CONFIG_RANGE_MIN)->GetWindowText(str);
	range_min = _ttof(str);

	GetDlgItem(IDC_EDIT_SA_CONFIG_RANGE_MAX)->GetWindowText(str);
	range_max = _ttof(str);

	//set
	ERVS_SetVisionConfigOption(SEARCHAREA_VISION_CONFIG_BLUR, blur);
	ERVS_SetVisionConfigOption(SEARCHAREA_VISION_CONFIG_DENOISING, denoising);
	ERVS_SetVisionConfigOption(SEARCHAREA_VISION_CONFIG_EDGE_LOW_THRESHOLD, edge_low_thre);
	ERVS_SetVisionConfigOption(SEARCHAREA_VISION_CONFIG_EDGE_MAX_LOW_THRESHOLD, edge_max_thre);
	ERVS_SetVisionConfigOption(SEARCHAREA_VISION_CONFIG_EDGE_RATIO, edge_ratio);
	ERVS_SetVisionConfigOption(SEARCHAREA_VISION_CONFIG_EDGE_KERNEL_SIZE, edge_kernel_size);
	ERVS_SetVisionConfigOption(SEARCHAREA_VISION_CONFIG_EDGE_MATCHING_MARGIN, edge_margin);

	ERVS_SetVisionConfigOption(SEARCHAREA_VISION_CONFIG_RANGE_MIN, range_min);
	ERVS_SetVisionConfigOption(SEARCHAREA_VISION_CONFIG_RANGE_MAX, range_max);

	//check
	OnBnClickedButtonSearchAreaConfigGet();
}


void CEyedeaSearchAreaDlg::OnBnClickedButtonSearchAreaConfigRemake()
{
	// TODO: Add your control notification handler code here
	ERVS_ApplyAndMakeSearchAreaLocalInfo();
}


BOOL CEyedeaSearchAreaDlg::PreTranslateMessage(MSG* pMsg)
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
