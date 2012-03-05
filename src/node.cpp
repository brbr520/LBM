/**
 * node.cpp
 *
 * Defines a class called node whith definitions for various properties.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 4 March 2012
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
    liquid = 1;
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
                            (cx*u+cy*v)*(cx*u+cy*v)/(2.0*cs2*cs2)-
                            (u*u+v*v)/(2.0*cs2));
    }
}

// catch-all function to update macroscopic properties of a node
void Node::update_macroscopic_properties(void) {
    calculate_density();
    calculate_velocity();
    calculate_feq();
}

// calculate density
void Node::calculate_density(void) {
    double temp_rho(0.0);
    for (int i = 0; i < 9; i++) {
        temp_rho += f[i];
    }
    rho = temp_rho;
}

// calculate velocity
void Node::calculate_velocity(void) {
    double cx, cy, temp_u(0.0), temp_v(0.0);
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
        temp_u += cx*f[i];
        temp_v += cy*f[i];
    }
    u = temp_u/rho;
    v = temp_v/rho;
}

// collision operator
void Node::collide(Input inputs) {
    for (int i = 0; i < 9; i++) {
        f[i] += inputs.omega*(feq[i]-f[i]);
    }
}

// update f with delta f
void Node::update_f(Input inputs) {
    for (int i = 0; i < 9; i++) {
        switch(i) {
            case 1:
            case 5:
            case 8:
                f[i] += inputs.gradient/6.0;
                break;
            case 3:
            case 6:
            case 7:
                f[i] -= inputs.gradient/6.0;
                break;
            default:
                break;
        }
    }
}
