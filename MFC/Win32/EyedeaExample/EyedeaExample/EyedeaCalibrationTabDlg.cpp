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
	//m_calib_image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
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
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATION_COPY, &CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationCopy)
	ON_BN_CLICKED(IDC_BUTTON_STANDALONE_CALIB_RUN, &CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibRun)
	ON_BN_CLICKED(IDC_BUTTON_STANDALONE_CALIB_GET_FEATURE_POS, &CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibGetFeaturePos)
	ON_BN_CLICKED(IDC_BUTTON_STANDALONE_CALIB_SET_MATRIX, &CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibSetMatrix)
	ON_BN_CLICKED(IDC_BUTTON_STANDALONE_CALIB_GET_MATRIX, &CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibGetMatrix)
	ON_BN_CLICKED(IDC_BUTTON_STANDALONE_CALIB_CALC_MATRIX, &CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibCalcMatrix)
	ON_BN_CLICKED(IDC_BUTTON_STANDALONE_CALIB_INIT, &CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibInit)
	ON_BN_CLICKED(IDC_BUTTON_STANDALONE_CALIB_SET_Y_DIRECTION, &CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibSetYDirection)
	ON_BN_CLICKED(IDC_BUTTON_STANDALONE_CALIB_SET_Y_DIRECTION_INV, &CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibSetYDirectionInv)
	ON_BN_CLICKED(IDC_BUTTON_CALIB_SET_CUSTOM_CENTER, &CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibSetCustomCenter)
END_MESSAGE_MAP()


// CEyedeaCalibrationTabDlg message handlers


BOOL CEyedeaCalibrationTabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString str;
	str.Format(_T("-"));

	if (boost::filesystem::exists("ervs_example.ini"))
	{
		try
		{
			//last environment from ini
			boost::property_tree::ptree pt_eyedea;
			boost::property_tree::ini_parser::read_ini("ervs_example.ini", pt_eyedea);
			int chess_nx = pt_eyedea.get<int>("ervs_example.calibration_chess_nx");
			int chess_ny = pt_eyedea.get<int>("ervs_example.calibration_chess_ny");
			int chess_size = pt_eyedea.get<int>("ervs_example.calibration_chess_size");

			str.Format(_T("%d"), chess_nx);
			GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NX)->SetWindowText(str);
			str.Format(_T("%d"), chess_ny);
			GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NY)->SetWindowText(str);
			str.Format(_T("%d"), chess_size);
			GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_SIZE)->SetWindowText(str);
		}
		catch (std::exception &ex)
		{
			GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NX)->SetWindowText(str);
			GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NY)->SetWindowText(str);
			GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_SIZE)->SetWindowText(str);
		}
	}
	else
	{
		GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NX)->SetWindowText(str);
		GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_NY)->SetWindowText(str);
		GetDlgItem(IDC_EDIT_CALIBRATION_CHESS_SIZE)->SetWindowText(str);
	}

	str.Format(_T("-"));

	GetDlgItem(IDC_EDIT_CALIBRATION_MOVE_ROBOT_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_MOVE_ROBOT_Y)->SetWindowText(str);

	GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_Y)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_Y)->SetWindowText(str);

	GetDlgItem(IDC_EDIT_CALIBRATION_TL_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_TL_Y)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_BR_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_BR_Y)->SetWindowText(str);
	
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
	m_calib_image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
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

		//ERVS_Calibration_GetID
		int calibration_id = ERVS_Calibration_GetID();
		CString strText;
		strText.Format(_T("%d"), calibration_id);
		GetDlgItem(IDC_EDIT_CALIBRATION_ID)->SetWindowText(strText);
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

	boost::property_tree::ptree pt;
	pt.put("ervs_example.calibration_chess_nx", (int)number_cols);
	pt.put("ervs_example.calibration_chess_ny", (int)number_rows);
	pt.put("ervs_example.calibration_chess_size", (int)square_size);
	boost::property_tree::ini_parser::write_ini("ervs_example.ini", pt);
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

void CEyedeaCalibrationTabDlg::UpdateDataCalibrationRun(void)
{
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

	int number_cols = ERVS_GetVisionConfigOption(VISION_CONFIG_CALIBRATION_CHESS_NUM_COLS);
	int number_rows = ERVS_GetVisionConfigOption(VISION_CONFIG_CALIBRATION_CHESS_NUM_ROWS);

	//Get Chess Top-Left
	int top_left_index = (number_rows - 2);
	float robot_x_on_chess_top_left = 0;
	float robot_y_on_chess_top_left = 0;
	ERVS_Calibration_GetChessPoint(top_left_index, &robot_x_on_chess_top_left, &robot_y_on_chess_top_left);

	str.Format(_T("%.3f"), robot_x_on_chess_top_left);
	GetDlgItem(IDC_EDIT_CALIBRATION_TL_X)->SetWindowText(str);
	str.Format(_T("%.3f"), robot_y_on_chess_top_left);
	GetDlgItem(IDC_EDIT_CALIBRATION_TL_Y)->SetWindowText(str);

	//Get Chess Bottom-Right
	int bottom_right_index = (number_rows - 1) * (number_cols - 2);
	float robot_x_on_chess_bottom_right = 0;
	float robot_y_on_chess_bottom_right = 0;
	ERVS_Calibration_GetChessPoint(bottom_right_index, &robot_x_on_chess_bottom_right, &robot_y_on_chess_bottom_right);

	str.Format(_T("%.3f"), robot_x_on_chess_bottom_right);
	GetDlgItem(IDC_EDIT_CALIBRATION_BR_X)->SetWindowText(str);
	str.Format(_T("%.3f"), robot_y_on_chess_bottom_right);
	GetDlgItem(IDC_EDIT_CALIBRATION_BR_Y)->SetWindowText(str);

	//UpdateDataCalibrationRun();
}

void CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationRun()
{
	// TODO: Add your control notification handler code here
	ERVS_Calibration_Run();

	UpdateDataCalibrationRun();
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
	if (!m_calib_image.empty())
	{
		int len = 921600;
		ERVS_GetImage(GET_IMAGE_CALIBRATION_FEATURE, 0, (char**)&m_calib_image.data, &len);
	}
}

void CEyedeaCalibrationTabDlg::Update()
{
	OnBnClickedButtonCalibrationChessInfoGet();
	OnBnClickedButtonCalibrationGetListInfo();

	CString str;
	str.Format(_T("-"));

	GetDlgItem(IDC_EDIT_CALIBRATION_MOVE_ROBOT_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_MOVE_ROBOT_Y)->SetWindowText(str);

	GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_PIXEL_Y)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_X)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_CALIBRATION_ROBOT_Y)->SetWindowText(str);
}

void CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibrationCopy()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_CALIBRATION_COPY_ID)->GetWindowText(str);
	int calibration_copy_id = _ttoi(str);

	ERVS_Calibration_Copy(calibration_copy_id);

	OnBnClickedButtonCalibrationGetListInfo();

	UpdateDataCalibrationRun();

}


BOOL CEyedeaCalibrationTabDlg::PreTranslateMessage(MSG* pMsg)
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


void CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibRun()
{
	// TODO: Add your control notification handler code here
	ERVS_Calibration_StandAlone_Run();

	UpdateDataCalibrationRun();
}



void CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibGetFeaturePos()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	float posA[3], posB[3], posC[3], posD[3];
	int nCalibrationInfo = ERVS_Calibration_StandAlone_Get_Image_Count();
	
	CString PosStr;
	for (int i = 0; i < nCalibrationInfo ; i++)
	{

		ERVS_Calibration_StandAlone_Get_Feature_Pos(i, posA, posB, posC, posD);

		CString str;
		str.Format(_T("PosA:[%.2f,%.2f,%.2f] / "), posA[0], posA[1], posA[2]);

		PosStr += str;

		str.Format(_T("PosB:[%.2f,%.2f,%.2f] / "), posB[0], posB[1], posB[2]);

		PosStr += str;

		str.Format(_T("PosC:[%.2f,%.2f,%.2f] / "), posC[0], posC[1], posC[2]);

		PosStr += str;

		str.Format(_T("PosD:[%.2f,%.2f,%.2f] \r\n"), posD[0], posD[1], posD[2]);

		PosStr += str;
	}

	GetDlgItem(IDC_EDIT_STANDALONE_CALIB_SHOW_FEATURE_POS)->SetWindowText(PosStr);
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibSetMatrix()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//float matrix[12] = { 1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.0,11.1,12.1};
	float matrix[12] = { 1,0,0,0,
						0,1,0,0,
						0,0,1,0 };
	ERVS_Calibration_StandAlone_Set_Matrix(matrix);
	UpdateDataCalibrationRun();
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibGetMatrix()
{
	float matrix[12];
	ERVS_Calibration_StandAlone_Get_Matrix(matrix);
	for (int i = 0; i < 12; i++)
	{
		printf("matval[%d] : %f\n", i, matrix[i]);
	}
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibCalcMatrix()
{
/*	float cposA[3] = { 0,0,0 };
	float cposB[3] = { 200,0,0 };
	float cposC[3] = { 0,100,0 };
	float cposD[3] = { 200,100,0 };
	float rposA[3] = { 1000,2000,3000 };
	float rposB[3] = { 1193.97,2040.14,2972.35 };
	float rposC[3] = { 982.9, 2096.46, 3020.07 };
	float rposD[3] = { 1176.87, 2136.60, 2992.42 };*/

	float cposA[3], cposB[3], cposC[3], cposD[3];
	int nCalibrationInfo = ERVS_Calibration_StandAlone_Get_Image_Count();
	for (int i = 0; i < nCalibrationInfo; i++)
	{
		ERVS_Calibration_StandAlone_Get_Feature_Pos(i, cposA, cposB, cposC, cposD);
	}

	/*float cposA[3] = { 0,0,0 };
	float cposB[3] = { 200,0,0 };
	float cposC[3] = { 0,100,0 };
	float cposD[3] = { 200,100,0 };*/
	float rposA[3] = { 0,75,0 };
	float rposB[3] = { 180,75, 0 };
	float rposC[3] = { 0,0, 0 };
	float rposD[3] = { 180,0, 0 };

	float matrix[12];
	ERVS_Calibration_StandAlone_Calc_Calib_Matrix(cposA, cposB, cposC, cposD, rposA, rposB, rposC, rposD, matrix);
	for (int i = 0; i < 12; i++)
	{
		printf(" matrix[%d] = %f\n",i, matrix[i]);
	}
	UpdateDataCalibrationRun();
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibInit()
{
	ERVS_Calibration_StandAlone_Init();
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibSetYDirection()
{
	ERVS_Calibration_StandAlone_Y_Direction(1);
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonStandaloneCalibSetYDirectionInv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ERVS_Calibration_StandAlone_Y_Direction(0);
}


void CEyedeaCalibrationTabDlg::OnBnClickedButtonCalibSetCustomCenter()
{
	CString str;
	GetDlgItem(IDC_EDIT_CUSTOM_CENTER_VAL)->GetWindowText(str);
	int customnum = _ttoi(str);
	ERVS_Calibration_Custom_Center_Point(customnum);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
