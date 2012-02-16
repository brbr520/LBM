/**
 * input.h
 *
 * Parses the LBM solver input file.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 15 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#ifndef INPUT_H
#define INPUT_H

class Input {
    public:
    // mesh parameters
    int nx;             // number of nodes in the x direction
    int ny;             // number of nodes in the y direction
    // fluid parameters
    double u0;          // initial u velocity
    double v0;          // initial v velocity
    double rho0;        // initial density
    double umax;        // maximum velocity
    double omega;       // what am I called again?
    // solver parameters
    int nts_max;        // maximum number of time steps before abort
    double epsilon;     // convergence criteria
    // derived values
    double gradient;    // pressure gradient

    // constructor
    Input() {
        parse();
        gradient = calculate_gradient();
    }

    private:
    void parse(void);
    void check(void);
    double calculate_gradient(void);
};

#endif
