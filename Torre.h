
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


	// Métodos de acceso (getters)
	int getDano() const; // Obtener el daño de la torre
	float getVelocidad() const; // Obtener la velocidad de ataque de la torre
	int getAlcance() const; // Obtener el alcance de la torre
	sf::Vector2i getPosicion() const; // Obtener la posición de la torre en el mapa

	int getNivel() const; // Obtener el nivel de la torre
	int getCostoUpgrade() const; // Obtener el costo de la torre
	float getProbabilidadEspecial() const; // Obtener la probabilidad de tener ataque especial


	//Comportamiento 
	bool estaEnRango(sf::Vector2i enemigoPos)const; // Verificar si un enemigo está dentro del rango de la torre

	bool upgrade(int oroJugador, int& oroRestante); // Mejorar la torre


};


#endif // !TORRE_H

