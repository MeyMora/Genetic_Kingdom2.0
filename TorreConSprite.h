#pragma once
// TorreConSprite.h

#include <SFML/Graphics.hpp>
#include <string>
#include"Torre.h"

class TorreConSprite: public Torre {
private:
    sf::Texture textura;
    sf::Sprite sprite;
    int fila, columna;
    float rangoAtaque;
    int danio;

public:
    TorreConSprite(const std::string& rutaSprite, int fila, int columna, float rango, int danio);
    void dibujar(sf::RenderWindow& window);
    sf::Vector2f getPosicion() const;
    void setPosicion(float x, float y);
    // Agregá más funciones si querés manejar ataques, animaciones, etc.
};
#pragma once