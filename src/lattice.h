/**
 * lattice.h
 *
 * Defines a class called lattice whith definitions for various properties.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 16 February 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#ifndef LATTICE_H 
#define LATTICE_H

std::vector<std::vector<Node> > initialize_lattice(Input);
void create_lattice(Input, std::vector<std::vector<Node> > &);
void set_boundaries(Input, std::vector<std::vector<Node> > &);
void update_nodes(Input, std::vector<std::vector<Node> > &);

#endif
