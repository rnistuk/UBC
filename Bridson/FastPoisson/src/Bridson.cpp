#include "Bridson.h"

#include <cmath>
#include <iostream>
#include <tuple>

namespace {
    typedef uint Domain_t;
    typedef double Distance_t;
    float sines[360];
    float cosines[360];
    //size_t mCols;
    //size_t mRows;
    Bridson::Grid_t grid;
    double cellSize;
}

namespace Bridson {

    Grid_t gridRect() {
        return grid;
    }

    void initializeTrigFunctions() {
        for (int i{0}; i < 360; ++i) {
            sines[i] = ::sin((double) i * 2 * M_PI / 360.0);
            cosines[i] = ::cos((double) i * 2 * M_PI / 360.0);
        }
    }

    double getDistance(int x1, int y1, int x2, int y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return ::sqrt(dx * dx + dy * dy);
    }

    double getDistance(const SDL_Point &a, const SDL_Point &b) {
        return getDistance(b.x, b.y, a.x, a.y);
    }

    SDL_Point randomAnnularPoint(const SDL_Point p, int r) {
        double radius = randomBetween<size_t>( (int)(1 + r), 2 * (int)(r)) ;
        size_t d = /*2.0 * M_PI * */randomBetween<int>(0, 359)/* / 360.0*/;
        auto x = radius * sines[d] + p.x;
        auto y = radius * cosines[d] + p.y;
        return SDL_Point{ static_cast<int>(std::lround(x)), static_cast<int>(std::lround(y)) };
    }

    std::vector<std::pair<int,int>> liveGridsCells(const Grid_t& g) {
        std::vector<std::pair<int,int>> o;
        int col {0};
        int row {0};
        for (const auto& a : g) {
            for (const auto& b : a) {
                if (b.alive) {
                    o.push_back(std::pair<int, int>(col, row));
                }
                ++row;
            }
            ++col;
        }
        return o;
    }

    std::vector<SDL_Point> generateNewPoints(int k, double r, const Grid_t& cells) {
        const auto ptIndexes { liveGridsCells(cells) };
        int i = randomBetween<int>(0,ptIndexes.size()-1);
        const auto centrePoint { cells[ptIndexes[i].first][ptIndexes[i].second].pt };
        std::vector<SDL_Point> activePoints(k);
        for(auto& p : activePoints) {
            p = randomAnnularPoint(centrePoint, r);
        }

        return activePoints;
    }

    Grid_t createSamples(int w, int h, int r=30, int k = 30) {
        // w - pixel width of window
        // h - pixel height of window
        // r - minimum distance between samples
        // cellSize s - r^2 = s^2 + s^2 -> r^2 = 2 * s^2 -> s = r/sqrt(n)
        initializeTrigFunctions();

        const Domain_t n { 2 };
        const Distance_t s { r / ::sqrt(n) };
        cellSize = s; // grid cell width and height

        int mCols = std::lround(w/s); // number of columns (x)
        int mRows = std::lround(h/s); // number of rows (y)
        const int N = mCols * mRows;

        // Initialize Grid
        grid.resize(mCols);
        int row{0};
        int col{0};
        for (auto& gc : grid) {
            gc.resize(mRows);
            for (auto& gr: gc) {
                gr.alive = false;
                gr.pt.x = -1;
                gr.pt.y = -1;
                gr.rct.x = col * s;
                gr.rct.y = row * s;
                gr.rct.w = s;
                gr.rct.h = s;
                ++col;
            }
            ++row;
        }

        // Set the first point in the grid
        SDL_Point p{ randomBetween<int>(0, w-1), randomBetween<int>(0, h-1) };
        col = static_cast<size_t>(std::floor( p.x / s));
        row = static_cast<size_t>(std::floor( p.y / s));
        grid[col][row].alive = true;
        grid[col][row].pt = p;

        auto shouldIgnore = [&w, &h, &s, &r](const SDL_Point p, Bridson::Grid_t grid) {
            int col = std::floor( p.x/s );
            int row = std::floor( p.y/s );
            int c {0};

            for (int x = col-2 ; x < (col+2); ++x) {
                if ((0 > x) || (grid[0].size() <= x)) {
                    continue;
                }

                for (int y =  row-2 ; y <= (row+2) ; ++y ) {
                    if ((0>y) || (grid.size() <= y)) {
                        continue;
                    }

                    const auto gridInfo = grid[x][y];

                    if (gridInfo.alive) {
                        const auto tp = gridInfo.pt;
                        if (r > getDistance(tp,p)) {
                            return true;
                        }
                    }
                }
            }

            return false;
        };

        for (int j{0}; j < 2*N-1 ; ++j) {
            std::vector<SDL_Point> candidates{ generateNewPoints(k, r, grid) };
            candidates.erase(std::remove_if(candidates.begin(),
                                            candidates.end(),
                                            [&w, &h](auto &x) {
                                                SDL_Rect rct{0, 0, (int)(w), (int)(h)};
                                                return !SDL_PointInRect(&x, &rct);
                                            }),
                             candidates.end());

            for (const auto &cp: candidates) {
                if (!shouldIgnore(cp, grid)) {
                    size_t x = std::floor( cp.x / s );
                    size_t y = std::floor( cp.y / s );

                    if (x<mCols && y<mRows && !grid[x][y].alive) {
                        grid[x][y].alive = true;
                        grid[x][y].pt = cp;
                        break;
                    }
                }
            }
        }

        return grid;
    }
}
