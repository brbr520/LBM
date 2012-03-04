/**
 * main.cpp
 *
 * This is a simple Lattice Boltzmann solver written for a class.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 4 March 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <iostream>
#include <vector>
#include "input.h"
#include "node.h"
#include "lattice.h"
#include "tools.h"

int main(int argc, char *argv[]) {

    Input inputs;
    std::vector<std::vector<Node> > lattice = initialize_lattice(inputs);
    std::vector<std::vector<Node> > lattnew = initialize_lattice(inputs);
    double converged(1.0);

    // time loop
    for (int timestep = 0; timestep < inputs.nts_max; timestep++) {
        update_nodes(inputs, lattice);
        set_boundaries(inputs, lattice);
        stream(inputs, lattice, lattnew);
        apply_forcing_term(inputs, lattnew);


        converged = get_max_norm(inputs, lattice, lattnew);
        if ((converged <= inputs.epsilon) && timestep != 0) {
            break;
        } else {
            copy_force_velocity(inputs, lattice, lattnew);
        }

        // remove me later
        std::cout.precision(16);
        std::cout << timestep << " " << converged << std::endl;
    }

    for (int j = 1; j < inputs.ny+1; j++) {
        std::cout.precision(16);
        std::cout << std::fixed << lattice[j][inputs.nx/2].u << std::endl;
    }

    write_gnuplot_files(inputs, lattice);

    return EXIT_SUCCESS;
}
