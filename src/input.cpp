/**
 * input.cpp
 *
 * Parses the LBM solver input file.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 5 March 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include "input.h"

void Input::parse(void) {
    std::ifstream input_file("lbm.in");
    if (input_file.is_open()) {
        std::string line, key, token, extra;
        while (getline(input_file, line)) {
            // read lines
            if (line == "") continue;       // skip blank lines
            std::stringstream iss(line);
            iss >> key >> token >> extra;   // tokenize
            if (key == "#") continue;       // skip comment lines
            // mesh parameters
            if      (key == "nx") nx = atoi(token.c_str());
            else if (key == "ny") ny = atoi(token.c_str());
            // fluid parameters
            else if (key == "u0") u0 = atof(token.c_str());
            else if (key == "v0") v0 = atof(token.c_str());
            else if (key == "rho0") rho0 = atof(token.c_str());
            else if (key == "umax") umax = atof(token.c_str());
            else if (key == "omega") omega = atof(token.c_str());
            // solver parameters
            else if (key == "nts_max") nts_max = atoi(token.c_str());
            else if (key == "epsilon") epsilon = atof(token.c_str());
            // porosity parameters
            else if (key == "porosity") {
                porosity = token;
                if (token != "none") radius = atof(extra.c_str());
            }
        }
    } else {
        std::cerr << "(-) ERROR: Input file not found!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Input::check(void) {
    // TODO
    // Eventually I will be a function to check my inputs for sanity.
}

double Input::calculate_gradient(void) {
    double mu(rho0*(1.0/omega-1.0/2.0)*(1.0/3.0));
    double temp_gradient(8.0*mu*umax/(ny*ny));
    return temp_gradient;
}
