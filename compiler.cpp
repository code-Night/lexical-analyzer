//============================================================================
// Name        : compiler.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include "automata.h"
#include "rules_parcer.h"
#include "NFA_generator.h"
#include "DFA_generator.h"




//#include "DFA_generator.h"
using namespace std;

int main() {
	rules_parcer *rp = new rules_parcer();
	rp->parce();
	NFA_generator * nfa = new NFA_generator(rp->get_regular_expressions(),rp->get_keywords(),rp->get_punctuation());
	automata final = nfa->final_NFA();
	DFA_generator * dfa = new DFA_generator(final , nfa->alphabet);
	cout << "going to DFA" << endl ;
	dfa->subset_construction();
//	for (int i = 0; i < final.graph.size(); i++) {
//		//		cout << final.graph[i]->id << endl;
//		state *curr = final.graph[i];
////		if (curr->get_acceptence())
////			cout << "this is acceptence state " << curr->id << " "
////					<< curr->get_token_type() << endl;
//		multimap<char, state*> n = curr->get_neighbors();
//		multimap<char, state*>::iterator it = n.begin();
//		cout << curr->id << endl;
//		cout << " " << n.size() << " " ;
//		for (it; it != n.end(); it++) {
//			cout << it->first << " " << it->second->id << " ";
//		}
//
//		cout << endl;
//	}
//	set<char>::iterator itr = nfa->alphabet.begin();
//	cout << "  ========================       \n" ;
//	for(itr ; itr!= nfa->alphabet.end() ; itr++)
//		cout << *itr << endl ;
//	cout << "done" << endl ;
//	automata x;
//	vector<automata> mp;
//	for (int i = 0; i < 26; i++) {
//		char cr = 'a' + i;
//		automata *curr = new automata();
//		curr->get_start_state()->connect(cr, curr->get_end_state());
//		mp.push_back(*curr);
//
//	}
//
//	// ====================== joining these automatas =====================
//	automata final;
//	for (int k = 0; k < 26; k++) {
//		automata *curr = &mp[k];
//		for (int j = 0; j < curr->graph.size(); j++) {
//			state *s = (curr->graph[j]);
//			final.add_state(s);
//
//		}
//		final.get_start_state()->connect('%', curr->get_start_state());
//		curr->get_end_state()->connect('%', final.get_end_state());
//	}

//	for (int i = 0; i < final.graph.size(); i++) {
////		cout << final.graph[i]->id << endl;
//		state *curr = final.graph[i];
//		multimap<char, state*> n = curr->get_neighbors();
//		multimap<char, state*>::iterator it = n.begin();
//		cout << curr->id << endl;
//		for (it; it != n.end(); it++) {
//			cout << it->first << " " << it->second->id << endl;
//		}
//	}
	return 0;
}
