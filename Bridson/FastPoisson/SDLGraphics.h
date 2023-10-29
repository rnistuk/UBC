#pragma once

#include <SDL2/SDL.h>
#include <vector>

namespace SDL{

    class SDLWindow {
    public:
        SDLWindow(int width, int height);
        ~SDLWindow();

        SDL_Window* getWindow() { return this->window; };
        SDL_Renderer* getRenderer()  { return SDL_GetRenderer(this->window); };
        int getWidth() {
            int w;
            SDL_GetWindowSize(this->window, &w, nullptr);
            return w;
        };

        int getHeight(){
            int h;
            SDL_GetWindowSize(this->window, nullptr, &h);
            return h;
        };

        void render() { SDL_RenderPresent(this->renderer); }

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    };

    int initSDL();

    void drawGrid(SDL::SDLWindow& w);

    void drawPoints(SDL::SDLWindow& w, const std::vector<SDL_Point>& pts);

}
