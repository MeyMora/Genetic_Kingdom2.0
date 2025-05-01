
#ifndef NODO_H
#define NODO_H

#include <vector>
#include "Casilla.h"

class Nodo { // Clase que representa un nodo en el grafo
public:
	Casilla* casilla;  // Casilla asociada al nodo
	std::vector<Nodo*> vecinos; // Lista de nodos vecinos
     
	Nodo(Casilla* casilla_) : casilla(casilla_) {} // Constructor que inicializa el nodo con una casilla

    void agregarVecino(Nodo* vecino) { // metodo para agregar un nodo vecino
		vecinos.push_back(vecino); // Agrega un nodo vecino a la lista de vecinos
    }
};
// Método para obtener la lista de nodos vecinos
#endif // NODO_H

