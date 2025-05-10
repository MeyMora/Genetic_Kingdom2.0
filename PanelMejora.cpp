
// PanelMejora.cpp
#include "PanelMejora.h"

PanelMejora::PanelMejora() {
    panel.setSize(tamanoPanel);
    panel.setFillColor(sf::Color(30, 30, 30, 200));
    panel.setOutlineColor(sf::Color::Yellow);
    panel.setOutlineThickness(2);
    panel.setPosition(posicionPanel);

    boton.setSize(sf::Vector2f(140, 25));
    boton.setFillColor(sf::Color(0, 100, 0));
	boton.setPosition(posicionPanel.x + 20, posicionPanel.y + 90);

    textoBoton.setCharacterSize(14);
    textoBoton.setFillColor(sf::Color::White);
    textoBoton.setPosition(boton.getPosition().x + 10, boton.getPosition().y + 2);
    textoBoton.setString("Mejorar torre");

    texto.setCharacterSize(14);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(posicionPanel.x + 10, posicionPanel.y + 10);
}

void PanelMejora::setTorre(Torre* t) {
    torre = t;
}

Torre* PanelMejora::getTorre() const {
    return torre;
}

void PanelMejora::dibujar(sf::RenderWindow& window, const sf::Font& font) {
    if (!torre) return;

    texto.setFont(font);
    textoBoton.setFont(font);

    std::string desc = "Nivel: " + std::to_string(torre->getNivel()) +
        "\nDano +5"
        "\nAlcance +1"
        "\nCosto: " + std::to_string(torre->getCostoUpgrade());
    texto.setString(desc);

    window.draw(panel);
    window.draw(texto);
    window.draw(boton);
    window.draw(textoBoton);
}

bool PanelMejora::clicEnBoton(sf::Vector2i mousePos) {
    return boton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
