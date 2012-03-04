/**
 * tools.cpp
 *
 * Various tools for my Lattice Boltzmann solver.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 16 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <vector>
#include <cmath>
#include "input.h"
#include "node.h"
#include <iostream>
#include <fstream>

double get_max_norm(Input inputs,
                       std::vector<std::vector<Node> > &lattold,
                       std::vector<std::vector<Node> > &lattnew) {

    // I'll just monitor the x-velocity via max-norm.
    double A(0.0), B(0.0);
    for (int j = 1; j < inputs.ny+1; j++) {
        for (int i = 1; i < inputs.nx+1; i++) {
            B = fabs(lattnew[j][i].u-lattold[j][i].u);
            if (B > A) A = B;
        }
    }
    return A;
}

void write_gnuplot_file(Input inputs,
                        std::vector<std::vector<Node> > &lattice) {
    std::ofstream myfile;
    
    // data
    myfile.open ("data.out");
    myfile << "# y  u" << std::endl;
    for (int j = 1; j < inputs.ny+1; j++) {
        myfile.precision(16);
        myfile << std::fixed << j-1 << " " << lattice[j][inputs.nx/2].u << std::endl;
    }
    myfile.close();

    // gnuplot
    myfile.open("gnuplot.in");
    myfile << "set terminal x11" << std::endl;
    myfile << "set title 'Centerline Velocity'" << std::endl;
    myfile << "set xlabel 'u'" << std::endl;
    myfile << "set ylabel 'y'" << std::endl;
    myfile << "plot 'data.out' u 2:1 t 'u' w linespoints" << std::endl;
    myfile.close();
}
