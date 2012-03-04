/**
 * lattice.h
 *
 * Defines a class called lattice whith definitions for various properties.
 *
 * Eric Chen (eric.chen@rwth-aachen.de)
 * Updated 4 March 2012
 *
 * Released under the MIT License, see included LICENSE file for more info.
 */

#ifndef LATTICE_H 
#define LATTICE_H

std::vector<std::vector<Node> > initialize_lattice(Input);
void create_lattice(Input, std::vector<std::vector<Node> > &);
void set_boundaries(Input, std::vector<std::vector<Node> > &);
void update_nodes(Input, std::vector<std::vector<Node> > &);
void stream(Input,
            std::vector<std::vector<Node> > &,
            std::vector<std::vector<Node> > &);
void apply_forcing_term(Input, std::vector<std::vector<Node> > &);
void copy_force_velocity(Input,
                         std::vector<std::vector<Node> > &,
                         std::vector<std::vector<Node> > &);

#endif
