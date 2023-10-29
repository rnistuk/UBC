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

std::vector<int> getNeighbourIndexes(const std::vector<std::vector<Bridson::GridInfo_t>>& gr, int c, int r) {
    std::vector<int> o;
    int dl {1};
    int cstart = c-dl >=0 ? c-dl : 0;
    int cstop = c+dl < gr.size() ? c+dl : gr.size();
    int rstart = r-dl >=0 ? r-dl : 0;
    int rstop = r+dl < gr[0].size() ? r+dl : gr[0].size();

    for(int col{cstart}; col<cstop;++col) {
        for(int row{rstart}; row<rstop;++row) {
            o.push_back(gr[col][row].first);
        }
    }

    return o;
}

void reportStats(const std::vector<SDL_Point>& points) {
    double maxR { 0 };
    double minR { 50000 };
    std::vector<std::vector<Bridson::GridInfo_t>> gr = Bridson::gridRects();
    for (int row{0} ; row<gr.size()-1; ++row) {
        for (int col{0} ; col<gr[row].size()-1; ++col) {
            int centeri {gr[col][row].first};
            const auto centerp {points[centeri]};

            auto neighbours = getNeighbourIndexes(gr, col, row);
            for(const auto& i : neighbours) {
                if (i!=-1 && i!=centeri) {
                    double d = Bridson::getDistance(centerp, points[i]);
                    if (d>maxR) {
                        maxR = d;
                    }
                    if (d<minR) {
                        minR = d;
                    }
                }
            }

        }
    }

    std::cout << "min: [" << minR << "]   max; [" << maxR << "]\n";






}

int main() {
    SDL::initSDL();
    auto window = SDL::SDLWindow(640, 480);
    window.render();

    auto start {std::chrono::system_clock::now()};
    // 640 x 480 = 2 * 2 * 160 x 3 * 160 = 2 * 2 * 2 * 80  x 3 * 2 * 80
    std::vector<SDL_Point> points = Bridson::createSamples(window.getWidth()
            , window.getHeight(), ::sqrt(2*10*10), 30);
    std::cout << "time:" << (std::chrono::system_clock::now() - start).count() << std::endl;

    reportStats(points);

    SDL_SetRenderDrawBlendMode(window.getRenderer(), SDL_BLENDMODE_BLEND);

    while(!handleEvents()) {
        // do render stuff
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(window.getRenderer());

        SDL::drawPoints(window, points);

        // draw grid
        SDL::drawGrid(window);

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




