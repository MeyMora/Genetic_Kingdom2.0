#include "TorreConSprite.h"
#include <iostream>
#include "TipoTorre.h"

const int CELL_SIZE = 80;
sf::CircleShape rangoVisual;

// Variable global para la ruta base (si no está definida en otro lado)
extern std::string ruta;

TorreConSprite::TorreConSprite(const std::string& rutaSprite, int fila_, int columna_, float rango, int danio_, TipoTorre tipo_)
    : Torre(danio_, 1.0f, static_cast<int>(rango), 5.0f, 2.0f, sf::Vector2i(columna_, fila_), 50),
    fila(fila_), columna(columna_), rangoAtaque(rango), danio(danio_), tipo(tipo_)
{
    if (!textura.loadFromFile(rutaSprite)) {
        std::cerr << "Error cargando textura desde: " << rutaSprite << std::endl;
    }
    sprite.setTexture(textura);
    sprite.setScale(0.17f, 0.17f);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height * 0.6f);
    sprite.setPosition((columna + 0.5f) * CELL_SIZE, (fila + 0.5f) * CELL_SIZE);

    rangoVisual.setRadius(rangoAtaque * CELL_SIZE);
    rangoVisual.setFillColor(sf::Color(0, 255, 255, 64)); // cian semitransparente
    rangoVisual.setOrigin(rangoVisual.getRadius(), rangoVisual.getRadius());
    rangoVisual.setPosition(sprite.getPosition());
}


void TorreConSprite::dibujar(sf::RenderWindow& window) {
    Torre::dibujar(window); // Dibuja el área de alcance y base cuadrada si querés
    window.draw(sprite);    // Dibuja el sprite encima
}

sf::Vector2f TorreConSprite::getPosicion() const {
    return sprite.getPosition();
}

void TorreConSprite::setPosicion(float x, float y) {
    sprite.setPosition(x, y);
}

void TorreConSprite::mejorarSprite() {
    // Obtener el nombre del tipo de torre
    std::string tipoTorre;
    switch (tipo) {
    case TipoTorre::Arquera:
        tipoTorre = "Arquera";
        break;
    case TipoTorre::Mago:
        tipoTorre = "Mago";
        break;
    case TipoTorre::Artillero:
        tipoTorre = "Artillero";
        break;
    default:
        tipoTorre = "Desconocido";
        break;
    }

    // Construir la ruta de la imagen basada en el tipo y el nivel
    std::string rutaMejorada = ruta + "Torre_" + tipoTorre + "_" + std::to_string(nivel) + ".png";

    if (!textura.loadFromFile(rutaMejorada)) {
        std::cerr << " Error cargando el sprite de mejora: " << rutaMejorada << std::endl;
    }
    else {
        sprite.setTexture(textura);

        // Ajuste de tamaño: Escala más pequeña para que encaje en la celda
        float escalaX = CELL_SIZE / sprite.getLocalBounds().width * 0.8f;
        float escalaY = CELL_SIZE / sprite.getLocalBounds().height * 0.8f;
        sprite.setScale(escalaX, escalaY);

        // Ajuste del origen: Centrar en la celda
        sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);

        // Colocar el sprite en el centro de la celda
        sprite.setPosition((columna + 0.5f) * CELL_SIZE, (fila + 0.5f) * CELL_SIZE);

        std::cout << " Sprite mejorado a nivel " << nivel << ": " << rutaMejorada << std::endl;
    }
}


void TorreConSprite::actualizarSprite(int nivel) {
    std::string rutaSprite = (nivel == 0) ? "torres/Torre_1.png" : "torres/Torre_1_mejorada.png";
    if (!textura.loadFromFile(rutaSprite)) {
        std::cerr << "Error cargando textura mejorada desde: " << rutaSprite << std::endl;
    }
    sprite.setTexture(textura);
}