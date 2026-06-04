#include <iostream>
#include <vector>
#include <sstream>




std::string report(const std::vector<double>& x) {
    std::stringstream ss;
    for (double v : x) {
        ss << v << ", ";
    }
    return  ss.str();
}


int main() {
    std::vector<double> s { 1.4f, 0.20f, 0.50f, 0.9f};
    double D = 0.2;
    std::vector<double> a_rate { 0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<double> a { 1.0f, 1.0f, 1.0f, 1.0f};

    double t {0};
    double dt {0.05};

    while (t<10.0) {
        for (int i{0}; i<a.size(); ++i) {
            a_rate[i] = (i>0 ? a[i-1] * a[i] : a[a.size()-1] * a[i]) - ( i+1 < a.size() ? a[i]*a[i+1] : a[i]*a[0]) + D * (s[i] - a[i]);
        }

        for (int i{0}; i<a.size(); ++i) {
            a[i] += a_rate[i] * dt;
        }

        std::cout<< t << "," /*<< report(a_rate) */<< report(a) << std::endl;

        t += dt;

    }











    return 0;
}

