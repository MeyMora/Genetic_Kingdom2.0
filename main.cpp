#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include "TorreFactory.h"
#include "TorreConTipo.h"
#include "SelectorTorre.h"
#include "MensajeTemporal.h"
#include "PanelEstadisticas.h"
#include <filesystem>
#include <windows.h>
#include <fstream>
#include "PanelMejora.h"
const int CELL_SIZE = 80;
const int ROWS = 6;
const int COLS = 8;
PanelEstadisticas panelEstadisticas;
int oroJugador = 100; // Oro inicial del jugador
int nivelJuego = 1;  // Nivel inicial del juego

std::vector<std::unique_ptr<Torre>> torres; // Vector para almacenar las torres colocadas
std::string ruta = "C:/Users/Meibel/Desktop/1Semestre 2025/Estructuras_de_Datos_II/Proyecto_2/Genetic_Kingdom/x64/Debug/Imagenes/torres";

Torre* torreMouseEncima = nullptr;
PanelMejora panelMejora;

int main() {

    sf::RenderWindow window(sf::VideoMode(COLS * CELL_SIZE + 200, ROWS * CELL_SIZE), "Genetic Kingdom - Colocar Torres");
    Mapa mapa(ROWS, COLS);

    mapa.setEntrada(0, 3);
    mapa.setMeta(5, 3);
    

    std::ifstream test(ruta);
    if (!test.is_open()) {
        std::cerr << "❌ ERROR de prueba: no se encontró el archivo en:\n" << ruta << std::endl;
    }
    else {
        std::cout << "✅ Archivo encontrado correctamente." << std::endl;
    }

    sf::Font font;
    if (!font.loadFromFile("C:/Users/Meibel/Desktop/1Semestre 2025/Estructuras_de_Datos_II/Proyecto_2/Genetic_Kingdom/x64/Debug/OpenSans-Regular.ttf")) {
        std::cerr << "Error cargando la fuente\n";
    }

    SelectorTorre selectorTorre(font);
    MensajeTemporal mensajeUI(font);
    sf::Vector2i celdaSeleccionada;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);
                int col = click.x / CELL_SIZE;
                int fila = click.y / CELL_SIZE;

                if (selectorTorre.estaVisible()) {
                    TipoTorre tipo;
                    int costo;
                    if (selectorTorre.manejarClick(click, tipo, costo)) {
                        if (oroJugador >= costo) {
                            oroJugador -= costo;
                            mapa.colocarTorre(celdaSeleccionada.y, celdaSeleccionada.x);
                            torres.push_back(crearTorre(tipo, celdaSeleccionada));
                        }
                        else {
                            mensajeUI.mostrar("❌ Se acabó el oro. No se pueden colocar más torres.");
                        }
                    }
                }
                else if (fila >= 0 && fila < ROWS && col >= 0 && col < COLS && mapa.getEstado(fila, col) == estadoCasilla::Empty) {
                    celdaSeleccionada = { col, fila };
                    selectorTorre.mostrarEn(click);
                }
            }
        }

        mensajeUI.actualizar(); // Actualiza el temporizador del mensaje

        sf::Vector2i mousePosPixel = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePosPixel);

        // Torre que está debajo del mouse (si hay alguna)
        torreMouseEncima = nullptr;

        for (const auto& torre : torres) {
            sf::Vector2f torrePos = static_cast<sf::Vector2f>(torre->getPosicion() * CELL_SIZE);
            sf::FloatRect bounds(torrePos.x, torrePos.y, CELL_SIZE, CELL_SIZE);
            if (bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
                torreMouseEncima = torre.get();
                panelEstadisticas.setTorre(torreMouseEncima);
                break;
            }
        }


        window.clear(sf::Color::Black);

        for (int fila = 0; fila < ROWS; ++fila) {
            for (int col = 0; col < COLS; ++col) {
                sf::RectangleShape celda(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
                celda.setPosition(col * CELL_SIZE, fila * CELL_SIZE);

                switch (mapa.getEstado(fila, col)) {
                case estadoCasilla::Empty:
                    celda.setFillColor(sf::Color(50, 50, 50));
                    break;
                case estadoCasilla::Torre:
                    celda.setFillColor(sf::Color::Red);
                    break;
                case estadoCasilla::Entrada:
                    celda.setFillColor(sf::Color::Green);
                    break;
                case estadoCasilla::Meta:
                    celda.setFillColor(sf::Color::Blue);
                    break;
                }

                celda.setOutlineThickness(1);
                celda.setOutlineColor(sf::Color::White);
                window.draw(celda);
            }
        }

        // Mostrar oro
        sf::Text textoOro;
        textoOro.setFont(font);
        textoOro.setCharacterSize(20);
        textoOro.setFillColor(sf::Color::Yellow);
        textoOro.setPosition(10, 10);
        textoOro.setString("Oro: " + std::to_string(oroJugador));

        // Mostrar nivel
        sf::Text textoNivel;
        textoNivel.setFont(font);
        textoNivel.setCharacterSize(20);
        textoNivel.setFillColor(sf::Color::Cyan);
        textoNivel.setPosition(window.getSize().x - 150, 10);
        textoNivel.setString("Nivel: " + std::to_string(nivelJuego));

        window.draw(textoOro);
        window.draw(textoNivel);
        panelEstadisticas.dibujar(window, font);

        // 🆕 Dibujar torres (sprites o cuadrado)
        for (auto& torre : torres) {
            torre->dibujar(window);

            // Detectar si el mouse está sobre esta torre
            sf::Vector2f torrePos = static_cast<sf::Vector2f>(torre->getPosicion()) * (float)CELL_SIZE;
            sf::FloatRect rect(torrePos, sf::Vector2f(80, 80));

            if (rect.contains(static_cast<sf::Vector2f>(mousePos))) {
                // Dibujar rango si el mouse está sobre esta torre
                sf::CircleShape rangoVisual;
                float radioPixeles = torre->getAlcance() * 80;
                rangoVisual.setRadius(radioPixeles);
                rangoVisual.setFillColor(sf::Color(0, 255, 255, 64));
                rangoVisual.setOrigin(radioPixeles, radioPixeles);
                rangoVisual.setPosition(torrePos.x + 40, torrePos.y + 40);
                window.draw(rangoVisual);
            }
        }





        selectorTorre.dibujar(window);
        mensajeUI.dibujar(window); // Dibuja mensaje si está visible

        if (torreMouseEncima) {
            float radioPixeles = torreMouseEncima->getAlcance() * CELL_SIZE;
            sf::CircleShape rangoVisual(radioPixeles);
            rangoVisual.setFillColor(sf::Color(0, 255, 255, 64));
            rangoVisual.setOrigin(radioPixeles, radioPixeles);

            sf::Vector2i gridPos = torreMouseEncima->getPosicion();
            rangoVisual.setPosition((gridPos.x + 0.5f) * CELL_SIZE, (gridPos.y + 0.5f) * CELL_SIZE);
            window.draw(rangoVisual);
        }



        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i gridPos = sf::Mouse::getPosition(window) / CELL_SIZE;
            for (auto& torre : torres) {
                if (torre->getPosicion() == gridPos) {
                    panelMejora.setTorre(torre.get());
                }
            }
        }

        if (event.mouseButton.button == sf::Mouse::Left && panelMejora.getTorre()) {
            if (panelMejora.clicEnBoton(sf::Mouse::getPosition(window))) {
                Torre* t = panelMejora.getTorre();
                if (t->upgrade(oroJugador, oroJugador)) {
                    mensajeUI.mostrar("✅ Torre mejorada");
                }
                else {
                    mensajeUI.mostrar("❌ No se pudo mejorar");
                }
                panelMejora.setTorre(nullptr); // Oculta el panel
            }
        }

        panelMejora.dibujar(window, font);

        window.display();
    }

    return 0;
}
