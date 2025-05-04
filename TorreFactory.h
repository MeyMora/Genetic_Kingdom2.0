	#pragma once
#ifndef TORREFABRICA_H	
#define TORREFABRICA_H
#include "Torre.h"	
#include "TipoTorre.h" // Incluir el archivo de definición del enum TipoTorre

#include <memory>

std::unique_ptr<Torre> crearTorre(TipoTorre tipo, sf::Vector2i posicion) {
	switch (tipo) {
	case TipoTorre::Arquera:
		return std::make_unique<Torre>(10, 1.0f, 3, 5.0f, 2.0f, posicion, 50);
	case TipoTorre::Mago:
		return std::make_unique<Torre>(15, 0.8f, 4, 6.0f, 1.5f, posicion, 60);
	case TipoTorre::Artillero:
		return std::make_unique<Torre>(20, 0.5f, 5, 7.0f, 1.0f, posicion, 70);
	default:
		return nullptr; // Tipo de torre no válido
	}
}

#endif // !TORREFABRICA_H