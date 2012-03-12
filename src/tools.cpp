/**
 * tools.cpp
 *
 * Various tools for my Lattice Boltzmann solver.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 5 March 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "input.h"
#include "node.h"

double get_max_norm(Input inputs,
                       std::vector<std::vector<Node> > &lattold,
                       std::vector<std::vector<Node> > &lattnew) {

    // Monitor max-norm of total velocity.
    double A(0.0), B(0.0), u(0.0), v(0.0);
    for (int j = 1; j < inputs.ny+1; j++) {
        for (int i = 1; i < inputs.nx+1; i++) {
            if (lattold[j][i].liquid == 1) {
                u = lattnew[j][i].u-lattold[j][i].u;
                v = lattnew[j][i].v-lattold[j][i].v;
                B = sqrt(u*u+v*v);
                if (B > A) A = B;
            }
        }
    }
    return A;
}

void write_gnuplot_files(Input inputs,
                         std::vector<std::vector<Node> > &lattice) {

    std::ofstream myfile;
    int x2 = inputs.nx/2;
    
    // data
    myfile.open("data.out");
    myfile.precision(16);
    for (int j = 1; j < inputs.ny+1; j++) {
        myfile << std::fixed << j << " " << lattice[j][x2].u << std::endl;
    }
    myfile.close();

    // gnuplot
    myfile.open("gnuplot.in");
    myfile << "set terminal postscript enhanced" << std::endl;
    myfile << "set output 'plot.ps'" << std::endl;
    myfile << "set title 'Centerline Velocity'" << std::endl;
    myfile << "set xlabel 'u'" << std::endl;
    myfile << "set ylabel 'y'" << std::endl;
    myfile << "set yrange[0:" << inputs.ny+1 << "]" << std::endl;
    myfile << "set ytics 1" << std::endl;
    myfile << "set grid" << std::endl;
    myfile << "unset key" << std::endl;
    myfile << "plot 'data.out' u 2:1 t 'u' w linespoints" << std::endl;
    myfile.close();
}

void write_matlab_files(Input inputs,
                        std::vector<std::vector<Node> > &lattice) {

    std::ofstream myfile;
    myfile.open("matlab.m");
    myfile.precision(16);
    
    // u
    myfile << "u = [" << std::endl;
    for (int j = 1; j < inputs.ny+1; j++) {
        for (int i = 1; i < inputs.nx+1; i++) {
            myfile << std::fixed << lattice[j][i].u << " ";
        }
        myfile << ";" << std::endl;
    }
    myfile << "];" << std::endl;

    // v
    myfile << "v = [" << std::endl;
    for (int j = 1; j < inputs.ny+1; j++) {
        for (int i = 1; i < inputs.nx+1; i++) {
            myfile << std::fixed << lattice[j][i].v << " ";
        }
        myfile << ";" << std::endl;
    }
    myfile << "];" << std::endl;

    // matlab
    myfile << "quiver(1:length(u), 1:length(v), u, v)" << std::endl;
    myfile.close();

//    // gnuplot
//    myfile.open("gnuplot.in");
//    myfile << "set terminal postscript enhanced" << std::endl;
//    myfile << "set output 'plot.ps'" << std::endl;
//    myfile << "set title 'Centerline Velocity'" << std::endl;
//    myfile << "set xlabel 'u'" << std::endl;
//    myfile << "set ylabel 'y'" << std::endl;
//    myfile << "set yrange[0:" << inputs.ny+1 << "]" << std::endl;
//    myfile << "set ytics 1" << std::endl;
//    myfile << "set grid" << std::endl;
//    myfile << "unset key" << std::endl;
//    myfile << "plot 'data.out' u 2:1 t 'u' w linespoints" << std::endl;
//    myfile.close();
}
