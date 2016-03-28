/*
 * rules_parcer.h
 *
 *  Created on: Mar 24, 2016
 *      Author: ali
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <stack>

#include "automata.h"

using namespace std ;


class rules_parcer{
public :
	rules_parcer();
	void parce(); // reads each line of input and calls postfix
	vector< vector<string> > get_regular_definitions () ;
	vector< vector<string> > get_regular_expressions () ;
	vector <string> get_keywords () ;
	vector <string> get_punctuation() ;

private :

	set<string> reserved_characters ;

	vector< vector<string> > regular_definitions ;

	map <string,vector<string> > def_map ;
	vector < vector<string> > regular_expressions ;
	vector <string> keywords ;
	vector <string> punctuation ;

	map<string,int> op_priority ;

	vector <string> to_postfix (vector<string> x);
	vector <string> break_rule (string rule) ; // break rule string into some tokens
	vector <string> insert_concate (vector <string> x) ;
	vector <string> parcing_keywords (string rule);
	vector <string> parcing_punctuation (string rule) ;

	vector<string> subsitiue_for_definition(vector<string> victim) ;


	vector<string> cleanUP(vector<string> regex) ; // to remove any / from the exp
	vector<string> replace_plus(vector<string> x) ;
	vector<string> replace_minus(vector<string> x) ;


};


