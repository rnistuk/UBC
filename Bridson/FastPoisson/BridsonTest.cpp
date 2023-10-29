#include "Bridson.h"
#include <gtest/gtest.h>

TEST(BridsonTest, test_makeGrid) {
    // Arrange
    int** sut {nullptr};
    size_t cols {100};
    size_t rows {25};

    // Act
    sut = Bridson::makeGrid(cols, rows);

    // Assert
    EXPECT_NE(nullptr, sut);

    for (size_t r {0} ; r < rows ; ++r) {
        for (size_t c {0} ; c < cols ; ++c) {
            EXPECT_EQ(-1, sut[c][r]);
        }
    }

    Bridson::deleteGrid(cols, sut);
}

TEST(BridsonTest, test_getDistance) {
    // Arrange
    int x1 { 0 };
    int y1 { 0 };
    int x2 { 87 };
    int y2 { 430 };

    // Act
    double d { Bridson::getDistance(x1, y1, x2, y2)};

    // Assert
    EXPECT_FLOAT_EQ(::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)), d);
}

TEST(BridsonTest, test_SDL_PointgetDistance) {
    // Arrange
    SDL_Point X1 { 0, 0};
    SDL_Point X2 { 450, 650};

    // Act
    double d { Bridson::getDistance(X1, X2)};

    // Assert
    EXPECT_FLOAT_EQ(::sqrt((X2.x-X1.x)*(X2.x-X1.x) + (X2.y-X1.y)*(X2.y-X1.y)), d);
}

TEST(BridsonTest, test_randomAnnularPoints) {
    // Arrange
    const SDL_Point O { 0, 0};
    const int r { 100 };
    Bridson::initializeTrigFunctions();

    // Act
    std::vector<SDL_Point> points(10000);
    for(auto& p : points) {
        p = Bridson::randomAnnularPoint(O,r);
    }

    // Assert
    for(auto& p : points) {
        auto dx = (double)(p.x);
        auto dy = (double)(p.y);
        auto d {::sqrt(dx*dx + dy*dy)};
        EXPECT_LT(r, d) << p.x << ":" << p.y;
    }


}
