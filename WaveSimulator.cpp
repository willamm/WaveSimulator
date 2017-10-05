// WaveSimulator.cpp : Defines the entry point for the console application.
//

#include "WaveSolver.h"

void main() {

    WaveSolver<double> solver(15, 15);

    const int maxT = 10;

    solver.addRectangle(1, 1, 4, 4);

    /// Print velocity distribution
    solver.getVelocity().print();
    std::cout << " ========================= " << std::endl;

    /// Print initial condition
    solver.getField().print();

    /// Main timestepping loop
    for (int curT = 0; curT < maxT; ++curT) {
        solver.doTimestep();
        solver.getField().print();
    }

}