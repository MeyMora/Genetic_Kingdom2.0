// PanelEstadisticas.cpp
#include "PanelEstadisticas.h"

PanelEstadisticas::PanelEstadisticas() {
    panel.setSize(tamanoPanel);
    panel.setFillColor(sf::Color(0, 0, 0, 150));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2);
    panel.setPosition(posicionPanel);

    texto.setCharacterSize(14);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(posicionPanel.x + 10, posicionPanel.y + 10);
}

void PanelEstadisticas::setTorre(Torre* torre) {
    torreActual = torre;
}

void PanelEstadisticas::dibujar(sf::RenderWindow& window, const sf::Font& font) {
    if (!torreActual) return;

    texto.setFont(font);
    std::string stats = "Dano: " + std::to_string(torreActual->getDano()) +
        "\nAlcance: " + std::to_string(torreActual->getAlcance()) +
        "\nNivel: " + std::to_string(torreActual->getNivel());

    texto.setString(stats);

    window.draw(panel);
    window.draw(texto);
}
