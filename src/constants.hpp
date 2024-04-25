#pragma once

const double DOUBLE_INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double deg_to_rad(double deg) {
    return deg * PI / 180;
}