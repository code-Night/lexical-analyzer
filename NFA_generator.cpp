/*
 * NFA_generator.cpp
 *
 *  Created on: Mar 25, 2016
 *      Author: ali
 */

#include "NFA_generator.h"

NFA_generator::NFA_generator(vector<vector<string> > expression,
		vector<string> keywords, vector<string> punct) {
	this->regular_expressions = expression;
	this->keywords = keywords;
	this->punctuation = punct;
//	cout << "====================\n";
//	for (int i = 0; i < regular_expressions.size(); i++) {
//		for (int j = 0; j < regular_expressions[i].size(); j++)
//			cout << regular_expressions[i][j] << ",";
//		cout << endl;
//	}
//	cout << "====================\n";
//
	operations_priority["*"] = 100;
	operations_priority["^"] = 50;
	operations_priority["|"] = 10;
}

automata NFA_generator::final_NFA() {
	keywords_automatas(keywords);
	punctuation_automatas(punctuation);
	expression_automata_generator();

//	for (int k = 0; k < all_automata.size(); k++) {
//		automata final = all_automata[k];
//		cout << "start state id : " << final.get_start_state()->id << endl;
//		cout << "end state id : " << final.get_end_state()->id << endl;
//
//		for (int i = 0; i < final.graph.size(); i++) {
//			//		cout << final.graph[i]->id << endl;
//			state *curr = final.graph[i];
//			if (curr->get_acceptence())
//				cout << "this is acceptence state " << curr->id << " "
//						<< curr->get_token_type() << endl;
//			multimap<char, state*> n = curr->get_neighbors();
//			multimap<char, state*>::iterator it = n.begin();
//			cout << curr->id << endl;
//			for (it; it != n.end(); it++) {
//				cout << it->first << " " << it->second->id << " ";
//			}
//			cout << endl;
//		}
//		cout << "============\n";
//	}
	automata result;
	result.graph.pop_back();
	for (int i = 0; i < all_automata.size(); i++) {
		for (int j = 0; j < all_automata[i].graph.size(); j++) {
			result.add_state(all_automata[i].graph[j]);
		}
		result.get_start_state()->connect('#',
				all_automata[i].get_start_state());
	}
	return result;
}

void NFA_generator::keywords_automatas(vector<string> keywords) {
	for (int i = 0; i < keywords.size(); i++) {
		automata x;
//		if (keywords[i] == "#")
//			cout << "in keywrds" << endl;
		x = string_to_automata(keywords[i]);
		x.get_end_state()->set_acceptence(true);
		x.get_end_state()->set_token_type(keywords[i]);
		all_automata.push_back(x);
	}
}

void NFA_generator::punctuation_automatas(vector<string> bunc) {
	for (int i = 0; i < bunc.size(); i++) {
		automata x;
//		if (bunc[i] == "#")
//			cout << "in punc" << endl;
		x = string_to_automata(bunc[i]);
		x.get_end_state()->set_acceptence(true);
		x.get_end_state()->set_token_type(bunc[i]);
		all_automata.push_back(x);

	}
}

automata NFA_generator::string_to_automata(string str) {
//	cout << str[0] << "6" << endl;
	automata x;
	x.graph.pop_back();
	state *last = x.get_start_state();
	for (int j = 0; j < str.size(); j++) {
//		cout << str[j] << endl;
		if (str[j] == '\\')
			continue;
//		if (str[j] == '#')
//			cout << "trip :\\ \"" << str << endl;
		alphabet.insert(str[j]);  // creating alphabet characters
		state *s = new state();
		int s_id = x.add_state(s);
		last->connect(str[j], s);
		last = s;
	}
	x.set_end_state(last);
//	last->connect('#', x.get_end_state());
//	x.get_end_state()->set_acceptence(true);
//	x.get_end_state()->set_token_type(str);
	return x;
}

void NFA_generator::expression_automata_generator() {
	for (int i = 0; i < regular_expressions.size(); i++) {
		vector<string> curr = regular_expressions[i];
		stack<automata> s;
		for (int j = 2; j < curr.size(); j++) {
			if (curr[j] == "*") {
				automata a = s.top();
				s.pop();
				automata A = zero_or_more(a);
				s.push(A);
			} else if (curr[j] == "^") {
				automata b = s.top();
				s.pop();
				automata a = s.top();
				s.pop();
				automata AB = concatenate(a, b);
				s.push(AB);
			} else if (curr[j] == "|") {
				automata b = s.top();
				s.pop();
				automata a = s.top();
				s.pop();
				automata AB = Or(a, b);
				s.push(AB);
			} else {
				if (curr[j] == "#")
					cout << "in punc" << endl;
				automata x = string_to_automata(curr[j]);
				s.push(x);
			}
		}
		all_automata.push_back(s.top());
		s.top().get_end_state()->set_acceptence(true);
		s.top().get_end_state()->set_token_type(curr[0]);

	}
}

automata NFA_generator::zero_or_more(automata a) {
	automata ans;
	ans.graph.pop_back();
	ans.graph.pop_back();
	for (int i = 0; i < a.graph.size(); i++) {
		ans.add_state(a.graph[i]);
	}
	ans.set_start_state(a.get_start_state());
	ans.set_end_state(a.get_end_state());
	ans.get_start_state()->connect('#', ans.get_end_state());
	ans.get_end_state()->connect('#', ans.get_start_state());
	return ans;
}

automata NFA_generator::concatenate(automata a, automata b) {
	automata ans;
	ans.graph.pop_back();
	ans.graph.pop_back();
	for (int i = 0; i < a.graph.size(); i++) {
		ans.add_state(a.graph[i]);
	}
	for (int i = 0; i < b.graph.size(); i++) {
		ans.add_state(b.graph[i]);
	}
	ans.set_start_state(a.get_start_state());
	ans.set_end_state(b.get_end_state());
	a.get_end_state()->connect('#',b.get_start_state());
//	ans.get_start_state()->connect('#', a.get_start_state());
//	a.get_end_state()->connect('#', b.get_start_state());
//	b.get_end_state()->connect('#', ans.get_end_state());
	return ans;
}
// the most expensive operation
automata NFA_generator::Or(automata a, automata b) {
	automata ans;
	ans.graph.pop_back();
	ans.graph.pop_back();
	for (int i = 0; i < a.graph.size(); i++) {
		ans.add_state(a.graph[i]);
	}
	for (int i = 0; i < b.graph.size(); i++) {
		ans.add_state(b.graph[i]);
	}
	ans.set_start_state(a.get_start_state());
	ans.set_end_state(a.get_end_state());
	ans.get_start_state()->connect('#', b.get_start_state());
	b.get_end_state()->connect('#', ans.get_end_state());
	return ans;
}
