#pragma once
#include "Utilities.h"

#include <SDL2/SDL.h>

namespace Bridson {
    typedef std::vector<SDL_Point>                  Points_t;
    typedef struct {
        SDL_Rect rct;
        //bool active;
        bool containsPoint;
        SDL_Point pt;
    }    GridInfo_t;
    typedef std::vector<std::vector<GridInfo_t>>    Grid_t;



    Grid_t createSamples(int w, int h, int r, int k);
    Grid_t gridRects();
    std::vector<SDL_Point> getCandidates();
    std::vector<std::pair<int,int>>& getActiveGridCells();

    // private
    double      getDistance(int x1, int y1, int x2, int y2);
    double      getDistance(const SDL_Point &a, const SDL_Point &b);
    void        initializeTrigFunctions();
    SDL_Point   randomAnnularPoint(const SDL_Point p, int r);
    Points_t    generateNewPoints(int k, double r, const SDL_Point& centrePoint);

    Grid_t      getGrid();
};
