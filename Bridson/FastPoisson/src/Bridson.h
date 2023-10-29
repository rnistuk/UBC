#pragma once

#include "SDLGraphics.h"
#include "Utilities.h"

#include <any>

namespace Bridson {
    typedef std::vector<SDL_Point> Points_t;
    typedef std::pair<int,SDL_Rect> GridInfo_t;
    typedef std::vector<std::vector<std::any>> GridPoints_t;

    Points_t createSamples(int w, int h, int r, int k);
    std::vector<std::vector<GridInfo_t>> gridRects();

    // private
    double      getDistance(int x1, int y1, int x2, int y2);
    double      getDistance(const SDL_Point &a, const SDL_Point &b);
    void        initializeTrigFunctions();
    SDL_Point   randomAnnularPoint(const SDL_Point p, int r);
    Points_t    generateNewPoints(int k, double r, const Points_t& points);
};
