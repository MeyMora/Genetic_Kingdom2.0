#include "MensajeTemporal.h"

MensajeTemporal::MensajeTemporal(sf::Font& font, float duracionSegundos)
    : duracion(duracionSegundos) {
    texto.setFont(font);
    texto.setCharacterSize(20);
    texto.setFillColor(sf::Color::White);

    fondo.setSize({ 600, 40 });
    fondo.setFillColor(sf::Color(100, 0, 0, 200));
    fondo.setPosition(10, 70);
}

void MensajeTemporal::mostrar(const std::string& mensaje, sf::Color colorTexto, sf::Color colorFondo) {
    texto.setString(mensaje);
    texto.setFillColor(colorTexto);
    fondo.setFillColor(colorFondo);
    reloj.restart();
    visible = true;
}

void MensajeTemporal::actualizar() {
    if (visible && reloj.getElapsedTime().asSeconds() > duracion) {
        visible = false;
    }
}

void MensajeTemporal::dibujar(sf::RenderWindow& window) {
    if (!visible) return;
    window.draw(fondo);
    texto.setPosition(fondo.getPosition().x + 10, fondo.getPosition().y + 10);
    window.draw(texto);
}

bool MensajeTemporal::estaVisible() const {
    return visible;
}
