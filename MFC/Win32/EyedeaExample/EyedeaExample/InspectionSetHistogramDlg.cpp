// InspectionSetHistogramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "InspectionSetHistogramDlg.h"
#include "afxdialogex.h"


// CInspectionSetHistogramDlg dialog

IMPLEMENT_DYNAMIC(CInspectionSetHistogramDlg, CDialogEx)

CInspectionSetHistogramDlg::CInspectionSetHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_INSPECTION_SET_HISTOGRAM, pParent)
	, m_select_id(0)
	, m_histogram_size(0.0)
	, m_p_histogram(NULL)
	, m_p_histogram_r(NULL)
	, m_p_histogram_g(NULL)
	, m_p_histogram_b(NULL)
	, m_i_histogram_lbdwn_object(-1)
	, m_i_histogmra_gray_min(-1)
	, m_i_histogmra_gray_max(-1)
	, m_i_histogmra_red_min(-1)
	, m_i_histogmra_red_max(-1)
	, m_i_histogmra_green_min(-1)
	, m_i_histogmra_green_max(-1)
	, m_i_histogmra_blue_min(-1)
	, m_i_histogmra_blue_max(-1)
{
	m_result_histogram_image = cv::Mat::zeros(cv::Size(300, 200), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
	m_result_histogram_r_image = cv::Mat::zeros(cv::Size(300, 200), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
	m_result_histogram_g_image = cv::Mat::zeros(cv::Size(300, 200), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
	m_result_histogram_b_image = cv::Mat::zeros(cv::Size(300, 200), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
}

CInspectionSetHistogramDlg::~CInspectionSetHistogramDlg()
{
	if (m_p_histogram != NULL)
	{
		free(m_p_histogram);
		m_p_histogram = NULL;
	}

	if (m_p_histogram_r != NULL)
	{
		free(m_p_histogram_r);
		m_p_histogram_r = NULL;
	}

	if (m_p_histogram_g != NULL)
	{
		free(m_p_histogram_g);
		m_p_histogram_g = NULL;
	}

	if (m_p_histogram_b != NULL)
	{
		free(m_p_histogram_b);
		m_p_histogram_b = NULL;
	}
}

void CInspectionSetHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInspectionSetHistogramDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_HISTO_GET, &CInspectionSetHistogramDlg::OnBnClickedButtonHistoGet)
	ON_BN_CLICKED(IDC_BUTTON_HISTO_SET, &CInspectionSetHistogramDlg::OnBnClickedButtonHistoSet)
	ON_BN_CLICKED(IDC_BUTTON_HISTO_GET2, &CInspectionSetHistogramDlg::OnBnClickedButtonHistoGet2)
	ON_BN_CLICKED(IDC_BUTTON_HISTO_SET2, &CInspectionSetHistogramDlg::OnBnClickedButtonHistoSet2)
	ON_BN_CLICKED(IDC_BUTTON_HISTO_GET3, &CInspectionSetHistogramDlg::OnBnClickedButtonHistoGet3)
	ON_BN_CLICKED(IDC_BUTTON_HISTO_SET3, &CInspectionSetHistogramDlg::OnBnClickedButtonHistoSet3)
	ON_BN_CLICKED(IDC_BUTTON_HISTO_GET4, &CInspectionSetHistogramDlg::OnBnClickedButtonHistoGet4)
	ON_BN_CLICKED(IDC_BUTTON_HISTO_SET4, &CInspectionSetHistogramDlg::OnBnClickedButtonHistoSet4)
	ON_BN_CLICKED(IDC_CHECK_HISTO_INSPEC_GRAY, &CInspectionSetHistogramDlg::OnBnClickedCheckHistoInspecGray)
	ON_BN_CLICKED(IDC_CHECK_HISTO_INSPEC_RED2, &CInspectionSetHistogramDlg::OnBnClickedCheckHistoInspecRed2)
	ON_BN_CLICKED(IDC_CHECK_HISTO_INSPEC_GREEN2, &CInspectionSetHistogramDlg::OnBnClickedCheckHistoInspecGreen2)
	ON_BN_CLICKED(IDC_CHECK_HISTO_INSPEC_BLUE2, &CInspectionSetHistogramDlg::OnBnClickedCheckHistoInspecBlue2)
	ON_BN_CLICKED(IDC_BUTTON_GET_PIXEL_COUNT, &CInspectionSetHistogramDlg::OnBnClickedButtonGetPixelCount)
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_HISTOGRAM_TOL_GET, &CInspectionSetHistogramDlg::OnBnClickedButtonHistogramTolGet)
	ON_BN_CLICKED(IDC_BUTTON_HISTOGRAM_TOL_SET, &CInspectionSetHistogramDlg::OnBnClickedButtonHistogramTolSet)
	ON_BN_CLICKED(IDOK, &CInspectionSetHistogramDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInspectionSetHistogramDlg message handlers


BOOL CInspectionSetHistogramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_histogram_size = 0;
	if (m_p_histogram != NULL)
	{
		free(m_p_histogram);
		m_p_histogram = NULL;
	}

	if (m_p_histogram_r != NULL)
	{
		free(m_p_histogram_r);
		m_p_histogram_r = NULL;
	}

	if (m_p_histogram_g != NULL)
	{
		free(m_p_histogram_g);
		m_p_histogram_g = NULL;
	}

	if (m_p_histogram_b != NULL)
	{
		free(m_p_histogram_b);
		m_p_histogram_b = NULL;
	}

	m_select_id = ERVS_DB_Get_Select_ID(); 

	if (m_select_id > 0)
	{
		ERVS_Histogram_Get_Graph(m_select_id, &m_p_histogram, &m_p_histogram_r, &m_p_histogram_g, &m_p_histogram_b, &m_histogram_size);
	}

	OnBnClickedButtonHistogramTolGet();
	
	//Inspection Elem. Option
	int option = 0;
	ERVS_Histogram_Get_Use_Element(m_select_id, &option);
	//Gray
	if (option & HISTOGRAM_USE_GRAY)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GRAY, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GRAY, FALSE);
	}
	//Red
	if (option & HISTOGRAM_USE_RED)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_RED2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_RED2, FALSE);
	}
	//Green
	if (option & HISTOGRAM_USE_GREEN)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GREEN2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GREEN2, FALSE);
	}
	//Blue
	if (option & HISTOGRAM_USE_BLUE)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_BLUE2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_BLUE2, FALSE);
	}

	//start Thread
	//eyedea - start of thread
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CInspectionSetHistogramDlg::ThreadFunctionDraw, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CInspectionSetHistogramDlg::DrawHistogram(int select_id)
{
	int histogram_size = (int)m_histogram_size;
	if (histogram_size > 0)
	{
		m_result_histogram_image = 0;
		m_result_histogram_r_image = 0;
		m_result_histogram_g_image = 0;
		m_result_histogram_b_image = 0;

		if (m_result_histogram_image.cols < histogram_size)
		{
			m_result_histogram_image = cv::Mat::zeros(cv::Size(histogram_size, 255), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
		}

		if (m_result_histogram_r_image.cols < histogram_size)
		{
			m_result_histogram_r_image = cv::Mat::zeros(cv::Size(histogram_size, 255), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
		}

		if (m_result_histogram_g_image.cols < histogram_size)
		{
			m_result_histogram_g_image = cv::Mat::zeros(cv::Size(histogram_size, 255), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
		}

		if (m_result_histogram_b_image.cols < histogram_size)
		{
			m_result_histogram_b_image = cv::Mat::zeros(cv::Size(histogram_size, 255), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
		}

		int start_x_v = (m_result_histogram_image.cols - histogram_size) / 2;
		int start_x_r = (m_result_histogram_r_image.cols - histogram_size) / 2;
		int start_x_g = (m_result_histogram_g_image.cols - histogram_size) / 2;
		int start_x_b = (m_result_histogram_b_image.cols - histogram_size) / 2;

		//scale 
		CRect rect_histogram_gray;
		GetDlgItem(IDC_STATIC_HISTOGRAM)->GetWindowRect(&rect_histogram_gray);
		ScreenToClient(&rect_histogram_gray);

		CRect rect_histogram_red;
		GetDlgItem(IDC_STATIC_HISTOGRAM_R)->GetWindowRect(&rect_histogram_red);
		ScreenToClient(&rect_histogram_red);

		CRect rect_histogram_green;
		GetDlgItem(IDC_STATIC_HISTOGRAM_G)->GetWindowRect(&rect_histogram_green);
		ScreenToClient(&rect_histogram_green);

		CRect rect_histogram_blue;
		GetDlgItem(IDC_STATIC_HISTOGRAM_B)->GetWindowRect(&rect_histogram_blue);
		ScreenToClient(&rect_histogram_blue);

		m_f_histogram_w_scale_v = (float)rect_histogram_gray.Width() / (float)m_result_histogram_image.cols;
		m_f_histogram_w_scale_r = (float)rect_histogram_red.Width() / (float)m_result_histogram_r_image.cols;
		m_f_histogram_w_scale_g = (float)rect_histogram_green.Width() / (float)m_result_histogram_g_image.cols;
		m_f_histogram_w_scale_b = (float)rect_histogram_blue.Width() / (float)m_result_histogram_b_image.cols;

		m_f_histogram_size_v_on_ui = histogram_size * m_f_histogram_w_scale_v;
		m_f_histogram_size_r_on_ui = histogram_size * m_f_histogram_w_scale_r;
		m_f_histogram_size_g_on_ui = histogram_size * m_f_histogram_w_scale_g;
		m_f_histogram_size_b_on_ui = histogram_size * m_f_histogram_w_scale_b;

		m_f_start_x_v_on_ui = (float)start_x_v * m_f_histogram_w_scale_v;
		m_f_start_x_r_on_ui = (float)start_x_r * m_f_histogram_w_scale_r;
		m_f_start_x_g_on_ui = (float)start_x_g * m_f_histogram_w_scale_g;
		m_f_start_x_b_on_ui = (float)start_x_b * m_f_histogram_w_scale_b;

		//float scale_x = 
		//m_f_histogram_size_on_ui
		//m_f_start_x_v_on_ui
		//m_f_start_x_r_on_ui
		//m_f_start_x_g_on_ui
		//m_f_start_x_b_on_ui

		//guide line
		cv::Scalar guide_rect_fill_colof = cv::Scalar(50, 50, 50);
		cv::Scalar guide_line_colof = cv::Scalar(128, 128, 128);

		//gray
		cv::rectangle(m_result_histogram_image, cv::Rect(start_x_v, 0, histogram_size, m_result_histogram_image.rows), guide_rect_fill_colof, CV_FILLED);
		cv::line(m_result_histogram_image, cv::Point(start_x_v, m_result_histogram_image.rows), cv::Point(start_x_v, 0), guide_line_colof, 1);
		cv::line(m_result_histogram_image, cv::Point(start_x_v + histogram_size, m_result_histogram_image.rows), cv::Point(start_x_v + histogram_size, 0), guide_line_colof, 1);
		//r
		cv::rectangle(m_result_histogram_r_image, cv::Rect(start_x_r, 0, histogram_size, m_result_histogram_r_image.rows), guide_rect_fill_colof, CV_FILLED);
		cv::line(m_result_histogram_r_image, cv::Point(start_x_r, m_result_histogram_r_image.rows), cv::Point(start_x_r, 0), guide_line_colof, 1);
		cv::line(m_result_histogram_r_image, cv::Point(start_x_r + histogram_size, m_result_histogram_r_image.rows), cv::Point(start_x_r + histogram_size, 0), guide_line_colof, 1);
		//g
		cv::rectangle(m_result_histogram_g_image, cv::Rect(start_x_g, 0, histogram_size, m_result_histogram_g_image.rows), guide_rect_fill_colof, CV_FILLED);
		cv::line(m_result_histogram_g_image, cv::Point(start_x_g, m_result_histogram_g_image.rows), cv::Point(start_x_g, 0), guide_line_colof, 1);
		cv::line(m_result_histogram_g_image, cv::Point(start_x_g + histogram_size, m_result_histogram_g_image.rows), cv::Point(start_x_g + histogram_size, 0), guide_line_colof, 1);
		//b
		cv::rectangle(m_result_histogram_b_image, cv::Rect(start_x_b, 0, histogram_size, m_result_histogram_b_image.rows), guide_rect_fill_colof, CV_FILLED);
		cv::line(m_result_histogram_b_image, cv::Point(start_x_b, m_result_histogram_b_image.rows), cv::Point(start_x_b, 0), guide_line_colof, 1);
		cv::line(m_result_histogram_b_image, cv::Point(start_x_b + histogram_size, m_result_histogram_b_image.rows), cv::Point(start_x_b + histogram_size, 0), guide_line_colof, 1);

		//Draw Range
		int min_value = 0;
		int max_value = 0;
		ERVS_Histogram_Get_Range(select_id, 0, &min_value, &max_value);

		cv::rectangle(m_result_histogram_image, cv::Rect(start_x_v + min_value, 0, max_value - min_value, m_result_histogram_image.rows), cv::Scalar(128, 128, 128), CV_FILLED);
		//cv::line(m_result_histogram_image, cv::Point(start_x_v + m_i_histogmra_gray_min, m_result_histogram_image.rows), cv::Point(start_x_v + m_i_histogmra_gray_min, 0), cv::Scalar(128, 128, 128), 2);
		//cv::line(m_result_histogram_image, cv::Point(start_x_v + m_i_histogmra_gray_max, m_result_histogram_image.rows), cv::Point(start_x_v + m_i_histogmra_gray_max, 0), cv::Scalar(128, 128, 128), 2);

		min_value = 0;
		max_value = 0;
		ERVS_Histogram_Get_Range(select_id, 1, &min_value, &max_value);

		cv::rectangle(m_result_histogram_r_image, cv::Rect(start_x_r + min_value, 0, max_value - min_value, m_result_histogram_r_image.rows), cv::Scalar(128, 128, 128), CV_FILLED);
		//cv::line(m_result_histogram_r_image, cv::Point(start_x_r + m_i_histogmra_red_min, m_result_histogram_r_image.rows), cv::Point(start_x_r + m_i_histogmra_red_min, 0), cv::Scalar(0, 0, 255), 2);
		//cv::line(m_result_histogram_r_image, cv::Point(start_x_r + m_i_histogmra_red_max, m_result_histogram_r_image.rows), cv::Point(start_x_r + m_i_histogmra_red_max, 0), cv::Scalar(0, 0, 255), 2);

		min_value = 0;
		max_value = 0;
		ERVS_Histogram_Get_Range(select_id, 2, &min_value, &max_value);

		cv::rectangle(m_result_histogram_g_image, cv::Rect(start_x_g + min_value, 0, max_value - min_value, m_result_histogram_g_image.rows), cv::Scalar(128, 128, 128), CV_FILLED);
		//cv::line(m_result_histogram_g_image, cv::Point(start_x_g + m_i_histogmra_green_min, m_result_histogram_g_image.rows), cv::Point(start_x_g + m_i_histogmra_green_min, 0), cv::Scalar(0, 255, 0), 2);
		//cv::line(m_result_histogram_g_image, cv::Point(start_x_g + m_i_histogmra_green_max, m_result_histogram_g_image.rows), cv::Point(start_x_g + m_i_histogmra_green_max, 0), cv::Scalar(0, 255, 0), 2);

		min_value = 0;
		max_value = 0;
		ERVS_Histogram_Get_Range(select_id, 3, &min_value, &max_value);

		cv::rectangle(m_result_histogram_b_image, cv::Rect(start_x_b + min_value, 0, max_value - min_value, m_result_histogram_b_image.rows), cv::Scalar(128, 128, 128), CV_FILLED);
		//cv::line(m_result_histogram_b_image, cv::Point(start_x_b + m_i_histogmra_blue_min, m_result_histogram_b_image.rows), cv::Point(start_x_b + m_i_histogmra_blue_min, 0), cv::Scalar(255, 0, 0), 2);
		//cv::line(m_result_histogram_b_image, cv::Point(start_x_b + m_i_histogmra_blue_max, m_result_histogram_b_image.rows), cv::Point(start_x_b + m_i_histogmra_blue_max, 0), cv::Scalar(255, 0, 0), 2);

		for (int i = 0; i < (int)histogram_size; i++)
		{
			int value = 0;

			if (m_p_histogram != NULL)
			{
				value = m_p_histogram[i] * m_result_histogram_image.rows;
				cv::line(m_result_histogram_image, cv::Point(start_x_v + i, m_result_histogram_image.rows), cv::Point(start_x_v + i, m_result_histogram_image.rows - value), cv::Scalar(255, 255, 255), 1);
			}

			//r
			if (m_p_histogram_r != NULL)
			{
				value = m_p_histogram_r[i] * m_result_histogram_r_image.rows;
				cv::line(m_result_histogram_r_image, cv::Point(start_x_r + i, m_result_histogram_r_image.rows), cv::Point(start_x_r + i, m_result_histogram_r_image.rows - value), cv::Scalar(128, 128, 255), 1);
			}

			if (m_p_histogram_g != NULL)
			{
				value = m_p_histogram_g[i] * m_result_histogram_g_image.rows;
				cv::line(m_result_histogram_g_image, cv::Point(start_x_g + i, m_result_histogram_g_image.rows), cv::Point(start_x_g + i, m_result_histogram_g_image.rows - value), cv::Scalar(128, 255, 128), 1);
			}

			if (m_p_histogram_b != NULL)
			{
				value = m_p_histogram_b[i] * m_result_histogram_b_image.rows;
				cv::line(m_result_histogram_b_image, cv::Point(start_x_b + i, m_result_histogram_b_image.rows), cv::Point(start_x_b + i, m_result_histogram_b_image.rows - value), cv::Scalar(255, 128, 128), 1);
			}
		}

		//cv::imwrite("histogram.png", m_result_histogram_image);
		//cv::imwrite("histogram_r.png", m_result_histogram_r_image);
		//cv::imwrite("histogram_g.png", m_result_histogram_g_image);
		//cv::imwrite("histogram_b.png", m_result_histogram_b_image);

	}
}

void CInspectionSetHistogramDlg::ThreadFunctionDraw()
{
	CRect rect_histogram_display;													//display rect
	GetDlgItem(IDC_STATIC_HISTOGRAM)->GetClientRect(&rect_histogram_display);			//get rect information on window
	CClientDC dc_histogram_display(GetDlgItem(IDC_STATIC_HISTOGRAM));					//device context for display mfc control

	CRect rect_histogram_r_display;													//display rect
	GetDlgItem(IDC_STATIC_HISTOGRAM_R)->GetClientRect(&rect_histogram_r_display);			//get rect information on window
	CClientDC dc_histogram_r_display(GetDlgItem(IDC_STATIC_HISTOGRAM_R));					//device context for display mfc control

	CRect rect_histogram_g_display;													//display rect
	GetDlgItem(IDC_STATIC_HISTOGRAM_G)->GetClientRect(&rect_histogram_g_display);			//get rect information on window
	CClientDC dc_histogram_g_display(GetDlgItem(IDC_STATIC_HISTOGRAM_G));					//device context for display mfc control

	CRect rect_histogram_b_display;													//display rect
	GetDlgItem(IDC_STATIC_HISTOGRAM_B)->GetClientRect(&rect_histogram_b_display);			//get rect information on window
	CClientDC dc_histogram_b_display(GetDlgItem(IDC_STATIC_HISTOGRAM_B));					//device context for display mfc control

	CvvImage vImage;		//display class for display on MFC control

	cv::Mat base_image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display

	CRect rect_display_base;													//display rect
	GetDlgItem(IDC_STATIC_IMAGE)->GetClientRect(&rect_display_base);			//get rect information on window
	CClientDC dc_display_base(GetDlgItem(IDC_STATIC_IMAGE));					//device context for display mfc control

	while (m_run_thread)
	{
		//ROI
		int len = 921600;

		BOOL bCheckGray = IsDlgButtonChecked(IDC_CHECK_HISTO_INSPEC_GRAY);
		BOOL bCheckRed = IsDlgButtonChecked(IDC_CHECK_HISTO_INSPEC_RED2);
		BOOL bCheckGreen = IsDlgButtonChecked(IDC_CHECK_HISTO_INSPEC_GREEN2);
		BOOL bCheckBlue = IsDlgButtonChecked(IDC_CHECK_HISTO_INSPEC_BLUE2);
		if (bCheckGray || bCheckRed || bCheckGreen || bCheckBlue)
		{
			ERVS_GetImage(GET_IMAGE_BASE_HISTORY_MASK, 1, (char**)&base_image.data, &len);
		}
		else
		{
			ERVS_GetImage(GET_IMAGE_BASE_ROI, 0, (char**)&base_image.data, &len);
		}

		vImage.CopyOf(&IplImage(base_image), 1);							//mat to vimage
		vImage.DrawToHDC(dc_display_base.m_hDC, &rect_display_base);				//draw on display_rect

		//histogram
		DrawHistogram(m_select_id);

		vImage.CopyOf(&IplImage(m_result_histogram_image), 1);							//mat to vimage
		vImage.DrawToHDC(dc_histogram_display.m_hDC, &rect_histogram_display);				//draw on display_rect

		vImage.CopyOf(&IplImage(m_result_histogram_r_image), 1);							//mat to vimage
		vImage.DrawToHDC(dc_histogram_r_display.m_hDC, &rect_histogram_r_display);				//draw on display_rect

		vImage.CopyOf(&IplImage(m_result_histogram_g_image), 1);							//mat to vimage
		vImage.DrawToHDC(dc_histogram_g_display.m_hDC, &rect_histogram_g_display);				//draw on display_rect

		vImage.CopyOf(&IplImage(m_result_histogram_b_image), 1);							//mat to vimage
		vImage.DrawToHDC(dc_histogram_b_display.m_hDC, &rect_histogram_b_display);				//draw on display_rect

		boost::this_thread::sleep(boost::posix_time::millisec(10));
	}
}

void CInspectionSetHistogramDlg::OnBnClickedButtonHistoGet()
{
	// TODO: Add your control notification handler code here
	int min_value = 0;
	int max_value = 0;
	ERVS_Histogram_Get_Range(m_select_id, 0, &min_value, &max_value);

	CString str;
	str.Format(_T("%d"), min_value);
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MIN)->SetWindowText(str);

	str.Format(_T("%d"), max_value);
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MAX)->SetWindowText(str);
}


void CInspectionSetHistogramDlg::OnBnClickedButtonHistoSet()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MIN)->GetWindowText(str);
	int min_value = _ttoi(str);

	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MAX)->GetWindowText(str);
	int max_value = _ttoi(str);

	ERVS_Histogram_Set_Range(m_select_id, 0, min_value, max_value);

	OnBnClickedButtonHistoGet();
}


void CInspectionSetHistogramDlg::OnBnClickedButtonHistoGet2()
{
	// TODO: Add your control notification handler code here
	int min_value = 0;
	int max_value = 0;
	ERVS_Histogram_Get_Range(m_select_id, 1, &min_value, &max_value);

	CString str;
	str.Format(_T("%d"), min_value);
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MIN2)->SetWindowText(str);

	str.Format(_T("%d"), max_value);
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MAX2)->SetWindowText(str);
}


void CInspectionSetHistogramDlg::OnBnClickedButtonHistoSet2()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MIN2)->GetWindowText(str);
	int min_value = _ttoi(str);

	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MAX2)->GetWindowText(str);
	int max_value = _ttoi(str);

	ERVS_Histogram_Set_Range(m_select_id, 1, min_value, max_value);

	OnBnClickedButtonHistoGet2();
}


void CInspectionSetHistogramDlg::OnBnClickedButtonHistoGet3()
{
	// TODO: Add your control notification handler code here
	int min_value = 0;
	int max_value = 0;
	ERVS_Histogram_Get_Range(m_select_id, 2, &min_value, &max_value);

	CString str;
	str.Format(_T("%d"), min_value);
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MIN3)->SetWindowText(str);

	str.Format(_T("%d"), max_value);
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MAX3)->SetWindowText(str);
}


void CInspectionSetHistogramDlg::OnBnClickedButtonHistoSet3()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MIN3)->GetWindowText(str);
	int min_value = _ttoi(str);

	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MAX3)->GetWindowText(str);
	int max_value = _ttoi(str);

	ERVS_Histogram_Set_Range(m_select_id, 2, min_value, max_value);

	OnBnClickedButtonHistoGet3();
}


void CInspectionSetHistogramDlg::OnBnClickedButtonHistoGet4()
{
	// TODO: Add your control notification handler code here
	int min_value = 0;
	int max_value = 0;
	ERVS_Histogram_Get_Range(m_select_id, 3, &min_value, &max_value);

	CString str;
	str.Format(_T("%d"), min_value);
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MIN4)->SetWindowText(str);

	str.Format(_T("%d"), max_value);
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MAX4)->SetWindowText(str);
}


void CInspectionSetHistogramDlg::OnBnClickedButtonHistoSet4()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MIN4)->GetWindowText(str);
	int min_value = _ttoi(str);

	GetDlgItem(IDC_EDIT_HISTOGRAM_RANGE_MAX4)->GetWindowText(str);
	int max_value = _ttoi(str);

	ERVS_Histogram_Set_Range(m_select_id, 3, min_value, max_value);

	OnBnClickedButtonHistoGet4();
}


void CInspectionSetHistogramDlg::OnBnClickedCheckHistoInspecGray()
{
	// TODO: Add your control notification handler code here
	int option = 0;
	ERVS_Histogram_Get_Use_Element(m_select_id, &option);

	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_HISTO_INSPEC_GRAY);

	if (bCheck)
	{
		option = option | HISTOGRAM_USE_GRAY;

		//printf("set option = %d\n", option);
		ERVS_Histogram_Set_Use_Element(m_select_id, option);
	}
	else
	{
		option = option & (~HISTOGRAM_USE_GRAY);

		//printf("set option = %d\n", option);
		ERVS_Histogram_Set_Use_Element(m_select_id, option);
	}

	//Inspection Elem. Option
	option = 0;
	ERVS_Histogram_Get_Use_Element(m_select_id, &option);
	//Gray
	if (option & HISTOGRAM_USE_GRAY)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GRAY, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GRAY, FALSE);
	}
	//Red
	if (option & HISTOGRAM_USE_RED)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_RED2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_RED2, FALSE);
	}
	//Green
	if (option & HISTOGRAM_USE_GREEN)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GREEN2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GREEN2, FALSE);
	}
	//Blue
	if (option & HISTOGRAM_USE_BLUE)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_BLUE2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_BLUE2, FALSE);
	}
}


void CInspectionSetHistogramDlg::OnBnClickedCheckHistoInspecRed2()
{
	// TODO: Add your control notification handler code here
	int option = 0;
	ERVS_Histogram_Get_Use_Element(m_select_id, &option);

	//printf("get option = %d\n", option);

	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_HISTO_INSPEC_RED2);

	if (bCheck)
	{
		option = option | HISTOGRAM_USE_RED;

		//printf("set option = %d\n", option);
		ERVS_Histogram_Set_Use_Element(m_select_id, option);
	}
	else
	{
		option = option & (~HISTOGRAM_USE_RED);

		//printf("set option = %d\n", option);
		ERVS_Histogram_Set_Use_Element(m_select_id, option);
	}

	//
	//Inspection Elem. Option
	option = 0;
	ERVS_Histogram_Get_Use_Element(m_select_id, &option);
	//Gray
	if (option & HISTOGRAM_USE_GRAY)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GRAY, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GRAY, FALSE);
	}
	//Red
	if (option & HISTOGRAM_USE_RED)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_RED2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_RED2, FALSE);
	}
	//Green
	if (option & HISTOGRAM_USE_GREEN)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GREEN2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GREEN2, FALSE);
	}
	//Blue
	if (option & HISTOGRAM_USE_BLUE)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_BLUE2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_BLUE2, FALSE);
	}
}


void CInspectionSetHistogramDlg::OnBnClickedCheckHistoInspecGreen2()
{
	// TODO: Add your control notification handler code here
	int option = 0;
	ERVS_Histogram_Get_Use_Element(m_select_id, &option);

	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_HISTO_INSPEC_GREEN2);

	if (bCheck)
	{
		option = option | HISTOGRAM_USE_GREEN;

		//printf("set option = %d\n", option);
		ERVS_Histogram_Set_Use_Element(m_select_id, option);
	}
	else
	{
		option = option & (~HISTOGRAM_USE_GREEN);

		//printf("set option = %d\n", option);
		ERVS_Histogram_Set_Use_Element(m_select_id, option);
	}

	//
	//Inspection Elem. Option
	option = 0;
	ERVS_Histogram_Get_Use_Element(m_select_id, &option);
	//Gray
	if (option & HISTOGRAM_USE_GRAY)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GRAY, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GRAY, FALSE);
	}
	//Red
	if (option & HISTOGRAM_USE_RED)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_RED2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_RED2, FALSE);
	}
	//Green
	if (option & HISTOGRAM_USE_GREEN)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GREEN2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GREEN2, FALSE);
	}
	//Blue
	if (option & HISTOGRAM_USE_BLUE)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_BLUE2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_BLUE2, FALSE);
	}
}


void CInspectionSetHistogramDlg::OnBnClickedCheckHistoInspecBlue2()
{
	// TODO: Add your control notification handler code here
	int option = 0;
	ERVS_Histogram_Get_Use_Element(m_select_id, &option);

	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK_HISTO_INSPEC_BLUE2);

	if (bCheck)
	{
		option = option | HISTOGRAM_USE_BLUE;

		//printf("set option = %d\n", option);
		ERVS_Histogram_Set_Use_Element(m_select_id, option);
	}
	else
	{
		option = option & (~HISTOGRAM_USE_BLUE);

		//printf("set option = %d\n", option);
		ERVS_Histogram_Set_Use_Element(m_select_id, option);
	}

	//
	//Inspection Elem. Option
	option = 0;
	ERVS_Histogram_Get_Use_Element(m_select_id, &option);
	//Gray
	if (option & HISTOGRAM_USE_GRAY)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GRAY, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GRAY, FALSE);
	}
	//Red
	if (option & HISTOGRAM_USE_RED)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_RED2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_RED2, FALSE);
	}
	//Green
	if (option & HISTOGRAM_USE_GREEN)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GREEN2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_GREEN2, FALSE);
	}
	//Blue
	if (option & HISTOGRAM_USE_BLUE)
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_BLUE2, TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_HISTO_INSPEC_BLUE2, FALSE);
	}
}


void CInspectionSetHistogramDlg::OnBnClickedButtonGetPixelCount()
{
	// TODO: Add your control notification handler code here
	int pixel_count = 0;
	ERVS_Histogram_Get_Pixel_Count(m_select_id, &pixel_count);

	CString str;
	str.Format(_T("%d"), pixel_count);
	GetDlgItem(IDC_EDIT_PIXEL_COUNT)->SetWindowText(str);

	if (pixel_count > 0)
	{
		//m_combo_get_image_option_base.SetCurSel(3);		//Get History Masking Image
	}

	//Get Base Information
	//float tol_rate = 0.0;
	//ERVS_Histogram_Get_Inspection_Pixel_Count_Tolerance_Rate(m_select_id, &tol_rate);

	//str.Format(_T("%.2f"), tol_rate);
	//GetDlgItem(IDC_EDIT_PIXEL_COUNT_TOL)->SetWindowText(str);
}

#if 0
void CInspectionSetHistogramDlg::OnBnClickedButtonSetInspectionPixelCount()
{
	// TODO: Add your control notification handler code here
	//pixel count
	CString str;
	GetDlgItem(IDC_EDIT_PIXEL_COUNT)->GetWindowText(str);
	int pixel_count = _ttoi(str);

	ERVS_Histogram_Set_Inspection_Pixel_Count(m_select_id, pixel_count);

	pixel_count = 0;
	ERVS_Histogram_Get_Inspection_Pixel_Count(m_select_id, &pixel_count);

	str.Format(_T("%d"), pixel_count);
	GetDlgItem(IDC_EDIT_PIXEL_COUNT)->SetWindowText(str);

	//tol rate
	/*
	GetDlgItem(IDC_EDIT_PIXEL_COUNT_TOL)->GetWindowText(str);
	float tol_rate = _ttof(str);

	ERVS_Histogram_Set_Inspection_Pixel_Count_Tolerance_Rate(m_select_id, tol_rate);

	tol_rate = 0.0;
	ERVS_Histogram_Get_Inspection_Pixel_Count_Tolerance_Rate(m_select_id, &tol_rate);

	str.Format(_T("%.2f"), tol_rate);
	GetDlgItem(IDC_EDIT_PIXEL_COUNT_TOL)->SetWindowText(str);
	*/
}
#endif

void CInspectionSetHistogramDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_run_thread = false;
	//m_thread.timed_join(boost::posix_time::seconds(1));			//wait for end of thread
	m_thread.join();			//wait for end of thread

	CDialogEx::OnClose();
}


void CInspectionSetHistogramDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect_histogram_gray;
	GetDlgItem(IDC_STATIC_HISTOGRAM)->GetWindowRect(&rect_histogram_gray);
	ScreenToClient(&rect_histogram_gray);

	CRect rect_histogram_red;
	GetDlgItem(IDC_STATIC_HISTOGRAM_R)->GetWindowRect(&rect_histogram_red);
	ScreenToClient(&rect_histogram_red);

	CRect rect_histogram_green;
	GetDlgItem(IDC_STATIC_HISTOGRAM_G)->GetWindowRect(&rect_histogram_green);
	ScreenToClient(&rect_histogram_green);

	CRect rect_histogram_blue;
	GetDlgItem(IDC_STATIC_HISTOGRAM_B)->GetWindowRect(&rect_histogram_blue);
	ScreenToClient(&rect_histogram_blue);

	//gray
	if (point.x >= rect_histogram_gray.left && point.x <= rect_histogram_gray.right &&
		point.y >= rect_histogram_gray.top && point.y <= rect_histogram_gray.bottom)
	{
		m_i_histogram_lbdwn_object = 0;

		int value = point.x - rect_histogram_gray.left;
		float f_value = ((float)((float)value - m_f_start_x_v_on_ui) / m_f_histogram_w_scale_v);

		m_i_histogmra_gray_min = f_value;

		if (m_i_histogmra_gray_min < 0) m_i_histogmra_gray_min = 0;
		else if (m_i_histogmra_gray_min > 255) m_i_histogmra_gray_min = 255;

		//printf("m_f_histogram_w_scale_v = %f\n", m_f_histogram_w_scale_v);
		//printf("m_f_start_x_v_on_ui = %f\n", m_f_start_x_v_on_ui);
		//printf("min value = %d, %f\n", value, f_value);

		m_select_id = ERVS_DB_Get_Select_ID();
		ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_gray_min, m_i_histogmra_gray_max);
	}
	else if (point.x >= rect_histogram_red.left && point.x <= rect_histogram_red.right &&
		point.y >= rect_histogram_red.top && point.y <= rect_histogram_red.bottom)
	{
		m_i_histogram_lbdwn_object = 1;

		int value = point.x - rect_histogram_red.left;
		float f_value = ((float)((float)value - m_f_start_x_r_on_ui) / m_f_histogram_w_scale_r);

		m_i_histogmra_red_min = f_value;

		if (m_i_histogmra_red_min < 0) m_i_histogmra_red_min = 0;
		else if (m_i_histogmra_red_min > 255) m_i_histogmra_red_min = 255;

		m_select_id = ERVS_DB_Get_Select_ID();
		ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_red_min, m_i_histogmra_red_max);

	}
	else if (point.x >= rect_histogram_green.left && point.x <= rect_histogram_green.right &&
		point.y >= rect_histogram_green.top && point.y <= rect_histogram_green.bottom)
	{
		m_i_histogram_lbdwn_object = 2;

		int value = point.x - rect_histogram_green.left;
		float f_value = ((float)((float)value - m_f_start_x_g_on_ui) / m_f_histogram_w_scale_g);

		m_i_histogmra_green_min = f_value;

		if (m_i_histogmra_green_min < 0) m_i_histogmra_green_min = 0;
		else if (m_i_histogmra_green_min > 255) m_i_histogmra_green_min = 255;

		m_select_id = ERVS_DB_Get_Select_ID();
		ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_green_min, m_i_histogmra_green_max);

	}
	else if (point.x >= rect_histogram_blue.left && point.x <= rect_histogram_blue.right &&
		point.y >= rect_histogram_blue.top && point.y <= rect_histogram_blue.bottom)
	{
		m_i_histogram_lbdwn_object = 3;

		int value = point.x - rect_histogram_blue.left;
		float f_value = ((float)((float)value - m_f_start_x_b_on_ui) / m_f_histogram_w_scale_b);

		m_i_histogmra_blue_min = f_value;

		if (m_i_histogmra_blue_min < 0) m_i_histogmra_blue_min = 0;
		else if (m_i_histogmra_blue_min > 255) m_i_histogmra_blue_min = 255;

		m_select_id = ERVS_DB_Get_Select_ID();
		ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_blue_min, m_i_histogmra_blue_max);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CInspectionSetHistogramDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_i_histogram_lbdwn_object >= 0)
	{
		if (m_i_histogram_lbdwn_object == 0)	//gray
		{
			ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_gray_min, m_i_histogmra_gray_max);
			OnBnClickedButtonHistoGet();
		}
		else if (m_i_histogram_lbdwn_object == 1)	//red
		{
			ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_red_min, m_i_histogmra_red_max);
			OnBnClickedButtonHistoGet2();
		}
		else if (m_i_histogram_lbdwn_object == 2)	//green
		{
			ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_green_min, m_i_histogmra_green_max);
			OnBnClickedButtonHistoGet3();
		}
		else if (m_i_histogram_lbdwn_object == 3)	//blue
		{
			ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_blue_min, m_i_histogmra_blue_max);
			OnBnClickedButtonHistoGet4();
		}

		m_i_histogram_lbdwn_object = -1;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CInspectionSetHistogramDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect_histogram_gray;
	GetDlgItem(IDC_STATIC_HISTOGRAM)->GetWindowRect(&rect_histogram_gray);
	ScreenToClient(&rect_histogram_gray);

	CRect rect_histogram_red;
	GetDlgItem(IDC_STATIC_HISTOGRAM_R)->GetWindowRect(&rect_histogram_red);
	ScreenToClient(&rect_histogram_red);

	CRect rect_histogram_green;
	GetDlgItem(IDC_STATIC_HISTOGRAM_G)->GetWindowRect(&rect_histogram_green);
	ScreenToClient(&rect_histogram_green);

	CRect rect_histogram_blue;
	GetDlgItem(IDC_STATIC_HISTOGRAM_B)->GetWindowRect(&rect_histogram_blue);
	ScreenToClient(&rect_histogram_blue);

	if (m_i_histogram_lbdwn_object >= 0)
	{
		if (m_i_histogram_lbdwn_object == 0)	//gray
		{
			int value = point.x - rect_histogram_gray.left;
			float f_value = ((float)((float)value - m_f_start_x_v_on_ui) / m_f_histogram_w_scale_v);

			if (m_i_histogmra_gray_min < f_value)
			{
				m_i_histogmra_gray_max = f_value;

				if (m_i_histogmra_gray_max < 0) m_i_histogmra_gray_max = 0;
				else if (m_i_histogmra_gray_max > 255) m_i_histogmra_gray_max = 255;

				ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_gray_min, m_i_histogmra_gray_max);
			}
			else
			{
				m_i_histogmra_gray_max = -1;
			}
		}
		else if (m_i_histogram_lbdwn_object == 1)	//red
		{
			int value = point.x - rect_histogram_red.left;
			float f_value = ((float)((float)value - m_f_start_x_r_on_ui) / m_f_histogram_w_scale_r);

			if (m_i_histogmra_red_min < f_value)
			{
				m_i_histogmra_red_max = f_value;

				if (m_i_histogmra_red_max < 0) m_i_histogmra_red_max = 0;
				else if (m_i_histogmra_red_max > 255) m_i_histogmra_red_max = 255;

				ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_red_min, m_i_histogmra_red_max);
			}
			else
			{
				m_i_histogmra_red_max = -1;
			}
		}
		else if (m_i_histogram_lbdwn_object == 2)	//green
		{
			int value = point.x - rect_histogram_green.left;
			float f_value = ((float)((float)value - m_f_start_x_g_on_ui) / m_f_histogram_w_scale_g);

			if (m_i_histogmra_green_min < f_value)
			{
				m_i_histogmra_green_max = f_value;

				if (m_i_histogmra_green_max < 0) m_i_histogmra_green_max = 0;
				else if (m_i_histogmra_green_max > 255) m_i_histogmra_green_max = 255;

				ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_green_min, m_i_histogmra_green_max);
			}
			else
			{
				m_i_histogmra_green_max = -1;
			}
		}
		else if (m_i_histogram_lbdwn_object == 3)	//blue
		{
			int value = point.x - rect_histogram_blue.left;
			float f_value = ((float)((float)value - m_f_start_x_b_on_ui) / m_f_histogram_w_scale_b);

			if (m_i_histogmra_blue_min < f_value)
			{
				m_i_histogmra_blue_max = f_value;

				if (m_i_histogmra_blue_max < 0) m_i_histogmra_blue_max = 0;
				else if (m_i_histogmra_blue_max > 255) m_i_histogmra_blue_max = 255;

				ERVS_Histogram_Set_Range(m_select_id, m_i_histogram_lbdwn_object, m_i_histogmra_blue_min, m_i_histogmra_blue_max);
			}
			else
			{
				m_i_histogmra_blue_max = -1;
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CInspectionSetHistogramDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	m_run_thread = false;
	//m_thread.timed_join(boost::posix_time::seconds(1));			//wait for end of thread
	m_thread.join();			//wait for end of thread

	CDialogEx::OnOK();
}


void CInspectionSetHistogramDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	m_run_thread = false;
	//m_thread.timed_join(boost::posix_time::seconds(1));			//wait for end of thread
	m_thread.join();			//wait for end of thread

	CDialogEx::OnCancel();
}


void CInspectionSetHistogramDlg::OnBnClickedButtonHistogramTolGet()
{
	// TODO: Add your control notification handler code here
	int min_value = 0;
	int max_value = 0;
	ERVS_Histogram_Get_Inspection_Pixel_Count_Tolerance(m_select_id, &min_value, &max_value);

	CString str;
	str.Format(_T("%d"), min_value);
	GetDlgItem(IDC_EDIT_HISTOGRAM_TOL_MIN)->SetWindowText(str);

	str.Format(_T("%d"), max_value);
	GetDlgItem(IDC_EDIT_HISTOGRAM_TOL_MAX)->SetWindowText(str);
}


void CInspectionSetHistogramDlg::OnBnClickedButtonHistogramTolSet()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_HISTOGRAM_TOL_MIN)->GetWindowText(str);
	int min_value = _ttoi(str);

	GetDlgItem(IDC_EDIT_HISTOGRAM_TOL_MAX)->GetWindowText(str);
	int max_value = _ttoi(str);

	ERVS_Histogram_Set_Inspection_Pixel_Count_Tolerance(m_select_id, min_value, max_value);

	OnBnClickedButtonHistogramTolGet();

}


void CInspectionSetHistogramDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_run_thread = false;
	//m_thread.timed_join(boost::posix_time::seconds(1));			//wait for end of thread
	m_thread.join();			//wait for end of thread

	CDialogEx::OnOK();
}
