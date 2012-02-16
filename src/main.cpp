/**
 * main.cpp
 *
 * This is a simple Lattice Boltzmann solver written for a class.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 16 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <iostream>
#include <vector>
#include "input.h"
#include "node.h"
#include "lattice.h"

int main(int argc, char *argv[]) {

    Input inputs;
    std::vector<std::vector<Node> > lattice = initialize_lattice(inputs);
    std::vector<std::vector<Node> > lattnew = initialize_lattice(inputs);

    // time loop
    for (int timestep = 0; timestep < inputs.nts_max; timestep++) {
        update_nodes(inputs, lattice);
        set_boundaries(inputs, lattice);
        stream(inputs, lattice, lattnew);
        apply_forcing_term(inputs, lattnew);
    }

//        if (check_convergence(lattice, lattnew, atoi(argv[1]), atoi(argv[2])) == true) {
//            std::cout << "conv reached after " << timestep << " steps" << std::endl;
//            break;
//        } else {
//            lattice = lattnew;
//            apply_boundary_conditions(lattice, argv); // check if this belongs HERE
//        }
//    }

    return EXIT_SUCCESS;
}
