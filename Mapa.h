#ifndef MAPA_H
#define MAPA_H
#include <iostream>
#include <vector>
#include "Casilla.h"
#include "estadoCasilla.h" // Incluir el archivo de definición del enum estadoCasilla
#include "Nodo.h" // Incluir la definición de la clase Nodo
#include <SFML/Graphics.hpp>



// Declaración externa de la variable global
extern std::string ruta;

class Mapa {
	// Clase que representa el mapa del juego
	private:
		int filas, columnas; // Dimensiones del mapa
		std::vector<std::vector<Casilla>> grid; // Matriz de casillas que representa el mapa
		std::vector<std::vector<Nodo*>> nodos; // Matriz de nodos que representa el grafo del mapa

		// 🆕 Texturas para el punto de ingreso y la meta
		sf::Texture texturaEntrada;
		sf::Texture texturaMeta;
		void buildGraph(); // Método para construir el grafo a partir del mapa


public:
	Mapa(int filas_, int columnas_);
	~Mapa(); // Destructor para liberar memoria
	void mostrarMapa(sf::RenderWindow& window) const; // Método para mostrar el mapa en la ventana
	bool colocarTorre(int x, int y); // Método para colocar una torre en el mapa

	Nodo* getNodo(int x, int y); // Método para obtener el nodo correspondiente a una casilla
	void setEntrada(int x, int y);
	void setMeta(int x, int y);
	bool existeCamino(); // Método para verificar si existe un camino entre la entrada y la meta
	estadoCasilla getEstado(int x, int y) const;

    
};

#endif // MAPA_H