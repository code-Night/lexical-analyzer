/*
 * automata.cpp
 *
 *  Created on: Mar 23, 2016
 *      Author: ali hafez el ga7ed
 */


/*
 * this class it the most dangerous class as it only has pointers
 *
 */
#include "automata.h"

automata::automata (){
	state *start = new state();
	state *end = new state();
	add_state(start);
	start_state = start ;
	add_state(end);
	end_state = end ;
}

void automata::set_start_state(state *s){
	this->start_state = s ;
}

void automata::set_end_state(state *s){
	this->end_state = s;
}

state* automata::get_start_state(){
	return start_state ;
}
state* automata::get_end_state(){
	return end_state ;
}
int automata::get_size(){
	return automata_size ;
}
/*
 * this method adds the new state to the graph
 * and return the id of the currently node
 * ex
 * state x ;
 * automata gr;
 * int id = gr.add(x) ;
 * this returns the id of this node in the graph
 * state just_inserted = gr[id] ;
 * just_inserted is x ;
 *
 * so if you want to get
 *
 */
int automata::add_state(state *s){
	s->id = graph.size();
	graph.push_back(s);
	automata_size++;
	return s->id ;
}
