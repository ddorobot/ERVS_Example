// EyedeaCalibrationTabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "EyedeaCalibrationTabDlg.h"
#include "afxdialogex.h"


// CEyedeaCalibrationTabDlg dialog

IMPLEMENT_DYNAMIC(CEyedeaCalibrationTabDlg, CDialogEx)

CEyedeaCalibrationTabDlg::CEyedeaCalibrationTabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CALIBRATION, pParent)
	, m_run_thread(false)
	, m_b_draw_pause(true)
{
	m_calib_image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
}

CEyedeaCalibrationTabDlg::~CEyedeaCalibrationTabDlg()
{
}

void CEyedeaCalibrationTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CALIBRATION_IMAGES, m_List_calibration);
}


BEGIN_MESSAGE_MAP(CEyedeaCalibrationTabDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATION_GET_LIST_INFO, &CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationGetListInfo)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATION_CHESS_INFO_GET, &CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationChessInfoGet)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATION_CHESS_INFO_SET, &CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationChessInfoSet)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATION_ADD_LIST_INFO, &CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationAddListInfo)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATION_DEL_LIST_INFO, &CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationDelListInfo)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATION_GET_LIST_INFO3, &CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationGetListInfo3)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATION_RUN, &CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationRun)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_SAVE_CALIBRATION, &CEyedeaCalibrationTabDlg::OnBnClickedButtonSaveCalibration)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_CALIBRATION, &CEyedeaCalibrationTabDlg::OnBnClickedButtonLoadCalibration)
	ON_BN_CLICKED(IDC_BUTTON_GET_CALIBRATION_IMAGE, &CEyedeaCalibrationTabDlg::OnBnClickedButtonGetCalibrationImage)
END_MESSAGE_MAP()


// CEyedeaCalibrationTabDlg message handlers


BOOL CEyedeaCalibrationTabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString str;
	str.Format(_T("-"));

	GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NX)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NY)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_SIZE)->SetWindowText(str);

	GetDlgItem(IDC_EDIT_CALIBRATION_MOVE_ROBOT_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_MOVE_ROBOT_Y)->SetWindowText(str);

	GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_Y)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_Y)->SetWindowText(str);
	
	m_ImgList.Create(160, 120, ILC_COLOR24, 0, 0); //이미지 아이콘의 크기를 결정하는듯			
	m_List_calibration.SetImageList(&m_ImgList, LVSIL_NORMAL);
	//m_List_calibration.SetExtendedStyle(LVS_EX_CHECKBOXES);

	//start Thread
	//eyedea - start of thread
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CEyedeaCalibrationTabDlg::ThreadFunctionDraw, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEyedeaCalibrationTabDlg::ThreadFunctionDraw()
{
	if(m_calib_image.empty()) 	m_calib_image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
	cv::Mat image_result = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display

	CRect rect_display_ori;													//display rect
	GetDlgItem(IDC_STATIC_IMAGE_CALIBRATION_ORI)->GetClientRect(&rect_display_ori);			//get rect information on window
	CClientDC dc_display_ori(GetDlgItem(IDC_STATIC_IMAGE_CALIBRATION_ORI));					//device context for display mfc control

	CvvImage vImage;		//display class for display on MFC control

	while (m_run_thread)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(1));

		if (m_b_draw_pause)
		{
			continue;
		}

		vImage.CopyOf(&IplImage(m_calib_image), 1);							//mat to vimage
		vImage.DrawToHDC(dc_display_ori.m_hDC, &rect_display_ori);				//draw on display_rect
	};
}

CBitmap* CEyedeaCalibrationTabDlg::IplImageToCBitmap(IplImage* img)
{
	CDC dc;
	CDC memDC;
	CDC* pDC = NULL;// this->GetDC();

	if (!dc.CreateDC(_T("DISPLAY"), NULL, NULL, NULL))
	{
		pDC = this->GetDC();

		if (!pDC)
		{
			printf("fail. createDC\n");

			return NULL;
		}
	}
	if (!memDC.CreateCompatibleDC(&dc))
	{
		printf("fail. CreateCompatibleDC\n");
		return NULL;
	}

	CBitmap* bmp = new CBitmap();
	CBitmap* pOldBitmap;

	CDC* thisDC = NULL;
	if (pDC)	thisDC = pDC;
	else		thisDC = &dc;
	
	bmp->CreateCompatibleBitmap(thisDC, img->width, img->height);
	pOldBitmap = memDC.SelectObject(bmp);

	CvvImage cvImage; // you will need OpenCV_2.2.0- to use CvvImage 
	cvImage.CopyOf(img);
	cvImage.Show(memDC.m_hDC, 0, 0, img->width, img->height, 0, 0);
	cvImage.Destroy();

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	
	if( pDC == NULL)
		dc.DeleteDC();

	return bmp;
}

void CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationGetListInfo()
{
	// Remove every other image from the image list.
	while (m_ImgList.GetImageCount()) m_ImgList.Remove(0);

	m_List_calibration.DeleteAllItems();

	int nCalibrationInfo = ERVS_Calibration_GetCount();

	cv::Mat calibration_image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);

	for (int i = 0; i < nCalibrationInfo; i++)
	{
		int len = 640*480*3;
		ERVS_Calibration_GetImage(i, (char**)&calibration_image.data, &len);

		float robot_x = 0.0, robot_y = 0.0;
		ERVS_Calibration_GetRobotInfo(i, &robot_x, &robot_y);

		cv::Mat image;
		cv::resize(calibration_image, image, cv::Size(160, 120));

		IplImage* iplimage_ = new IplImage(image);

		//cvShowImage("tt", iplimage_);
		//cv::waitKey(0);

		//CBitmap *aCBitmap = IplImageToCBitmap(image2);
		CBitmap *aCBitmap = IplImageToCBitmap(iplimage_);
		//CBitmap *aCBitmap = IplImageToCBitmap((IplImage*)&image);

		//
		if (aCBitmap)
		{
			m_ImgList.Add(aCBitmap, RGB(0, 0, 0)); // 두번째 인자는 마스크로 검정색으로 해야 이미지 주변이 하얗게 나온다.
			CString str;
			str.Format(_T("%.2f,%.2f"), robot_x, robot_y);
			m_List_calibration.InsertItem(i, str, i);

			delete aCBitmap;
			aCBitmap = NULL;
		}

		if (iplimage_)
		{
			delete iplimage_;
			iplimage_ = NULL;
		}
	}
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationChessInfoGet()
{
	// TODO: Add your control notification handler code here

	int number_cols = ERVS_GetVisionConfigOption(VISION_CONFIG_CALIBRATION_CHESS_NUM_COLS);
	int number_rows = ERVS_GetVisionConfigOption(VISION_CONFIG_CALIBRATION_CHESS_NUM_ROWS);
	float size = ERVS_GetVisionConfigOption(VISION_CONFIG_CALIBRATION_CHESS_SIZE);

	CString str;
	str.Format(_T("%d"), number_cols);
	GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NX)->SetWindowText(str);
	str.Format(_T("%d"), number_rows);
	GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NY)->SetWindowText(str);
	str.Format(_T("%.2f"), size);
	GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_SIZE)->SetWindowText(str);
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationChessInfoSet()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NX)->GetWindowText(str);
	float number_cols = _ttof(str);

	GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NY)->GetWindowText(str);
	float number_rows = _ttof(str);

	GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_SIZE)->GetWindowText(str);
	float square_size = _ttof(str);

	ERVS_SetVisionConfigOption(VISION_CONFIG_CALIBRATION_CHESS_NUM_COLS, number_cols);
	ERVS_SetVisionConfigOption(VISION_CONFIG_CALIBRATION_CHESS_NUM_ROWS, number_rows);
	ERVS_SetVisionConfigOption(VISION_CONFIG_CALIBRATION_CHESS_SIZE, square_size);

	OnBnClickedButtonCalibrationChessInfoGet();
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationAddListInfo()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_CALIBRATION_MOVE_ROBOT_X)->GetWindowText(str);
	float robot_x = _ttof(str);

	GetDlgItem(IDC_EDIT_CALIBRATION_MOVE_ROBOT_Y)->GetWindowText(str);
	float robot_y = _ttof(str);

	ERVS_Calibration_Add(robot_x, robot_y);

	OnBnClickedButtonCalibrationGetListInfo();
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationDelListInfo()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_List_calibration.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_List_calibration.GetNextSelectedItem(pos);
		ERVS_Calibration_Del(nItem);
	}

	OnBnClickedButtonCalibrationGetListInfo();
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationGetListInfo3()
{
	// TODO: Add your control notification handler code here
	ERVS_Calibration_Clear();

	OnBnClickedButtonCalibrationGetListInfo();
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationRun()
{
	// TODO: Add your control notification handler code here
	//pause 
	ERVS_Calibration_Run();

	//check calibration result
	float robot_x = 0;
	float robot_y = 0;
	ERVS_Calibration_GetPoint(0.5, 0.5, &robot_x, &robot_y);

	CString str;
	str.Format(_T("%.3f"), 640.0*0.5);
	GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_X)->SetWindowText(str);
	str.Format(_T("%.3f"), 480.0*0.5);
	GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_Y)->SetWindowText(str);
	str.Format(_T("%.3f"), robot_x);
	GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_X)->SetWindowText(str);
	str.Format(_T("%.3f"), robot_y);
	GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_Y)->SetWindowText(str);
}

void CEyedeaCalibrationTabDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetDlgItem(IDC_STATIC_IMAGE_CALIBRATION_ORI)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	//pattern_window
	if (point.x >= rect.left && point.x <= rect.right &&
		point.y >= rect.top && point.y <= rect.bottom)
	{
		float rate_x = (float)(point.x - rect.left) / (float)(rect.Width());
		float rate_y = (float)(point.y - rect.top) / (float)(rect.Height());

		float robot_x = 0;
		float robot_y = 0;
		ERVS_Calibration_GetPoint(rate_x, rate_y, &robot_x, &robot_y);

		CString str;
		str.Format(_T("%.3f"), 640.0*rate_x);
		GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_X)->SetWindowText(str);
		str.Format(_T("%.3f"), 480.0*rate_y);
		GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_Y)->SetWindowText(str);
		str.Format(_T("%.3f"), robot_x);
		GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_X)->SetWindowText(str);
		str.Format(_T("%.3f"), robot_y);
		GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_Y)->SetWindowText(str);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonSaveCalibration()
{
	// TODO: Add your control notification handler code here
	ERVS_Calibration_Save();
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonLoadCalibration()
{
	// TODO: Add your control notification handler code here
	ERVS_Calibration_Load();

	OnBnClickedButtonCalibrationGetListInfo();

	//check calibration result
	float robot_x = 0;
	float robot_y = 0;
	ERVS_Calibration_GetPoint(0.5, 0.5, &robot_x, &robot_y);

	CString str;
	str.Format(_T("%.3f"), 640.0*0.5);
	GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_X)->SetWindowText(str);
	str.Format(_T("%.3f"), 480.0*0.5);
	GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_Y)->SetWindowText(str);
	str.Format(_T("%.3f"), robot_x);
	GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_X)->SetWindowText(str);
	str.Format(_T("%.3f"), robot_y);
	GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_Y)->SetWindowText(str);
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonGetCalibrationImage()
{
	// TODO: Add your control notification handler code here
	int len = 921600;
	ERVS_GetImage(GET_IMAGE_CALIBRATION_FEATURE, 0, (char**)&m_calib_image.data, &len);
}
