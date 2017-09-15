
// EyedeaExampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "EyedeaExampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEyedeaExampleDlg dialog



CEyedeaExampleDlg::CEyedeaExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EYEDEAEXAMPLE_DIALOG, pParent)
	, m_run_thread(false)
	, m_command(USER_COMMAND_NORMAL)
	, m_pwndShow(NULL)
	, m_select_list_number(-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEyedeaExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_CONNECT, m_ip_addr);
	//DDX_Control(pDX, IDC_COMBO_GET_IMAGE_OPTION, m_combo_get_image_option);
	DDX_Control(pDX, IDC_TAB, m_tab_mode);
	DDX_Control(pDX, IDC_LIST_INFORMATION, m_list_information);
}

BEGIN_MESSAGE_MAP(CEyedeaExampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CEyedeaExampleDlg::OnBnClickedButtonConnect)
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_SET_SAMPLE_IMAGE, &CEyedeaExampleDlg::OnBnClickedButtonSetSampleImage)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CEyedeaExampleDlg::OnTcnSelchangeTab)
	ON_BN_CLICKED(IDC_BUTTON_NEW_MODEL, &CEyedeaExampleDlg::OnBnClickedButtonNewModel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_INFORMATION, &CEyedeaExampleDlg::OnNMDblclkListInformation)
	ON_BN_CLICKED(IDC_BUTTON_GET_VERSION, &CEyedeaExampleDlg::OnBnClickedButtonGetVersion)
	ON_BN_CLICKED(IDC_BUTTON_DEL_MODEL, &CEyedeaExampleDlg::OnBnClickedButtonDelModel)
	ON_BN_CLICKED(IDC_BUTTON_LIST_SAVE, &CEyedeaExampleDlg::OnBnClickedButtonListSave)
	//ON_BN_CLICKED(IDC_CHECK_LOG, &CEyedeaExampleDlg::OnBnClickedCheckLog)
	ON_BN_CLICKED(IDC_BUTTON_LIST_LOAD, &CEyedeaExampleDlg::OnBnClickedButtonListLoad)
END_MESSAGE_MAP()


// CEyedeaExampleDlg message handlers

BOOL CEyedeaExampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_tab_mode.InsertItem(0, _T("New - Setting"));
	//m_tab_mode.InsertItem(1, _T("Search Area"));
	m_tab_mode.InsertItem(1, _T("Demo"));
	m_tab_mode.InsertItem(2, _T("Calibration"));
	m_tab_mode.InsertItem(3, _T("SVM Camera Config"));	

	//tab
	CRect Rect;
	//m_tab_mode.SetParent(this);
	m_tab_mode.GetClientRect(&Rect);

	CRect tab_rect;
	m_tab_mode.GetWindowRect(tab_rect);
	ScreenToClient(tab_rect);

	//m_tab_dlg_vision_config.Create(IDD_DIALOG_VISION_CONFIG, &m_tab_mode);
	m_tab_dlg_vision_config.Create(IDD_DIALOG_VISION_CONFIG, this);
	m_tab_dlg_vision_config.SetWindowPos(NULL, tab_rect.left+3, tab_rect.top + 23, tab_rect.Width() - 7, tab_rect.Height() - 27, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_tab_dlg_vision_config;
	m_pwndShow->ShowWindow(SW_HIDE);

	/*
	m_tab_dlg_searcharea.Create(IDD_DIALOG_SEARCH_AREA, this);
	m_tab_dlg_searcharea.SetWindowPos(NULL, tab_rect.left + 3, tab_rect.top + 23, tab_rect.Width() - 7, tab_rect.Height() - 27, SWP_NOZORDER);
	m_pwndShow = &m_tab_dlg_searcharea;
	m_pwndShow->ShowWindow(SW_HIDE);
	*/

	m_tab_dlg_calibration.Create(IDD_DIALOG_CALIBRATION, this);
	m_tab_dlg_calibration.SetWindowPos(NULL, tab_rect.left + 3, tab_rect.top + 23, tab_rect.Width() - 7, tab_rect.Height() - 27, SWP_NOZORDER);
	m_pwndShow = &m_tab_dlg_calibration;
	m_pwndShow->ShowWindow(SW_HIDE);

	m_tab_dlg_check_defect.Create(IDD_DIALOG_OBEJCT_DETECT_AND_CHECK_DEFECT, this);
	m_tab_dlg_check_defect.SetWindowPos(NULL, tab_rect.left + 3, tab_rect.top + 23, tab_rect.Width() - 7, tab_rect.Height() - 27, SWP_NOZORDER);
	m_pwndShow = &m_tab_dlg_check_defect;
	m_pwndShow->ShowWindow(SW_HIDE);

	
	m_tab_dlg_camera_config.Create(IDD_DIALOG_CAMERA_CONFIG, this);
	m_tab_dlg_camera_config.SetWindowPos(NULL, tab_rect.left + 3, tab_rect.top + 23, tab_rect.Width() - 7, tab_rect.Height() - 27, SWP_NOZORDER);
	m_pwndShow = &m_tab_dlg_camera_config;
	m_pwndShow->ShowWindow(SW_HIDE);
	

	m_tab_dlg_vision_config.ShowWindow(SW_SHOW);
	m_pwndShow = &m_tab_dlg_vision_config;

	m_ip_addr.SetAddress(192, 168, 100, 3);		
	//m_ip_addr.SetAddress(192, 168, 123, 77);		
	//m_ip_addr.SetAddress(192, 168, 100, 7);
	//m_ip_addr.SetAddress(192, 168, 137, 11);
	//m_ip_addr.SetAddress(192, 168, 122, 131);
	//m_ip_addr.SetAddress(192, 168, 122, 129);

	CString str;
	str.Format(_T("%d"), 4000);
	GetDlgItem(IDC_EDIT_CONNECT_PORT)->SetWindowText(str);

#if 0
	m_combo_get_image_option.AddString(_T("GET_IMAGE_INPUT"));
	m_combo_get_image_option.AddString(_T("GET_IMAGE_WITH_INFO"));
	m_combo_get_image_option.AddString(_T("GET_IMAGE_BASE"));
	m_combo_get_image_option.AddString(_T("GET_IMAGE_ZOOM_SEARCH_AREA"));
	m_combo_get_image_option.AddString(_T("GET_IMAGE_ZOOM_MASTER_AREA"));
	m_combo_get_image_option.AddString(_T("GET_IMAGE_RESULT"));
	m_combo_get_image_option.AddString(_T("GET_IMAGE_RESULT_PAP"));
	m_combo_get_image_option.AddString(_T("CHECK:GET_IMAGE_MASTER_ROI"));
	m_combo_get_image_option.AddString(_T("CHECK:GET_IMAGE_BASE_OBJECT_ROI"));
	m_combo_get_image_option.AddString(_T("GET_IMAGE_SEARCH_AREA_INFO"));
	m_combo_get_image_option.SetCurSel(0);
#endif

	str.Format(_T("-"));
	GetDlgItem(IDC_EDIT_MODE)->SetWindowText(str);

	TCHAR szPath[512] = { 0 };
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_COMMON_DESKTOPDIRECTORY, FALSE);

	str.Format(_T("./ERVS_DB"), szPath);
	GetDlgItem(IDC_EDIT_DB_PATH)->SetWindowText(str);

	//Initialize list
	m_list_information.DeleteAllItems();
	// 리스트 스타일 설정
	m_list_information.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// 타이틀 삽입
	m_list_information.InsertColumn(0, _T("Select"), LVCFMT_CENTER, 50, -1);
	m_list_information.InsertColumn(1, _T("ID"), LVCFMT_CENTER, 100, -1);
	m_list_information.InsertColumn(2, _T("Mode"), LVCFMT_CENTER, 150, -1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEyedeaExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEyedeaExampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEyedeaExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEyedeaExampleDlg::OnBnClickedButtonConnect()
{
	// TODO: Add your control notification handler code here
	//GetDlgItem(IDC_IPADDRESS_CONNECT)->GetAddress()
	BYTE IP_a, IP_b, IP_c, IP_d; 

	m_ip_addr.GetAddress(IP_a, IP_b, IP_c, IP_d);

	if (IP_a == NULL || IP_b == NULL || IP_c == NULL || IP_d == NULL)
	{
		MessageBox(_T("Wrong IP address"), MB_OK);
	}
	else
	{
		char ip_addr[255];
		sprintf(ip_addr, "%d.%d.%d.%d", (int)IP_a, (int)IP_b, (int)IP_c, (int)IP_d);

		CString strPort;
		GetDlgItem(IDC_EDIT_CONNECT_PORT)->GetWindowText(strPort);
		int port = _ttoi(strPort);

		int ret = ERVS_Connect(ip_addr, port);

		if (ret == 0)
		{
			ERVS_SetMode(ERVS_MODE_NORMAL);

			//-----------------------------------------------
			//tab control
			if (m_pwndShow != NULL)
			{
				m_pwndShow->ShowWindow(SW_HIDE);
				m_pwndShow = NULL;
			}
			m_tab_mode.SetCurSel(0);
			m_tab_dlg_check_defect.m_b_draw_pause = true;
			m_tab_dlg_calibration.m_b_draw_pause = true;
			m_tab_dlg_vision_config.m_b_draw_pause = false;

			//m_tab_dlg_pick_and_place.m_b_draw_pause = true;
			m_tab_dlg_vision_config.ShowWindow(SW_SHOW);
			m_pwndShow = &m_tab_dlg_vision_config;
			//tab control
			//-----------------------------------------------

			//Check Version
			OnBnClickedButtonGetVersion();

			//Check Select
			int select_id = ERVS_DB_Get_Select_ID();

			if (select_id >= 1000)
			{
				//----------------------------------------------
				//Goto tab
				//m_tab_mode.SetCurSel(2);
				//OnTcnSelchangeTabMy(2);
				m_tab_mode.SetCurSel(0);
				OnTcnSelchangeTabMy(0);

				TCITEM tcItem;
				CString pszString;
				//pszString.Format(_T("%d - Object Detection"), id);
				pszString.Format(_T("%d - Setting"), select_id);
				//  Get the current tab item text.
				TCHAR buffer[256] = { 0 };
				tcItem.pszText = buffer;
				tcItem.cchTextMax = 256;
				tcItem.mask = TCIF_TEXT;
				tcItem.pszText = pszString.LockBuffer();

				m_tab_mode.SetItem(0, &tcItem);
				//Goto tab
				//----------------------------------------------
			}

			//start Thread
			//eyedea - start of thread
			m_run_thread = true;

			//cread thread
			m_thread = boost::thread(boost::bind(&CEyedeaExampleDlg::ThreadFunctionDraw, this));
		}
		else
		{
			MessageBox(_T("ERVS connection error"), MB_OK);
		}
	}
}


void CEyedeaExampleDlg::ThreadFunctionDraw()
{
	CvvImage vImage;		//display class for display on MFC control
							//cv::Mat display = cv::Mat::zeros(cv::Size(10,10), CV_8UC3) ;		//opencv mat for display
	if (m_display.empty())
	{
		m_display = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
	}

	CRect rect_display;													//display rect
	GetDlgItem(IDC_STATIC_IMAGE)->GetClientRect(&rect_display);			//get rect information on window
	CClientDC dc_display(GetDlgItem(IDC_STATIC_IMAGE));					//device context for display mfc control

	while (m_run_thread)												//thread loop
	{
		ManageDBListInfo();

		//---------------------------------------------------------------------------------
		//Get Image
		int len = 921600;		//640*480*3;
		ERVS_GetImage(GET_IMAGE_INPUT, 0, (char**)&m_display.data, &len);

#if 0
		/*
		m_combo_get_image_option.AddString(_T("GET_IMAGE_INPUT"));
		m_combo_get_image_option.AddString(_T("GET_IMAGE_WITH_INFO"));
		m_combo_get_image_option.AddString(_T("GET_IMAGE_BASE"));
		m_combo_get_image_option.AddString(_T("GET_IMAGE_ZOOM_SEARCH_AREA"));
		m_combo_get_image_option.AddString(_T("GET_IMAGE_ZOOM_MASTER_AREA"));
		m_combo_get_image_option.AddString(_T("GET_IMAGE_RESULT"));
		m_combo_get_image_option.AddString(_T("GET_IMAGE_RESULT_PAP"));
		m_combo_get_image_option.AddString(_T("CHECK:GET_IMAGE_MASTER_ROI"));
		m_combo_get_image_option.AddString(_T("CHECK:GET_IMAGE_BASE_OBJECT_ROI"));
		*/
		int get_image_option = m_combo_get_image_option.GetCurSel();

		
		if (get_image_option == 0)
		{
			int len = 921600;		//640*480*3;
			ERVS_GetImage(GET_IMAGE_INPUT, 0, (char**)&m_display.data, &len);
		}
		else if (get_image_option == 1)
		{
			int len = 921600;		//640*480*3;
			unsigned int option = 0;

			if (m_command == USER_COMMAND_SELECT_SEARCH_AREA)
			{
				option |= WITH_DRAW_SEARCH_AREA_RANGE;
			}

			ERVS_GetImage(GET_IMAGE_WITH_INFO, option, (char**)&m_display.data, &len);
		}
		else if (get_image_option == 2)
		{
			int len = 921600;		//640*480*3;
			ERVS_GetImage(GET_IMAGE_BASE, 0, (char**)&m_display.data, &len);
		}
		else if (get_image_option == 3)
		{
			int len = 921600;		//640*480*3;
			ERVS_GetImage(GET_IMAGE_ZOOM_SEARCH_AREA, 0, (char**)&m_display.data, &len);
		}
		else if (get_image_option == 4)
		{
			int len = 921600;		//640*480*3;
			ERVS_GetImage(GET_IMAGE_ZOOM_MASTER_AREA, 0, (char**)&m_display.data, &len);
		}
		else if (get_image_option == 5)		//GET_IMAGE_RESULT
		{
			int len = 921600;		//640*480*3;
			//ERVS_GetImage(GET_IMAGE_RESULT, RESULT_DRAW_OPTION_ALL, (char**)&m_display.data, &len);
			ERVS_GetImage(GET_IMAGE_RESULT, RESULT_DRAW_OPTION_SEARCH_BOX+RESULT_DRAW_OPTION_MASTER_BOX+ RESULT_DRAW_OPTION_OBJECT, (char**)&m_display.data, &len);
		}
		else if (get_image_option == 6)
		{
			int len = 921600;		//640*480*3;
			ERVS_GetImage(GET_IMAGE_RESULT_PAP, RESULT_DRAW_OPTION_SEARCH_BOX + RESULT_DRAW_OPTION_MASTER_BOX + RESULT_DRAW_OPTION_OBJECT, (char**)&m_display.data, &len);
		}
		else if (get_image_option == 7)
		{
			//CHECK:GET_IMAGE_MASTER_ROI
			int len = 921600;		//640*480*3;
			ERVS_GetImage(GET_IMAGE_ZOOM_MASTER_AREA, 0, (char**)&m_display.data, &len);
		}
		else if (get_image_option == 8)
		{
			//CHECK:GET_IMAGE_BASE_OBJECT_ROI
			int len = 921600;		//640*480*3;
			//ERVS_GetImage(GET_IMAGE_ZOOM_MASTER_AREA, 0, (char**)&m_display.data, &len);
			ERVS_GetImage(GET_IMAGE_BASE_ROI, WITH_DRAW_OPTION_FEATURE, (char**)&m_display.data, &len);
		}
		else if (get_image_option == 9)
		{
			//GET_IMAGE_SEARCH_AREA_INFO
			int len = 921600;		//640*480*3;
			ERVS_GetImage(GET_IMAGE_SEARCH_AREA_INFO, 0, (char**)&m_display.data, &len);
		}
#endif
		//Get Image
		//---------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------
		//draw display on static control
		//draw center
		if (!m_display.empty())
		{
			cv::Point center;
			center.x = m_display.cols / 2;
			center.y = m_display.rows / 2;

			int line_length = 20;
			cv::line(m_display, cv::Point(center.x- line_length, center.y), cv::Point(center.x+ line_length, center.y), cv::Scalar(0, 0, 255), 2);
			cv::line(m_display, cv::Point(center.x, center.y- line_length), cv::Point(center.x, center.y+ line_length), cv::Scalar(0, 0, 255), 2);


		}
		
		vImage.CopyOf(&IplImage(m_display), 1);							//mat to vimage
		vImage.DrawToHDC(dc_display.m_hDC, &rect_display);				//draw on display_rect
		//draw display on static control
		//---------------------------------------------------------------------------------

		//check ERVS mode
		int mode = ERVS_GetMode();
		CString str;
		CString strMode ;
		if (mode == ERVS_MODE_NORMAL) strMode.Format(_T("Normal"));
		else if (mode == ERVS_MODE_CALIBRATION) strMode.Format(_T("Calibration"));
		else strMode.Format(_T("-"));

		str.Format(_T("%d : %s"), mode, strMode);
		GetDlgItem(IDC_EDIT_MODE)->SetWindowText(str);
	};

	ERVS_Disconnect();
}


void CEyedeaExampleDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	m_run_thread = false;		//thread close

	m_thread.join();			//wait

	CDialogEx::OnClose();
}

#if 0
void CEyedeaExampleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//Main Draw Rect information on Window
	CRect rect;
	GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	//pattern_window
	if (point.x >= rect.left && point.x <= rect.right &&
		point.y >= rect.top && point.y <= rect.bottom)
	{
		if (m_command == USER_COMMAND_SELECT_SEARCH_AREA || m_command == USER_COMMAND_SELECT_MASTER_AREA || m_command == USER_COMMAND_SELECT_OBJECT ||
			m_command == USER_COMMAND_SELECT_PAP_MASTER_OBJECT || m_command == USER_COMMAND_SELECT_BASE_OBJECT)
		{
			m_b_mouse_ldown_on_drawwindow = true;

			m_pt_mouse.x = point.x - rect.left;
			m_pt_mouse.y = point.y - rect.top;

			m_user_rect.x = m_pt_mouse.x;
			m_user_rect.y = m_pt_mouse.y;

			m_user_rect.width = 1;
			m_user_rect.height = 1;

			m_user_select_roi = m_user_rect;

			//m_user_select_roi.x = point.x;

			m_b_mouse_move_pattern = true;
		}
		else
		{
			m_b_mouse_ldown_on_drawwindow = false;
		}
	}
	else
	{
		m_b_mouse_ldown_on_drawwindow = false;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
#endif

#if 0
void CEyedeaExampleDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_b_mouse_move_pattern)
	{
		//m_b_add_object_pyramid = true;

		//set pyramid
		if (m_user_select_roi.x > 0 && m_user_select_roi.y > 0 &&
			m_user_select_roi.width > 0 && m_user_select_roi.height > 0)
		{
			CRect rect;
			GetDlgItem(IDC_STATIC_IMAGE)->GetClientRect(&rect);
			CClientDC dc(GetDlgItem(IDC_STATIC_IMAGE));

			//Set Zoom Area
			float rate_x = (float)(m_user_select_roi.x - rect.left) / (float)(rect.Width());
			float rate_y = (float)(m_user_select_roi.y - rect.top) / (float)(rect.Height());
			float rate_w = (float)(m_user_select_roi.width) / (float)(rect.Width());
			float rate_h = (float)(m_user_select_roi.height) / (float)(rect.Height());

			//pDlg->m_cls_eyedea_rvs.AddObjectPyramid(pDlg->m_user_select_roi);
			if (m_command == USER_COMMAND_SELECT_SEARCH_AREA)
			{
				ERVS_SetSearchArea(rate_x, rate_y, rate_w, rate_h);

				//m_combo_get_image_option.SetCurSel(9);	//Draw Search Area Info
				//m_combo_get_image_option.SetCurSel(0);	//Input original image
			}
			else if (m_command == USER_COMMAND_SELECT_MASTER_AREA)
			{
#if 0
				//ERVS_GetMasterArea(float* out_x, float* out_y, float* out_w, float* out_h)
				int get_image_option = m_combo_get_image_option.GetCurSel();
				
				bool set_info = false;

				if (get_image_option == 2)//base
				{
					ERVS_SetMasterArea(rate_x, rate_y, rate_w, rate_h);

					set_info = true;
				}
				else if (get_image_option == 3)//search image
				{
					//GEt Search Area
					float search_x = 0.0, search_y = 0.0, search_w = 0.0, search_h = 0.0;
					ERVS_GetSearchArea(&search_x, &search_y, &search_w, &search_h);
					
					float master_x = search_x + (search_w * rate_x);
					float master_y = search_y + (search_h * rate_y);
					float master_w = search_w * rate_w;
					float master_h = search_h * rate_h;

					printf("search_x=%f, search_y=%f, search_w=%f, search_h=%f\n", search_x, search_y, search_w, search_h);
					printf("master_x=%f, master_y=%f, master_w=%f, master_h=%f\n", master_x, master_y, master_w, master_h);

					ERVS_SetMasterArea(master_x, master_y, master_w, master_h);

					set_info = true;
				}
				else
				{
					MessageBox(_T("It can be set in basic or search image information."), MB_OK);
					m_combo_get_image_option.SetCurSel(2);
				}

				if (set_info)
				{
					//-------------------------------------------------------------------------
					//Display on List Control
					float get_x = 0.0;
					float get_y = 0.0;
					float get_w = 0.0;
					float get_h = 0.0;
					ERVS_GetMasterArea(&get_x, &get_y, &get_w, &get_h);
					CString str;
					str.Format(_T("%.2f,%.2f,%.2f,%.2f"), get_x, get_y, get_w, get_h);
					m_list_information.SetItem(m_select_list_number, 4, LVIF_TEXT, str, 0, 0, 0, NULL);
					//Display on List Control
					//-------------------------------------------------------------------------
				}
#endif
			}
			else if (m_command == USER_COMMAND_SELECT_BASE_OBJECT)
			{
				ERVS_SetSelectBaseObject(rate_x, rate_y, rate_w, rate_h);
			}
			else if (m_command == USER_COMMAND_SELECT_OBJECT)
			{
#if 0
				int get_image_option = m_combo_get_image_option.GetCurSel();
				//int get_object_type = m_tab_dlg_check_defect.m_combo_object_type.GetCurSel();

				bool set_info = false;

				if (get_image_option == 2)	//base
				{
#if 0
					if (get_object_type == 0)		//circle
					{
						ERVS_SetObjectCircle(rate_x, rate_y, rate_w, rate_h);

						set_info = true;
					}
#endif
				}
				else if (get_image_option == 3)		//search image
				{
					//GEt Search Area
					float search_x = 0.0, search_y = 0.0, search_w = 0.0, search_h = 0.0;
					ERVS_GetSearchArea(&search_x, &search_y, &search_w, &search_h);

					float master_x = search_x + (search_w * rate_x);
					float master_y = search_y + (search_h * rate_y);
					float master_w = search_w * rate_w;
					float master_h = search_h * rate_h;
#if 0
					if (get_object_type == 0)		//circle
					{
						ERVS_SetObjectCircle(master_x, master_y, master_w, master_h);

						set_info = true;
					}
#endif
				}
				else if (get_image_option == 4)		//master image
				{
					//GEt master Area
					float master_x = 0.0, master_y = 0.0, master_w = 0.0, master_h = 0.0;
					ERVS_GetMasterArea(&master_x, &master_y, &master_w, &master_h);

					float object_x = master_x + (master_w * rate_x);
					float object_y = master_y + (master_h * rate_y);
					float object_w = master_w * rate_w;
					float object_h = master_h * rate_h;
#if 0
					if (get_object_type == 0)		//circle
					{
						ERVS_SetObjectCircle(object_x, object_y, object_w, object_h);

						set_info = true;
					}
#endif
				}
				else
				{
					MessageBox(_T("It can be set in basic or search / master image information."), MB_OK);
					m_combo_get_image_option.SetCurSel(4);
				}

				if (set_info)
				{
					//-------------------------------------------------------------------------
					//Display on List Control
					float get_x = 0.0;
					float get_y = 0.0;
					float get_r1 = 0.0;
					float get_r2 = 0.0;
					ERVS_GetObjectCircle(&get_x, &get_y, &get_r1, &get_r2);
					CString str;
					str.Format(_T("%.2f,%.2f,%.2f,%.2f"), get_x, get_y, get_r1, get_r2);
					m_list_information.SetItem(m_select_list_number, 6, LVIF_TEXT, str, 0, 0, 0, NULL);
					//Display on List Control
					//-------------------------------------------------------------------------
				}
#endif
			}

			m_user_select_roi.x = 0;
			m_user_select_roi.y = 0;
			m_user_select_roi.width = 0;
			m_user_select_roi.height = 0;

			m_user_rect.x = 0;
			m_user_rect.y = 0;
			m_user_rect.width = 0;
			m_user_rect.height = 0;
			//m_rect_sub_pattern = m_user_select_roi;
		}
	}

	m_b_mouse_move_pattern = false;

	m_b_mouse_ldown_on_drawwindow = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}
#endif

#if 0
void CEyedeaExampleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	if (m_b_mouse_ldown_on_drawwindow)
	{
		//pattern_window
		if (point.x >= rect.left && point.x <= rect.right &&
			point.y >= rect.top && point.y <= rect.bottom)
		{
			m_b_mouse_move_pattern = true;

			//m_pt_mouse.x = point.x - rect_pattern.left ;
			//m_pt_mouse.y = point.y - rect_pattern.top ;

			m_user_rect.width = (point.x - rect.left) - m_user_rect.x;
			m_user_rect.height = (point.y - rect.top) - m_user_rect.y;

		}
		else
		{
			m_user_rect.width = 0;
			m_user_rect.height = 0;

			//m_b_mouse_move_pattern = false ;
			m_b_mouse_ldown_on_drawwindow = false;
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
#endif

#if 0
void CEyedeaExampleDlg::DrawBoxForUserArea(cv::Mat draw)
{
	CRect rect;
	GetDlgItem(IDC_STATIC_IMAGE)->GetClientRect(&rect);
	CClientDC dc(GetDlgItem(IDC_STATIC_IMAGE));

	if (!draw.empty())
	{
		float scala_w = (float)draw.cols / (float)rect.Width();
		float scala_h = (float)draw.rows / (float)rect.Height();

		cv::Point mouse_in_win(
			(int)((float)m_pt_mouse.x*(float)(scala_w)),
			(int)((float)m_pt_mouse.y*(float)(scala_h))
		);

		//cv::Rect roi1 ;
		m_user_select_roi = m_user_rect;
		cv::Rect draw_rect = m_user_select_roi;

		draw_rect.x = (int)(m_user_rect.x * scala_w);
		draw_rect.y = (int)(m_user_rect.y * scala_h);
		draw_rect.width = (int)(m_user_rect.width * scala_w);
		draw_rect.height = (int)(m_user_rect.height * scala_h);

		if (draw_rect.x > 0 && draw_rect.y > 0 &&
			draw_rect.width > 0 && draw_rect.height > 0)
		{
			if (m_command == USER_COMMAND_SELECT_OBJECT)
			{
#if 0
				int get_object_type = m_tab_dlg_check_defect.m_combo_object_type.GetCurSel();

				if (get_object_type == 0)		//circle
				{
					//cv::circle(draw, cv::Point(m_user_select_roi.x, m_user_select_roi.y), m_user_select_roi.width, cv::Scalar(255, 255, 0), 3);
					cv::ellipse(draw, cv::Point(draw_rect.x, draw_rect.y), cv::Size(draw_rect.width, draw_rect.height),
						0, 0, 360, cv::Scalar(255, 255, 0), 3, 8, 0);
				}
#endif
			}
			else
			{
				//cv::circle(cimg, cv::Point(pDlg->m_user_select_roi.x, pDlg->m_user_select_roi.y), 10, cv::Scalar(0,0,255), 4) ;
				cv::rectangle(draw, draw_rect, cv::Scalar(255, 255, 0), 3);
			}
		}
	}
}
#endif

void CEyedeaExampleDlg::OnBnClickedButtonSetSampleImage()
{
	// TODO: Add your control notification handler code here
	ERVS_SetNextImage();

#if 0
	int mode = ERVS_GetMode();
	if (mode== ERVS_MODE_NORMAL)
	{
		m_combo_get_image_option.SetCurSel(1);
	}
	else
	{ 
		m_combo_get_image_option.SetCurSel(0);
	}
#endif
}

void CEyedeaExampleDlg::OnTcnSelchangeTabMy(int index)
{
	if (m_pwndShow != NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}

	/*
	m_tab_mode.InsertItem(0, _T("Vision Config"));
	m_tab_mode.InsertItem(1, _T("Search Area"));
	m_tab_mode.InsertItem(2, _T("NEW - Object Detection"));
	m_tab_mode.InsertItem(3, _T("Calibration"));
	m_tab_mode.InsertItem(4, _T("SVM Camera Config"));
	*/

	switch (index)
	{
	case 0:		//Vision Config
	{
		ERVS_SetMode(ERVS_MODE_NORMAL);

		m_tab_dlg_check_defect.m_b_draw_pause = true;
		m_tab_dlg_calibration.m_b_draw_pause = true;
		m_tab_dlg_vision_config.m_b_draw_pause = false;
		//m_tab_dlg_searcharea.m_b_draw_pause = true;

		m_tab_dlg_vision_config.ShowWindow(SW_SHOW);
		m_pwndShow = &m_tab_dlg_vision_config;

		m_tab_dlg_vision_config.RoadAllFromERVS();

		break;
	}
	/*
	case 1:		//Search Area
	{
		m_tab_dlg_check_defect.m_b_draw_pause = true;
		m_tab_dlg_calibration.m_b_draw_pause = true;
		m_tab_dlg_vision_config.m_b_draw_pause = true;
		m_tab_dlg_searcharea.m_b_draw_pause = false;

		m_tab_dlg_searcharea.ShowWindow(SW_SHOW);
		m_pwndShow = &m_tab_dlg_searcharea;
		break;
	}
	*/
	case 1:		//Object Detection and Check Defect
	{
		ERVS_SetMode(ERVS_MODE_NORMAL);

		//m_tab_dlg_check_defect.OnBnClickedCheckFindMultiObjects();

		m_tab_dlg_check_defect.m_b_draw_pause = false;
		m_tab_dlg_calibration.m_b_draw_pause = true;
		m_tab_dlg_vision_config.m_b_draw_pause = true;
		//m_tab_dlg_searcharea.m_b_draw_pause = true;

		m_tab_dlg_check_defect.ShowWindow(SW_SHOW);
		m_pwndShow = &m_tab_dlg_check_defect;

		m_tab_dlg_check_defect.RoadAllFromERVS();

		break;
	}
	case 2:		//calibration
	{
		ERVS_SetMode(ERVS_MODE_CALIBRATION);
		m_tab_dlg_check_defect.m_b_draw_pause = true;
		m_tab_dlg_calibration.m_b_draw_pause = false;
		m_tab_dlg_vision_config.m_b_draw_pause = true;
		//m_tab_dlg_searcharea.m_b_draw_pause = true;

		//m_tab_dlg_vision_config.OnBnClickedButtonCalibrationGetListInfo();

		m_tab_dlg_calibration.Update();
		m_tab_dlg_calibration.ShowWindow(SW_SHOW);
		m_pwndShow = &m_tab_dlg_calibration;
		break;
	}
	case 3:
		m_tab_dlg_check_defect.m_b_draw_pause = true;
		m_tab_dlg_calibration.m_b_draw_pause = true;
		m_tab_dlg_vision_config.m_b_draw_pause = true;
		//m_tab_dlg_searcharea.m_b_draw_pause = true;

		m_tab_dlg_camera_config.ShowWindow(SW_SHOW);
		m_pwndShow = &m_tab_dlg_camera_config;
		break;
	case 5:
		break;
	}
}

void CEyedeaExampleDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nIndex = m_tab_mode.GetCurSel();

	OnTcnSelchangeTabMy(nIndex);

	*pResult = 0;
}


void CEyedeaExampleDlg::OnBnClickedButtonNewModel()
{
	// TODO: Add your control notification handler code here
	//Add New Item

	int newid = ERVS_DBAddObject();

	if (newid > 0)
	{
		/*
		m_tab_mode.InsertItem(0, _T("Vision Config"));
		m_tab_mode.InsertItem(1, _T("Search Area"));
		m_tab_mode.InsertItem(2, _T("NEW - Object Detection"));
		m_tab_mode.InsertItem(3, _T("Calibration"));
		m_tab_mode.InsertItem(4, _T("SVM Camera Config"));
		*/
		//--------------------------------------------------------
		//Go to object detection tab.
		m_tab_mode.SetCurSel(0);
		OnTcnSelchangeTabMy(0);

		TCITEM tcItem;
		CString pszString;
		//pszString.Format(_T("%d - Object Detection"), newid);
		pszString.Format(_T("%d - Setting"), newid);
		//  Get the current tab item text.
		TCHAR buffer[256] = { 0 };
		tcItem.pszText = buffer;
		tcItem.cchTextMax = 256;
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = pszString.LockBuffer();

		m_tab_mode.SetItem(0, &tcItem);
	}
}

void CEyedeaExampleDlg::ManageDBListInfo(void)
{
	int list_num_ui = m_list_information.GetItemCount();
	POSITION pos = m_list_information.GetFirstSelectedItemPosition();

	//Get DB Count
	int nDB = ERVS_DB_Get_Count();
	int select_id = ERVS_DB_Get_Select_ID();

#if 0
	CString pszString;
	if (select_id > 0)
	{
		pszString.Format(_T("[%d] Object Detection"), select_id);
	}
	else
	{
		pszString.Format(_T("[-] Object Detection"));
	}

	TCITEM tcItem;
	//  Get the current tab item text.
	TCHAR buffer[256] = { 0 };
	tcItem.pszText = buffer;
	tcItem.cchTextMax = 256;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = pszString.LockBuffer();

	m_tab_mode.SetItem(1, &tcItem);
#endif

	int nItem = 0;
	for (nItem = 0; nItem < m_list_information.GetItemCount(); )
	{
		if (nItem >= nDB)
		{
			m_list_information.DeleteItem(nItem);
		}
		else
		{
			int id = ERVS_DB_Get_Info_Id(nItem);

			char* mode = ERVS_DB_Get_Mode(id);

			//id check
			CString list_id;
			list_id = m_list_information.GetItemText(nItem, 1/*id*/);

			int i_list_id = _ttoi(list_id);

			if (id != i_list_id)
			{
				//update list id
				CString str;
				str.Format(_T("%d"), id);
				//id
				m_list_information.SetItem(nItem, 1/*id*/, LVIF_TEXT, str, 0, 0, 0, NULL);
			}

			CString list_mode;
			list_mode = m_list_information.GetItemText(nItem, 2/*id*/);
			CString db_mode;
			//db_mode.Format(_T("%s"), mode);
			//str.Format(_T("%s"), version);
			db_mode = (LPSTR)mode;

			if (list_mode != db_mode)
			{
				//mode
				m_list_information.SetItem(nItem, 2/*mode*/, LVIF_TEXT, db_mode, 0, 0, 0, NULL);
			}

			if (id == select_id)
			{
				CString str;

				str = m_list_information.GetItemText(nItem, 0/*select*/);

				if (str != "▶")
				{
					str.Format(_T("▶"));
					m_list_information.SetItem(nItem, 0/*select*/, LVIF_TEXT, str, 0, 0, 0, NULL);
				}
			}
			else
			{
				CString str;

				str = m_list_information.GetItemText(nItem, 0/*select*/);

				if (str != "-")
				{
					str.Format(_T("-"));
					m_list_information.SetItem(nItem, 0/*select*/, LVIF_TEXT, str, 0, 0, 0, NULL);
				}
			}

			if (mode != NULL)
			{
				delete mode;
				mode = NULL;
			}

			++nItem;
		}
	}

	for (; nItem < nDB; nItem++)
	{
		int id = ERVS_DB_Get_Info_Id(nItem);

		char* mode = ERVS_DB_Get_Mode(id);

		//-----------------------
		//Insert
		// 0 : select
		CString str;
		str.Format(_T("-"));
		m_list_information.InsertItem(nItem, str);

		// 1 : id
		str.Format(_T("%d"), id);
		m_list_information.SetItem(nItem, 1/*id*/, LVIF_TEXT, str, 0, 0, 0, NULL);

		// 2 : mode
		str = (LPSTR)mode;
		m_list_information.SetItem(nItem, 2/*mode*/, LVIF_TEXT, str, 0, 0, 0, NULL);

		if (id == select_id)
		{
			CString str;

			str = m_list_information.GetItemText(nItem, 0/*select*/);

			if (str != "▶")
			{
				str.Format(_T("▶"));
				m_list_information.SetItem(nItem, 0/*select*/, LVIF_TEXT, str, 0, 0, 0, NULL);
			}
		}
		else
		{
			CString str;

			str = m_list_information.GetItemText(nItem, 0/*select*/);

			if (str != "-")
			{
				str.Format(_T("-"));
				m_list_information.SetItem(nItem, 0/*select*/, LVIF_TEXT, str, 0, 0, 0, NULL);
			}
		}

		if (mode != NULL)
		{
			delete mode;
			mode = NULL;
		}
	}
		
#if 0
	for (int i = 0; i < nDB; i++)
	{
		int id = ERVS_DB_Get_Info_Id(i);

		char* mode = ERVS_DB_Get_Mode(id);

		if (i < list_num_ui)
		{
			//id check
			CString list_id;
			list_id = m_list_information.GetItemText(i, 1/*id*/);

			int i_list_id = _ttoi(list_id);

			if (id != i_list_id)
			{
				//update list id
				CString str;
				str.Format(_T("%d"), id);
				//id
				m_list_information.SetItem(i, 1/*id*/, LVIF_TEXT, str, 0, 0, 0, NULL);
			}

			CString list_mode;
			list_mode = m_list_information.GetItemText(i, 2/*id*/);
			CString db_mode;
			//db_mode.Format(_T("%s"), mode);
			//str.Format(_T("%s"), version);
			db_mode = (LPSTR)mode;

			if (list_mode != db_mode)
			{
				//mode
				m_list_information.SetItem(i, 2/*mode*/, LVIF_TEXT, db_mode, 0, 0, 0, NULL);
			}
		}
		else
		{
			//-----------------------
			//Insert
			// 0 : select
			CString str;
			str.Format(_T("-"));
			m_list_information.InsertItem(i, str);

			// 1 : id
			str.Format(_T("%d"), id);
			m_list_information.SetItem(i, 1/*id*/, LVIF_TEXT, str, 0, 0, 0, NULL);

			// 2 : mode
			str = (LPSTR)mode;
			m_list_information.SetItem(i, 2/*mode*/, LVIF_TEXT, str, 0, 0, 0, NULL);
		}

		if (id == select_id)
		{
			CString str;

			str = m_list_information.GetItemText(i, 0/*select*/);

			if (str != "▶")
			{
				str.Format(_T("▶"));
				m_list_information.SetItem(i, 0/*select*/, LVIF_TEXT, str, 0, 0, 0, NULL);
			}
		}
		else
		{
			CString str;

			str = m_list_information.GetItemText(i, 0/*select*/);

			if (str != "-")
			{
				str.Format(_T("-"));
				m_list_information.SetItem(i, 0/*select*/, LVIF_TEXT, str, 0, 0, 0, NULL);
			}
		}

		if (mode != NULL)
		{
			delete mode;
			mode = NULL;
		}
	}
#endif
}

void CEyedeaExampleDlg::OnNMDblclkListInformation(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	if (pNMItemActivate->iItem != -1)
	{
		//select id
		CString strSelectID = m_list_information.GetItemText(pNMItemActivate->iItem, 1);

		int id = _ttoi(strSelectID);

		//Get Information From DB
		ERVS_SetObject(id);

		//----------------------------------------------
		//Goto tab
		//m_tab_mode.SetCurSel(2);
		//OnTcnSelchangeTabMy(2);
		m_tab_mode.SetCurSel(0);
		OnTcnSelchangeTabMy(0);

		TCITEM tcItem;
		CString pszString;
		//pszString.Format(_T("%d - Object Detection"), id);
		pszString.Format(_T("%d - Setting"), id);
		//  Get the current tab item text.
		TCHAR buffer[256] = { 0 };
		tcItem.pszText = buffer; 
		tcItem.cchTextMax = 256;
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = pszString.LockBuffer();

		m_tab_mode.SetItem(0, &tcItem);
		//Goto tab
		//----------------------------------------------
	}

	*pResult = 0;
}

void CEyedeaExampleDlg::OnBnClickedButtonGetVersion()
{
	// TODO: Add your control notification handler code here
	char* version = ERVS_GetVersion();

	CString str;
	//str.Format(_T("%s"), version);
	str = (LPSTR)version;

	GetDlgItem(IDC_EDIT_VERSION)->SetWindowText(str);

	if (version != NULL)
	{
		delete version;
		version = NULL;
	}
}

void CEyedeaExampleDlg::OnBnClickedButtonDelModel()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < m_list_information.GetItemCount(); i++)
	{
		int unState = m_list_information.GetItemState(i, LVIS_STATEIMAGEMASK);

		if (unState == 0x2000)
		{
			//select id
			CString strSelectID = m_list_information.GetItemText(i, 1/*id*/);

			int id = _ttoi(strSelectID);

			ERVS_DB_Del_ID(id);
		}
	}

	m_list_information.DeleteAllItems();
}


void CEyedeaExampleDlg::OnBnClickedButtonListSave()
{
	// TODO: Add your control notification handler code here
	CString strDBPath;
	GetDlgItem(IDC_EDIT_DB_PATH)->GetWindowText(strDBPath);

	//std::string str_path((LPCTSTR)strDBPath);
	std::string str_path = std::string(CT2CA(strDBPath.operator LPCWSTR()));

	ERVS_FileSaveObjectDBList(str_path);
}

#if 0
void CEyedeaExampleDlg::OnBnClickedCheckLog()
{
	// TODO: Add your control notification handler code 
	BOOL bLog = IsDlgButtonChecked(IDC_CHECK_LOG);

	if (bLog)
	{
		ERVS_SetLog(1);
	}
	else
	{
		ERVS_SetLog(0);
	}
}
#endif


void CEyedeaExampleDlg::OnBnClickedButtonListLoad()
{
	// TODO: Add your control notification handler code here
	CString strDBPath;
	GetDlgItem(IDC_EDIT_DB_PATH)->GetWindowText(strDBPath);

	//std::string str_path((LPCTSTR)strDBPath);
	std::string str_path = std::string(CT2CA(strDBPath.operator LPCWSTR()));

	ERVS_FileLoadObjectDBList(str_path);
}


BOOL CEyedeaExampleDlg::PreTranslateMessage(MSG* pMsg)
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
