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
    // constructor
    Node(Input inputs) {
        initialize(inputs);
    }

//    double calculate_density(void);
//    std::vector<double> calculate_velocity(void);

    private:
    double u, v, rho;
    std::vector<double> f, feq;
    void initialize(Input);
    void calculate_feq(void);
};

#endif
