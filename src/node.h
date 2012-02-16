/**
 * node.h
 *
 * Defines a class called node whith definitions for various properties.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 16 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#ifndef NODE_H 
#define NODE_H

#include "input.h"

class Node {
    public:
    std::vector<double> f, feq;
    Node(Input inputs) {
        initialize(inputs);
    }
    void update_macroscopic_properties(void);
    void collide(Input);

    private:
    double u, v, rho;
    void initialize(Input);
    void calculate_feq(void);
    void calculate_density(void);
    void calculate_velocity(void);
};

#endif
