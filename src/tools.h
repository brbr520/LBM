/**
 * tools.h
 *
 * Various tools for my Lattice Boltzmann solver.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 5 March 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#ifndef TOOLS_H 
#define TOOLS_H

double get_max_norm(Input,
                    std::vector<std::vector<Node> > &,
                    std::vector<std::vector<Node> > &);
void write_gnuplot_files(Input,
                         std::vector<std::vector<Node> > &);

#endif
