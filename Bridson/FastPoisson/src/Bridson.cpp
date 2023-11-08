#include "Bridson.h"

#include <cmath>
#include <iostream>
#include <tuple>

namespace {
    typedef uint Domain_t;
    typedef double Distance_t;
    float sines[360];
    float cosines[360];
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
        double radius = randomBetween<size_t>(r, 2 * r) ;
        size_t d = /*2.0 * M_PI * */randomBetween<int>(0, 359)/* / 360.0*/;
        auto x = radius * sines[d] + p.x;
        auto y = radius * cosines[d] + p.y;
        return SDL_Point{ static_cast<int>(std::lround(x)), static_cast<int>(std::lround(y)) };
    }

    std::vector<std::pair<int,int>> activeGridCells(const Grid_t& g) {
        std::vector<std::pair<int,int>> o;
        int col {0};
        int row {0};
        for (const auto& a : g) {
            row = 0;
            for (const auto& b : a) {
                if (b.active) {
                    o.push_back(std::pair<int, int>(col, row));
                }
                ++row;
            }
            ++col;
        }
        return o;
    }

    std::vector<SDL_Point> generateNewPoints(int k, double r, const SDL_Point& centrePoint) {
        std::vector<SDL_Point> testPoints(k);
        for(auto& p : testPoints) {
            p = randomAnnularPoint(centrePoint, r);
        }

        return testPoints;
    }

    Grid_t initializeGrid(int w, int h, Distance_t s) {
        Grid_t g;
        int mCols = std::lround(w/s); // number of columns (x)
        int mRows = std::lround(h/s); // number of rows (y)

        g.resize(mCols);
        int row{0};
        int col{0};
        for (auto& gc : g) {
            gc.resize(mRows);
            row = 0;
            for (auto& gr: gc) {
                gr.active = false;
                gr.pt.x = -1;
                gr.pt.y = -1;
                gr.rct.x = col * s +1;
                gr.rct.y = row * s + 1;
                gr.rct.w = s - 2;
                gr.rct.h = s - 2;
                ++row;
            }
            ++col;
        }

        return g;
    }

    std::pair<int,int>& selectRandomGridCell(std::vector<std::pair<int, int>>& activeCells) {
        return activeCells[randomBetween((int)0, (int)activeCells.size()-1)];
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

        grid = initializeGrid(w, h, s);
        const int N = grid.size() * grid.begin()->size();

        // Initialize Grid

        // Set the first point in the grid
        SDL_Point p{ randomBetween<int>(0, w-1), randomBetween<int>(0, h-1) };
        int col = static_cast<size_t>(std::floor( p.x / s));
        int row = static_cast<size_t>(std::floor( p.y / s));
        grid[col][row].active = true;
        grid[col][row].containsPoint = true;
        grid[col][row].pt = p;

        auto shouldIgnore = [&s, &r](const SDL_Point p, Bridson::Grid_t grid) {
            int col = std::floor( p.x/s );
            int row = std::floor( p.y/s );

            if (col>=grid.size() || row>=grid[0].size()) {
                return true;
            }

            for (int x = col-3 ; x < (col+3); ++x) {
                if ((0 > x) || (grid[0].size() <= x)) {
                    continue;
                }

                for (int y =  row-2 ; y <= (row+2) ; ++y ) {
                    if ((0>y) || (grid.size() <= y)) {
                        continue;
                    }
                    const auto gridInfo = grid[x][y];
                    if (gridInfo.containsPoint) {
                         auto d = getDistance(p, gridInfo.pt);
                         if (d<r) {
                             return true;
                         }
                    }
                }
            }

            return false;
        };

        for (int j{0}; j < 2 * N - 1 ; ++j) {
            auto activeCells {activeGridCells(grid)};
            if (activeCells.empty()) {
                break;
            }
            auto& i = selectRandomGridCell(activeCells);
            auto centerPt = grid[i.first][i.second].pt;

            std::vector<SDL_Point> candidates{ generateNewPoints(k, r, centerPt) };

            candidates.erase(std::remove_if(candidates.begin(),
                                            candidates.end(),
                                            [&w, &h](auto &x) {
                                                SDL_Rect rct{0, 0, (int)(w), (int)(h)};
                                                return !SDL_PointInRect(&x, &rct);
                                            }),
                             candidates.end());

            size_t ignored {0};
            for (const auto &cp: candidates) {
                if (shouldIgnore(cp, grid)) {
                    ++ignored;
                    continue;
                }

                size_t col = std::floor( cp.x / s );
                size_t row = std::floor( cp.y / s );
                grid[col][row].active = true;
                grid[col][row].containsPoint = true;
                grid[col][row].pt = cp;
                break;
            }

            if (ignored == k) {
                // if none of the candidates are good, let's set the grid cell
                // to inactive
                grid[i.first][i.second].active=false;
            }
        }

        return grid;
    }
}
