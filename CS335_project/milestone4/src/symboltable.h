#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

typedef struct inf{
	public:
		bool flag = false;	
		int next = INT_MAX;	 
}inf;


extern vector < unordered_map <string,inf*>> symboltable;



extern unordered_map <string,string> address;
extern unordered_map <string,string> regis;	
extern unordered_map <int,int> temp;

extern list <string> is_empt;

extern unordered_map<string, inf*>:: iterator itr1;
extern unordered_map<string, string>:: iterator itr2;

