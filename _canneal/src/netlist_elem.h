// netlist_elem.h
//
// Created by Daniel Schwartz-Narbonne on 14/04/07.
//
// Copyright 2007 Princeton University
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.


#ifndef NETLIST_ELEM_H
#define NETLIST_ELEM_H

#include <string>
#include <vector>
#include <deque>

#include "AtomicPtr.h"
#include "location_t.h"
#include "annealer_types.h" 

#ifdef USE_VECTOR_INTRINSIC
#include "../../common/vector_defines.h"
#endif

using threads::AtomicPtr;

class netlist_elem{
public:	
	netlist_elem();
	routing_cost_t routing_cost_given_loc(location_t loc);

#ifdef USE_VECTOR_INTRINSIC
    void add_fanin_x(unsigned long *);
  void add_fanin_y(unsigned long *);
  void add_fanout_x(unsigned long *);
  void add_fanout_y(unsigned long *);
//	routing_cost_t swap_cost_vector(_MMR_i32 xAFanin_loc ,_MMR_i32 xBFanin_loc ,int a_fan_size);
  routing_cost_t swap_cost_vector(location_t* old_loc, location_t* new_loc);
#else // !USE_VECTOR_INTRINSIC
	routing_cost_t swap_cost(location_t* old_loc, location_t* new_loc);
#endif //USE_VECTOR_INTRINSIC
	
public:
	std::string item_name;
	std::vector<netlist_elem*> fanin;
	std::vector<netlist_elem*> fanout;
	AtomicPtr<location_t> present_loc;
	//std::deque<location_t *> fan_locs;
//    std::vector<unsigned long *> fanin_locs_x;
//    std::vector<unsigned long *> fanin_locs_y;
//    std::vector<unsigned long *> fanout_locs_x;
//    std::vector<unsigned long *> fanout_locs_y;
#ifdef USE_VECTOR_INTRINSIC
    unsigned long * fanin_locs_x;
    unsigned long * fanin_locs_y;
    unsigned long * fanout_locs_x;
    unsigned long * fanout_locs_y;
#endif
protected:
#ifdef USE_VECTOR_INTRINSIC
    int fanin_x_size = 0;
    int fanin_y_size = 0;
    int fanout_x_size = 0;
    int fanout_y_size = 0;
    int fanin_x_capacity = SPECIES_32;
    int fanin_y_capacity = SPECIES_32;
    int fanout_x_capacity = SPECIES_32;
    int fanout_y_capacity = SPECIES_32;
#endif
};


#endif

