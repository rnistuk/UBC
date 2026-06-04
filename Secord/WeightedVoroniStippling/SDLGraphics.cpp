//#include "Bridson.h"
#include "SDLGraphics.h"

namespace SDL {
    SDLWindow::SDLWindow(int w, int h) {
        this->window = SDL_CreateWindow("Fast Poisson"
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

    void setCellColor(SDL::SDLWindow& w, bool t) {
        if (!t) {
            SDL_SetRenderDrawColor(w.getRenderer(), 255, 2, 0, 140);
            return;
        }
        SDL_SetRenderDrawColor(w.getRenderer(), 2, 255, 0, 140);
    }

    SDL_Point* pointsInCircle(size_t nPts, const SDL_Point& p, int radius) {
        SDL_Point* pts = new SDL_Point[nPts];
        double t = 0;
        double dt = 2.0 * M_PI / (double) (nPts-1);
        for(int i=0; i<nPts-1; ++i) {
            pts[i].x = std::lround(p.x + radius * cos(t));
            pts[i].y = std::lround(p.y + radius * sin(t));
            t += dt;
        }

        pts[nPts-1].x = pts[0].x;
        pts[nPts-1].y = pts[0].y;

        return pts;
    }

    void drawPoint(SDL::SDLWindow& w, const SDL_Point& p, int radius) {
        int nPts{33};
        SDL_Point* pts = pointsInCircle(nPts, p, radius);
        SDL_RenderDrawLines(w.getRenderer(), pts, nPts);
        delete [] pts;
    }

}
