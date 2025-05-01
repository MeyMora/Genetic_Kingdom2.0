#ifndef MAPA_H
#define MAPA_H
#include <iostream>
#include <vector>
#include "Casilla.h"
#include "estadoCasilla.h" // Incluir el archivo de definici�n del enum estadoCasilla
#include "Nodo.h" // Incluir la definici�n de la clase Nodo

class Mapa {
	// Clase que representa el mapa del juego
	private:
		int filas, columnas; // Dimensiones del mapa
		std::vector<std::vector<Casilla>> grid; // Matriz de casillas que representa el mapa
		std::vector<std::vector<Nodo*>> nodos; // Matriz de nodos que representa el grafo del mapa


public:
	Mapa(int filas_, int columnas_);
	~Mapa(); // Destructor para liberar memoria
	void mostrarMapa() const; // M�todo para mostrar el mapa en la consola
	bool colocarTorre(int x, int y); // M�todo para colocar una torre en el mapa
	void buildGraph(); // M�todo para construir el grafo a partir del mapa
	Nodo* getNodo(int x, int y); // M�todo para obtener el nodo correspondiente a una casilla
	void setEntrada(int x, int y);
	void setMeta(int x, int y);
	bool existeCamino(); // M�todo para verificar si existe un camino entre la entrada y la meta
	estadoCasilla getEstado(int x, int y) const;

    
};

#endif // MAPA_H