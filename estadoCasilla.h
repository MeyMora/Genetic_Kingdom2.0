#ifndef ESTADOCASILLA_H
#define ESTADOCASILLA_H
#include <iostream>
// Enum para representar el estado de una casilla
enum class estadoCasilla {
    Empty,      // Casilla libre
    Torre,      // Casilla ocupada por una torre
    Entrada,    // Punto de entrada de enemigos
    Meta        // Puente (Es la meta final)
};

#endif // ESTADOCASILLA_H