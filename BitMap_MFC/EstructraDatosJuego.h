#pragma once

#include "stdafx.h"
#include "afxdialogex.h"

// todo lo que va hacer este es almacenar datos dentro de si mismo para no tener que  
//Pasar por referencia todos los datos todo el timepo .
struct SDatosJuego {

	CBitmap *m_ptrBitMap;
	CBitmap m_BitMap;
public:
	CDC *m_pDC;
	CDC *m_bmDC;
public:
	RECT m_miRect;


};