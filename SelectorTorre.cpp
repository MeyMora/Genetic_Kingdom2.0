#include "SelectorTorre.h"

SelectorTorre::SelectorTorre(sf::Font& font) : fuente(font) {
    sf::Vector2f size(100, 30);

    botonArquera.setSize(size);
    botonMago.setSize(size);
    botonArtillero.setSize(size);

    botonArquera.setFillColor(sf::Color(100, 200, 100));
    botonMago.setFillColor(sf::Color(100, 100, 255));
    botonArtillero.setFillColor(sf::Color(255, 150, 50));

    textoArquera.setFont(fuente);
    textoMago.setFont(fuente);
    textoArtillero.setFont(fuente);

    textoArquera.setCharacterSize(14);
    textoMago.setCharacterSize(14);
    textoArtillero.setCharacterSize(14);

    textoArquera.setString("Arquera (15)");
    textoMago.setString("Mago (25)");
    textoArtillero.setString("Artillero (35)");
}

void SelectorTorre::mostrarEn(sf::Vector2f pos) {
    posicion = pos;

    botonArquera.setPosition(pos);
    botonMago.setPosition(pos + sf::Vector2f(0, 40));
    botonArtillero.setPosition(pos + sf::Vector2f(0, 80));

    textoArquera.setPosition(pos + sf::Vector2f(5, 5));
    textoMago.setPosition(pos + sf::Vector2f(5, 45));
    textoArtillero.setPosition(pos + sf::Vector2f(5, 85));

    visible = true;
}

void SelectorTorre::ocultar() {
    visible = false;
}

bool SelectorTorre::estaVisible() const {
    return visible;
}

void SelectorTorre::dibujar(sf::RenderWindow& window) {
    if (!visible) return;

    window.draw(botonArquera);
    window.draw(botonMago);
    window.draw(botonArtillero);

    window.draw(textoArquera);
    window.draw(textoMago);
    window.draw(textoArtillero);
}

bool SelectorTorre::manejarClick(sf::Vector2f clickPos, TipoTorre& tipoSeleccionado, int& costo) {
    if (!visible) return false;

    if (botonArquera.getGlobalBounds().contains(clickPos)) {
        tipoSeleccionado = TipoTorre::Arquera;
        costo = 15;
        visible = false;
        return true;
    }
    else if (botonMago.getGlobalBounds().contains(clickPos)) {
        tipoSeleccionado = TipoTorre::Mago;
        costo = 25;
        visible = false;
        return true;
    }
    else if (botonArtillero.getGlobalBounds().contains(clickPos)) {
        tipoSeleccionado = TipoTorre::Artillero;
        costo = 35;
        visible = false;
        return true;
    }

    // Si clic fuera de todos los botones, cerrar menú
    visible = false;
    return false;
}
