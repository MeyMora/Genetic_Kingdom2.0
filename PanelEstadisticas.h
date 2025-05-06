#pragma once
// PanelEstadisticas.h
#ifndef PANELESTADISTICAS_H
#define PANELESTADISTICAS_H

#include <SFML/Graphics.hpp>
#include "Torre.h"

class PanelEstadisticas {
private:
    Torre* torreActual = nullptr;
    sf::Vector2f posicionPanel = { 700, 100 }; // Posición por defecto a la derecha
    sf::Vector2f tamanoPanel = { 150, 80 };
    sf::Text texto;
    sf::RectangleShape panel;

public:
    PanelEstadisticas();
    void setTorre(Torre* torre);
    void dibujar(sf::RenderWindow& window, const sf::Font& font);
};

#endif

#pragma once
