/*
 * automata.h
 *
 *  Created on: Mar 23, 2016
 *      Author: ali
 */

#ifndef AUTOMATA_H_
#define AUTOMATA_H_
#include <vector>
#include "state.h"
using namespace std;

class automata {
public:
	automata();
	state * get_start_state ();
	void set_start_state(state *s);
	state * get_end_state();
	void set_end_state (state *s);
	int get_size();
	int add_state (state *s); // return the id of the currently added state ;


	vector<state*> graph;

private:

	int automata_size = 0 ;
	state * start_state;
	state * end_state;
};

#endif /* AUTOMATA_H_ */
