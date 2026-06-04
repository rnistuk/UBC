#include "SDLGraphics.h"

#include <iostream>
#include <vector>

#include "../../../../../../../opt/homebrew/include/SDL2/SDL_rect.h"

bool handleEvents();

struct Vertex {
    int x {0};
    int y {0};
    bool operator==(Vertex v) { return this->x == v.x && this->y == v.y; };
};

SDL_Point operator-(const Vertex& A, const Vertex& B) {
    return SDL_Point {B.x - A.x, B.y - A.y};
}

double magnitude(const Vertex& X) {
    return ::sqrt( X.x * X.x + X.y * X.y );
}

int dotProduct(const Vertex& A, const Vertex& B) {
    return A.x * B.x + A.y * B.y;
}

double angleBetween(const Vertex& A, const Vertex& B) {
    return ::acos(dotProduct(A,B) / (magnitude(A) * magnitude(B)));
}

struct Edge {
    Vertex v0;
    Vertex v1;
    bool operator==(Edge e) { return (this->v0 == e.v0 && this->v1 == e.v1) || (this->v1 == e.v0 && this->v0 == e.v1); }
};

struct Triangle {
    Vertex A;
    Vertex B;
    Vertex C;

    SDL_Point circumCircle() {
        // https://www.cuemath.com/geometry/circumcenter/
        SDL_Point O;
        SDL_Point a { C - B }, b { C - A }, c { B - C };
        double sin_2A { ::sin(2.0 * angleBetween(B,C)) };
        double sin_2B { ::sin(2.0 * angleBetween(A,C)) };
        double sin_2C { ::sin(2.0 * angleBetween(A,C)) };
        double denom { sin_2A + sin_2B + sin_2C };

        return SDL_Point {
                int((a.x * sin_2A + b.x * sin_2B + C.x * sin_2C) / denom)
                , int((a.y * sin_2A + b.y *  sin_2B + c.y * sin_2C ) / denom)};
    }

    bool inCircumCircle() {
        return false;
    }
};

Triangle superTriangle(const std::vector<Vertex>& vertices) {
    int minx {10000};
    int miny {10000};
    int maxx {-10000};
    int maxy {-10000};
    return Triangle();
}





// https://www.gorillasun.de/blog/bowyer-watson-algorithm-for-delaunay-triangulation/
void BowyerWatson (const std::vector<SDL_Point>& pointList) {
    // pointList is a set of coordinates defining the points to be
    // triangulated
    triangulation := empty triangle mesh data structure

// must be large enough to completely contain all the points in pointList
    add super-triangle to triangulation

// add all the points one at a time to the triangulation
    for each point in pointList do

        badTriangles := empty set

// first find all the triangles that are no longer valid due to the insertion
    for each triangle in triangulation do
        if point is inside circumcircle of triangle
    add triangle to badTriangles

    polygon := empty set

// find the boundary of the polygonal hole
    for each triangle in badTriangles do
        for each edge in triangle do
        if edge is not shared by any other triangles in badTriangles
    add edge to polygon

// remove them from the data structure
    for each triangle in badTriangles do
        remove triangle from triangulation

// re-triangulate the polygonal hole
    for each edge in polygon do
        newTri := form a triangle from edge to point
    add newTri to triangulation

// done inserting points, now clean up
    for each triangle in triangulation
    if triangle contains a vertex from original super-triangle
    remove triangle from triangulation

    return triangulation


}







int main() {
    SDL::initSDL();
    auto window = SDL::SDLWindow(800, 800);
    window.render();


    auto points = std::vector<SDL_Point>(100);
    for (auto& p : points) {
        p.x = std::rand() % 800;
        p.y = std::rand() % 800;
    }

    while(!handleEvents()) {
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(window.getRenderer());

        SDL_SetRenderDrawColor(window.getRenderer(), 255, 24, 140, 140);
        for (const auto p : points) {
            SDL::drawPoint(window, p, 2);
        }
        window.render();

    }



    SDL::cleanUpSDL(window.getWindow(), window.getRenderer());
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
