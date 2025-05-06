#include "TorreConSprite.h"
#include <iostream>

const int CELL_SIZE = 80;
sf::CircleShape rangoVisual;



TorreConSprite::TorreConSprite(const std::string& rutaSprite, int fila_, int columna_, float rango, int danio_)
    : Torre(danio_, 1.0f, static_cast<int>(rango), 5.0f, 2.0f, sf::Vector2i(columna_, fila_), 50),
    fila(fila_), columna(columna_), rangoAtaque(rango), danio(danio_)
{
    if (!textura.loadFromFile(rutaSprite)) {
        std::cerr << "Error cargando textura desde: " << rutaSprite << std::endl;
    }
    sprite.setTexture(textura);
    sprite.setScale(0.22f, 0.22f);
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
