﻿#include "Torre.h"
#include <cmath>
#include <iostream>

Torre::Torre(int dano_, float velocidad_, int alcance_,
	float recargaEspecial, float recargaNormal, sf::Vector2i pos, int costo_)
	: dano(dano_), velocidad(velocidad_), alcance(alcance_),
	tiempoRecargaEspecial(recargaEspecial), tiempoRecarga(recargaNormal), posicion(pos),
	nivel(0), costo(costo_), probabilidadEspecial(0.1f) {} //10% de probabilidad de ataque especial

int Torre::getNivel() const {
	return nivel; // Obtener el nivel de la torre
}
int Torre::getCostoUpgrade() const {
	return costo; // Obtener el costo de la torre
}
float Torre::getProbabilidadEspecial() const {
	return probabilidadEspecial; // Obtener la probabilidad de tener ataque especial
}

int Torre::getDano() const {
	return dano; // Obtener el daño de la torre
}
float Torre::getVelocidad() const {
	return velocidad; // Obtener la velocidad de ataque de la torre
}

int Torre::getAlcance() const {
	return alcance; // Obtener el alcance de la torre
}

sf::Vector2i Torre::getPosicion() const {
	return posicion; // Obtener la posición de la torre en el mapa
}


bool Torre::estaEnRango(sf::Vector2i enemigoPos) const {
	int dx = enemigoPos.x - posicion.x; // Diferencia en X
	int dy = enemigoPos.y - posicion.y; // Diferencia en Y
	return dx * dx + dy * dy <= alcance * alcance; // Comparación con distancia²
}

bool Torre::upgrade(int oroJugador, int& oroRestante) {
    if (nivel >= 3) {
        std::cout << " Torre ya está al máximo nivel.\n";
        return false; // No se puede mejorar más allá del nivel 3
    }

    int costoUpgrade = getCostoUpgrade();
    if (oroJugador < costoUpgrade) {
        std::cout << " No hay suficiente oro para mejorar. Costo: " << costoUpgrade << ", Oro: " << oroJugador << "\n";
        return false; // No hay suficiente oro
    }

    // Descontar el oro antes de mejorar
    oroRestante -= costoUpgrade;

    // Incrementar el nivel
    nivel++;

    // Ajustar estadísticas según el nuevo nivel
    switch (nivel) {
    case 1:
        dano += 5;
        alcance += 1;
        costo += 10;
        break;
    case 2:
        dano += 10;
        alcance += 2;
        costo += 20;
        break;
    case 3:
        dano += 15;
        alcance += 3;
        costo += 30;
        break;
    default:
        break;
    }

    // Aumentar la probabilidad de ataque especial
    probabilidadEspecial += 0.05f;

    std::cout << "✅ Torre mejorada a nivel " << nivel << ". Oro restante: " << oroRestante << "\n";

    return true;
}