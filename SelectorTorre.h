#pragma once
#include <SFML/Graphics.hpp>
#include "TipoTorre.h"

class SelectorTorre {
private:
    sf::RectangleShape botonArquera, botonMago, botonArtillero;
    sf::Text textoArquera, textoMago, textoArtillero;
    bool visible = false;
    sf::Vector2f posicion;
    sf::Font& fuente;

public:
    SelectorTorre(sf::Font& font);

    void mostrarEn(sf::Vector2f pos);
    void ocultar();
    bool estaVisible() const;

    void dibujar(sf::RenderWindow& window);
    bool manejarClick(sf::Vector2f clickPos, TipoTorre& tipoSeleccionado, int& costo);
};
