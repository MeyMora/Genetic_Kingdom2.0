#include <SDL3/SDL.h>
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        SDL_Delay(2000); // Espera para ver el mensaje
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Ventana SDL3", 640, 480, 0);
    if (!window) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        SDL_Delay(2000);
        return 1;
    }

    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
