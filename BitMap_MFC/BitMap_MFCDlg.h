
// BitMap_MFCDlg.h : header file
//

#pragma once


// CBitMapMFCDlg dialog
class CBitMapMFCDlg : public CDialog
{
// Construction
public:
	CBitMapMFCDlg(CWnd* pParent = nullptr);	// standard constructor
	void PaintBall();
	void MoverPelota(int &velocidad, int &velocidadEnX,LONG MaxEnEjeY,LONG MaxEnEjeX);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BITMAP_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
