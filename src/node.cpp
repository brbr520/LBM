/**
 * node.cpp
 *
 * Defines a class called node whith definitions for various properties.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 02 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <iostream>
#include "node.h"

void Node::initialize(double u0, double v0, double rho0) {
    u.resize(2);
    f.resize(9);
    feq.resize(9);
    u[0] = u0;
    u[1] = v0;
    rho = rho0;
}

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

// calculate feq
std::vector<double> Node::calculate_feq(void) {
    std::vector<double> force;
    force.resize(9);
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
        force[i] = w*rho*(1.0+(cx*u[0]+cy*u[1])/cs2+
                              (cx*u[0]+cy*u[1])*(cx*u[0]+cy*u[1])/(2*cs2*cs2)-
                              (u[0]*u[0]+u[1]*u[1])/(2*cs2));
    }
    return force;
}

/*  // force calculation not yet implemented (not required for ex 5/6)
std::vector<double> calculate_force(std::vector<std::vector<Node> > &old_system,
                                    std::vector<std::vector<Node> > &new_system,
                                    int i, int j, double omega) {
    new_system[j][i].f
*/
