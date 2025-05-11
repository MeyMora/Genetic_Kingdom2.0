	#pragma once
#ifndef TORREFABRICA_H	
#define TORREFABRICA_H
#include "Torre.h"	
#include "TipoTorre.h" // Incluir el archivo de definición del enum TipoTorre
#include "TorreConSprite.h"

#include <memory>

#include <filesystem>

// Alias para el espacio de nombres de filesystem
namespace fs = std::filesystem;
// Variable global para la ruta base (si no está definida en otro lado)
extern std::string ruta;
std::unique_ptr<Torre> crearTorre(TipoTorre tipo, sf::Vector2i posicion) {
    std::string rutaSprite;
    switch (tipo) {
    case TipoTorre::Arquera:
        rutaSprite = ruta+ "/Torre_1.png";

        return std::make_unique<TorreConSprite>(rutaSprite, posicion.y, posicion.x, 1.5f, 10, tipo);

    case TipoTorre::Mago:
        rutaSprite = ruta + "/Torre_2.png";
        return std::make_unique<TorreConSprite>(rutaSprite, posicion.y, posicion.x, 2.0f, 20, tipo);

    case TipoTorre::Artillero:
        rutaSprite = ruta + "/Torre_3.png";
        return std::make_unique<TorreConSprite>(rutaSprite, posicion.y, posicion.x, 3.0f, 30, tipo);

    default:
        return nullptr;
    }
}


#endif // !TORREFABRICA_H