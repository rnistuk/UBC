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

std::vector<SDL_Point> Bridson::generateNewPoints(int k, double r, const Bridson::Grid_t& cells);

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

void reportStats(const Bridson::Grid_t& gr, double r) {
    std::vector<Bridson::GridInfo_t> liveCells;
    for (const auto& a : gr) {
        for (const auto& b : a) {
            if (b.alive) {
                liveCells.push_back(b);
            }
        }
    }

    double min{10000};
    for (int i=0; i<liveCells.size(); ++i) {
        for (int j=i+1; j<liveCells.size(); ++j) {
            min = std::min(min, Bridson::getDistance(liveCells[i].pt, liveCells[j].pt));
        }
    }
    std::cout << "Min distance: [" << min << "]   r:[" << r << "] s:[" << r / ::sqrt(2) << "]\n";
}

int main() {
    SDL::initSDL();
    auto window = SDL::SDLWindow(800, 800);
    window.render();

    auto start {std::chrono::high_resolution_clock::now()};
    // 640 x 480 = 2 * 2 * 160 x 3 * 160 = 2 * 2 * 2 * 2 * 40   x 3 * 2 * 2 * 40
    Bridson::Grid_t gridCells = Bridson::createSamples(window.getWidth() , window.getHeight(),  30 , 30);
    auto d { (std::chrono::high_resolution_clock::now() - start) };
    std::cout << "time:" << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << " ms" << std::endl;

    reportStats(gridCells, 30);

    SDL_SetRenderDrawBlendMode(window.getRenderer(), SDL_BLENDMODE_BLEND);
    while(!handleEvents()) {
        // do render stuff
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(window.getRenderer());

        // draw grid
        //SDL::drawGrid(window, gridCells);

        SDL::drawPoints(window, gridCells);

        // render screen
        window.render();
    }

    return 0;
}

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




