	#pragma once
#ifndef TORREFABRICA_H	
#define TORREFABRICA_H
#include "Torre.h"	
#include "TipoTorre.h" // Incluir el archivo de definición del enum TipoTorre
#include "TorreConSprite.h"

#include <memory>



std::unique_ptr<Torre> crearTorre(TipoTorre tipo, sf::Vector2i posicion) {
    std::string rutaSprite;
    switch (tipo) {
    case TipoTorre::Arquera:
		rutaSprite = "Imagenes/torres/Torre_1.png";

        return std::make_unique<TorreConSprite>(rutaSprite, posicion.y, posicion.x, 1.5f, 10);

    case TipoTorre::Mago:
        rutaSprite = "Imagenes/torres/Torre_2.png";
        return std::make_unique<TorreConSprite>(rutaSprite, posicion.y, posicion.x, 2.0f, 20);

    case TipoTorre::Artillero:
        rutaSprite = "Imagenes/torres/Torre_3.png";
        return std::make_unique<TorreConSprite>(rutaSprite, posicion.y, posicion.x, 3.0f, 30);

    default:
        return nullptr;
    }
}


#endif // !TORREFABRICA_H