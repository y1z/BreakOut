
// BitMap_MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BitMap_MFC.h"
#include "BitMap_MFCDlg.h"
#include "afxdialogex.h"
#include "Pelota.h"// el header donde esta la programacion de mi pelota .
#include "EstructraDatosJuego.h"// es un struc que usare para 
#include <thread>
#include <chrono>
#include <random>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBitMapMFCDlg dialog


// aqui esta la inicializacion de mi objeto 'pelota' .
// los dos valores son la posicion que le di a la pelota . 
Pelota pelota(200,300);
//
SDatosJuego datosjuego;

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
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBitMapMFCDlg::OnBnClickedOk)
	ON_WM_TIMER()

	ON_WM_MOUSEMOVE()
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
	GetClientRect(&miRect);
	//CDialog::OnOK();
	HANDLE HBitMap = LoadImage(0, TEXT("Circulo.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);// Esto es par cargar la imagen 
	HANDLE BlacoBitMap = LoadImage(0, TEXT("BarraJugador.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);// Esto es para que lo pelota 


	CBitmap bmp;
	CBitmap BlacoMap;

	BITMAP DimencionesDePelota;// uso esta variable para sacar las Demenciones  del bitmap y ponerlas en mi estructura pelota ( la razon de porque es un struct es porque cuando intente
							// crear un clase recibi muchos errores que no entendian pero cuando cambie esa clase a struct me dejo de salir esos errores ) 

	

	bmp.Attach(reinterpret_cast<HBITMAP>(HBitMap));
	BlacoMap.Attach(reinterpret_cast<HBITMAP>(BlacoBitMap));

	datosjuego.m_BitMap.Attach(reinterpret_cast<HBITMAP>(HBitMap));

	::GetObject(HBitMap, sizeof(DimencionesDePelota), &DimencionesDePelota);
	pelota.m_DimencionX = DimencionesDePelota.bmWidth;
	pelota.m_DimencionY = DimencionesDePelota.bmHeight;

	CDC * pDC = this->GetDC();
	CDC bmDC;
	CDC BlancoDC;

	bmDC.CreateCompatibleDC(pDC);
	bmDC.SelectObject(&bmp);

	BlancoDC.CreateCompatibleDC(pDC);
	BlancoDC.SelectObject(&BlacoMap);
	
	CBitmap * oldBMP = bmDC.SelectObject(&bmp);

	pDC->BitBlt(pelota.m_PosicionEnX, pelota.m_PosicionEnY, pelota.m_DimencionX, pelota.m_DimencionY, &bmDC, 0, 0, SRCCOPY);// SRCCOPY crea una copia de la imagen || SRCINVERT Es para invertir los colores de lo imagen 
	
	pelota.m_VelocidadEnX = 5;// ahy un metodo que cambia estos valores cada vez que la pelota tinen una colision . 
	pelota.m_VelocidadEnY = 1;

	//aqui asigno todo los dato que el juego necesita para funcionar 
	// para no tener que pasarlos por mil parametros ( para que sea mas combiniente para mi ) .
	datosjuego.m_miRect = miRect;
	
	datosjuego.m_pDC = pDC;
	datosjuego.m_bmDC = &bmDC;
	

	SetTimer(1, 16, NULL);
	OnTimer(1);
	

}

void CBitMapMFCDlg::PintarVentana(CDC * pDC, CDC &BitMap, RECT &miRect) {
	//CDC * pDC = this->GetDC();

	for (int i = 0; i < miRect.bottom; i += 64)
	{
		for (int j = 0; j < miRect.right; j += 64)
		{
			pDC->BitBlt(j, i, 64, 64, &BitMap, 0, 0, WHITENESS);
		}
	}

}
// Original 
void CBitMapMFCDlg::ComenzarJuego(RECT &ventana, CDC *pDC,CDC &BitMapBola) {
	srand(time(0));

	//PintarVentana(pDC, BitMapBola, ventana);// todo lo que hace es pintar una ventana de color blanco Untilizando un bitmap . 

	//while (true) {
		//SleepEx(16, false);
		MoverPelota(pelota.m_VelocidadEnY, pelota.m_VelocidadEnX, ventana.bottom, ventana.right);
		pDC->BitBlt(pelota.m_PosicionEnX - pelota.m_VelocidadEnX, pelota.m_PosicionEnY - pelota.m_VelocidadEnY, 64, 64, &BitMapBola, 0, 0, WHITENESS);// el Espacio en blanco 
		pDC->BitBlt(pelota.m_PosicionEnX, pelota.m_PosicionEnY, 64, 64, &BitMapBola, 0, 0, SRCCOPY); // la pelota 

	//}
}

void CBitMapMFCDlg::ComenzarJuego(SDatosJuego &datos) {
	
	MoverPelota(pelota.m_VelocidadEnY, pelota.m_VelocidadEnX, datos.m_miRect.bottom, datos.m_miRect.right);
	datos.m_pDC->BitBlt(pelota.m_PosicionEnX - pelota.m_VelocidadEnX, pelota.m_PosicionEnY - pelota.m_VelocidadEnY, 64, 64, &(*datosjuego.m_bmDC), 0, 0, WHITENESS);
	datos.m_pDC->BitBlt(pelota.m_PosicionEnX, pelota.m_PosicionEnY, 64, 64, &(*datosjuego.m_bmDC), 0, 0, SRCCOPY);

}

//esta Funcion Cambia la velocidad de la pelota para que el juego no sea aburrido 
void CBitMapMFCDlg::MoverPelota(int &VelocidadEnY, int &VelocidadEnX, LONG MaxEnEjeY, LONG MaxEnEjeX) {
	if (pelota.m_PosicionEnY + pelota.m_DimencionY >= MaxEnEjeY) {
		pelota.m_PosicionEnY = MaxEnEjeY - pelota.m_DimencionY;

		VelocidadEnY = VelocidadEnY * -1;
		pelota.SeleccionarVelocidad(pelota.m_VelocidadEnY);
	}
	else if (pelota.m_PosicionEnY < 0) {
		pelota.m_PosicionEnY = 0;

		VelocidadEnY = VelocidadEnY * -1;
		pelota.SeleccionarVelocidad(pelota.m_VelocidadEnY);

	}

	if (pelota.m_PosicionEnX + pelota.m_DimencionX >= MaxEnEjeX) {
		pelota.m_PosicionEnX = MaxEnEjeX - pelota.m_DimencionX;
		pelota.SeleccionarVelocidad(pelota.m_VelocidadEnX);
		VelocidadEnX = VelocidadEnX * -1;
	}
	else if (pelota.m_PosicionEnX < 0) {
		VelocidadEnX = VelocidadEnX * -1;
		pelota.SeleccionarVelocidad(pelota.m_VelocidadEnX);
	}

	pelota.m_PosicionEnX += VelocidadEnX;
	pelota.m_PosicionEnY += VelocidadEnY;
}

// En otras palabras la pelota se movia de forma demasiado uniforme 
void CBitMapMFCDlg::CambiarVelocidadPelota(int &velocidadEnY, int &velocidadEnX)
{

	if (velocidadEnX < 0) 
	{ 	

		velocidadEnX = (-rand() - 5) % 10; 
		if (velocidadEnX == 0) 
		{
			velocidadEnX -= 3; 
		}

	}
	else {
		velocidadEnX = (rand() + 5) % 10;
		if (velocidadEnX == 0)
		{
			velocidadEnX += 3;
		}
	}

	if (velocidadEnY < 0) 
	{
		velocidadEnY = (-rand() - 5) % 10; 
		if (velocidadEnY == 0 || velocidadEnY == -1)
		{
			velocidadEnY -= 3;
		}
	
	}
	else {
		
		velocidadEnY = (rand() + 5) % 10;
		if (velocidadEnY == 0) 
		{
			velocidadEnY += 3;
		}
	}
}


// la programacion del boton 
// que comienza el juego .
void CBitMapMFCDlg::OnBnClickedOk()
{
	//SetTimer(1, 16, NULL);// esto dictara la velocidad del juego . 
	PaintBall();
}

// El evento on timer 
void CBitMapMFCDlg::OnTimer(UINT_PTR nIDEvent){
	ComenzarJuego(datosjuego);
}

void CBitMapMFCDlg::OnTimer(UINT_PTR nIDEvent, RECT &ventana, CDC *pDC, CDC &bmDC) 
{
	ComenzarJuego(ventana, pDC, bmDC);

}

void CBitMapMFCDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default


	CDialog::OnMouseMove(nFlags, point);
}
