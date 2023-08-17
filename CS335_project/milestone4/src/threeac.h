#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <list>
#include <vector>
#include "symboltable.h"
using namespace std;

class tac{			
	
	public:
	int lineno = 1;
	string type = "";	
	string in1 = "";				
	string in2 = "";			
	string out = "";						
		
	int target  = -1;
	string op = "";			
	
	void get_inf(){
		cout << "line = " << lineno << " type = " << type << " in1 = " << in1 << " in2 = " << in2 << " out = " << out << " target = " << target << " op = " << op << endl; 
	}
};

extern vector <tac> three_ac;
extern vector <int> headers;		
extern vector <int> label_headers;
extern int block_num;
extern vector <int> open_block;
extern vector <int> close_block;

extern vector < vector <tuple <string,bool,int> > > changes;

void display_3ac();

void commit_changes(vector < unordered_map <string,inf*>> &symboltable);

void display_symtab(vector < unordered_map <string,inf*>> &symboltable,int block_num);

void make_addr(vector < unordered_map <string,inf*>> &symboltable,int block_num);

void display_addr();

string find_loc(string var_name);

void change_loc(string var_name,string reg_name);

void change_reg(string reg_name,string var_name);

string find_reg(string var, tac instr,vector < unordered_map <string,inf*>> &symboltable);		

void update_symboltable(vector < unordered_map <string,inf*>> &symboltable,vector < vector <tuple <string,bool,int> > > changes,int lineno);

bool check_reg(string str);

bool is_labelleader(int x);

void add_empt(string reg);

void res_block();

void init_block();

extern int ret;

void generate(tac instr,string &blockcode);


bool check_int(string s);



