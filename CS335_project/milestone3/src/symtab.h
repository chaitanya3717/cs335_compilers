#include <iostream>
#include <vector>
#include<fstream>
#include<unordered_map>
#include<map>
#include<stack>
#include<string>
using namespace std;

bool is_error = 0;

typedef struct ent{
	string type="NULL";
}ent;

typedef unordered_map <string,ent> stable;	

stable* n1_stable(){
	stable* sym_pt = new stable;
	return sym_pt;
}



typedef struct table{
	stable* stab;
	table *par;
	int t_type=0;
}table;

table * n1_table(stable *map1,table *par1){	
	table *t1= (table*)malloc(sizeof(table));
	t1->stab = map1;
	t1->par = par1;
	t1->t_type = 0;
	return t1;
}

table * n1_root_table(stable *map1){
	table *t1= (table*)malloc(sizeof(table));
	t1->stab = map1;
	t1->par = NULL;
	t1->t_type = 1;
	return t1;
}

ent * get_sentry(string type){
	ent *s1= (ent*)malloc(sizeof(ent));
	return s1;
}

bool find(string str1,stable *stab1){
	int flag = 0;
	
	stable &stab = *stab1;
	unordered_map<string, ent>:: iterator itr;
	if(stab.size()==0){
		flag=0;
	}
	else{
	for(itr=stab.begin();itr!=stab.end();itr++){
		if(itr->first==str1){
			flag = 1;
			break;
		}
	}
	}
	return flag;
}

bool check(string str,table * t1){
	int flag = 0;
	table * temp1 = t1;
	while(temp1->t_type!=1){
		if(find(str,temp1->stab)==1){
			flag=1;
			break;
		}
		temp1=temp1->par;		
	}
	return flag;	
}

void insert(string s,table *t,string temp){
	stable a;
	stable *sm = &a;
	if(!check(s,t)){
		(*t->stab)[s].type = temp;
	}
	else{
		cout << "Error: variable " << s << " already declared.\n";
		is_error = 1;
	}
}
