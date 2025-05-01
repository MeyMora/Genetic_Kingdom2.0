#ifndef CASILLA_H
#define CASILLA_H

#include "estadoCasilla.h" // Incluir el archivo de definición del enum estadoCasilla

class Casilla {	 // Clase que representa una casilla en el tablero
public:
	int x, y;	// Coordenadas de la casilla
	estadoCasilla estado;  // Estado de la casilla

    Casilla(int x_, int y_, estadoCasilla estadoInicial = estadoCasilla::Empty); //Verificar si la casillla esta vacia

	bool isBlocked() const; // Verificar si la casilla esta ocupada por una torre

	void setEstado(estadoCasilla nuevoEstado); // Establecer el nuevo estado de la casilla
	estadoCasilla getEstado() const; // Obtener el estado de la casilla
};

#endif // CASILLA_H

