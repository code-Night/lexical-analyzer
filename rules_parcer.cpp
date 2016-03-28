/*
 * rules_parcer.cpp
 *
 *  Created on: Mar 24, 2016
 *      Author: ali
 */

#include "rules_parcer.h"

rules_parcer::rules_parcer() {
	freopen("rules.txt", "r", stdin);
	reserved_characters.insert("=");
	reserved_characters.insert("-");
	reserved_characters.insert("|");
	reserved_characters.insert(" ");
	reserved_characters.insert("(");
	reserved_characters.insert(")");
	reserved_characters.insert("*");
	reserved_characters.insert("+");
	reserved_characters.insert(":");
	reserved_characters.insert("^");
	op_priority["*"] = 10;
	op_priority["+"] = 9;
	op_priority["^"] = 8;
	op_priority["-"] = 7;
	op_priority["|"] = 5;
	op_priority["("] = 0;
}

void rules_parcer::parce() {
	string rule = "";
	while (getline(cin, rule)) {
		string rule_name = "";
//		cout << rule << endl;
		if (rule[0] != '{' && rule[0] != '[') { // not keyword and not puncutuation
			vector<string> broken_rule = break_rule(rule);
			broken_rule = insert_concate(broken_rule);
			broken_rule = replace_plus(broken_rule);
			broken_rule = replace_minus(broken_rule);
			broken_rule = to_postfix(broken_rule);
//			broken_rule = cleanUP(broken_rule);
			if (broken_rule[1] == ":") {
				regular_expressions.push_back(broken_rule);
			} else if (broken_rule[1] == "=") {
				def_map[broken_rule[0]] = broken_rule;
				regular_definitions.push_back(broken_rule);
			}
		} else if (rule[0] == '{') { // breaking keywords ;
			vector<string> kw = parcing_keywords(rule);
			keywords.insert(keywords.end(), kw.begin(), kw.end());
		} else if (rule[0] == '[') {
			vector<string> pp = parcing_punctuation(rule);
			punctuation.insert(punctuation.end(), pp.begin(), pp.end());
		}
	}

	//    replace every definition with it's value
	//loop on definitions
	for(int i=0 ; i<regular_definitions.size() ; i++){
		vector <string> t = subsitiue_for_definition(regular_definitions[i]);
		def_map[regular_definitions[i][0]] = t ;
	}
	for(int i=0 ; i<regular_expressions.size() ; i++){
		vector<string> t= subsitiue_for_definition(regular_expressions[i]);
		regular_expressions[i] = t ;
	}

}

vector<string> rules_parcer::subsitiue_for_definition(vector<string> victim) {
	vector<string> x;
	x.push_back(victim[0]);
	x.push_back(victim[1]);
	for (int j = 2; j < victim.size(); j++) {
		if (def_map.find(victim[j]) != def_map.end()) {
//			x.push_back("(");
			x.insert(x.end(), def_map[victim[j]].begin() + 2,
					def_map[victim[j]].end());
//			x.push_back(")");

		} else {
			x.push_back(victim[j]);
		}

	}
	return x ;
}

vector<string> rules_parcer::parcing_keywords(string rule) {
	vector<string> keywords;
	string kw = "";
	for (int i = 1; i < rule.size() - 1; i++) {
		if (rule[i] == ' ') {
			if (kw == "")
				continue;
			keywords.push_back(kw);
			kw = "";
		} else {
			kw += rule[i];
		}
	}
	if (kw != "")
		keywords.push_back(kw);
	return keywords;
}
vector<string> rules_parcer::parcing_punctuation(string rule) {
	vector<string> punctuation;
	string kw = "";
	for (int i = 1; i < rule.size() - 1; i++) {
		if (rule[i] == '\\') {
			kw += rule[i + 1];
			i++;
		} else if (rule[i] == ' ') {
			if (kw == "")
				continue;
			punctuation.push_back(kw);
			kw = "";
		} else {
			kw += rule[i];
		}
	}
	if (kw != "")
		punctuation.push_back(kw);
	return punctuation;
}
vector<string> rules_parcer::break_rule(string rule) {
	vector<string> k;
	string token = "";
	int i = 0;
	while (i < (int) rule.size()) {
		string Char = "";
		Char += rule[i];
		if (rule[i] == '\\') {
			if (rule[i + 1] == 'L')
				token += '#';
			else {
				token += rule[i];
				token += rule[i + 1];
			}
			i++;
		} else if (reserved_characters.find(Char)
				== reserved_characters.end()) { //not a special char ;
			token += rule[i];
		} else {
			if (token != "" && token != " ") {
				k.push_back(token);
			}
			token = "";
			token += rule[i];
			if (token != "" && token != " ") {
				k.push_back(token);
			}
			token = "";
		}
		i++;
	}
	if (token != "" && token != " ") {
		k.push_back(token);
	}
//	k = cleanUP(k);
	return k;
}

vector<string> rules_parcer::insert_concate(vector<string> x) {
	vector<string> ans;
	ans.push_back(x[0]);
	ans.push_back(x[1]);
	for (int i = 2; i < x.size(); i++) {
		if (x[i] == "(") {
			if (ans.back() == "*" || ans.back() == "+"
					|| reserved_characters.find(ans.back())
							== reserved_characters.end()) {
				ans.push_back("^");

			}

		} else if (reserved_characters.find(x[i])
				== reserved_characters.end()) { // current is id
			if (reserved_characters.find(ans.back())
					== reserved_characters.end() || ans.back() == ")"
					|| ans.back() == "*" || ans.back() == "+") {
				ans.push_back("^");

			}

		}
		ans.push_back(x[i]);
	}
	return ans;
}

vector<string> rules_parcer::to_postfix(vector<string> x) {
	vector<string> ans;
	stack<string> pf;
	ans.push_back(x[0]);
	ans.push_back(x[1]);
	for (int i = 2; i < x.size(); i++) {
		if (reserved_characters.find(x[i]) == reserved_characters.end()) {
			ans.push_back(x[i]);
		} else {
			if (x[i] == "(") {
				pf.push(x[i]);
			} else if (x[i] == ")") {
				while (!pf.empty() && pf.top() != "(") {
					ans.push_back(pf.top());
					pf.pop();
				}
				pf.pop();
			} else {
				while (!pf.empty() && op_priority[x[i]] <= op_priority[pf.top()]) {
					ans.push_back(pf.top());
					pf.pop();

				}
				pf.push(x[i]);
			}
		}
	}
	while (!pf.empty()) {
		ans.push_back(pf.top());
		pf.pop();
	}
	return ans;
}

vector<vector<string> > rules_parcer::get_regular_definitions() {
	return regular_definitions;
}
vector<vector<string> > rules_parcer::get_regular_expressions() {
	return regular_expressions;
}
vector<string> rules_parcer::get_keywords() {
	return keywords;
}
vector<string> rules_parcer::get_punctuation() {
	return punctuation;
}

vector<string> rules_parcer::cleanUP(vector<string> x) {
	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < x[i].size(); j++) {
			if (x[i][j] == '\\') {
				x[i].erase(x[i].begin() + j);
			}
		}
	}
	return x;
}

vector<string> rules_parcer::replace_plus(vector<string> rule) {
//	cout << "replacing plus\n";
	for (int i = 0; i < rule.size(); i++) {
		if (rule[i] == "+") {
//			cout << "loop\n";
			string lexem = rule[i - 1];
			vector<string> rep;
			rule.erase(rule.begin() + i);
			rule.erase(rule.begin() + (i - 1));
			rep.push_back("(");
			rep.push_back(lexem);
			rep.push_back("^");
			rep.push_back(lexem);
			rep.push_back("*");
			rep.push_back(")");
			rule.insert(rule.begin() + i - 1, rep.begin(), rep.end());

		}
	}
	return rule;
}

vector<string> rules_parcer::replace_minus(vector<string> x) {
	vector<string> ans;
	int last_delete_index = -1;
	for (int i = 0; i < x.size() - 1; i++) {
		if (x[i + 1] == "-") {
			last_delete_index = i;
			ans.push_back("(");
			for (int j = (int) (x[i][0]); j <= (int) (x[i + 2][0]); j++) {
				string s = "";
				s += (char) (j);
//				cout << s ;
				ans.push_back(s);
				ans.push_back("|");
			}
			ans.pop_back();
			ans.push_back(")");
//			x.erase(x.begin() + i, x.begin() + i + 3);
			i += 2;
		} else {
			ans.push_back(x[i]);
//			x.erase(x.begin() + i,x.begin()+i+1);
		}

	}
	if (x.size() - 1 - last_delete_index > 2)
		ans.push_back(x.back());
	return ans;
}
