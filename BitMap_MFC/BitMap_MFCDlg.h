
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
	void MoverPelota(int &VelocidadEnY, int &VelocidadEnX, LONG MaxEnEjeY, LONG MaxEnEjeX);
	void ComenzarJuego(RECT &ventana, CDC *pDC, CDC &BitMapBola);
	void PintarVentana(CDC * pDC, CDC &BitMap, RECT &miRect);
	void CambiarVelocidadPelota(int &velocidadEnY, int &velocidadEnX);
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
