#include "Bridson.h"

#include <cmath>
#include <iostream>

namespace {
    typedef uint Domain_t;
    typedef double Distance_t;
    float sines[360];
    float cosines[360];
    size_t mCols;
    size_t mRows;
    Bridson::GridPoints_t grid;
    double cellSize;
}

namespace Bridson {

    GridPoints_t gridRect() {
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

    std::vector<SDL_Point> generateNewPoints(int k, double r, const std::vector<SDL_Point>& points) {
        std::vector<SDL_Point> c(k);
        int i = randomBetween<int>(0,points.size()-1);
        auto ap { points.at(i) };
        for(auto& p: c) {
            p = randomAnnularPoint(ap, r);
        }

        return c;
    }

    std::vector<SDL_Point> createSamples(int w, int h, int r=30, int k = 30) {
        // w - pixel width of window
        // h - pixel height of window
        // r - minimum distance between samples
        // cellSize s - r^2 = s^2 + s^2 -> r^2 = 2 * s^2 -> s = r/sqrt(n)
        initializeTrigFunctions();

        const Domain_t n { 2 };
        const Distance_t s { r / ::sqrt(n) };
        cellSize = s; // grid cell width and height

        mCols = std::lround(w/s); // number of columns (x)
        mRows = std::lround(h/s); // number of rows (y)
        const int N = mCols * mRows;

        // Initialize Grid
        grid.resize(mCols);
        for (auto& gc : grid) {
            gc.resize(mRows);
            for (auto& gr: gc) {
                gr = -1;
            }
        }


        // Set the first point in the grid
        SDL_Point p{ randomBetween<int>(0, w-1), randomBetween<int>(0, h-1) };
        size_t col { static_cast<size_t>(std::floor( p.x / s)) };
        size_t row { static_cast<size_t>(std::floor( p.y / s)) };
        grid[col][row] = p;


        auto shouldIgnore = [&w, &h, &s, &points, &r](const SDL_Point p, Bridson::GridPoints_t grid) {
            int col = std::floor( p.x/s );
            int row = std::floor( p.y/s );
            int c {0};

            for (int x = col-2 ; x < (col+2); ++x) {
                if ((0 > x) || (mCols <= x)) {
                    continue;
                }

                for (int y =  row-2 ; y <= (row+2) ; ++y ) {
                    if ((0>y) || (mRows <= y)) {
                        continue;
                    }

                    if (grid[x][y]>-1) {
                        const auto tp = points.at(grid[x][y]);
                        if (r > getDistance(tp,p)) {
                            return true;
                        }
                    }
                }
            }

            return false;
        };
        for (int j{0}; j < 20*N-1 ; ++j) {
            std::vector<SDL_Point> candidates{generateNewPoints(k, r, points)};
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

                    if (x<mCols && y<mRows && grid[x][y] < 0) {
                        grid[x][y] = points.size();
                        points.push_back(cp);
                        break;
                    }
                }
            }
        }




        //deleteGrid( mCols, grid);
        return points;
    }
}
