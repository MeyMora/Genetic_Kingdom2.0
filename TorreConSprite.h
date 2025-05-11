#pragma once
// TorreConSprite.h
#include <SFML/Graphics.hpp>
#include "Torre.h"
#include "TipoTorre.h"  // Aseg�rate de incluirlo

#include <string>


class TorreConSprite: public Torre {
private:
    sf::Texture textura;
    sf::Sprite sprite;
    TipoTorre tipo;
    int fila, columna;
    float rangoAtaque;
    int danio;


public:
    TorreConSprite(const std::string& rutaSprite, int fila, int columna, float rango, int danio, TipoTorre tipo);
    void dibujar(sf::RenderWindow& window);
    sf::Vector2f getPosicion() const;
    void setPosicion(float x, float y);
    // Agreg� m�s funciones si quer�s manejar ataques, animaciones, etc.
    void mejorarSprite();
    void actualizarSprite(int nivel);
};
#pragma once