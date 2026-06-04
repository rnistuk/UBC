#include <iostream>
#include <sstream>

namespace {
    const double sigma = 5.670374419e-8;
}

double stephanBoltzmannTemperature(double F) {
    return ::pow(F/sigma,1.0/4.0);
}

double KToC(double K) {
    return K-273.15;
}

std::string reportTemp(double t_k) {
    std::stringstream ss;
    ss << t_k << " °K (" << KToC(t_k) << " °C)";
    return ss.str();
}

int main() {
    std::cout << "Energy Balance\n";
    double F_emits {0.06};
    double F_sun {341.0};

    double T = { stephanBoltzmannTemperature(F_emits) };
    std::cout << "\tNo Sun - Earth emits "<< F_emits << " W/m^2 -> " << reportTemp(T) << "\n\n";

    std::cout << "\tWith Sun - at equilibrium Earth absorbs "<< F_sun <<"W/m^2 and emits " << F_emits << "W/m^2\n";
    T = stephanBoltzmannTemperature(F_sun - F_emits);
    std::cout << "\t\t " << F_sun - F_emits << " W/m^2 -> " << reportTemp(T) <<"\n\n";


    std::cout << "\tTurn on reflection: Earth reflects ~30% of Suns influx\n";
    double F { 341-0.06 - 0.3*341.0  };
    T = stephanBoltzmannTemperature(F);
    std::cout << "\t\tAt Equilibrium: " << F << " W/m^2 -> " << reportTemp(T) << "\n\n";

    std::cout << "\tAdd Greenhouse Gases:\n";
    std::cout << "\t\tGHG absorb all Earth emission (239 W/m^2 + 0.06 W/m^2)\n";
    std::cout << "\t\tSolar inflow(341 W/m^2 - 30% of  341 W/m^2) = 239 W/m^2\n";
    std::cout << "\t\tWe assume downward emission of GHG equals upward emission (239 W/m^2)\n";
    std::cout << "\t\tSo the earth absorbs 239 W/m^2 from atmosphere and 239 W/m^2 from Sun\n";
    F = 2.0*239.0-0.06;
    std::cout << "\t\tAt equilibrium the earth must emit " << F << " W/m^2\n";
    T = stephanBoltzmannTemperature(F);
    std::cout << "\t\tAt equilibrium: " << F << " W/m^2 -> " << reportTemp(T) <<"\n\n";

    return 0;
}