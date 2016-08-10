// TennisBallDlg.h : header file
//

#pragma once
#include "Hardware.h"

// CTennisBallDlg dialog
class CTennisBallDlg : public CDialog, public CTCSys
{
// Construction
public:
	CTennisBallDlg(CWnd* pParent = NULL);	// standard constructor
	CBitmapButton		m_Exit;
// Dialog Data
	enum { IDD = IDD_TENNISBALL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
	void movecatcher(float x, float y);
	CWinThread* t;


public:
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedLoadimg();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedUpdateimg();
	BOOL m_UpdateImage;
	afx_msg void OnBnClickedSaveimg();
	afx_msg void OnBnClickedShowseq();
	afx_msg void OnBnClickedCatch();
	afx_msg void OnBnClickedCatchreset();
	afx_msg void OnBnClickedCatchermove();
	afx_msg void OnBnClickedGrab();
	afx_msg void OnBnClickedStop();
	BOOL m_Acquisition;
	int m_PlayDelay;
	afx_msg void OnBnClickedCapture();
	double m_CatchX;
	double m_CatchY;
	afx_msg void OnBnClickedCenter();
};


struct coord
{
	float x;
	float y;
	ImagingResources* IR;

};

UINT catcherthread( LPVOID param);
