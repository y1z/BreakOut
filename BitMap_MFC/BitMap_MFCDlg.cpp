
// BitMap_MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BitMap_MFC.h"
#include "BitMap_MFCDlg.h"
#include "afxdialogex.h"
#include "Pelota.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBitMapMFCDlg dialog


// aqui Ponder los Structs  
Pelota pelota;
int m_y = 0;
int m_x = 0;

CBitMapMFCDlg::CBitMapMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BITMAP_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBitMapMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBitMapMFCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBitMapMFCDlg::OnBnClickedOk)
END_MESSAGE_MAP()



// CBitMapMFCDlg message handlers

BOOL CBitMapMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBitMapMFCDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBitMapMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBitMapMFCDlg::PaintBall() {

	RECT miRect;
	//LPRECT ptrRect;
	GetClientRect(&miRect);
	//CDialog::OnOK();
	HANDLE HBitMap = LoadImage(0, TEXT("Circulo.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);// Esto es par cargar la imagen 
	HANDLE BlacoBitMap = LoadImage(0, TEXT("BitMapBlanco.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);// Esto es para que lo pelota 

	CBitmap bmp;
	CBitmap BlacoMap;

	bmp.Attach(reinterpret_cast<HBITMAP>(HBitMap));
	BlacoMap.Attach(reinterpret_cast<HBITMAP>(BlacoBitMap));

	CDC * pDC = this->GetDC();
	//CDC * ptrBlancoDC = this->GetDC();
	CDC bmDC;
	CDC BlancoDC;//

	bmDC.CreateCompatibleDC(pDC);
	bmDC.SelectObject(&bmDC);

	BlancoDC.CreateCompatibleDC(pDC);
	BlancoDC.SelectObject(&BlacoMap);
	

	CBitmap * oldBMP = bmDC.SelectObject(&bmp);

	pDC->BitBlt(pelota.PosicionEnX, pelota.PosicionEnY, 64, 64, &bmDC, 0, 0, SRCCOPY);// SRCCOPY crea una copia de la imagen || SRCINVERT Es para invertir los colores de lo imagen 
	
	pelota.VelocidadEnX = 5;
	pelota.VelocidadEnY = 1;

	while(true){
		Sleep(16);
		MoverPelota(pelota.VelocidadEnY, pelota.VelocidadEnX, miRect.bottom, miRect.right);
		pDC->BitBlt(pelota.PosicionEnX - pelota.VelocidadEnX, pelota.PosicionEnY - pelota.VelocidadEnY, 64, 64, &BlancoDC, 0, 0, SRCCOPY);// el Espacio en blanco 
		pDC->BitBlt(pelota.PosicionEnX, pelota.PosicionEnY, 64, 64, &bmDC, 0, 0, SRCCOPY ); // la pelota 
	
	}
	 
}

void CBitMapMFCDlg::MoverPelota(int &VelocidadEnY, int &VelocidadEnX, LONG MaxEnEjeY, LONG MaxEnEjeX) {
	if (pelota.PosicionEnY >= MaxEnEjeY ) {
		pelota.PosicionEnY = MaxEnEjeY;
		VelocidadEnY = VelocidadEnY * -1;

	}
	else if (pelota.PosicionEnY < 0) {
		pelota.PosicionEnY = 0;
		VelocidadEnY = VelocidadEnY * -1;
	}

	if (pelota.PosicionEnX >= MaxEnEjeX) {
		pelota.PosicionEnX = MaxEnEjeX;
		VelocidadEnX = VelocidadEnX * -1;
	}
	else if (pelota.PosicionEnX < 0) {
		VelocidadEnX = VelocidadEnX * -1;
	}

	pelota.PosicionEnX += VelocidadEnX;
	pelota.PosicionEnY += VelocidadEnY;
}

void CBitMapMFCDlg::OnBnClickedOk()
{
	PaintBall();
}
