/**
 * tools.cpp
 *
 * Various tools for my Lattice Boltzmann solver.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 02 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <iostream>
#include <vector>
#include "tools.h"

// checks if enough inputs are passed as arguments
void check_input(int argc) {
    switch (argc) {
        case 4:
        case 7:
        break;
        default:
        std::cout << std::endl;
        std::cout << "USAGE\t";
        std::cout << "\t./lbm [nx] [ny] [ts] [u0] [v0] [rho0]" << std::endl;
        std::cout << std::endl;
        std::cout << "nx\trequired\t number of nodes in x direction" << std::endl;
        std::cout << "ny\trequired\t number of nodes in y direction" << std::endl;
        std::cout << "ts\trequired\t number of time steps" << std::endl;
        std::cout << "u0\toptional\t initial u (default 1.0)" << std::endl;
        std::cout << "v0\toptional\t initial v (default 1.0)" << std::endl;
        std::cout << "rho0\toptional\t initial rho (default 1.0)" << std::endl;
        std::cout << std::endl;
        exit(EXIT_FAILURE);
    }
}

// creates and initializes my lattice
std::vector<std::vector<Node> > create_lattice(int argc, char *argv[]) {

    // tokenize argv and defaults
    int nx = atoi(argv[1]);
    int ny = atoi(argv[2]);
    double u0(1.0), v0(1.0), rho0(1.0);
    switch (argc) {
        case 7:
            u0 = atof(argv[4]);
            v0 = atof(argv[5]);
            rho0 = atof(argv[6]);
            break;
    }

    // construct lattice
    std::vector<std::vector<Node> > lattice;
    for (int j = 0; j < ny+2; j++) {
        lattice.push_back(std::vector<Node>());
        for (int i = 0; i < nx+2; i++) {
            Node temp_node(u0, v0, rho0);
            lattice[j].push_back(temp_node);
        }
    }

    return lattice;
}

// apply boundary conditions
void apply_boundary_conditions(std::vector<std::vector<Node> > &system,
                               char *argv[]) {
    // tokenize argv
    int nx = atoi(argv[1]);
    int ny = atoi(argv[2]);

    // left and right ghost points, not counting corners
    for (int j = 1; j < ny+1; j++) {
        system[j][0   ].u[0] = -system[j][nx].u[0];
        system[j][0   ].u[1] = -system[j][nx].u[1];
        system[j][nx+1].u[0] = -system[j][1 ].u[0];
        system[j][nx+1].u[1] = -system[j][1 ].u[1];
    }

    // top and bottom ghost points, not counting corners
    for (int i = 1; i < nx+1; i++) {
        system[0   ][i].u[0] = -system[ny][i].u[0];
        system[0   ][i].u[1] = -system[ny][i].u[1];
        system[ny+1][i].u[0] = -system[1 ][i].u[0];
        system[ny+1][i].u[1] = -system[1 ][i].u[1];
    }

    // corners
    system[0   ][0   ].u[0] = -system[ny][nx].u[0];
    system[0   ][0   ].u[1] = -system[ny][nx].u[0];
    system[0   ][nx+1].u[0] = -system[ny][1 ].u[0];
    system[0   ][nx+1].u[1] = -system[ny][1 ].u[0];
    system[ny+1][nx+1].u[0] = -system[1 ][1 ].u[0];
    system[ny+1][nx+1].u[1] = -system[1 ][1 ].u[0];
    system[ny+1][0   ].u[0] = -system[1 ][nx].u[0];
    system[ny+1][0   ].u[1] = -system[1 ][nx].u[0];
}

// streaming operator
void stream(std::vector<std::vector<Node> > &system, int i, int j) {
    /*0*/ system[j  ][i  ].f[0] = system[j][i].f[0];
    /*1*/ system[j  ][i+1].f[1] = system[j][i].f[1];
    /*2*/ system[j+1][i  ].f[2] = system[j][i].f[2];
    /*3*/ system[j  ][i-1].f[3] = system[j][i].f[3];
    /*4*/ system[j-1][i  ].f[4] = system[j][i].f[4];
    /*5*/ system[j+1][i+1].f[5] = system[j][i].f[5];
    /*6*/ system[j+1][i-1].f[6] = system[j][i].f[6];
    /*7*/ system[j-1][i-1].f[7] = system[j][i].f[7];
    /*8*/ system[j-1][i+1].f[8] = system[j][i].f[8];

    // But, is this correct?
    // I would think sys[j][i].f[6] --> sys[j+1][i-1].f[8]
    // Or not?

    // TODO
    // Also, this isn't efficient, to be calling this function so many
    // times in the context of the two loops. Maybe I can pass on the
    // loops inside here but we need to see what the last assignment
    // is.
}

// collision operator
std::vector<double> collision(std::vector<std::vector<Node> > &system,
                              int i, int j, double omega) {
    std::vector<double> c_out;
    c_out.resize(9);
    for (int k = 0; k < 9; k++) {
        c_out[k] = omega*(system[j][i].feq[k]-system[j][i].f[k]);
    }
    return c_out;
}
