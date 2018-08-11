#pragma once
#include <list>
#include <random>
#include <chrono>

class Pelota {

public:// Estos miembros son para saber donde esta la pelota 
	int m_PosicionEnY = 0;
	int m_PosicionEnX = 0;
public:// Estos miembros son para controlar la velocidad de nuetra pelota con ayuda de una lista ( la lista es para tener aun mas control sobre la velocidad de la bola )
	int m_VelocidadEnY = 0;
	int m_VelocidadEnX = 0;
public: // Estos miembros esta aqui para que determinar el Tamanuo de nuestra pelota . 
	int m_DimencionX = 0;
	int m_DimencionY = 0;
public:
	Pelota();//<- Consturctor por defecto
	Pelota(int PosX, int PosY); //<- Constructor que crear una posicion para la pelota .
	~Pelota();//<-  Destructor por defecto
public:
	int SeleccionarVelocidad(int &Velocidad);// cambia la velocidad de la pelota pelota
	


private:
	// esta lista determinara la velocidades que lo pelota puede ir 
	std::list<int> m_ListaDeVelocidades = { 3,4,5,6,7,8 };
	std::list<int>::iterator m_it;

};
