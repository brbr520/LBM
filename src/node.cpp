/**
 * node.cpp
 *
 * Defines a class called node whith definitions for various properties.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 16 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <iostream>
#include <vector>
#include "node.h"

// initialize Node object with inputs
void Node::initialize(Input inputs) {
    u = inputs.u0;
    v = inputs.v0;
    rho = inputs.rho0;
    f.resize(9);
    feq.resize(9);
    calculate_feq();
    f = feq;
}

// calculate feq
void Node::calculate_feq(void) {
    double cx, cy, w, cs2(1.0/3.0);
    for (int i = 0; i < 9; i++) {
        switch (i) {
            case 0:
                cx = 0.0;
                cy = 0.0;
                w = 4.0/9.0;
                break;
            case 1:
                cx = 1.0;
                cy = 0.0;
                w = 1.0/9.0;
                break;
            case 2:
                cx = 0.0;
                cy = 1.0;
                w = 1.0/9.0;
                break;
            case 3:
                cx = -1.0;
                cy = 0.0;
                w = 1.0/9.0;
                break;
            case 4:
                cx = 0.0;
                cy = -1.0;
                w = 1.0/9.0;
                break;
            case 5:
                cx = 1.0;
                cy = 1.0;
                w = 1.0/36.0;
                break;
            case 6:
                cx = -1.0;
                cy = 1.0;
                w = 1.0/36.0;
                break;
            case 7:
                cx = -1.0;
                cy = -1.0;
                w = 1.0/36.0;
                break;
            case 8:
                cx = 1.0;
                cy = -1.0;
                w = 1.0/36.0;
                break;
        }
        feq[i] = w*rho*(1.0+(cx*u+cy*v)/cs2+
                            (cx*u+cy*v)*(cx*u+cy*v)/(2*cs2*cs2)-
                            (u*u+v*v)/(2*cs2));
    }
}

/*
// calculate density
double Node::calculate_density(void) {
    double rho(0.0);
    for (int i = 0; i < 9; i++) {
        rho += f[i];
    }
    return rho;
}

// calculate velocity
std::vector<double> Node::calculate_velocity(void) {
    std::vector<double> velocity;
    velocity.resize(2);
    double cx, cy;
    for (int i = 0; i < 9; i++) {
        switch (i) {
            case 0:
                cx = 0.0;
                cy = 0.0;
                break;
            case 1:
                cx = 1.0;
                cy = 0.0;
                break;
            case 2:
                cx = 0.0;
                cy = 1.0;
                break;
            case 3:
                cx = -1.0;
                cy = 0.0;
                break;
            case 4:
                cx = 0.0;
                cy = -1.0;
                break;
            case 5:
                cx = 1.0;
                cy = 1.0;
                break;
            case 6:
                cx = -1.0;
                cy = 1.0;
                break;
            case 7:
                cx = -1.0;
                cy = -1.0;
                break;
            case 8:
                cx = 1.0;
                cy = -1.0;
                break;
        }
        velocity[0] += cx*f[i];
        velocity[1] += cy*f[i];
    }
    velocity[0] /= rho;
    velocity[1] /= rho;
    return velocity;
}

*/
/*  // force calculation not yet implemented (not required for ex 5/6)
std::vector<double> calculate_force(std::vector<std::vector<Node> > &old_system,
                                    std::vector<std::vector<Node> > &new_system,
                                    int i, int j, double omega) {
    new_system[j][i].f
*/
