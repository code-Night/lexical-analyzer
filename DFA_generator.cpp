/*
 * DFA_generator.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: ali (codeNight) #3la_wd3ey
 */

#include "DFA_generator.h"

DFA_generator::DFA_generator(automata NFA, set<char> alphabet) {
	this->NFA = NFA;
	this->alphabet = alphabet;

	this->alphabet.erase('#');
	cout << alphabet.size() << endl;
}

automata DFA_generator::subset_construction() {
	set<state*> start = eps_closure(NFA.get_start_state());
	queue<set<state*> > Dstate;
	map<set<state*>, int> set_id;
	Dstate.push(start);
	set_id[start] = 0;
	automata x;
	x.graph.pop_back();
	while (!Dstate.empty()) {
		set<state*> curr = (Dstate.front());
//		cout << "curr : ";
//		for (set_itr it = curr.begin(); it != curr.end(); it++) {
//			cout << (*it)->id << " ";
//		}
//		cout << endl;
		Dstate.pop();
		int curr_id = set_id[curr];
		state* curr_s = x.graph[curr_id];
		set<char>::iterator alphabet_it;
		for (alphabet_it = alphabet.begin(); alphabet_it != alphabet.end();
				alphabet_it++) {
//			cout << (*alphabet_it) << " nxt : ";
			set<state*> next = eps_closure(move((*alphabet_it), curr));
//			for (set_itr it = next.begin(); it != next.end(); it++) {
//				cout << (*it)->id << " ";
//			}
//			cout << endl;
			int nxt_id;
			state* nxt_s;
			if (set_id.find(next) == set_id.end()) {
				Dstate.push(next);
				state* s = new state();
				nxt_id = x.add_state(s);
				set_id[next] = nxt_id;
				curr_s->connect((*alphabet_it), s);
			} else {
				nxt_id = set_id[next];
				nxt_s = x.graph[nxt_id];
				curr_s->connect((*alphabet_it), nxt_s);
			}
		}

	}
	// before you return , loop on the available sets
	// and modify the acceptance state using priorities
	// note that priorities should be input to the DFA generator
	map<set<state*>, int>::iterator it;
	cout << "final size" << set_id.size() << endl;
	for(int i=0 ; i<x.graph.size() ; i++){
		state* s = x.graph[i] ;
		cout << s->id << " " ;
		for(map_itr it = s->next.begin() ; it!= s->next.end() ; it++){
			cout << it->first << " " << it->second->id << " ";
		}
		cout << endl ;
	}

//	for (it = set_id.begin(); it != set_id.end(); it++) {
//		vector<string> acceptence;
////		cout << it->second << " : ";
//		for (set_itr j = it->first.begin(); j != it->first.end(); it++) {
//			if ((*j)->get_acceptence()) {
//				acceptence.push_back((*j)->get_token_type());
//				cout << (*j)->get_token_type() << " ";
//			}
//		}
//		cout << endl;
//	}
	return x;
}
set<state*> DFA_generator::get_eps_transations(state* s) {

	set<state*> ans;

	range r = s->next.equal_range('#');
	for (map_itr it = r.first; it != r.second; it++) {

		ans.insert(it->second);
	}

//	cout << "out " << endl ;
	return ans;
}

set<state*> DFA_generator::eps_closure(state *s) {
//	cout << "in state eps" << endl ;
//	cout << s->id << endl ;
	queue<state*> q;
	set<state*> ans;

	q.push(s);

	set<int> visited;

	while (!q.empty()) {
//		cout << q.size() << " " << endl;
		state* curr = q.front();
		set<state*> trans = get_eps_transations(curr);
		ans.insert(q.front());
		q.pop();
		for (set_itr it = trans.begin(); it != trans.end(); it++) {

			if (visited.find((*it)->id) == visited.end()) {
				q.push(*it);
				visited.insert((*it)->id);
			}
		}
	}
//	cout << "out state eps" << endl ;
	return ans;
}

set<state*> DFA_generator::eps_closure(set<state*> t) {
//	cout << "in set eps" << endl ;
	set<state*> ans;
	int i = 0;
	for (set_itr it = t.begin(); it != t.end(); it++) {
//		cout << ++i << endl ;
		set<state*> tmp = eps_closure(*it);
		for (set_itr it2 = tmp.begin(); it2 != tmp.end(); it2++) {
			ans.insert(*it2);
		}
	}
	return ans;
}

set<state*> DFA_generator::move(char x, set<state*> t) { // done
//	cout << "in move" << endl ;
	set<state*> ans;
	for (set_itr it = t.begin(); it != t.end(); it++) {
		range r = (*it)->get_neighbors().equal_range(x);
		for (map_itr it2 = r.first; it2 != r.second; it2++){
			ans.insert(it2->second);
		}
	}
	return ans;
}
