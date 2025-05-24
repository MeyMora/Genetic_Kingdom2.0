#include "GameBoard.h"
#include <iostream>
#include "AStar.cpp"

const int GRID_SIZE = 50; // Tamaño de cada celda

GameBoard::GameBoard(int r, int c) : rows(r), cols(c) {
    // Inicializar el tablero con celdas vacías
    grid.resize(rows, std::vector<int>(cols, 0));
    
    // Definir entrada y salida
    entrance = {0, r/2};
    exit = {c-1, r/2};
    
    // Inicializar el mapa con múltiples caminos
    initializeMap();
}

void GameBoard::initializeMap() {
    // Limpiamos el grid (excepto las torres)
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] != 2) { // No tocar las torres existentes
                grid[r][c] = 0;
            }
        }
    }
    
    findPath(entrance, exit);
    
    // Marcar entrada y salida
    grid[entrance.y][entrance.x] = 1;
    grid[exit.y][exit.x] = 1;
}

bool GameBoard::hasValidPath() {
    return findPath(entrance, exit);
}

std::vector<SDL_Point> GameBoard::getMainPath() {
    return mainPath;
}

void GameBoard::showPath(std::vector<SDL_Point> path) {
    for (SDL_Point point : path) {
        grid[point.y][point.x] = 1;
    }
}

bool GameBoard::findPath(SDL_Point start, SDL_Point end) {
    auto isWalkable = [this](int x, int y) {
        return this->isCellWalkable(x, y);
    };

    std::cout << "Generando camino con A* desde (" << start.x << "," << start.y 
              << ") hasta (" << end.x << "," << end.y << ")" << std::endl;

    std::vector<SDL_Point> path = AStar::findPath(
        isWalkable, {start.x, start.y}, end, 
        getCols(), getRows()); 

    if (!path.empty()) {
        mainPath = path;
        showPath(path);
        return true;
    }
    std::cerr << "¡Error! A* no pudo encontrar un camino." << std::endl;    
    return false;
}

void GameBoard::render(SDL_Renderer* renderer) const {
    // Dibujar el tablero
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            SDL_Rect cell = {c * GRID_SIZE, r * GRID_SIZE, GRID_SIZE, GRID_SIZE};
            
            // Colorear según el tipo de celda
            switch (grid[r][c]) {
                case 0: // Celda vacía - verde claro
                    SDL_SetRenderDrawColor(renderer, 144, 238, 144, 255);
                    break;
                case 1: // Camino - marrón
                    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
                    break;
                case 2: // Torre - gris
                    SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
                    break;
            }
            
            SDL_RenderFillRect(renderer, &cell);
            
            // Dibujar borde de la celda
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
    
    // Dibujar entrada (izquierda) - rojo
    SDL_Rect entranceRect = {entrance.x * GRID_SIZE, entrance.y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &entranceRect);
    
    // Dibujar puente/salida (derecha) - azul
    SDL_Rect exitRect = {exit.x * GRID_SIZE, exit.y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &exitRect);
}

bool GameBoard::isValidTowerPosition(int r, int c) {
    // Verificar límites
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return false;

    // No permitir en entrada o salida
    if ((r == entrance.y && c == entrance.x) ||
        (r == exit.y && c == exit.x))
        return false;

    // Ya hay una torre ahí
    if (grid[r][c] == 2)
        return false;

    // Guardar el estado original
    int originalValue = grid[r][c];
    grid[r][c] = 2;  // Colocar torre temporalmente

    // Probar si A* puede encontrar un nuevo camino
    auto isWalkable = [this](int x, int y) {
        return this->isCellWalkable(x, y);
    };

    std::vector<SDL_Point> newPath = AStar::findPath(isWalkable, entrance, exit, getCols(), getRows());

    if (!newPath.empty()) {
        // Actualizar mainPath y mostrarlo en el grid
        mainPath = newPath;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (grid[r][c] == 1)
                    grid[r][c] = 0;
        showPath(newPath);
        return true;
    }

    // Restaurar si no se pudo encontrar nuevo camino
    grid[r][c] = originalValue;
    return false;
}

bool GameBoard::placeTower(int r, int c) {
    if (isValidTowerPosition(r, c)) {
        return true;
    }
    return false;
}

SDL_Point GameBoard::screenToGrid(int x, int y) const {
    return {x / GRID_SIZE, y / GRID_SIZE};
}

int GameBoard::getCellType(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        return grid[r][c];
    }
    return -1; // Fuera de límites
}

bool GameBoard::isCellWalkable(int x, int y) const {
    // Verificar límites
    if (x < 0 || x >= cols || y < 0 || y >= rows) {
        return false;
    }
    
    // Celda es caminable si es un camino (1) o entrada/salida
    return grid[y][x] != 2;
}