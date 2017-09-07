// EyedeaPickAndPlaceTabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EyedeaExample.h"
#include "EyedeaPickAndPlaceTabDlg.h"
#include "afxdialogex.h"
#include "EyedeaExampleDlg.h"

// CEyedeaPickAndPlaceTabDlg dialog

IMPLEMENT_DYNAMIC(CEyedeaPickAndPlaceTabDlg, CDialogEx)

CEyedeaPickAndPlaceTabDlg::CEyedeaPickAndPlaceTabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PICK_AND_PLACE, pParent)
	, m_run_thread(false)
	, m_b_draw_pause(true)
{

}

CEyedeaPickAndPlaceTabDlg::~CEyedeaPickAndPlaceTabDlg()
{
	m_b_draw_pause = true;
	m_run_thread = false;
}

void CEyedeaPickAndPlaceTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEyedeaPickAndPlaceTabDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PAP_SET_MASTER_OBJECT, &CEyedeaPickAndPlaceTabDlg::OnBnClickedButtonPapSetMasterObject)
END_MESSAGE_MAP()


// CEyedeaPickAndPlaceTabDlg message handlers


void CEyedeaPickAndPlaceTabDlg::OnBnClickedButtonPapSetMasterObject()
{
	// TODO: Add your control notification handler code here
	//((CEyedeaExampleDlg *)GetParent())->m_combo_get_image_option.SetCurSel(0);		//Set Image

	((CEyedeaExampleDlg *)GetParent())->m_command = USER_COMMAND_SELECT_PAP_MASTER_OBJECT;
}


BOOL CEyedeaPickAndPlaceTabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//start Thread
	//eyedea - start of thread
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CEyedeaPickAndPlaceTabDlg::ThreadFunctionDraw, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEyedeaPickAndPlaceTabDlg::ThreadFunctionDraw()
{

	while (m_run_thread)
	{
		if (m_b_draw_pause)
		{
			boost::this_thread::sleep(boost::posix_time::millisec(1));
			continue;
		}
	};
}

BOOL CEyedeaPickAndPlaceTabDlg::PreTranslateMessage(MSG* pMsg)
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
