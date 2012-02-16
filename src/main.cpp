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
//#include "tools.h"

int main(int argc, char *argv[]) {

    Input inputs;
    std::vector<std::vector<Node> > lattice = initialize_lattice(inputs);
    std::vector<std::vector<Node> > lattnew = initialize_lattice(inputs);

    for (int j = 0; j < inputs.ny+2; j++) {
        for (int i = 0; i < inputs.nx+2; i++) {
            std::cout << lattice[j][i].f[6] << " ";
        }
        std::cout << std::endl;
    }
    


//    std::vector<std::vector<Node> > lattnew = create_lattice(argc, argv);
//    double gradient(calculate_gradient(argc, argv));
//
//    // time loop
//    for (int timestep = 0; timestep < 100; timestep++) {
//        for (int j = 1; j < atoi(argv[2])+1; j++) {
//            for (int i = 1; i < atoi(argv[1])+1; i++) {
//                stream(lattice, lattnew, i, j);
//                lattnew[j][i].rho = lattice[j][i].calculate_density();
//                lattnew[j][i].u   = lattice[j][i].calculate_velocity();
//                lattnew[j][i].feq = lattice[j][i].calculate_feq();
//                lattnew[j][i].f   = lattice[j][i].feq;
//            }
//        }
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
