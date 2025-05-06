#pragma once
//PanelMejora.h	

#include <SFML/Graphics.hpp>
#include "Torre.h"	

class PanelMejora {
private:
	Torre* torre = nullptr;
	sf::Vector2f posicionPanel = { 700, 200 }; // Posición por defecto a la derecha
	sf::Vector2f tamanoPanel = { 185, 140 };
	sf::RectangleShape panel;
	sf::Text texto;
	sf::RectangleShape boton;
	sf::Text textoBoton;
public:
	PanelMejora();
	void setTorre(Torre* t);
	Torre* getTorre() const;
	void dibujar(sf::RenderWindow& window, const sf::Font& font);
	bool clicEnBoton(sf::Vector2i mousePos);

};
	