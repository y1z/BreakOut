#pragma once

#include "stdafx.h"

// todo lo que va hacer este es almacenar datos dentro de si mismo para no tener que  
//Pasar por referencia todos los datos todo el timepo .
struct SDatosJuego {
	CDC *m_pDC = nullptr;
	CDC m_bmPC;
	
	RECT m_miRect;



};