#include "Bridson.h"
#include "SDLGraphics.h"

namespace SDL {
    SDLWindow::SDLWindow(int w, int h) {
        this->window = SDL_CreateWindow("const char *title"
                ,10 ,10
                ,w , h
                , 0);

        this->renderer = SDL_CreateRenderer(this->window, 0, 0);


    }

    SDLWindow::~SDLWindow() {
        SDL_RenderClear(this->renderer);
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
    }

    int initSDL() {
        if (SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

            return 1;
        }

        return 0;
    }

    void cleanUpSDL(SDL_Window* w, SDL_Renderer* r) {
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
        SDL_Quit();
    }

    void setCellColor(SDL::SDLWindow& w, int t) {
        if (-1 == t) {
            SDL_SetRenderDrawColor(w.getRenderer(), 255, 2, 0, 40);
        } else {
            SDL_SetRenderDrawColor(w.getRenderer(), 2, 255, 0, 40);
        }
    }

    void drawCell(SDL::SDLWindow& w, const Bridson::GridInfo_t& gi) {
        int t {gi.first};
        SDL_Rect rct { gi.second};
        setCellColor(w, t);
        SDL_RenderFillRect(w.getRenderer(), &rct);
    };

    void drawGrid(SDL::SDLWindow& w) {
        auto g = Bridson::gridRects();
        size_t cols { g.size() };
        for (int c{0} ; c < cols ; ++c) {
            size_t rows {g[c].size()};
            for (int r{0} ;  r < rows ; r++) {
                drawCell(w, g[c][r]);
            }
        }
    }

    void drawPoints(SDL::SDLWindow& w, const std::vector<SDL_Point>& pts) {
        SDL_SetRenderDrawColor(w.getRenderer(), 255, 255, 255, 175);
        int i {0};

        static bool once {false};
        for(const auto& p : pts) {
            SDL_Rect rct{p.x-1, p.y-1, 2, 2};
            SDL_RenderFillRect(w.getRenderer(), &rct);
        }
    }

}


