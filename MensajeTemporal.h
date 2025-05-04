#pragma once
#include <SFML/Graphics.hpp>

class MensajeTemporal {
private:
    sf::Text texto;
    sf::RectangleShape fondo;
    sf::Clock reloj;
    bool visible = false;
    float duracion;

public:
    MensajeTemporal(sf::Font& font, float duracionSegundos = 3.0f);

    void mostrar(const std::string& mensaje, sf::Color colorTexto = sf::Color::White, sf::Color colorFondo = sf::Color(100, 0, 0, 200));
    void actualizar();
    void dibujar(sf::RenderWindow& window);
    bool estaVisible() const;
};
#pragma once
