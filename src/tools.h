/**
 * tools.h
 *
 * Various tools for my Lattice Boltzmann solver.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 16 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#ifndef TOOLS_H 
#define TOOLS_H

bool check_convergence(Input inputs,
                       std::vector<std::vector<Node> > &,
                       std::vector<std::vector<Node> > &);

#endif
