// TennisBallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TennisBall.h"
#include "TennisBallDlg.h"
#include "math.h"
#include "string.h"

#include "tbget.h"

#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif









// CTennisBallDlg dialog


CTennisBallDlg::CTennisBallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTennisBallDlg::IDD, pParent)
	, m_UpdateImage(FALSE)
	, m_Acquisition(FALSE)
	, m_PlayDelay(0)
	, m_CatchX(0)
	, m_CatchY(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTennisBallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_UPDATEIMG, m_UpdateImage);
	DDX_Radio(pDX, IDC_STOP, m_Acquisition);
	DDX_Text(pDX, IDC_SDELAY, m_PlayDelay);
	DDV_MinMaxInt(pDX, m_PlayDelay, 0, 2000);
	DDX_Text(pDX, IDC_CATCHX, m_CatchX);
	DDV_MinMaxDouble(pDX, m_CatchX, -9.0, 9.0);
	DDX_Text(pDX, IDC_CATCHY, m_CatchY);
	DDV_MinMaxDouble(pDX, m_CatchY, -8.0, 8.0);
}

BEGIN_MESSAGE_MAP(CTennisBallDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDEXIT, &CTennisBallDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_LOADIMG, &CTennisBallDlg::OnBnClickedLoadimg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_UPDATEIMG, &CTennisBallDlg::OnBnClickedUpdateimg)
	ON_BN_CLICKED(IDC_SAVEIMG, &CTennisBallDlg::OnBnClickedSaveimg)
	ON_BN_CLICKED(IDC_SHOWSEQ, &CTennisBallDlg::OnBnClickedShowseq)
	ON_BN_CLICKED(IDC_CATCH, &CTennisBallDlg::OnBnClickedCatch)
	ON_BN_CLICKED(IDC_CATCHRESET, &CTennisBallDlg::OnBnClickedCatchreset)
	ON_BN_CLICKED(IDC_CATCHERMOVE, &CTennisBallDlg::OnBnClickedCatchermove)
	ON_BN_CLICKED(IDC_GRAB, &CTennisBallDlg::OnBnClickedGrab)
	ON_BN_CLICKED(IDC_STOP, &CTennisBallDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_CAPTURE, &CTennisBallDlg::OnBnClickedCapture)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CENTER, &CTennisBallDlg::OnBnClickedCenter)
END_MESSAGE_MAP()


// CTennisBallDlg message handlers

BOOL CTennisBallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	VERIFY(m_Exit.AutoLoad(IDEXIT, this));
	WINDOWPLACEMENT lpwndpl;
	GetWindowPlacement(&lpwndpl);
	//lpwndpl.showCmd = SW_SHOWMAXIMIZED;
	SetWindowPlacement(&lpwndpl);
	// Added for Display Using DIB
	MainWnd = this;
	ImageDC[0] = GetDlgItem(IDC_IMAGE_DISPLAY1)->GetDC();
	ParentWnd[0] = GetDlgItem(IDC_IMAGE_DISPLAY1);
	ParentWnd[0]->GetWindowPlacement(&lpwndpl);
	ImageRect[0] = lpwndpl.rcNormalPosition;
	ParentWnd[0]->GetWindowRect(DispRect[0]);

	ImageDC[1] = GetDlgItem(IDC_IMAGE_DISPLAY2)->GetDC();
	ParentWnd[1] = GetDlgItem(IDC_IMAGE_DISPLAY2);
	ParentWnd[1]->GetWindowPlacement(&lpwndpl);
	ImageRect[1] = lpwndpl.rcNormalPosition;
	ParentWnd[1]->GetWindowRect(DispRect[1]);

	QSSysInit();
	m_UpdateImage = IR.UpdateImage;
	m_Acquisition = IR.Acquisition;
	m_PlayDelay = IR.PlayDelay;
	UpdateData(FALSE);
	t = NULL;

#ifdef USE_STAGE
	if(IR.Hoop->device.IsConnected() == false) exit(0);
	if (IR.Hoop->device.SetConfig(_MMOD, Y_MOTOR, OPEN_LOOP_SP) != RQ_SUCCESS) AfxMessageBox("Error setting operating mode");	// Set to open loop speed move
	if (IR.Hoop->device.SetConfig(_MMOD, X_MOTOR, OPEN_LOOP_SP) != RQ_SUCCESS) AfxMessageBox("Error setting operating mode");	// Set to open loop speed move
	if (IR.Hoop->device.SetCommand(_GO, Y_MOTOR, 0) != RQ_SUCCESS) AfxMessageBox("Error sending move command");	// stop motor
	if (IR.Hoop->device.SetCommand(_GO, X_MOTOR, 0) != RQ_SUCCESS) AfxMessageBox("Error sending move command");	// stop motor
#endif
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTennisBallDlg::OnPaint()
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
		if (IR.UpdateImage == TRUE) {
			::SetDIBitsToDevice(
				ImageDC[0]->GetSafeHdc(), 1, 1,
				m_bitmapInfo.bmiHeader.biWidth, 
				::abs(m_bitmapInfo.bmiHeader.biHeight),
				0, 0, 0, 
				::abs(m_bitmapInfo.bmiHeader.biHeight),
				IR.DispBuf[0].data, 
 				&m_bitmapInfo, DIB_RGB_COLORS);
			if(IR.NumCameras == 2) {
				::SetDIBitsToDevice(
					ImageDC[1]->GetSafeHdc(), 1, 1,
					m_bitmapInfo.bmiHeader.biWidth, 
					::abs(m_bitmapInfo.bmiHeader.biHeight),
					0, 0, 0, 
					::abs(m_bitmapInfo.bmiHeader.biHeight),
					IR.DispBuf[1].data, // changed to camera 2 
					&m_bitmapInfo, DIB_RGB_COLORS);
			}
		}
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTennisBallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTennisBallDlg::OnBnClickedExit()
{
	CDialog::OnOK();
}

void CTennisBallDlg::OnBnClickedLoadimg()
{
	CString		DirectoryName;
	CString		Filter;
	Filter.Format("Bitmap Image (*.bmp)|*.bmp|| | TIFF Document (*.tif)|*.tif");
	DirectoryName.Format("%sImages\\*.bmp",APP_DIRECTORY);
	CFileDialog dlg(TRUE, NULL, DirectoryName, OFN_PATHMUSTEXIST, Filter, NULL);
	if (dlg.DoModal() == IDOK) {
		char	FileName[512], FileExt[512];
		CString WholeName;
		WholeName = dlg.GetPathName();
		strcpy_s(FileName, WholeName.Left(WholeName.Find(".")-3));
		strcpy_s(FileExt, dlg.GetFileExt());
		char	FullName[512];
		int i;
		for (i=0; i<MAX_BUFFER; i++) {
			if (i<10)
				sprintf_s(FullName, "%sL0%d.%s", FileName, i, FileExt);
			else
				sprintf_s(FullName, "%sL%d.%s", FileName, i, FileExt);
			IR.SaveBuf[0][i] = imread(FullName, -1);
		}
		for (i=0; i<MAX_BUFFER; i++) {
			if (i<10)
				sprintf_s(FullName, "%sR0%d.%s", FileName, i, FileExt);
			else
				sprintf_s(FullName, "%sR%d.%s", FileName, i, FileExt);
			IR.SaveBuf[1][i] = imread(FullName, -1);
		}
		Invalidate(FALSE);
	}
}

void CTennisBallDlg::OnBnClickedSaveimg()
{
	CString		DirectoryName;
	CString		Filter;
	Filter.Format("Bitmap Image (*.bmp)|*.bmp|| | TIFF Document (*.tif)|*.tif");
	DirectoryName.Format("%sImages\\*.bmp",APP_DIRECTORY);
	CFileDialog dlg(FALSE, "bmp", DirectoryName, OFN_PATHMUSTEXIST, Filter, NULL);
	if (dlg.DoModal() == IDOK) {
		char	FileName[512], FileExt[512];
		CString WholeName;
		WholeName = dlg.GetPathName();
		strcpy_s(FileName, WholeName.Left(WholeName.Find(".")));
		strcpy_s(FileExt, dlg.GetFileExt());
		char	FullName[512];
		int i;
		for (i=0; i<MAX_BUFFER; i++) {
			if (i<10)
				sprintf_s(FullName, "%sL0%d.%s", FileName, i, FileExt);
			else
				sprintf_s(FullName, "%sL%d.%s", FileName, i, FileExt);
			imwrite(FullName, IR.SaveBuf[0][i]);
		}
		for (i=0; i<MAX_BUFFER; i++) {
			if (i<10)
				sprintf_s(FullName, "%sR0%d.%s", FileName, i, FileExt);
			else
				sprintf_s(FullName, "%sR%d.%s", FileName, i, FileExt);
			imwrite(FullName, IR.SaveBuf[1][i]);
		}
	}
}


void CTennisBallDlg::OnDestroy()
{
	__super::OnDestroy();

	IR.Acquisition = FALSE;
	IR.UpdateImage = FALSE;
	// AfxMessageBox("Closing Point Grey");
	QSSysFree();	
	UpdateData(TRUE);
}

void CTennisBallDlg::OnBnClickedUpdateimg()
{
	UpdateData(TRUE);
	IR.UpdateImage = m_UpdateImage;
}

void CTennisBallDlg::OnBnClickedShowseq()
{
	UpdateData(TRUE);
	IR.Acquisition = m_Acquisition = FALSE;
	UpdateData(FALSE);

	IR.PlayDelay = m_PlayDelay;
	IR.FrameID = 0;
	IR.DisplaySequence = TRUE;
}

void CTennisBallDlg::OnBnClickedGrab()
{
	UpdateData(TRUE);
	IR.Acquisition = m_Acquisition;
}

void CTennisBallDlg::OnBnClickedStop()
{
	UpdateData(TRUE);
	IR.Acquisition = m_Acquisition;
}

void CTennisBallDlg::OnBnClickedCapture()
{
	UpdateData(TRUE);
	IR.Acquisition = m_Acquisition = TRUE;
	UpdateData(FALSE);

	IR.PlayDelay = m_PlayDelay;
	IR.FrameID = 0;
	IR.CaptureSequence = TRUE;
}

void CTennisBallDlg::OnBnClickedCatchreset()
{
#ifdef USE_STAGE
	if(IR.Hoop->device.IsConnected()) {
		if (!IR.Hoop->Home()) AfxMessageBox("Homing failed.  Try again!");
	}
#endif
}

void CTennisBallDlg::OnBnClickedCatchermove()
{
#ifdef USE_STAGE
	// Functions to move the catcher
	UpdateData(TRUE);
	if(IR.Hoop->device.IsConnected()) {
		if (!IR.Hoop->Move(m_CatchX, m_CatchY)) AfxMessageBox("Move failed.  Try again!");
	}
#endif
}

void CTennisBallDlg::OnBnClickedCenter()
{
#ifdef USE_STAGE
	// Functions to move the catcher
	UpdateData(TRUE);
	if(IR.Hoop->device.IsConnected()) {
		if (!IR.Hoop->Move(0.0, 0.0)) AfxMessageBox("Center failed.  Try again!");
	}
#endif
}

void CTennisBallDlg::OnBnClickedCatch()
{
//	UpdateData(TRUE);
//	IR.Acquisition = m_Acquisition = TRUE;
//	UpdateData(FALSE);
//	IR.CatchBall = ~IR.CatchBall;

	float scalex = 22/23.5;
	float transx = -11.25;

	float scaley = -10/15.75;
	float transy = 13.7;


	float newx = 0;
	float newy = 0;

	int clearedthresh = 100;

	UpdateData(TRUE);
	IR.Acquisition = m_Acquisition = TRUE;
	UpdateData(FALSE);
	
	setupParams();

	bool clearvals = true;

	bool foundfirstball = false;
	int ballnum = 0;
	ofstream fout("trajectory.txt");

	int ballcleared = 0;

	//namedWindow("Left",WINDOW_AUTOSIZE);
	//namedWindow("Right",WINDOW_AUTOSIZE);

	Point3f prevpoint = Point3f(0,0,0);

	t = NULL;

	UpdateData(TRUE);
	if(IR.Hoop->device.IsConnected()) 
	{
		if (!IR.Hoop->Move(0.0, 0.0)) AfxMessageBox("Center failed.  Try again!");
	}


	
	while(1)
	{
		Point3f coordinate = findCoordinate(IR.AcqBuf[0], IR.AcqBuf[1]);

		imshow("Left",IR.AcqBuf[0]);
		imshow("Right",IR.AcqBuf[1]);

		if (prevpoint == coordinate)
		{

			if (ballnum == 0)
			{
				ballcleared++;
			}
			else
				ballcleared = 0;

			if (ballcleared >= clearedthresh)
			{
				movecatcher(0,0);
				ballcleared = 0;
			}

			sleepms(1);

			if (waitKey(1) == 'q')
			{
				IR.CatchBall = ~IR.CatchBall;
				break;
			}
			continue;
		}
		else
			prevpoint = coordinate;


		if (coordinate != Point3f(0,0,0))
		{
			ballnum++;
			Point2f estimatedpos = catchPosition(coordinate, clearvals);
			clearvals = false;
			
			newx = estimatedpos.x;
			newy = estimatedpos.y;


			double xcoeffs[6] = {-0.003329,  -0.001922,0.954977, 0.045192, -0.000419, -10.531141};
			double ycoeffs[6] = {-0.000199, 0.006984, -0.114204, -0.958848, 0.002248, 13.105832};

			double xmotor = xcoeffs[0] * newx * newx + xcoeffs[1] * newy * newy + xcoeffs[2] * newx + xcoeffs[3] * newy + xcoeffs[4] * newx * newy + xcoeffs[5];
			double ymotor = ycoeffs[0] * newx * newx + ycoeffs[1] * newy * newy + ycoeffs[2] * newx + ycoeffs[3] * newy + ycoeffs[4] * newx * newy + ycoeffs[5];
			/*
			double xcoeffs[3] = {0.883565, 0.003565, -10.105395};
			double ycoeffs[3] = {-0.086635, -0.793270,  12.201830};
			double xmotor = xcoeffs[0] * newx + xcoeffs[1] * newy + xcoeffs[2];
			double ymotor = ycoeffs[0] * newx + ycoeffs[1] * newy + ycoeffs[2];
			*/

			newx = ((transx + estimatedpos.x) * scalex);

			newy = -0.089959 * newx - 0.822482 * estimatedpos.y + 11.5969;

			/*
			if (newx < 4 * scalex)
				scaley = 4/11.75;
			else if (newx < 12 * scalex)
				scaley = 11.2/23.5;
			else
				scaley = 6.8/11.75;*/

			int intx = (int)xmotor;
			int inty = (int)ymotor;
			double diffx = xmotor - intx;
			double diffy = ymotor - inty;
			
			fout << estimatedpos << " [" << newx << ", " << newy <<  "] "   << " [" << xmotor << ", " << ymotor <<  "] " << ballnum << endl;


			if (diffx > 0.5)
				xmotor += (1-diffx+0.01);
			if (diffy > 0.5)
				ymotor += (1-diffy+0.01);

			if (diffx < -0.5)
				xmotor -= (1 + diffx + 0.01);
			if (diffy < -0.5)
				ymotor -= (1 + diffy + 0.01);


			fout << estimatedpos << " [" << newx << ", " << newy <<  "] " << " [" << xmotor << ", " << ymotor <<  "] " << ballnum << endl;


			if (ballnum == 2 || ballnum == 9 || ballnum == 15)
			{
				if (ballnum == 2)
					ymotor = 0;

				coord n;
				n.x = xmotor;
				n.y = ymotor;
				n.IR = &IR;

				if (t != NULL)
				{
					DWORD exitcode;
					GetExitCodeThread(t,&exitcode);
					if (exitcode != STILL_ACTIVE)
						t = AfxBeginThread(catcherthread, (LPVOID)&n);
				}
				else
				{
					t = AfxBeginThread(catcherthread, (LPVOID)&n);
				}
			}
		}
		else
		{
			ballnum = 0;
			clearvals = true;
		}

		//sleepms(1);

		if (waitKey(1) == 'q')
		{
			IR.CatchBall = ~IR.CatchBall;
			break;
		}
	}

	/*
	int posX, posY;
	if(IR.Hoop->device.IsConnected()) {
		if (!IR.Hoop->GetPos(posX, posY)) 
			AfxMessageBox("Reading positions failed.  Try again!");
		else {
			CString Msg;
			Msg.Format("%d %d", posX, posY);
			AfxMessageBox(Msg);
		}
	}*/

}

void CTennisBallDlg::movecatcher(float x, float y)
{
	if (x > 9)
		x = 9;
	else if (x < -9)
		x = -9;

	if (y > 8)
		y = 8;
	else if (y < -8)
		y = -8;

	IR.Hoop->Move(x, y);
}

UINT catcherthread(LPVOID param)
{
	coord* coordvals = (coord*) param;
	float x = coordvals->x;
	float y = coordvals->y;
	ImagingResources* IR = coordvals->IR;

	if (x > 9)
		x = 9;
	else if (x < -9)
		x = -9;

	if (y > 8)
		y = 8;
	else if (y < -8)
		y = -8;
	
	if (IR->Hoop->device.IsConnected())
		IR->Hoop->Move(x, y);

	return 0;
}
