/**
 * main.cpp
 *
 * This is a simple Lattice Boltzmann solver written for a class.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 02 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <iostream>
#include <vector>
#include "tools.h"
#include "node.h"

int main(int argc, char *argv[]) {

    check_input(argc);
    std::vector<std::vector<Node> > lattice = create_lattice(argc, argv);
    std::vector<std::vector<Node> > lattnew = create_lattice(argc, argv);

    // print out initial state for homework
    // these will be removed but are shown here to prove that i did
    // the assignment correctly
    std::cout << "printing u ..." << std::endl;
    for (int j = 0; j < atoi(argv[2])+2; j++) {
        for (int i = 0; i < atoi(argv[1])+2; i++) {
            std::cout << lattice[j][i].u[0] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "printing v ..." << std::endl;
    for (int j = 0; j < atoi(argv[2])+2; j++) {
        for (int i = 0; i < atoi(argv[1])+2; i++) {
            std::cout << lattice[j][i].u[1] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "printing rho ..." << std::endl;
    for (int j = 0; j < atoi(argv[2])+2; j++) {
        for (int i = 0; i < atoi(argv[1])+2; i++) {
            std::cout << lattice[j][i].rho << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // time loop
    for (int timestep = 0; timestep < 100; timestep++) {
        apply_boundary_conditions(lattice, argv);
        apply_boundary_conditions(lattnew, argv);
        for (int j = 1; j < atoi(argv[2])+1; j++) {
            for (int i = 1; i < atoi(argv[1])+1; i++) {
                stream(lattice, i, j);
                lattnew[j][i].rho = lattice[j][i].calculate_density();
                lattnew[j][i].u   = lattice[j][i].calculate_velocity();
                lattnew[j][i].feq = lattice[j][i].calculate_feq();
                lattnew[j][i].f   = lattice[j][i].feq;
            }
        }
        lattice = lattnew;
    }
    
    // print out final state for homework
    // these will be removed but are shown here to prove that i did
    // the assignment correctly
    std::cout << "printing u ..." << std::endl;
    for (int j = 0; j < atoi(argv[2])+2; j++) {
        for (int i = 0; i < atoi(argv[1])+2; i++) {
            std::cout << lattice[j][i].u[0] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "printing v ..." << std::endl;
    for (int j = 0; j < atoi(argv[2])+2; j++) {
        for (int i = 0; i < atoi(argv[1])+2; i++) {
            std::cout << lattice[j][i].u[1] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "printing rho ..." << std::endl;
    for (int j = 0; j < atoi(argv[2])+2; j++) {
        for (int i = 0; i < atoi(argv[1])+2; i++) {
            std::cout << lattice[j][i].rho << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Note! The velocities are different, because they" << std::endl;
    std::cout << "were called before the boundary conditions were" << std::endl;
    std::cout << "applied! i.e., these are the initialized values." << std::endl;

    return EXIT_SUCCESS;
}
