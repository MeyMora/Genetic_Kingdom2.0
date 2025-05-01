#include "Casilla.h"

// Implementaci�n del constructor
Casilla::Casilla(int x_, int y_, estadoCasilla estadoInicial)  // Constructor que inicializa las coordenadas y el estado de la casilla
	: x(x_), y(y_), estado(estadoInicial) {     // Inicializa las coordenadas y el estado de la casilla
}

// Implementaci�n del m�todo isBlocked
bool Casilla::isBlocked() const {   // Verifica si la casilla est� ocupada por una torre
	return estado == estadoCasilla::Torre; // Verifica si el estado de la casilla es Torre
}
// Implementaci�n del m�todo setEstado
// Establece el nuevo estado de la casilla
void Casilla::setEstado(estadoCasilla nuevoEstado) {
	estado = nuevoEstado;
}
// Implementaci�n del m�todo getEstado
estadoCasilla Casilla::getEstado() const {
	return estado;
}