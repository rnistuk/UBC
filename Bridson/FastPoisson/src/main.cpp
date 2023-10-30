#include "Bridson.h"
#include "SDLGraphics.h"
#include "Utilities.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
// https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf
// https://www.youtube.com/watch?v=mj_qBX-_pzg
// see also:  https://www.youtube.com/watch?v=ITsvn4wAvCw

bool handleEvents();

std::vector<Bridson::GridInfo_t> getNeighbourGrids(const Bridson::Grid_t& gr, int c, int r) {
    std::vector<Bridson::GridInfo_t> o;
    int dl {1};
    int cstart = c-dl >=0 ? c-dl : 0;
    int cstop = c+dl < gr.size() ? c+dl : gr.size();
    int rstart = r-dl >=0 ? r-dl : 0;
    int rstop = r+dl < gr[0].size() ? r+dl : gr[0].size();

    for(int col{cstart}; col<cstop;++col) {
        for(int row{rstart}; row<rstop;++row) {
            o.push_back(gr[col][row]);
        }
    }

    return o;
}

void reportStats(const std::vector<SDL_Point>& points) {
    std::cout << "reportStats not implemented" << std::endl;
}

int main() {
    SDL::initSDL();
    auto window = SDL::SDLWindow(640, 480);
    window.render();

    auto start {std::chrono::system_clock::now()};
    // 640 x 480 = 2 * 2 * 160 x 3 * 160 = 2 * 2 * 2 * 80  x 3 * 2 * 80
    Bridson::Grid_t gridCells = Bridson::createSamples(window.getWidth()
            , window.getHeight(), ::sqrt(2*10*10), 30);
    std::cout << "time:" << (std::chrono::system_clock::now() - start).count() << std::endl;

    //reportStats(gridCells);

    SDL_SetRenderDrawBlendMode(window.getRenderer(), SDL_BLENDMODE_BLEND);

    while(!handleEvents()) {
        // do render stuff
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(window.getRenderer());

        // draw grid
        SDL::drawGrid(window, gridCells);

        SDL::drawPoints(window, gridCells);

        // render screen
        window.render();
    }

    return 0;
}

void reportStats();


bool handleEvents() {
    SDL_Event event;
    bool shift_pressed{false};
    bool ctrl_pressed{false};
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return SDL_TRUE;
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            //
            //   SDL_Point p;
            //   p.x = event.button.x;
            //   p.y = event.button.y;
            //   auto n = graph.node_on_point(p);
            //   if (n != nullptr) {
            //        if (shift_pressed) {
            //            graph.set_start_node(n);
            //        } else if (ctrl_pressed) {
            //            graph.set_end_node(n);
            //        } else {
            //            n->node_type = (n->node_type == empty ? obstacle : empty);
            //        }
            //    }
        }
        if (event.type == SDL_KEYDOWN) {
            std::cout << event.key.keysym.scancode << "\n";
            if (event.key.keysym.scancode == 225) {
                shift_pressed = true;
            }
            if (event.key.keysym.scancode == 224) {
                ctrl_pressed = true;
            }
        }

        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == 225) {
                shift_pressed = false;
            }
            if (event.key.keysym.scancode == 224) {
                ctrl_pressed = false;
            }
        }
    }

    return SDL_FALSE;
}




