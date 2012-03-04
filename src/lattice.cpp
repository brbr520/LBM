/**
 * lattice.cpp
 *
 * Defines a class called lattice whith definitions for various properties.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 16 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <vector>
#include "node.h"
#include "input.h"
#include "lattice.h"

// catch-all function to create a lattice and set ghost cells
std::vector<std::vector<Node> > initialize_lattice (Input inputs) {
    std::vector<std::vector<Node> > lattice;
    create_lattice(inputs, lattice);
    set_boundaries(inputs, lattice);
    return lattice;
}

// creates a lattice object out of node objects
void create_lattice(Input inputs,
                    std::vector<std::vector<Node> > &lattice) {
    for (int j = 0; j < inputs.ny+2; j++) {
        lattice.push_back(std::vector<Node>());
        for (int i = 0; i < inputs.nx+2; i++) {
            Node temp_node(inputs);
            lattice[j].push_back(temp_node);
        }
    }
}

// sets boundary conditions
void set_boundaries(Input inputs,
                    std::vector<std::vector<Node> > &lattice) {

    // periodic boundaries along the x direction, not counting corners
    for (int j = 1; j < inputs.ny+1; j++) {
        lattice[j][0].f = lattice[j][inputs.nx].f;
        lattice[j][inputs.nx+1].f = lattice[j][1].f;
    }

    // bounce back boundaries along the y direction, not counting corners
    for (int i = 1; i < inputs.nx+1; i++) {
        lattice[0][i].f[7] = lattice[1][i-1].f[5];
        lattice[0][i].f[4] = lattice[1][i].f[2];
        lattice[0][i].f[8] = lattice[1][i+1].f[6];
        lattice[inputs.ny+1][i].f[6] = lattice[inputs.ny][i-1].f[8];
        lattice[inputs.ny+1][i].f[2] = lattice[inputs.ny][i].f[4];
        lattice[inputs.ny+1][i].f[5] = lattice[inputs.ny][i+1].f[7];
    }

    // mixture of boundaries at the corners
    lattice[0][0].f[8] = lattice[1][1].f[6];
    lattice[0][inputs.nx+1].f[7] = lattice[1][inputs.nx].f[5];
    lattice[inputs.ny+1][0].f[5] = lattice[inputs.ny][1].f[7];
    lattice[inputs.ny+1][inputs.nx+1].f[6] = lattice[inputs.ny][inputs.nx].f[8];
}

// catch-all function to loop over every node and update properties
void update_nodes(Input inputs,
                  std::vector<std::vector<Node> > &lattice) {
    for (int j = 1; j < inputs.ny+1; j++) {
        for (int i = 1; i < inputs.nx+1; i++) {
            lattice[j][i].update_macroscopic_properties();
            lattice[j][i].collide(inputs);
        }
    }
}

// streaming operator
void stream(Input inputs,
            std::vector<std::vector<Node> > &lattold,
            std::vector<std::vector<Node> > &lattnew) {
    for (int j = 1; j < inputs.ny+1; j++) {
        for (int i = 1; i < inputs.nx+1; i++) {
            lattnew[j][i].f[0] = lattold[j  ][i  ].f[0];
            lattnew[j][i].f[1] = lattold[j  ][i+1].f[1];
            lattnew[j][i].f[2] = lattold[j+1][i  ].f[2];
            lattnew[j][i].f[3] = lattold[j  ][i-1].f[3];
            lattnew[j][i].f[4] = lattold[j-1][i  ].f[4];
            lattnew[j][i].f[5] = lattold[j+1][i+1].f[5];
            lattnew[j][i].f[6] = lattold[j+1][i-1].f[6];
            lattnew[j][i].f[7] = lattold[j-1][i-1].f[7];
            lattnew[j][i].f[8] = lattold[j-1][i+1].f[8];
//            lattnew[j  ][i  ].f[0] = lattold[j][i].f[0];
//            lattnew[j  ][i+1].f[1] = lattold[j][i].f[1];
//            lattnew[j+1][i  ].f[2] = lattold[j][i].f[2];
//            lattnew[j  ][i-1].f[3] = lattold[j][i].f[3];
//            lattnew[j-1][i  ].f[4] = lattold[j][i].f[4];
//            lattnew[j+1][i+1].f[5] = lattold[j][i].f[5];
//            lattnew[j+1][i-1].f[6] = lattold[j][i].f[6];
//            lattnew[j-1][i-1].f[7] = lattold[j][i].f[7];
//            lattnew[j-1][i+1].f[8] = lattold[j][i].f[8];
        }
    }
} // TODO flip the equations

// applies the forcing term G to f
void apply_forcing_term(Input inputs,
                        std::vector<std::vector<Node> > &lattice) {
    for (int j = 1; j < inputs.ny+1; j++) {
        for (int i = 1; i < inputs.nx+1; i++) {
            lattice[j][i].update_f(inputs);
        }
    }
}
