﻿#include "Mapa.h"
#include <iostream>
#include <queue> // Necesario para usar std::queue en BFS
#include <filesystem> // Necesario para usar std::filesystem
#include <SFML/Graphics.hpp>
#include <fstream>  // Para verificar la existencia de archivos
// Indicar que la variable global está definida en otro archivo
// Declaración de la variable global
extern std::string ruta;

Mapa::Mapa(int filas_, int columnas_)
    : filas(filas_),
    columnas(columnas_),
    grid(filas_, std::vector<Casilla>(columnas_, Casilla(0, 0))),
    nodos(filas_, std::vector<Nodo*>(columnas_, nullptr))
{
    // Cargar la textura del punto de ingreso
    if (!texturaEntrada.loadFromFile(ruta + "Inicio.png")) {
        std::cerr << "Error al cargar la textura del punto de ingreso desde: " << ruta + "Inicio.png" << std::endl;
    }

    // Cargar la textura del puente de meta
    if (!texturaMeta.loadFromFile(ruta + "Meta.png")) {
        std::cerr << "Error al cargar la textura del puente de meta desde: " << ruta + "Meta.png" << std::endl;
    }

    // Inicializar la matriz de casillas
    for (int i = 0; i < filas_; ++i) {
        for (int j = 0; j < columnas_; ++j) {
            grid[i][j] = Casilla(i, j);
        }
    }
}


void Mapa::mostrarMapa(sf::RenderWindow& window) const {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            sf::RectangleShape celda(sf::Vector2f(80, 80));
            celda.setPosition(j * 80, i * 80);

            switch (grid[i][j].estado) {
            case estadoCasilla::Empty:
                celda.setFillColor(sf::Color(50, 50, 50));
                break;
            case estadoCasilla::Torre:
                celda.setFillColor(sf::Color::Red);
                break;
            case estadoCasilla::Entrada: {
                sf::Sprite spriteEntrada;
                spriteEntrada.setTexture(texturaEntrada);
                spriteEntrada.setPosition(j * 80, i * 80);
                window.draw(spriteEntrada);
                continue;
            }
            case estadoCasilla::Meta: {
                sf::Sprite spriteMeta;
                spriteMeta.setTexture(texturaMeta);
                spriteMeta.setPosition(j * 80, i * 80);
                window.draw(spriteMeta);
                continue;
            }
            }

            celda.setOutlineThickness(1);
            celda.setOutlineColor(sf::Color::White);
            window.draw(celda);
        }
    }
}


bool Mapa::colocarTorre(int x, int y) {
    if (grid[x][y].estado != estadoCasilla::Empty) {
        return false; // Solo se pueden poner torres en casillas vacías
    }

    // Colocamos temporalmente la torre
    grid[x][y].estado = estadoCasilla::Torre;

	buildGraph(); // reconstruimos el grafo

	if (existeCamino()) { // Verificamos si hay un camino entre la entrada y la meta
		return true; // Hay camino, dejamos la torre
    }
    else {
		// Si no hay camino, quitamos la torre
		grid[x][y].estado = estadoCasilla::Empty; // Restauramos el estado original
		buildGraph(); // reconstruimos el grafo
		return false; 
    }
}

void Mapa::buildGraph() {
	// Método para construir el grafo a partir del mapa
	// Limpiar nodos existentes
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            delete nodos[i][j];
            nodos[i][j] = nullptr;
        }
    }

    // Crear nodos para cada casilla no bloqueada
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (grid[i][j].estado != estadoCasilla::Torre) {
                nodos[i][j] = new Nodo(&grid[i][j]);
            }
        }
    }

	// Conectar los nodos vecinos
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (nodos[i][j] != nullptr) {
                if (i > 0 && nodos[i - 1][j] != nullptr) // arriba
                    nodos[i][j]->agregarVecino(nodos[i - 1][j]);
                if (i < filas - 1 && nodos[i + 1][j] != nullptr) // abajo
                    nodos[i][j]->agregarVecino(nodos[i + 1][j]);
                if (j > 0 && nodos[i][j - 1] != nullptr) // izquierda
                    nodos[i][j]->agregarVecino(nodos[i][j - 1]);
                if (j < columnas - 1 && nodos[i][j + 1] != nullptr) // derecha
                    nodos[i][j]->agregarVecino(nodos[i][j + 1]);
            }
        }
    }
}

Nodo* Mapa::getNodo(int x, int y) { // Método para obtener el nodo correspondiente a una casilla
    if (x >= 0 && x < filas && y >= 0 && y < columnas) {
        return nodos[x][y];
    }
    return nullptr;
}   
// Método para establecer la entrada en el mapa
void Mapa::setEntrada(int x, int y) {
    if (grid[x][y].estado == estadoCasilla::Empty) {
        grid[x][y].estado = estadoCasilla::Entrada;
    }
}
// Método para establecer la meta en el mapa
void Mapa::setMeta(int x, int y) { 
	if (grid[x][y].estado == estadoCasilla::Empty) { 
        grid[x][y].estado = estadoCasilla::Meta;
    }
}

bool Mapa::existeCamino() { // Método para verificar si existe un camino entre la entrada y la meta
    Nodo* start = nullptr;// // Nodo de entrada
    Nodo* end = nullptr; // Nodo de meta

    // Buscar los nodos de entrada y meta
    for (int i = 0; i < filas; ++i) { // Recorrer filas
        for (int j = 0; j < columnas; ++j) { // Recorrer columnas
            if (nodos[i][j] != nullptr) { // Si el nodo no es nulo
                if (grid[i][j].estado == estadoCasilla::Entrada) { // Si es la entrada
                    start = nodos[i][j]; // Guardar el nodo de entrada
                }
                else if (grid[i][j].estado == estadoCasilla::Meta) { // Si es la meta 
                    end = nodos[i][j]; // Guardar el nodo de meta
                }
            }
        }
    }

    if (start == nullptr || end == nullptr) {
        std::cout << "Error: No se ha definido la entrada o la meta.\n";
        return false;
    }

    // BFS
    std::queue<Nodo*> q; // Cola para BFS
    std::vector<std::vector<bool>> visitado(filas, std::vector<bool>(columnas, false)); // Matriz de visitados

    q.push(start); // Agregar el nodo de entrada a la cola
    visitado[start->casilla->x][start->casilla->y] = true; // Marcarlo como visitado
    // Recorrer el grafo
    while (!q.empty()) {
        Nodo* actual = q.front(); // Obtener el nodo actual
        q.pop(); // Sacarlo de la cola

        if (actual == end) { // Si llegamos a la meta
            return true; // Se encontró un camino
        }

        for (Nodo* vecino : actual->vecinos) { // Recorrer los vecinos
            int vx = vecino->casilla->x;// Obtener las coordenadas del vecino
            int vy = vecino->casilla->y; // \

            if (!visitado[vx][vy]) { // Si no ha sido visitado
                visitado[vx][vy] = true; // Marcarlo como visitado
                q.push(vecino); // Agregarlo a la cola  
            }
        }
    }

    return false; // No se encontró un camino
} 
Mapa::~Mapa() {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (nodos[i][j] != nullptr) {
                delete nodos[i][j];
            }
        }
    }
}

estadoCasilla Mapa::getEstado(int x, int y) const {
    return grid[x][y].estado;
}