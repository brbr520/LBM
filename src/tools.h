/**
 * tools.h
 *
 * Various tools for my Lattice Boltzmann solver.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 02 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#ifndef TOOLS_H 
#define TOOLS_H

#include "node.h"

void check_input(int);
std::vector<std::vector<Node> > create_lattice(int, char *[]);
void apply_boundary_conditions(std::vector<std::vector<Node> > &, char *[]);
void stream(std::vector<std::vector<Node> > &, int, int);
std::vector<double> collision(std::vector<std::vector<Node> > &, int, int, double);

#endif
