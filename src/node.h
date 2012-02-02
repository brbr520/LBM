/**
 * node.h
 *
 * Defines a class called node whith definitions for various properties.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 02 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#ifndef NODE_H 
#define NODE_H

#include <vector>

class Node {
    public:
    double rho;
    std::vector<double> u, f, feq;
    Node(double u0, double v0, double rho0) {
        initialize(u0, v0, rho0);
        feq  = calculate_feq();     // homework 5
        f = feq;                    // homework 5
        rho = calculate_density();  // homework 5
        u = calculate_velocity();   // homework 5
    }
    double calculate_density(void);
    std::vector<double> calculate_velocity(void);
    std::vector<double> calculate_feq(void);

    private:
    void initialize(double, double, double);
};

#endif
