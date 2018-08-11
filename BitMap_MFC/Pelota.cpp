#include "stdafx.h"
#include "Pelota.h"

// contructor por defecto 
Pelota::Pelota() {}
// contructor sobrecargado 
Pelota::Pelota(int PosX, int PosY) 
{
	m_PosicionEnX = PosX;
	m_PosicionEnY = PosY;
}

//destructor por defecto .
Pelota::~Pelota() {}


// este metodo
int Pelota::SeleccionarVelocidad(int &Velocidad) {
	
	srand(time(0) - Velocidad);

	m_it = m_ListaDeVelocidades.begin();

	if (Velocidad < 0) {
		std::advance(m_it, rand() % (m_ListaDeVelocidades.size() - 1));
		Velocidad = *m_it;
		Velocidad = Velocidad * -1;
	}
	else {
		std::advance(m_it, rand() % (m_ListaDeVelocidades.size() - 1));
		Velocidad = *m_it;
	}

	return Velocidad;
}