#include <map>
#include <vector>
#include <string>
using namespace std;

class state {
public :
	state();
	int id ;
	void connect (char x , state* dest) ; // connecting this node to dest node
	void set_acceptence(bool is_acceptence);
	bool get_acceptence ();
	multimap<char,state*> get_neighbors ();
	void set_token_type(string tk);
	string get_token_type() ;
	multimap<char, state*> next;
	// this -- x --> dest ,
private:
	bool is_acceptence = false;
	string token_type = "" ; // if it is acceptence state , what is accepts , keyword , id ,or what
	                         // make sure that this parameter is empty string when is_acceptence = false :D
};

