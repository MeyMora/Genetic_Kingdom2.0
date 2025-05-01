#include "Casilla.h"

// Implementación del constructor
Casilla::Casilla(int x_, int y_, estadoCasilla estadoInicial)  // Constructor que inicializa las coordenadas y el estado de la casilla
	: x(x_), y(y_), estado(estadoInicial) {     // Inicializa las coordenadas y el estado de la casilla
}

// Implementación del método isBlocked
bool Casilla::isBlocked() const {   // Verifica si la casilla está ocupada por una torre
	return estado == estadoCasilla::Torre; // Verifica si el estado de la casilla es Torre
}
// Implementación del método setEstado
// Establece el nuevo estado de la casilla
void Casilla::setEstado(estadoCasilla nuevoEstado) {
	estado = nuevoEstado;
}
// Implementación del método getEstado
estadoCasilla Casilla::getEstado() const {
	return estado;
}