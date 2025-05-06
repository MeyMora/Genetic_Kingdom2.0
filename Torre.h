
#ifndef TORRE_H
#define TORRE_H
#include <SFML/Graphics.hpp>
class Torre {
protected:
	int dano; // Daño de la torre
	float velocidad; // Velocidad de ataque de la torre
	int alcance; // Alcance de la torre
	float tiempoRecargaEspecial; // Tiempo de recarga del ataque especial
	float tiempoRecarga; // Tiempo de recarga del ataque normal
	sf::Vector2i posicion; // Posición de la torre en el mapa

	int nivel; // Nivel de la torre (0 por defecto)
	int costo; // Costo inicial para las torres 
	float probabilidadEspecial; // Probabilidad de ataque especial


public: 
	Torre(int dano_, float velocidad_, int alcance_, 
		float recargaEspecial, float recargaNormal, sf::Vector2i pos, int costo_); // Constructor de la clase Torre
	virtual ~Torre() = default; // Destructor virtual para permitir la eliminación de objetos derivados

	virtual void dibujar(sf::RenderWindow& window) {
		// SOLO DIBUJAR la torre base (cuadrado rojo) si no tiene sprite
		sf::RectangleShape shape(sf::Vector2f(78, 78));
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(posicion.x * 80, posicion.y * 80);
		window.draw(shape);
	}
	virtual void dibujarRangoSiSeleccionado(sf::RenderWindow& window, sf::Vector2f mousePos) {
		sf::FloatRect bounds(posicion.x * 80.f, posicion.y * 80.f, 80.f, 80.f);

		if (bounds.contains(mousePos)) {
			sf::CircleShape rangoVisual;
			rangoVisual.setRadius(alcance * 80.f);
			rangoVisual.setFillColor(sf::Color(0, 255, 255, 60));
			rangoVisual.setOrigin(rangoVisual.getRadius(), rangoVisual.getRadius());
			rangoVisual.setPosition((posicion.x + 0.5f) * 80.f, (posicion.y + 0.5f) * 80.f);
			window.draw(rangoVisual);
		}
	}




	// Métodos de acceso (getters)
	int getDano() const; // Obtener el daño de la torre
	float getVelocidad() const; // Obtener la velocidad de ataque de la torre
	int getAlcance() const; // Obtener el alcance de la torre
	sf::Vector2i getPosicion() const; // Obtener la posición de la torre en el mapa

	int getNivel() const; // Obtener el nivel de la torre
	int getCostoUpgrade() const; // Obtener el costo de la torre
	float getProbabilidadEspecial() const; // Obtener la probabilidad de tener ataque especial
	float getRango() const { return static_cast<float>(alcance); } // Obtener el rango de la torre (en celdas)

	//Comportamiento 
	bool estaEnRango(sf::Vector2i enemigoPos)const; // Verificar si un enemigo está dentro del rango de la torre

	bool upgrade(int oroJugador, int& oroRestante); // Mejorar la torre


};


#endif // !TORRE_H

