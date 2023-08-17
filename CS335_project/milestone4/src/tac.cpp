#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <list>
#include <vector>
#include "threeac.h"
using namespace std;

vector <tac> three_ac;		
int line_num;
	
vector <int> headers;	
vector <int> label_headers;

int block_num;
vector <int> open_block;
vector <int> close_block;

vector < vector <tuple <string,bool,int> > > changes;	

unordered_map<string, inf*>:: iterator itr1;
unordered_map<string, string>:: iterator itr2;

unordered_map <string,string> address;			
unordered_map <string,string> regis;	
unordered_map <int,int> temp;
vector < unordered_map <string,inf*>> symboltable;				

list <string> is_empt = {"$a1","$a2","$a3","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$t8","$t9","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};

int ret = 0;

string block_str = "";

void add_empt(string str){
	is_empt.push_back(str);
}

bool is_labelleader(int a){
	bool flag = 0;
	for(int i=0;i<label_headers.size();i++){
		if(a==label_headers[i]){
			flag= 1;
			break;
		}	
	}
	return flag;
}

void commit_changes(vector < unordered_map <string,inf*>> &symboltable){		
	
	for(int i=0;i<block_num;i++){			 
		for(int j=open_block[i];j<=close_block[i];j++){
			if(three_ac[j-1].in1!=""){
				if(check_int(three_ac[j-1].in1)!=1){
					string var_name = three_ac[j-1].in1;
					if(symboltable[i].find(var_name)==symboltable[i].end()){
						inf * info = new inf();
						symboltable[i].insert(make_pair(var_name, info));						
					}
				}	
			}
			if(three_ac[j-1].in2!=""){
				if(check_int(three_ac[j-1].in2)!=1){
					string var_name = three_ac[j-1].in2;
					if(symboltable[i].find(var_name)==symboltable[i].end()){
						inf * info = new inf();
						symboltable[i].insert(make_pair(var_name, info));						
					}
				}	
			}
			if(three_ac[j-1].out!=""){
				if(check_int(three_ac[j-1].out)!=1){
					string var_name = three_ac[j-1].out;
					if(symboltable[i].find(var_name)==symboltable[i].end()){
						inf * info = new inf();
						symboltable[i].insert(make_pair(var_name, info));				
					}
				}	
			}
		}
	
	}
}

void update_next( unordered_map <string,inf*> &symboltable,int open_block,int close_block){
	
	for(int i=close_block;i>=open_block;i--){	
		string str1 = three_ac[i-1].in1;
		string str2 = three_ac[i-1].in2;
		string str3 = three_ac[i-1].out;
		
		if(str3!="" && check_int(str3)!=1){	
			changes[i-1].push_back(make_tuple(str3,symboltable[str3]->flag,symboltable[str3]->next));
			symboltable[str3]->flag = false;
			symboltable[str3]->next = INT_MAX;
		}
		if(str1!="" && check_int(str1)!=1){
			changes[i-1].push_back(make_tuple(str1,symboltable[str1]->flag,symboltable[str1]->next));
			symboltable[str1]->flag = true;
			symboltable[str1]->next = i;
		}
		if(str2!="" && check_int(str2)!=1){
			changes[i-1].push_back(make_tuple(str2,symboltable[str2]->flag,symboltable[str2]->next));
			symboltable[str2]->flag = true;
			symboltable[str2]->next = i;
		}
	}
}

void update_symboltable(vector < unordered_map <string,inf*>> &symboltable,vector < vector <tuple <string,bool,int> > > changes,int lineno){
	int block_no = temp[lineno];	
	for(int i=0;i<changes[lineno-1].size();i++){
		string var = get<0>(changes[lineno-1][i]);
		bool flag_new = get<1>(changes[lineno-1][i]);
		int next_new = get<2>(changes[lineno-1][i]);
		symboltable[block_no][var]->flag = flag_new;
		symboltable[block_no][var]->next = next_new; 
	}
	
}

void display_3ac(){
	for(int i=0;i<three_ac.size();i++){
		three_ac[i].get_inf();
	}
}

void display_symtab(vector < unordered_map <string,inf*>> &symboltable,int block_num){				
	for(int i=0;i<block_num;i++){
		cout << "----------Block " << i << "---------------" << endl;
		for (itr1 = symboltable[i].begin(); itr1 != symboltable[i].end(); itr1++)
	    	{
			cout << itr1->first << "\t" << itr1->second->flag << "\t" << itr1->second->next << endl;
	     	}
     	}
}

void make_addr(vector < unordered_map <string,inf*>> &symboltable,int block_num){
	for(int i=0;i<block_num;i++){
		for (itr1 = symboltable[i].begin(); itr1 != symboltable[i].end(); itr1++)
		    	{
				if(address.find(itr1->first)==address.end()){
					address.insert(make_pair(itr1->first,"mem"));
				}	
		     	}
	}
}

void display_addr(){
	for (itr2 = address.begin(); itr2 != address.end(); itr2++)
	    	{
			cout << itr2->first << "\t" << itr2->second << endl;
	     	}
}

string find_loc(string var_name){
	return address[var_name];
} 

void change_loc(string var_name,string reg_name){
	address[var_name] = reg_name;
} 

void change_reg(string reg_name,string var_name){
	regis[reg_name] = var_name;
}

bool check_reg(string str){
	if(str[0]=='$')return true;	
	else return false;
}

string find_reg(string var,tac instr,vector < unordered_map <string,inf*>> &symboltable){			
	string reg;
	string a = instr.in1;		
	string c = instr.out;	
	int block_no = temp[instr.lineno];
	if(var==c){
		if(check_int(a)==0 && check_reg(find_loc(a))==true && symboltable[block_no][a]->next==INT_MAX ){
			reg = find_loc(a);
			block_str = block_str + "sw\t" + reg + ", " + a + "\n";
			change_loc(a,"mem");
		}
		else if(is_empt.size()>0){
			reg = is_empt.front();
			is_empt.pop_front();
		}
		else{
			int max_next = 0;
			string var_maxnext = "";
			for(itr1 = symboltable[block_no].begin(); itr1 != symboltable[block_no].end(); itr1++){
				if(check_reg(address[itr1->first])==true){
					if(itr1->second->next >= max_next){
						max_next = itr1->second->next;
						var_maxnext = itr1->first;
					}
				}
			}
			reg = find_loc(var_maxnext);
			block_str = block_str + "sw\t" + reg + ", " + var_maxnext + "\n";
			change_loc(var_maxnext,"mem");
		}
	}
		
	else{						
		if(is_empt.size()>0){
			reg = is_empt.front();
			is_empt.pop_front();
		}
		else{	
			int max_next = 0;
			string var_maxnext = "";
			for(itr1 = symboltable[block_no].begin(); itr1 != symboltable[block_no].end(); itr1++){
				if(var!= itr1->first && check_reg(address[itr1->first])==true){
					if(itr1->second->next >= max_next){
						max_next = itr1->second->next;
						var_maxnext = itr1->first;
					}
				}
			}	
			reg = find_loc(var_maxnext);
			block_str = block_str + "sw\t" + reg + ", " + var_maxnext + "\n";
			change_loc(var_maxnext,"mem");
		}
	}
	return reg;
}

void res_block(){
	for (itr2 = address.begin(); itr2 != address.end(); itr2++)
	    	{
			if(check_reg(itr2->second)==1){
			string str1= itr2->second;	
			string str2 = itr2->first;
			block_str = block_str + "sw\t" + str1 + ", " +  str2 + "\n";
			add_empt(str1);
			change_loc(str2,"mem");
			change_reg(str1,"");		
		}
	}
}

void init_block(){
	for (itr2 = address.begin(); itr2 != address.end(); itr2++)
	    	{
			if(check_reg(itr2->second)==1){
			string str1 = itr2->second;	
			string str2 = itr2->first;
			add_empt(str1);
			change_loc(str2,"mem");
			change_reg(str1,"");		
		}
	}
}

int main(int argc, char **argv){

	headers.push_back(1);
	string line;
	ifstream mycode(argv[1]);
	int flag = 0;	
	
	while(getline(mycode,line)){
		istringstream str(line);
		string token;
		int i = 1;
		
		tac output;
		while(getline(str,token,',')){
			
			
			if(i==1){			
				output.lineno = stoi(token);
			}
			else if(i==2){				
				if(token=="="){
					output.type = "assign1";					
				}	
				else if(token=="+"||token=="-"||token=="*"||token=="/"||token=="&"||token=="|"||token=="^"||token=="%"){	
					output.type = "assign2";
					output.op = token;
				}
				else if(token=="ifgoto"){
					output.type = "ifgoto";
				}
				else if(token=="goto"){
					output.type = "goto";
				}
				else if(token=="call"){
					output.type = "call";
				}
				else if(token=="label"){
					output.type = "label";
				}
				else if(token=="exit"){					
					output.type = "return1";					
				}
				else if(token=="return"){
					output.type = "return2";
				}
				else if(token=="print"){
					output.type = "print";
				}
		
				else if(token=="getreturn"){
					output.type = "getreturn";
				}
			
			}
			else{
				if(output.type == "assign1"){						
					if(i==3)output.out = token;
					if(i==4)output.in1 = token;
				}
				else if(output.type == "assign2"){
					if(i==3)output.out = token;
					if(i==4)output.in1 = token;
					if(i==5)output.in2 = token;
				}
				else if(output.type == "ifgoto"){
					if(i==3)output.op = token;
					if(i==4)output.in1 = token;
					if(i==5)output.in2 = token;
					if(i==6)output.target = stoi(token);
				}
				else if(output.type == "goto"){
					if(i==3)output.target = stoi(token);
				}
		
				else if(output.type == "call"){
					if(i==3)output.op = token;
					
				}
				else if(output.type == "label"){
					if(i==3)output.op = token;
				}
				else if(output.type == "ret"){
					if(i==3)output.in1 = token;
				}
				else if(output.type == "print"){
					if(i==3)output.in1 = token;
				}
				else if(output.type == "getreturn"){
					if(i==3)output.in1 = token;
				}
			}
			i++;
		}
		if(flag==1){
			headers.push_back(output.lineno);
			flag = 0;
		}
		if(output.type == "ifgoto" || output.type == "goto" || output.type == "label" || output.type == "call"){	//checl for label is block or not??
			if(output.type == "ifgoto" || output.type == "goto"){
				headers.push_back(output.target);
				flag = 1;
			}
			else if(output.type == "label"){
				label_headers.push_back(output.lineno);
				headers.push_back(output.lineno);	
			}
			else{
				headers.push_back(output.lineno);
			}	
		}	
		three_ac.push_back(output);
			
	}
	
	line_num = three_ac.size();
	sort(headers.begin(),headers.end());			
	headers.erase( unique( headers.begin(), headers.end() ), headers.end() );
	
	
	block_num = headers.size();
	open_block = headers;
	for(int i=0;i<headers.size()-1;i++){
		close_block.push_back(headers[i+1]-1);
	}
	close_block.push_back(line_num);

	for(int i=0;i<block_num;i++){
		for(int j=open_block[i];j<=close_block[i];j++){
			temp.insert(make_pair(j,i));
		}
	}

	symboltable.resize(block_num);
	
	commit_changes(symboltable);
	make_addr(symboltable,block_num);
     	
     	changes.resize(line_num);
     
     	for(int i=0;i<block_num;i++){
     		update_next(symboltable[i],open_block[i],close_block[i]);
     	}
	cout << ".data\n";
	for (itr2 = address.begin(); itr2 != address.end(); itr2++)
	{
		cout << itr2->first << ":\t.word\t0" << endl;
	}
	cout << ".text\nmain:\n";
	
	
	for(int i=0;i<block_num;i++){
		init_block();	
		int flag = 0;
		if(is_labelleader(headers[i])!=true){
			block_str = "l" + to_string(headers[i]) + ":\n";
		}
		else{
			block_str = "";
		}
		for(int index = open_block[i];index<=close_block[i];index++){
			if(three_ac[index-1].type=="ifgoto"||three_ac[index-1].type=="goto"||three_ac[index-1].type=="return1"){
				res_block();
				flag = 1;
			}
			generate(three_ac[index-1],block_str);
			update_symboltable(symboltable,changes,index);
		}
		
		if(flag==0){
			res_block();
		}	
		cout << block_str;
		
	}

	return 0;
}
