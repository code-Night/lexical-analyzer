/*
 * NFA_generator.h
 *
 *  Created on: Mar 25, 2016
 *      Author: ali
 */

#include "automata.h"
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <stack>
#include <set>
using namespace std ;
class NFA_generator {
public:
	NFA_generator(vector< vector<string> > expression,  vector<string> keywords, vector<string> punct);
	automata final_NFA () ;
	set<char> alphabet ;
private:

	vector < vector<string> > regular_expressions;
	vector<string> keywords;
	vector<string> punctuation;
	map<string,int> operations_priority ;
	vector<automata> all_automata ;
	void keywords_automatas (vector <string> keywords) ;
	void punctuation_automatas(vector <string> automatas) ;
	void expression_automata_generator () ;
	automata string_to_automata (string s);
	automata zero_or_more(automata a);
	automata concatenate(automata a,automata b);
	automata Or (automata a,automata b);
};

