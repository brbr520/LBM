/**
 * tools.cpp
 *
 * Various tools for my Lattice Boltzmann solver.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 16 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <vector>
#include <cmath>
#include "input.h"
#include "node.h"
#include <iostream>

bool check_convergence(Input inputs,
                       std::vector<std::vector<Node> > &lattold,
                       std::vector<std::vector<Node> > &lattnew) {

    // I think for convergence I can just monitor the density.
    double row_norm(0.0), total_norm(0.0), temp(0.0);
    for (int j = 1; j < inputs.ny+1; j++) {
        for (int i = 1; i < inputs.nx+1; i++) {
            temp = lattnew[j][i].rho-lattold[j][i].rho;
            row_norm += temp*temp;
        }
        total_norm += row_norm;
        row_norm = 0.0;
    }
    total_norm = sqrt(total_norm);
    std::cout << total_norm << std::endl;
    bool converged(false);
    if (total_norm <= inputs.epsilon) {
        converged = true;
    }
    return converged;
}

