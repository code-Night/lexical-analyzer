/*
 * DFA_generator.h
 *
 *  Created on: Mar 27, 2016
 *      Author: ali  (codeNight)
 */
#include <iostream>
#include <set>
#include <stack>
#include <queue>

#include "automata.h"

using namespace std;

typedef set<state*>::iterator set_itr ;
typedef multimap<char,state*>::iterator map_itr ;
typedef pair<map_itr, map_itr > range ;

class DFA_generator {

public:
	DFA_generator(automata NFA,set<char> alphabet);
	automata subset_construction() ;
private:
	automata NFA;
	set<char> alphabet ;
	set<state*> eps_closure(state *s);
	set<state*> eps_closure(set<state*> t);
	set<state*> move(char x, set<state*> t);
	set<state*> get_eps_transations(state*s);

};
